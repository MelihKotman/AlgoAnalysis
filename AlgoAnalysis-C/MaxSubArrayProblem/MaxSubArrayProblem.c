/*Yapiacaklar
1. Asagidaki dosyada subArray yapisini kullanarak maksimum altdizi problemini asagidaki fonksiyonlari kullanarak cozunuz.
- Kaba kuvvet ile (BruteForce fonksiyonu)
- Bol ve yonet yontemi ile (FIND_MAX_CROSSING_SUBARRAY, FIND_MAXIMUM_SUBARRAY fonksiyonlari ile)
2. Daha sonra iki farkli yontemi farkli girdi boyutlari ile karsilastiriniz. */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ARRAYSIZE 200000 // toplam fiyat sayisi

typedef struct subArray{ // Üç farklı değeri bir yapıda toplamak için yapılan struct yapısı
    int alisGunu; //Başlangıç değerimiz
    int satisGunu; //Bitiş değerimiz
    int kar; //Bitiş ile Başlangıç arasındaki fark değerimiz
}subArray;

//Fonksiyonlarımızın prototiplerini burada belirttik
subArray FIND_MAX_CROSSING_SUBARRAY(int A[], int low, int mid, int high);
subArray FIND_MAXIMUM_SUBARRAY(int A[], int low, int high);
subArray BruteForce(int A[]);

