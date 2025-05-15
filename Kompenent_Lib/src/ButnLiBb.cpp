#include "ButnLiBb.h"
#define BUTON_BASILDI LOW
#define BUTON_BASILMADI HIGH
#define afk_sure 20

uint16_t ___dbc = 0;
uint16_t ___min_basili_tutus_ms = 500;

Buton::Buton() {}

void Buton::baslat__()
{
    ogren.ogren_btn = this;
    ogren.sure.sure_btn = this;
    ogren.sure.sure_ogrn = &ogren;
    ayar.ayar_btn = this;
}

void Buton::kur(uint8_t pinn)
{
    _pin = pinn;
    ___dbc = 50;
    _dbc_sayac = 0;
    _basili_tut_syc = 0;
    ___min_basili_tutus_ms = 100;
    gecen_zmn = 0;
    g_mss = 10;
    b_syc = 0;
    _afk_sayac = 0;
    _afk_ms = 0;
    _afk_sn = 0;
    _afk_dk = 0;
    _afk_saat = 0;
    baslat__();
    pinMode(_pin, INPUT_PULLUP);
}

uint32_t Buton::oku()
{
    _son_durum = digitalRead(_pin);
    if (millis() - gecen_zmn >= g_mss)
    {
        gecen_zmn = millis();
        _afk_sayac++;
        if (_son_durum == BUTON_BASILDI) // butona tıklanıyor
        {
            b_syc = 0;
            afk_reset();
            _dbc_sayac++;
            if (_dbc_sayac * g_mss >= ___dbc)
            {
                _basili_tut_syc++;
                if (_basili_tut_syc * g_mss >= ___min_basili_tutus_ms) // basılı tutuldu
                {
                    if (durum == TIKLANDI)
                        degisim = TIKLANDIDAN_BASILIYA;
                    durum = BASILI;
                    basili_tutus_ms += g_mss;
                }
                else // sadece tıklanıyor
                {
                    if (durum == SERBEST)
                        degisim = SERBESTTEN_TIKLANDIYA;
                    basili_tutus_ms = 1;
                    durum = TIKLANDI;
                }
            }
        }
        else if (_son_durum == BUTON_BASILMADI && b_syc < 1) // butona tıklanmıyor
        {
            if (durum == TIKLANDI)
                degisim = TIKLANDIDAN_SERBESTE;
            else if (durum == BASILI)
                degisim = BASILIDAN_SERBESTE;
            durum = SERBEST;
            basili_tutus_ms = 0;
            _dbc_sayac = 0;
            _basili_tut_syc = 0;
            b_syc++;
            afk_reset();
        }
        else if (b_syc >= 1 && b_syc < 30 && g_mss * _afk_sayac >= afk_sure) // sistem afk hareket yok
        {
            afk_reset();
            degisim = DEGISIM_YOK;
            b_syc = 50;
            _afk_sayac = 0;
            basili_tutus_ms = 0;
        }
        else if (degisim == DEGISIM_YOK) // afk kalan sistem afk süresi hesaplıyor
            afk_sure_hesap();
    }
    return basili_tutus_ms;
}