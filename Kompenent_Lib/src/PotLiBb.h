#pragma once
#include "BUTPOTLIB.h"
/**
 * @class Potansiyometre
 * @brief Potansiyometre okuma işlemi, kalibrasyon, hız ve AFK kontrolü sağlar.
 */
class Potansiyometre
{
private:
    void hiz_kontrol(uint16_t c, uint16_t maxx); /**< Hız değişimini kontrol eder. */

    friend class ogren_;
    friend class ayar_;
    uint8_t _pin;               ///< Potansiyometre'nin bağlı olduğu pin
    uint16_t _adc_maxdeger;     ///< ADC için max değer
    uint16_t _adc_mindeger;     ///< ADC için min değer
    int16_t _min;               ///< Çıkış aralığının minimum değeri
    int16_t _max;               ///< Çıkış aralığının maksimum değeri
    uint16_t _okuma_tolerans;   ///< Okuma sırasında tolerans değeri
    int16_t _son_deger;         ///< Son okunan değer
    uint16_t _son_saf_deger;    ///< Son okunan saf ADC değeri
    int16_t _degisim_miktar;    ///< Değişim miktarı
    uint32_t afk_sure_ms;       ///< AFK kalınan süre
    uint16_t afk_dogrulama_ms;  ///< AFK doğrulama süresi
    bool _oto_maxdeger_kalibre; ///< Otomatik maksimum değer kalibrasyonu durumu
    uint16_t _cozunurluk_deger; ///< Çözünürlük değeri
    bool _sabit_cozunurluk;     ///< Sabit çözünürlük durumu
    unsigned long gecen_zamann; ///< Geçen zaman
    uint8_t g_mss;              ///< Geçiş süresi

    enum drm
    {
        ARTTI,  ///< Değer arttı
        AZALDI, ///< Değer azaldı
        SABIT   ///< Değer sabit
    };

    enum dgsm
    {
        YOK,    ///< Değişim yok
        NORMAL, ///< Normal hızda değişim
        YAVAS,  ///< Yavaş değişim
        HIZLI   ///< Hızlı değişim
    };

public:
    drm durum;    ///< Durum: arttı, azaldı, sabit
    dgsm degisim; ///< Değişim hızı: yok, normal, yavaş, hızlı

    /**
     * @brief Yapıcı fonksiyon. Potansiyometre sınıfının varsayılan ayarlarını yapar.
     */
    Potansiyometre();

    /**
     * @brief Potansiyometre'yi kurar.
     * @param pin Analog pin numarası
     * @param minn Minumum çıktı değeri (boş bırakılabilir, varsayılan : 0)
     * @param maxx Maksimum çıktı değeri (boş bırakılabilir, varsayılan : 1023)
     */
    void kur(int16_t pin, int16_t minn = 0, int16_t maxx = 1023);

    /**
     * @brief Potansiyometre'den okuma yapar ve sonucu döndürür.
     * @return Potansiyometre'nin okuduğu saf değeri döndürür
     */
    int16_t oku();

    /**
     * @brief Potansiyometre'den okuma yapar ve sonucu döndürür.
     * @param minn Minumum çıktı değeri (boş bırakılabilir, varsayılan : 0)
     * @param maxx Maksimum çıktı değeri (boş bırakılabilir, varsayılan : 1023)
     * @return Potansiyometre'nin okuduğu değeri verdiginiz çıktı aralıgında döndürür
     */
    int16_t oku_map(int16_t minn, int16_t maxx);

    /**
     * @brief Seri ekranda kütüphane fonksiyonlarını test eder
     * @param izin çalışma izni (boş bırakılabilir, varsayılan : true)
     */
#if defined(SERI_TEST) && SERI_TEST
    void test(bool izinn = true);
#endif

    class ogren_
    {
    private:
        Potansiyometre *pot; ///< Potansiyometre nesnesi
        friend class Potansiyometre;

