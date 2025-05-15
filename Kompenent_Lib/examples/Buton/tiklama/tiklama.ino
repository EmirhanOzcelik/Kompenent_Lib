#include "Kompenent.h"

/*
    buton tıklama örnegi
*/

Buton buton1;

void setup()
{
    Serial.begin(9600);
    buton1.kur(3); // pin 3
}

void loop()
{
    // isterseniz tıklanma verisini kendiniz alabilirsiniz 1.örnek;

    uint16_t buton1_veri = buton1.oku(); // tıklandıysa 1,basılı tutulduysa basılı tutulma milisaniyesi döndürür

    if (buton1_veri == 1)
        Serial.println(" buton tiklandi");
    else
        Serial.println(" buton tiklanmiyor");

    // isterseniz basılı tutulma milisaniyesini dışardan da alabilirsiniz 2.örnek;

    buton1.oku();

    if (buton1.ogren.tiklandi_mi())
        Serial.println(" buton tiklandi");
    else
        Serial.println(" buton tiklanmiyor");
}