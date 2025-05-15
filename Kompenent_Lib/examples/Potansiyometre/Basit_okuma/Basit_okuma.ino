#include "Kompenent.h"

/*
    potansiyometre temel okuma ve veri alma örneği
*/

Potansiyometre pot1, pot2;

void setup()
{
    Serial.begin(9600);
    pot1.kur(A0); // pin A0
    pot2.kur(A1); // pin A1

    pot1.ayarla.tolerans(5); // parazit dalgalanma vs için koruma saglar eğer kullanmayacaksanız 0 girin veya hiç yazmayın
    pot2.ayarla.tolerans(5);
}

void loop()
{
    // 1. potansiyometremizi normal , ikincisini ise belirli aralıkta okuyalım
    uint16_t potansiyometre_1 = pot1.oku(); // normal sınırlarda ( çogu kart için 0-1023) okuma yapılıyor

    uint16_t potansiyometre_2 = pot2.oku_map(0, 255); // belirttiğimiz sınırlarda okuma yapılıyor

    Serial.print("1. potansiyometre verisi : ");
    Serial.println(potansiyometre_1);
    Serial.print("2. potansiyometre verisi : ");
    Serial.println(potansiyometre_2);
}