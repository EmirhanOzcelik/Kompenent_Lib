#include "PotLiBb.h"

constexpr byte max_boyut = 2;
byte sycpaket1 = 0;
byte sycpaket2 = 0;
uint16_t paket1[max_boyut] = {0, 0}; // okunan ham degerleri tutar aşama 1
uint16_t paket2[max_boyut] = {0, 0}; // okunan ham degerlerden ayıklanan max degerleri tutar
uint16_t veri_max = 0;               // nihai okunan max sonuc

void max_deger_elle_gir(uint16_t veri) { veri_max = veri; }

uint16_t max_deger_yakala(uint16_t giris, uint16_t maxx)
{
    if (giris == 0) // 0 ise ugrastırma
        return veri_max;
    else if (giris >= veri_max) // zaten büyükse ugrastırma
    {
        veri_max = giris;
        return veri_max;
    }
    else if (giris > maxx)
        return veri_max;
    else if (veri_max > maxx)
        veri_max = 0;
    else if (sycpaket1 < max_boyut)
    {
        paket1[sycpaket1] = giris;
        sycpaket1++;
    }
    else
    {
        uint16_t y = 0;
        for (byte i = 0; i < max_boyut; i++)
        {
            if (y < paket1[i])
                y = paket1[i];
            paket1[i] = 0;
        }
        sycpaket1 = 0;
        if (sycpaket2 < max_boyut)
        {
            paket2[sycpaket2] = y;
            sycpaket2++;
        }
        else
        {
            for (byte i = 0; i < max_boyut; i++)
            {
                if (veri_max < paket2[i] && paket2[i] < maxx)
                    veri_max = paket2[i];
                paket2[i] = 0;
            }
            sycpaket2 = 0;
        }
    }
    return veri_max;
}

/*
void Potansiyometre::hiz_kontrol(uint16_t c, uint16_t maxx)
{
    if (maxx == 0)
    {
        degisim = YOK;
        return;
    }
    float skor = log10f((float)c + 1) / log10f((float)maxx + 1); // 0.0 - 1.0 arası
    if (skor > 0.8f)
        degisim = HIZLI;
    else if (skor > 0.4f)
        degisim = NORMAL;
    else
        degisim = YAVAS;
}
*/
void Potansiyometre::hiz_kontrol(uint16_t c, uint16_t maxx)
{
    if (maxx == 0)
    {
        degisim = YOK;
        return;
    }
    uint16_t oran = (c * 100) / maxx;
    if (oran > 75) // Hızlı (> 75%)
        degisim = HIZLI;
    else if (oran > 35) // Normal (35%–75%)
        degisim = NORMAL;
    else // Yavaş (< 35%)
        degisim = YAVAS;
}

////////////////////////////////////////////////////////////////////////////////////

void Potansiyometre::ayar_::ogrenimli_kalibre(bool trfls)
{
    pot->_oto_maxdeger_kalibre = trfls;
}
void Potansiyometre::ayar_::afk_kalma_ms(uint16_t milisaniye)
{
    pot->afk_dogrulama_ms = milisaniye;
}
void Potansiyometre::ayar_::tolerans(uint8_t tolare_degeri)
{
    pot->_okuma_tolerans = tolare_degeri;
}
void Potansiyometre::ayar_::ceviri_aralik(int16_t minn, int16_t maxx)
{
    pot->_min = minn;
    pot->_max = maxx;
}
void Potansiyometre::ayar_::cozunurluk_max_deger(uint16_t max_adc_deger)
{
    pot->_cozunurluk_deger = max_adc_deger;
}

////////////////////////////////////////////////////////////////////////////////////

bool Potansiyometre::ogren_::artti_mi()
{
    return pot->durum == ARTTI; //
}
bool Potansiyometre::ogren_::azaldi_mi()
{
    return pot->durum == AZALDI; //
}
bool Potansiyometre::ogren_::sabit_mi()
{
    return pot->durum == SABIT; //
}
bool Potansiyometre::ogren_::afk_mi()
{
    return pot->afk_sure_ms > pot->afk_dogrulama_ms; //
}
bool Potansiyometre::ogren_::hizli_mi_degisti()
{
    return pot->degisim == HIZLI; //
}
bool Potansiyometre::ogren_::yavas_mi_degisti()
{
    return pot->degisim == YAVAS; //
}
bool Potansiyometre::ogren_::normal_mi_degisti()
{
    return pot->degisim == NORMAL; //
}
int16_t Potansiyometre::ogren_::degisim_miktari()
{
    return pot->_degisim_miktar;
}
uint32_t Potansiyometre::ogren_::afk_kalinan_ms()
{
    return pot->afk_sure_ms;
}
uint16_t Potansiyometre::ogren_::degisim_hizi_yuzde(uint16_t maxx)
{
    uint16_t c = map(degisim_miktari(), 0, maxx, 0, 100);
    uint16_t k = (c < 101) ? c : 100;
    return k;
}