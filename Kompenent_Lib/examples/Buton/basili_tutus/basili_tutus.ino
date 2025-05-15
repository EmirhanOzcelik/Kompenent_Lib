#include "Kompenent.h"

/*
    basılı tutulan butonları okuyup karşılaştırma örneği
*/

Buton buton1, buton2;

void setup()
{
    Serial.begin(9600);
    buton1.kur(3); // pin 3
    buton2.kur(4); // pin 4
}

void loop()
{
    // isterseniz basılı tutulma milisaniyesini kendiniz alabilirsiniz 1.örnek;

    uint16_t buton1_veri = buton1.oku(); // tıklandıysa 1,basılı tutulduysa basılı tutulma milisaniyesi döndürür
    uint16_t buton2_veri = buton2.oku(); // tıklandıysa 1,basılı tutulduysa basılı tutulma milisaniyesi döndürür

    if (buton1_veri > buton2_veri)
        Serial.println("1.buton, 2.butondan once basılı tutulmaya baslandi");
    else
        Serial.println("1.buton, 2.butondan sonra basılı tutulmaya baslandi");

    // isterseniz basılı tutulma milisaniyesini dışardan da alabilirsiniz 2.örnek;

    buton1.oku();
    buton2.oku();

    if (buton1.ogren.sure.basili_tutulan_ms() > buton2.ogren.sure.basili_tutulan_ms())
        Serial.println("1.buton, 2.butondan once basılı tutulmaya baslandi");
    else
        Serial.println("1.buton, 2.butondan sonra basılı tutulmaya baslandi");
}