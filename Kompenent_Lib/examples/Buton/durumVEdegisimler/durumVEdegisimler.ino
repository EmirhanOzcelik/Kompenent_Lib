#include "Kompenent.h"

/*
    butonun durumunu ve değişimini alma örneği
*/

Buton buton1;

void setup()
{
    Serial.begin(9600);
    buton1.kur(3); // pin 3
}

void loop()
{
    // isterseniz durum ve değişim verisini kendiniz alabilirsiniz bunu yazmaya usendim kusura bakmayin;

    uint16_t buton1_veri = buton1.oku(); // tıklandıysa 1,basılı tutulduysa basılı tutulma milisaniyesi döndürür

    // isterseniz durum ve değişim verisini dışardan da alabilirsiniz 2.örnek;

    buton1.oku();

    // buton durumu sorgulamaları
    if (buton1.ogren.tiklandi_mi()) // buton tıklama durumu kontrolü
        Serial.println("tiklanildi");
    else if (buton1.ogren.basili_mi()) // buton basılı tutma durumu kontrolü
        Serial.println("basili tutuluyor");
    else if (buton1.ogren.serbest_mi()) // buton pasif durumu kontrolü
        Serial.println("butonda islem yapilmiyor, serbest");

    // buton değişimi sorgulamaları
    if (buton1.ogren.birakildi_mi()) // buton tıklandıktan sonra mı bırakıldı?
        Serial.println("tiklanip birakildi");
    else if (buton1.ogren.uzun_basma_tamamlandi_mi()) // buton basılı tutulduktan sonra mı bırakıldı?
        Serial.println("basili tutulup birakildi");
}