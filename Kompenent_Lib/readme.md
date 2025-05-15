# BUTPOTLIB

Arduino için gelişmiş Buton ve Potansiyometre yönetim kütüphanesi.

Bu kütüphane, butonlar ve potansiyometreler ile çalışırken debounce, basılı tutma süresi, AFK (hareketsizlik) tespiti, hız analizi gibi gelişmiş özellikler sağlar. ESP ve UNO gibi kartlarla uyumludur.Uno dışındaki kartlar için gerekli ayarlamaları sagladıgınızdan emin olun.

## İçindekiler

- [Kurulum](#kurulum)
- [Buton Sınıfı](#buton-sınıfı)
- [Potansiyometre Sınıfı](#potansiyometre-sınıfı)

---

## Kurulum

1. `BUTPOTLIB` klasörünü `Arduino/libraries/` klasörüne ekleyin.
2. `.ino` dosyanızda aşağıdaki gibi dahil edin:

```cpp
#include <BUTPOTLIB.h>
```

### Buton Sınıfı - 

Buton();  
    → Sınıf yapıcı (constructor) fonksiyonu. Buton nesnesini başlatır.

void kur(uint8_t pinn);  
    → Buton pinini ayarlayıp giriş moduna alır.

uint32_t oku();  
    → Buton durumunu günceller.  
      - Tıklandıysa `1` döner.  
      - Basılı tutuluyorsa geçen süreyi (ms) döner.  
      - Serbestse `0` döner.

drm durum;  
    → Mevcut fiziksel buton durumu: `SERBEST`, `TIKLANDI`, `BASILI`.

dgsm degisim;  
    → Son durum değişikliği:  
      `DEGISIM_YOK`, `SERBESTTEN_TIKLANDIYA`, `TIKLANDIDAN_SERBESTE`,  
      `TIKLANDIDAN_BASILIYA`, `BASILIDAN_SERBESTE`.

ayaR ayar;  
    → Ayar yapıları:  
      - `debounce(ms)`  
      - `min_basili_tutma_ms(ms)`

ogren_ ogren;  
    → Durum sorguları:  
      - `tiklandi_mi()`  
      - `basili_mi()`  
      - `birakildi_mi()`  
      - `serbest_mi()`  
      - `uzun_basma_tamamlandi_mi()`

ogren_.sure_ sure;  
    → Süre bilgileri:  
      - `basili_tutulan_ms()`  
      - `basili_tutulan_sn()`  
      - `basili_tutulan_dk()`  
      - `afk_sure_ms()`  
      - `afk_sure_sn()`  
      - `afk_sure_dk()`  
      - `afk_sure_saat()`

### Potansiyometre Sınıfı - 

Potansiyometre();  
    → Sınıf yapıcı (constructor) fonksiyonu. Potansiyometre ayarlarını varsayılan olarak başlatır.

void kur(int16_t pin, int16_t minn = 0, int16_t maxx = 1023);  
    → Potansiyometre'yi analog pine bağlar ve çıkış aralığını ayarlar.

int16_t oku();  
    → Potansiyometreden okunan değeri döndürür (ham/saf ADC değeri).

int16_t oku_map(int16_t minn, int16_t maxx);  
    → Okunan değeri verilen aralıkta yeniden ölçekleyerek döndürür.

drm durum;  
    → Son değişim yönü: `ARTTI`, `AZALDI`, `SABIT`.

dgsm degisim;  
    → Değişim hızı durumu: `YOK`, `YAVAS`, `NORMAL`, `HIZLI`.

ogren_ ogren;  
    → Durum sorguları:  
      - `artti_mi()`  
      - `azaldi_mi()`  
      - `sabit_mi()`  
      - `afk_mi()`  
      - `hizli_mi_degisti()`  
      - `yavas_mi_degisti()`  
      - `normal_mi_degisti()`  
      - `degisim_miktari()`  
      - `afk_kalinan_ms()`  
      - `degisim_hizi_yuzde()`

ayar_ ayarla;  
    → Ayarlama işlevleri:  
      - `ogrenimli_kalibre(bool)`  
      - `afk_kalma_ms(ms)`  
      - `tolerans(uint8_t)`  
      - `ceviri_aralik(min, max)`  
      - `cozunurluk_max_deger(uint16_t)`