int main(){
    //Fiyatların dizisini oluşturup bu diziye verilen ARRAYSIZE kadar rastgele fiyat koyduk
    int i;
    int fiyatlar[ARRAYSIZE];
    int degisim[ARRAYSIZE];
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++){
        fiyatlar[i] = (rand() % 120) + 1; // Fiyatları oluşturduk
    }
    //Fiyatların değişimi hesapladık
    for(i = 1; i < ARRAYSIZE; i++){
        degisim[i] = fiyatlar[i] - fiyatlar[i-1];
    }
    /*
    //Fiyatları sırasıyla yazdıran for döngüsü
    for(i = 0; i < ARRAYSIZE; i++){
        printf("%d: %d\n", i, fiyatlar[i]);
    }*/
    //Böl ve Yönet Çalışma Zamanı Hesabı ve Sonucu
    clock_t start_t, end_t;
    double cpu_time_used;
    start_t = clock();
    subArray res = FIND_MAXIMUM_SUBARRAY(degisim,1,ARRAYSIZE-1);// Böl ve Yöntemiyle çalıştır
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //Böl ve Yönet için sonuçlar
    printf("Toplam gecen sure (Bol ve yonet yontemi): %f saniyedir.\n", cpu_time_used);
    printf("Al: %d\n", res.alisGunu - 1);
    printf("Sat: %d\n", res.satisGunu);
    printf("Kar: %d\n", res.kar);

    //Kaba Kuvvet Çalışma Zamanı Hesabı ve Sonucu
    start_t = clock();
    subArray res2 = BruteForce(fiyatlar);//bulunan degerleri yazdiralim
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    //Kaba Kuvvet için sonuçlar
    printf("Toplam gecen sure (Kaba kuvvet): %f saniyedir.\n", cpu_time_used);
    printf("Al: %d\n", res2.alisGunu);
    printf("Sat: %d\n", res2.satisGunu);
    printf("Kar: %d\n", res2.kar);
	return 0;
}
//Kaba Kuvvet ile yazalım.(Her olasılığı deneyecek)
subArray BruteForce(int A[]){ //Önce diziyi gönderiyoruz
    subArray res; //Oluşturduğum struct yapısından bir boş struct oluşturduk
    res.kar = 0; //Karı ilk önce 0 dedik
    for (int i = 0; i < ARRAYSIZE;i++) { // "Alış gününü" dizinin son değeri hariç hepsini gezecek
        for (int j = i + 1; j < ARRAYSIZE; j++) { // "Satış gününü" dizinin son değeri hariç "Alış günün" bir fazlasından başlayıp gezecek
            if (A[j]-A[i] > res.kar) { //Eğer satış-alış arası fark kâr'dan büyükse
                res.kar = A[j] - A[i]; //Kârı güncelle
                res.alisGunu = i; //Alış Gününü güncelle
                res.satisGunu = j; //Satış gününü güncelle
            }
        }
    }
    return res; //Tüm değerleri struct olarak gönder
}
// Fonksiyon tanımı: 'A' dizisini, 'low' (başlangıç), 'mid' (orta) ve 'high' (bitiş)
// indekslerini alır ve bir 'subArray' yapısı döndürür.
subArray FIND_MAX_CROSSING_SUBARRAY(int A[], int low, int mid, int high){
    // Sonucu (alış, satış, kar) saklamak için bir 'subArray' yapısı oluşturulur.
    subArray res;
    // Ortadan sola doğru tararken bulunacak en iyi toplamı saklar.
    // 'INT_MIN' (mümkün olan en küçük tamsayı) ile başlatılır ki,
    // bulunan ilk değer (negatif bile olsa) bundan büyük olsun.
    int leftSum = INT_MIN;
    // Döngü içinde o anki toplamı tutmak için geçici bir değişken.
    int sumLeft = 0;
    // En iyi sol toplamın başladığı günü (indeksi) saklayacak değişken.
    int maxLeft = 0;
    // Bir döngü başlat: 'i' değişkeni 'mid' (orta) noktasından başlar
    // ve 'low' (en sol) noktaya doğru geriye doğru (i--) gider.
    for (int i = mid; i >= low; i--) {
        // Geriye doğru giderken, o günün değerini anlık toplama (sumLeft) ekle.
        sumLeft = sumLeft + A[i];
        // Eğer o anki toplam (sumLeft), bugüne kadar bulunan en iyi sol toplamdan (leftSum) daha büyükse...
        if (sumLeft > leftSum) {
            // ...yeni en iyi sol toplamı 'sumLeft' olarak güncelle.
            leftSum = sumLeft;
            // ...ve bu en iyi toplamın başladığı günü 'i' olarak kaydet.
            maxLeft = i;
        }
    } // Sol tarafı tarama döngüsü burada biter.
    // Şimdi aynı işlemin sağ taraf için olanı:
    // Ortadan sağa doğru tararken bulunacak en iyi toplamı saklar ('INT_MIN' ile başlar).
    int rightSum = INT_MIN;
    // Sağ taraf için anlık toplamı tutan geçici değişken.
    int sumRight = 0;
    // En iyi sağ toplamın bittiği günü (indeksi) saklayacak değişken.
    int maxRight = 0;
    // Bir döngü başlat: 'j' değişkeni 'mid + 1' (ortanın bir sağı) noktasından başlar
    // ve 'high' (en sağ) noktaya doğru ileriye doğru (j++) gider.
    for (int j = mid + 1; j <= high; j++) {
        // İleriye doğru giderken, o günün değerini anlık sağ toplama (sumRight) ekle.
        sumRight = sumRight + A[j];
        // Eğer o anki sağ toplam (sumRight), bugüne kadar bulunan en iyi sağ toplamdan (rightSum) daha büyükse...
        if (sumRight > rightSum) {
            // ...yeni en iyi sağ toplamı 'sumRight' olarak güncelle.
            rightSum = sumRight;
            // ...ve bu en iyi toplamın bittiği günü 'j' olarak kaydet.
            maxRight = j;
        }
    } // Sağ tarafı tarama döngüsü burada biter.
    res.alisGunu = maxLeft; // 'res' yapısının 'alisGunu' alanına, bulunan en iyi sol başlangıç gününü ('maxLeft') ata.
    res.satisGunu = maxRight; // 'res' yapısının 'satisGunu' alanına, bulunan en iyi sağ bitiş gününü ('maxRight') ata.
    res.kar = leftSum + rightSum; // Toplam kar, en iyi sol toplam (leftSum) ile en iyi sağ toplamın (rightSum) birleşimidir.
    return(res); // Ortayı kesen en iyi dönemin bilgilerini içeren 'res' yapısını çağrıldığı yere geri döndür.
}
// Ana "Böl ve Yönet" fonksiyonu. 'A' dizisini, 'low' (başlangıç) ve 'high' (bitiş)
// indekslerini alır ve o aralıktaki en kârlı 'subArray' yapısını döndürür.
subArray FIND_MAXIMUM_SUBARRAY(int A[], int low, int high){
    // Sonucu döndürmek için boş bir 'subArray' yapısı oluşturulur.
    // Bu, özellikle 'temel durum' için kullanılır.
    subArray res; // Aynı şekilde boş bir struct oluşturduk
    // --- TEMEL DURUM (BASE CASE) ---
    // Özyinelemenin (recursion) durma noktasıdır.
    // Eğer 'high' ve 'low' indeksleri eşitse, dizide sadece 1 eleman kalmış demektir.
    if (high == low) { //Eğer tek diziyse
        // O elemanın alış günü 'low'dur.
        res.alisGunu = low;
        // O elemanın satış günü de 'high'dır (zaten 'low' ile aynı).
        res.satisGunu = high;
        // Kâr (veya zarar), o elemanın kendi değeridir.
        res.kar = A[low];
        // Bu tek elemanlı dizinin bilgilerini içeren 'res' yapısını döndür.
        return(res); //Tüm değerleri aynı şekilde geri gönder.
    }
    // --- ÖZYİNELEMELİ DURUM (RECURSIVE CASE) ---
    else { // Ama değilse (yani dizide 1'den fazla eleman varsa)
        // --- 1. BÖL (DIVIDE) ADIMI ---
        // Dizinin tam orta noktasının indeksini hesapla (tamsayı bölmesi).
        int mid = (low + high) / 2; // Orta noktayı bul
        // --- 2. YÖNET (CONQUER) ADIMI ---
        // Şimdi 3 olası senaryo için alt problemleri çöz:
        // 1. Senaryo (Sol Taraf): Fonksiyonun *kendisini* sadece sol yarı
        // ('low'dan 'mid'e kadar) için tekrar çağır. Gelen sonuca 'leftres' de.
        subArray leftres = FIND_MAXIMUM_SUBARRAY(A, low, mid); // Orta noktanın öncesi tekrar çağır
        // 2. Senaryo (Sağ Taraf): Fonksiyonun *kendisini* sadece sağ yarı
        // ('mid + 1'den 'high'a kadar) için tekrar çağır. Gelen sonuca 'rightres' de.
        subArray rightres = FIND_MAXIMUM_SUBARRAY(A, mid + 1, high); // Orta noktanın sonrası tekrar çağır
        // 3. Senaryo (Ortayı Kesen): Yukarıda açıkladığımız 'CROSSING' fonksiyonunu çağırarak
        // 'mid' noktasını kesen en iyi sonucu bul. Gelen sonuca 'crossres' de.
        subArray crossres = FIND_MAX_CROSSING_SUBARRAY(A, low, mid, high); // Ana fonksiyondaki dizinin değerini hesapla
        // --- 3. BİRLEŞTİR (COMBINE) ADIMI ---
        // Elimizdeki 3 sonucu ('leftres', 'rightres', 'crossres') karşılaştır:
        // Eğer sol tarafın kârı, hem sağ tarafın kârından hem de ortayı kesen kârdan
        // büyük veya eşitse...
        if (leftres.kar >= rightres.kar && leftres.kar >= crossres.kar) { //Eğer en soldaki değer büyükse hepsinden
                // ...en iyi sonuç 'leftres'tir, onu döndür.
                return(leftres);  // En soldaki dizinin struct'ını sonuç olarak gönder
        }
        // Değilse, bir de sağ tarafın kârına bak:
        // Eğer sağ tarafın kârı, hem sol tarafın kârından hem de ortayı kesen kârdan
        // büyük veya eşitse...
        else if(rightres.kar >= leftres.kar && rightres.kar >= crossres.kar) { //Eğer en sağdaki değer büyükse hepsinden
                // ...en iyi sonuç 'rightres'tir, onu döndür.
                return(rightres); // En sağdaki dizinin struct'ını sonuç olarak gönder
        }
        // Eğer en iyi kâr ne solda ne de sağdaysa,
        // o zaman en iyi kâr ortayı kesen 'crossres' olmalıdır.
        else {
                // ...'crossres'i döndür.
                return(crossres); //
        }
    }
}

