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

    if (pot1.ogren.afk_mi())
    {
        Serial.println("potansiyometreden veri gelmiyor");
        Serial.print("su milisaniye suredir afk : ");
        Serial.println(pot1.ogren.afk_kalinan_ms());
    }
}