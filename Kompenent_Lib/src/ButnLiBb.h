#pragma once
#include "BUTPOTLIB.h"
/**
 * @file ButnLiBb.h
 * @brief Buton sınıfı - Gelişmiş buton yönetimi (debounce, basılı süre, AFK izleme)
 */

/// Global debounce süresi (ms)
extern uint16_t ___dbc;

/// Minimum basılı tutma süresi (ms)
extern uint16_t ___min_basili_tutus_ms;

/**
 * @class Buton
 * @brief Arduino üzerinde buton takibi, basılı tutma ve AFK hesaplama yapan sınıf.
 *
 * Kullanım örneği:
 * @code
 * Buton btn;
 * btn.kur(4);              // Buton 4 numaralı pine bağlandı
 * btn.oku();               // Her loop() içinde çağrılır
 * if (btn.ogren.tiklandi_mi()) {
 *     // Tıklama algılandı
 * }
 * @endcode
 */
class Buton
{
private:
    enum drm
    {
        SERBEST,
        TIKLANDI,
        BASILI
    };
    enum dgsm
    {
        DEGISIM_YOK,
        TIKLANDIDAN_SERBESTE,
        SERBESTTEN_TIKLANDIYA,
        BASILIDAN_SERBESTE,
        TIKLANDIDAN_BASILIYA
    };

    uint8_t _pin;
    bool _son_durum;
    uint16_t _dbc_sayac;
    uint32_t _basili_tut_syc;
    uint32_t basili_tutus_ms;
    unsigned long gecen_zmn;
    uint8_t g_mss;
    uint8_t b_syc;
    uint16_t _afk_sayac;
    uint32_t _afk_ms;
    uint8_t _afk_sn;
    uint8_t _afk_dk;
    uint16_t _afk_saat;

    void baslat__();
    void afk_reset();
    void afk_sure_hesap();

    friend class ogren_;
    friend class ayaR;

public:
    /**
     * @brief Butonun mevcut fiziksel durumunu belirtir.
     *
     *`durum` enum türündedir. `oku()` fonksiyonunda güncellenir.
     *
     * `SERBEST`: Butona basılmıyor.
     *
     * `TIKLANDI`: Kısa süreli basıldı.
     *
     * `BASILI`: Uzun süre basılı tutuluyor.
     *
     * @see drm
     */
    drm durum;

    /**
     * @brief Buton durum değişimlerini takip eden olay izleyicisidir.
     *
     * `degisim` enum türündedir. Her `oku()` çağrısında, butonun bir önceki durumuna göre
     * oluşan geçişi temsil eder. Sürekli değişmez; sadece bir olay gerçekleştiğinde güncellenir.
     *
     * Olası geçişler:
     *
     *
     * `DEGISIM_YOK`: Herhangi bir yeni değişiklik yok. (AFK MOD)
     *
     * `SERBESTTEN_TIKLANDIYA`: Boşta olan butona kısa süreli basıldı.
     *
     * `TIKLANDIDAN_SERBESTE`: Kısa basma sonrası bırakıldı.
     *
     * `TIKLANDIDAN_BASILIYA`: Kısa basma uzun basmaya dönüştü.
     *
     * `BASILIDAN_SERBESTE`: Uzun basılan buton bırakıldı.
     *
     * Bu yapı sayesinde buton olayları tekil olarak yakalanabilir.
     *
     * @see dgsm
     */
    dgsm degisim;

    /**
     * @brief Buton sınıfı kurucu fonksiyonu
     */
    Buton();

    /**
     * @brief Buton donanım pinini ayarlar ve başlatır.
     * @param pinn Bağlı olduğu pin numarası (örneğin 4)
     *
     * @code
     * btn.kur(2); // 2 numaralı pine bağlandı
     * @endcode
     */
    void kur(uint8_t pinn);

    /**
     * @brief Buton durumunu günceller ve iç değişkenleri işler.
     * Bu fonksiyon loop() içinde düzenli çağrılmalıdır.
     * @return basılı tutulma süresi (ms cinsinden)
     *
     * buton serbestse 0, tıklandıysa 1,basılı tutuluyorsa basılı tutulan ms dondurur
     *
     * @code
     * uint32_t sure = btn.oku();
     * @endcode
     */
    uint32_t oku();

#if defined(SERI_TEST) && SERI_TEST
    void test(bool izin = true);
#endif

    /**
     * @class ayaR
     * @brief Ayar işlemleri için alt sınıf (debounce süresi vb.)
     */
    class ayaR
    {
    private:
        Buton *ayar_btn;
        friend class Buton;
        friend class ogren_;
        friend class sure_;

    public:
        /**
         * @brief Buton için debounce süresini ayarlar.
         * @param dbc Debounce süresi (ms)
         *
         * @code
         * btn.ayar.debounce(30);
         * @endcode
         */
        void debounce(uint16_t dbc);

        /**
         * @brief basılı tutma işlemini başlatacak minimum süreyi ayarlar.
         * @param max_ms Süre (milisaniye)
         *
         * @code
         * btn.ayar.min_basili_tutma_ms(1500);
         * @endcode
         */
        void min_basili_tutma_ms(uint16_t max_ms);
    } ayar;

    /**
     * @class ogren_
     * @brief Butonun durumu hakkında sorgulamalar yapmak için sınıf.
     */
    class ogren_
    {
    private:
        Buton *ogren_btn;
        friend class Buton;
        friend class ayar_;
        friend class sure_;

    public:
        /**
         * @brief Butonun bir kez tıklanıp bırakıldığını kontrol eder.
         * @return true ise tıklama olmuş demektir.
         */
        bool tiklandi_mi();

        /**
         * @brief Buton basılı tutuluyor mu kontrol eder.
         * @return true ise şu an basılı demektir.
         */
        bool basili_mi();

        /**
         * @brief Buton bırakıldı mı?
         * @return true ise bırakılmıştır.
         */
        bool birakildi_mi();

        /**
         * @brief Buton serbest mi?
         * @return true ise hareket yoktur.
         */
        bool serbest_mi();

        /**
         * @brief Uzun basma tamamlandı mı?
         * @return true ise uzun basım sonrası bırakma gerçekleşmiş.
         */
        bool uzun_basma_tamamlandi_mi();

        /**
         * @class sure_
         * @brief Süre bilgilerini öğrenmek için alt sınıf.
         */
        class sure_
        {
        private:
            ogren_ *sure_ogrn;
            Buton *sure_btn;
            friend class Buton;
            friend class ogren_;
            friend class ayar_;

        public:
            /**
             * @brief Butonun basılı tutulma süresi (ms)
             */
            uint32_t basili_tutulan_ms();

            /**
             * @brief Basılı tutma süresi saniye cinsinden
             */
            uint16_t basili_tutulan_sn();

            /**
             * @brief Basılı tutma süresi dakika cinsinden
             */
            uint8_t basili_tutulan_dk();

            /**
             * @brief AFK kalınan süre (ms)
             */
            uint32_t afk_sure_ms();

            /**
             * @brief AFK süresi saniye olarak
             */
            uint32_t afk_sure_sn();

            /**
             * @brief AFK süresi dakika olarak
             */
            uint32_t afk_sure_dk();

            /**
             * @brief AFK süresi saat olarak
             */
            uint16_t afk_sure_saat();
        } sure;
    } ogren;
};