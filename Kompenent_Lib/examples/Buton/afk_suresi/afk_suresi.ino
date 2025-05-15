#include "Kompenent.h"

/*
    butonun üstünde işlem yapılmadıgı (butonun afk kalma süresini) süreyi alma örneği
*/

Buton buton1;

unsigned long gecen_zaman = 0;     // millis icin genel degisken kullandık
uint16_t afk_kalma_milisaniye = 0; // afk suresini tutacak degisken

void setup()
{
    Serial.begin(9600);
    buton1.kur(3); // pin 3
}

void loop()
{
    // isterseniz afk suresi verisini kendiniz alabilirsiniz 1.örnek;

    uint16_t buton1_veri = buton1.oku(); // tıklandıysa 1,basılı tutulduysa basılı tutulma milisaniyesi döndürür

    if (buton1_veri == 0)
    {
        if (millis() - gecen_zaman >= 20)
        {
            gecen_zaman = millis();
            afk_kalma_milisaniye = afk_kalma_milisaniye + 20;
            Serial.print("buton su milisaniyedir pasif : ");
            Serial.println(afk_kalma_milisaniye);
        }
    }
    else
    {
        Serial.println(" buton aktif");
        afk_kalma_milisaniye = 0; // buton aktif oldu afk kalma suresini sifirladik
    }

    // isterseniz afk kalma verisini dışardan da alabilirsiniz 2.örnek;

    buton1.oku();

    if (buton1.ogren.serbest_mi())
    {
        Serial.print(" buton su suredir pasif : ");
        Serial.println(buton1.ogren.sure.afk_sure_ms());
    }
    else
        Serial.println(" buton tiklanmiyor");
}