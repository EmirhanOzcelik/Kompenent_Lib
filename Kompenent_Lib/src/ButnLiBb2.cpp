#include "ButnLiBb.h"

bool Buton::ogren_::tiklandi_mi()
{
    return ogren_btn->durum == TIKLANDI;
}
bool Buton::ogren_::basili_mi()
{
    return ogren_btn->durum == BASILI;
}
bool Buton::ogren_::serbest_mi()
{
    return ogren_btn->durum == SERBEST;
}
bool Buton::ogren_::birakildi_mi()
{
    return ogren_btn->degisim == TIKLANDIDAN_SERBESTE || ogren_btn->degisim == BASILIDAN_SERBESTE;
}

bool Buton::ogren_::uzun_basma_tamamlandi_mi()
{
    return ogren_btn->degisim == BASILIDAN_SERBESTE;
}
////////////////////////////////////////////////////////////
void Buton::ayaR::debounce(uint16_t dbc)
{
    ___dbc = dbc;
}
void Buton::ayaR::min_basili_tutma_ms(uint16_t max_ms)
{
    ___min_basili_tutus_ms = max_ms;
}
uint32_t Buton::ogren_::sure_::basili_tutulan_ms()
{
    return sure_ogrn->ogren_btn->basili_tutus_ms;
}
uint16_t Buton::ogren_::sure_::basili_tutulan_sn()
{
    return sure_ogrn->ogren_btn->basili_tutus_ms / 1000;
}
uint8_t Buton::ogren_::sure_::basili_tutulan_dk()
{
    return basili_tutulan_sn() / 60;
}
////////////////////////////////////////////////////////////
void Buton::afk_reset()
{
    _afk_sayac = 0;
    _afk_ms = 0;
    _afk_sn = 0;
    _afk_dk = 0;
    _afk_saat = 0;
}

void Buton::afk_sure_hesap()
{
    _afk_ms += _afk_sayac * g_mss;
    if (_afk_sayac * g_mss >= 1000)
    {
        _afk_sayac = 0;
        _afk_sn++;
        if (_afk_sn >= 60)
        {
            _afk_sn = 0;
            _afk_dk++;
            if (_afk_dk >= 60)
            {
                _afk_dk = 0;
                _afk_saat++;
            }
        }
    }
}
uint32_t Buton::ogren_::sure_::afk_sure_ms()
{
    return sure_ogrn->ogren_btn->_afk_ms;
}
uint32_t Buton::ogren_::sure_::afk_sure_sn()
{
    return sure_ogrn->ogren_btn->_afk_sn;
}
uint32_t Buton::ogren_::sure_::afk_sure_dk()
{
    return sure_ogrn->ogren_btn->_afk_dk;
}
uint16_t Buton::ogren_::sure_::afk_sure_saat()
{
    return sure_ogrn->ogren_btn->_afk_saat;
}
///////////////////////////////////////////////////////////////

#if defined(SERI_TEST) && SERI_TEST
void Buton::test(bool izin)
{
    if (!izin)
        return;

    // Buton verilerini oku
    oku();

    const char *durum_str =
        (durum == SERBEST) ? "SERBEST" : (durum == TIKLANDI) ? "TIKLANDI"
                                     : (durum == BASILI)     ? "BASILI "
                                                             : "HATA  ";

    const char *degisim_str =
        (degisim == DEGISIM_YOK) ? "YOK   " : (degisim == TIKLANDIDAN_SERBESTE) ? "TK->SR"
                                          : (degisim == SERBESTTEN_TIKLANDIYA)  ? "SR->TK"
                                          : (degisim == TIKLANDIDAN_BASILIYA)   ? "TK->BS"
                                          : (degisim == BASILIDAN_SERBESTE)     ? "BS->SR"
                                                                                : "?????";

    // Verileri al
    uint32_t basili_ms = ogren.sure.basili_tutulan_ms();
    uint16_t basili_sn = ogren.sure.basili_tutulan_sn();
    uint8_t basili_dk = ogren.sure.basili_tutulan_dk();

    uint32_t afk_ms = ogren.sure.afk_sure_ms();
    uint32_t afk_sn = ogren.sure.afk_sure_sn();
    uint32_t afk_dk = ogren.sure.afk_sure_dk();
    uint16_t afk_st = ogren.sure.afk_sure_saat();
    String afk_str = ogren.sure.afk_sure_formatli();

    // ANSI kodu: imleci en üst sol köşeye al
    Serial.print("\033[H");

    // Başlık
    Serial.println(F(" DURUM    DEGISIM  BASILI(ms/sn/dk)   AFK(ms/sn/dk/saat)    AFK_FMT"));

    // Satır verisi
    char satir[160];
    snprintf(satir, sizeof(satir),
             " %-8s %-8s %5lu/%2u/%2u     %6lu/%3lu/%3lu/%2u     %-25s",
             durum_str, degisim_str,
             basili_ms, basili_sn, basili_dk,
             afk_ms, afk_sn, afk_dk, afk_st,
             afk_str.c_str());

    Serial.print(satir);
}
#endif