    public:
        /**
         * @brief Değer arttı mı?
         * @return değer arttıysa true, artmadıysa false
         */
        bool artti_mi();

        /**
         * @brief Değer azaldı mı?
         * @return değer azaldıysa true, artmadıysa false
         */
        bool azaldi_mi();

        /**
         * @brief Değer sabit mi?
         * @return değer sabitse true, sabit değilse false
         */
        bool sabit_mi();

        /**
         * @brief Potansiyometre AFK durumda mı?
         * @return AFK durumda ise true, değilse false
         */
        bool afk_mi();

        /**
         * @brief Değişim hızlı mı?
         * @return değişim hızlıysa true, değilse false
         */
        bool hizli_mi_degisti();

        /**
         * @brief Değişim yavaş mı?
         * @return değişim yavaşsa true, değilse false
         */
        bool yavas_mi_degisti();

        /**
         * @brief Değişim normal hızda mı?
         * @return değişim normal hızda ise true, değilse false
         */
        bool normal_mi_degisti();

        /**
         * @brief Değişimi döndürür.
         * @return Değişim miktarı (azalmışsa negatif ,artmışsa pozitif)
         */
        int16_t degisim_miktari();

        /**
         * @brief son okumadan beri AFK kalınan süreyi döndürür.
         * @return AFK süresi
         */
        uint32_t afk_kalinan_ms();

        /**
         * @brief Değişim hızını yüzde olarak döndürür.
         * @return Değişim hızı (yüzde)
         */
        uint16_t degisim_hizi_yuzde();
    };
    class ogren_ ogren; ///< Potansiyometre'nin okuma ve kontrol fonksiyonları

    class ayar_
    {
    private:
        Potansiyometre *pot; ///< Potansiyometre nesnesi
        friend class Potansiyometre;

    public:
        /**
         * @brief Potansiyometrenin kendini otomatik öğrenimli kalibre etmesi için izin
         * @brief potansiyometre verilerini okur ve max veriyi potansiyometrenin sınırı olarak kabul eder
         * @brief belirli uygulamalar dışında false olarak tutmanız önerilir varsayılan olarak false dir
         * @brief eğer kullanacaksanız potansiyometrenin en az bir kez max konuma getirileceğinden emin olmalısınız 
         * @param trfls Kalibrasyon tipi (true/false)
         */
        void ogrenimli_kalibre(bool trfls = false);

        /**
         * @brief AFK kalma süresini ayarlar.
         * @brief durum ve değişimlerin resetlenme süresidir
         * @brief önerilen süre 20ms dir
         * @param milisaniye AFK süresi
         */
        void afk_kalma_ms(uint16_t milisaniye = 20);

        /**
         * @brief Okuma tolerans değerini ayarlar.(önerilir)
         * @brief önerilen deger 0-1023 aralıgı için 5 dir, kullanmayacaksanız 0 girin
         * @param tolare_degeri Tolerans değeri(başlarken varsayılan : 0 dır)
         */
        void tolerans(uint8_t tolare_degeri = 5);

        /**
         * @brief Çıkış aralığını ayarlar.
         * @brief oku_map() fonksiyonunun gelişimi ile bu fonksiyon rafa kaldırıldı kullanmanız önerilmez
         * @param minn okunan veririn dönüştürüleceği çıktının min noktası
         * @param maxx okunan veririn dönüştürüleceği çıktının max noktası
         */
        void ceviri_aralik(int16_t minn, int16_t maxx);

        /**
         * @brief Çözünürlük değerini ayarlar.
         * @brief Arduino uno nano esp8266 vb. kartlar için genelde 1023 dür.
         * @param max_adc_deger ADC'nin maksimum çözünürlük değeri
         */
        void cozunurluk_max_deger(uint16_t max_adc_deger);
    };
    class ayar_ ayarla;
    ///< Potansiyometre ayar fonksiyonları
};
