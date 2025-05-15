#include "Kompenent.h"

/*
    potansiyometre durum ve degisim alma
*/

Potansiyometre pot1;

void setup()
{
    Serial.begin(9600);
    pot1.kur(A0); // pin A0

    pot1.ayarla.tolerans(5); // parazit dalgalanma vs için koruma saglar eğer kullanmayacaksanız 0 girin veya hiç yazmayın
}

void loop()
{
    // potansiyometremizi okuyalım
    uint16_t potansiyometre_1 = pot1.oku(); // normal sınırlarda ( çogu kart için 0-1023) okuma yapılıyor

    // potansiyometre durum sorgulamaları
    if (pot1.ogren.artti_mi()) // potansiyometre verisi artış gösterdi mi?
        Serial.println("potansiyometre degeri artti");
    else if (pot1.ogren.azaldi_mi()) // potansiyometre verisi azalış gösterdi mi?
        Serial.println("potansiyometre degeri azaldi");
    else if (pot1.ogren.sabit_mi()) // potansiyometre verisi sabit mi?
        Serial.println("potansiyometre degeri sabit");

    // potansiyometre değişim sorgulamaları
    if (pot1.ogren.hizli_mi_degisti()) // potansiyometre verisi hizli mi degişti?
    {
        Serial.println("potansiyometre degeri hizli degisti");
        Serial.print("degisim yuzdesi : ");
        Serial.println(pot1.ogren.degisim_hizi_yuzde());
        Serial.print("degisim miktari : ");
        Serial.println(pot1.ogren.degisim_miktari());
    }
    else if (pot1.ogren.normal_mi_degisti()) // potansiyometre verisi normal mi degişti?
    {
        Serial.println("potansiyometre degeri normal degisti");
        Serial.print("degisim yuzdesi : ");
        Serial.println(pot1.ogren.degisim_hizi_yuzde());
        Serial.print("degisim miktari : ");
        Serial.println(pot1.ogren.degisim_miktari());
    }
    else if (pot1.ogren.yavas_mi_degisti()) // potansiyometre verisi yavas mi degişti?
    {
        Serial.println("potansiyometre degeri yavas degisti");
        Serial.print("degisim yuzdesi : ");
        Serial.println(pot1.ogren.degisim_hizi_yuzde());
        Serial.print("degisim miktari : ");
        Serial.println(pot1.ogren.degisim_miktari());
    }
}