#include <stdio.h>  // Standart input/output fonksiyonlarını kullanmak için gerekli
#include <string.h> // String işlemleri için gerekli

// Maksimum sınırı belirleyip bellek tüketimi kontrol altında tutmak için sabit bir değer belirliyoruz
#define MAX_URUN 100

// Ürün bilgilerini tutacak bir structure tanımlıyoruz
typedef struct {
    char ad[20];    // Ürünün adı (20 karaktere kadar)
    float kalori;   // Ürünün kalori değeri
} Urun;

int main() {
    FILE *kaloriDosya, *siparisDosya;  // Dosyalar pointer olarak tanımlanıyor
    Urun urunler[MAX_URUN];           // Ürün bilgilerini tutacak bir dizi
    char urunAdi[20];                 // Siparişteki ürün adını tutmak için geçici bir değişken
    float porsiyon;                   // Siparişteki ürün porsiyonu
    int urunSayisi = 0;               // Ürün sayısını takip edecek sayaç
    float toplamKalori = 0;           // Toplam kalori hesaplaması için bir değişken

    // Kalori dosyasını okuma modunda açıyoruz (r)
    kaloriDosya = fopen("C:\\proje_odev\\kalori.txt", "r");
    if (kaloriDosya == NULL) {
        // Eğer dosya açılamazsa, bir hata mesajı yazdırıyoruz ve programı sonlandırıyoruz
        printf("kalori.txt dosyasi acilamadi!\n");
        return 1; // Hata kodunu döndürüyoruz
    }

    // Kalori dosyasındaki veriyi satır satır okuyoruz
    while (fscanf(kaloriDosya, "%s %f", urunler[urunSayisi].ad, &urunler[urunSayisi].kalori) == 2) {
        // Ürünün adını ve kalori değerini diziye ekliyoruz
        urunSayisi++; // Ürün sayısını artırıyoruz
        if (urunSayisi >= MAX_URUN) {
            // Eğer maksimum ürün sınırı aşılırsa bir hata mesajı yazdırıp döngüden çıkıyoruz
            printf("Maksimum urun siniri asildi!\n");
            break;
        }
    }
    fclose(kaloriDosya); // Dosyayı kapatıyoruz

    // Sipariş dosyasını okuma modunda açıyoruz (r)
    siparisDosya = fopen("C:\\proje_odev\\siparis.txt", "r");
    if (siparisDosya == NULL) {
        // Eğer dosya açılamazsa bir hata mesajı yazdırıyoruz ve programı sonlandırıyoruz
        printf("siparis.txt dosyasi acilamadi!\n");
        return 1; // Hata kodunu döndürüyoruz
    }

    // Sipariş dosyasındaki her bir ürünü ve porsiyonu okuyoruz
    while (fscanf(siparisDosya, "%s %f", urunAdi, &porsiyon) == 2) {
        int bulundu = 0; // Ürünün kalori listesinde bulunup bulunmadığını takip eden bir döngü kuruyoruz
        for (int i = 0; i < urunSayisi; i++) {
            // Sipariş edilen ürün adı, kalori dosyasındaki bir ürünle eşleşiyor mu kontrol ediyoruz
            if (strcmp(urunAdi, urunler[i].ad) == 0) {
                // Eğer eşleşme varsa, bu ürünün toplam kalori değerini hesaplıyoruz
                toplamKalori += porsiyon * urunler[i].kalori;
                bulundu = 1; // Ürünün bulunduğunu işaretliyoruz
                break;       // Daha fazla arama yapmamıza gerek yok, döngüden çıkıyoruz
            }
        }
        if (!bulundu) {
            // Eğer siparişteki ürün kalori listesinde bulunmazsa bir uyarı mesajı yazdırıyoruz
            printf("Urun bulunamadi: %s\n", urunAdi);
        }
    }
    fclose(siparisDosya); // Dosyayı kapatıyoruz

    // Hesaplanan toplam kalori miktarını ekrana yazdırıyoruz
    printf("Toplam Kalori: %.2f\n", toplamKalori);

    return 0; // Programı sonlandırıyoruz
}