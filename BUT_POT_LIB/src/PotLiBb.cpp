#include "BUTPOTLIB.h"
#include "PotLiBb.h"

#define degisim_max 150

Potansiyometre::Potansiyometre()
{
    ogren.pot = this;
    ayarla.pot = this;
    g_mss = 10;
    afk_sure_ms = 0;
    _pin = A0;
    _cozunurluk_deger = 1023; // 1
    _adc_mindeger = 0;
    _adc_maxdeger = 1023;
    _min = 0;                      // 1
    _max = 1023;                   // 1
    _okuma_tolerans = 5;           // 1
    afk_dogrulama_ms = 20;         // 1
    _oto_maxdeger_kalibre = false; // 1
}

void Potansiyometre::kur(int16_t pin, int16_t minn, int16_t maxx)
{
    _pin = pin;
    _min = minn;
    _max = maxx;
    gecen_zamann = millis();
    if (_oto_maxdeger_kalibre)
        for (byte k = 0; k < 3; k++)
            oku();
}

int16_t Potansiyometre::oku()
{
    uint16_t deger = analogRead(_pin);
    if (abs(_son_saf_deger - deger) > _okuma_tolerans) // değişiklik var mı?
    {
        if (deger > _son_saf_deger)
        {
            afk_sure_ms = 0;
            durum = ARTTI;
            _degisim_miktar = deger - _son_saf_deger;
            _son_saf_deger = deger;
            hiz_kontrol(_degisim_miktar, max_deger_yakala(_degisim_miktar, degisim_max));
            return _son_saf_deger;
        }
        else
        {
            afk_sure_ms = 0;
            durum = AZALDI;
            _degisim_miktar = _son_saf_deger - deger;
            _son_saf_deger = deger;
            hiz_kontrol(_degisim_miktar, max_deger_yakala(_degisim_miktar, degisim_max));
            return _son_saf_deger;
        }
    }
    else if (millis() - gecen_zamann >= g_mss) // degisiklik yapılmazsa afk
    {
        if (durum != SABIT && afk_sure_ms * g_mss > afk_dogrulama_ms)
        {
            _degisim_miktar = 0;
            durum = SABIT;
            degisim = YOK;
        }
        gecen_zamann = millis();
        afk_sure_ms++;
        return _son_saf_deger;
    }
    return _son_saf_deger;
}
int16_t Potansiyometre::oku_map(int16_t minn, int16_t maxx)
{
    uint16_t deger = oku();
    if (abs(minn - maxx) == 0)
        return deger;
    else
    {
        _adc_maxdeger = (_oto_maxdeger_kalibre) ? max_deger_yakala(deger) : _cozunurluk_deger;
        _min = minn;
        _max = maxx;
        _son_deger = map(deger, _adc_mindeger, _adc_maxdeger, _min, _max + 1);
        return _son_deger;
    }
}

#if defined(SERI_TEST) && SERI_TEST

void Potansiyometre::test(bool izinn)
{
    if (!izinn)
        return;

    int16_t deger = oku_map(0, 180);
    uint16_t fark = _degisim_miktar;

    // === Sabit dizilerle sabit metinleri yöneten yapı ===
    const char *durum_ =
        ogren.artti_mi() ? "ARTTI" : ogren.azaldi_mi() ? "AZALDI"
                                 : ogren.sabit_mi()    ? "SABIT "
                                                       : "HATA  ";

    const char *degisim_ =
        ogren.hizli_mi_degisti() ? "HIZLI " : ogren.normal_mi_degisti() ? "NORMAL"
                                          : ogren.yavas_mi_degisti()    ? "YAVAS "
                                                                        : "SIFIR ";

    uint16_t DT1 = max_deger_yakala(_degisim_miktar, degisim_max);
    uint8_t degisim_yuzde = ogren.degisim_hizi_yuzde(max_deger_yakala(_degisim_miktar, degisim_max));
    int16_t degisim_miktar = ogren.degisim_miktari();
    uint32_t afk_ms = ogren.afk_mi() ? ogren.afk_kalinan_ms() : 0;

    // === ANSI: sadece imleci sol üst köşeye al ===
    Serial.print("\033[H");

    // === Başlık (sabit 2 satır) ===
    Serial.println(F(" DEGER  DURUM  HIZ    DT1    %HIZ   MIKTAR    AFK(ms)   FARK"));
    Serial.println(F("------------------------------------------------------------"));

    // === Veriler hizalanmış yazılır ===
    char satir[120];
    snprintf(satir, sizeof(satir),
             " %5d  %-6s %-6s %5u   %4u   %6d   %8lu   %5u",
             deger, durum_, degisim_, DT1, degisim_yuzde,
             degisim_miktar, afk_ms, fark);

    Serial.print(satir);
}
#endif
