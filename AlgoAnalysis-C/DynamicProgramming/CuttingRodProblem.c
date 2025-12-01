#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<limits.h>

// Yardımcı fonksiyon prototipi (maksimumu bulmak için)
int max(int num1, int num2);

// Çubuk kesme fonksiyonlarının prototipleri
int CUT_ROD(int p[],int n);
int BOTTOMUP_CUT_ROD(int p[], int n);
int MEMOIZED_CUT_ROD(int p[],int n);
int MEMOIZED_CUT_ROD_AUX(int p[],int n,int r[]);
int EXTENDED_BOTTOM_UP_CUT_ROD(int p[],int s[],int n);
void PRINT_CUT_ROD_SOLUTION(int p[],int s[],int n);

int main(){
    // Fiyat listesi dizisi.
    // p[0] = 1 (1 birimlik parça fiyatı), p[1] = 5 (2 birimlik parça fiyatı)... şeklinde gider.
    int p[10] = {1,5,8,9,10,17,17,20,24,30};

    printf("Uzunlugu belirtiniz: ");
    int uzunluk;
    // Kullanıcıdan çubuk uzunluğunu alıyoruz.
    scanf("%d",&uzunluk);

    // Kesim noktalarını tutacak dizi (s dizisi).
    // Boyutu 'uzunluk + 1' yapıyoruz çünkü 0'dan n'e kadar indeksleri kullanacağız.
    int kesim_noktasi[uzunluk + 1];

    // Aşağıdan yukarıya (Bottom-Up) yöntemini çağırıp sonucu yazdırıyoruz.
    printf("Maksimum kazanc (BOTTUMUP_CUT_ROD): %d\n",BOTTOMUP_CUT_ROD(p,uzunluk));

    // Çözümün detaylarını (hangi parçaların kesildiğini) yazdıran fonksiyonu çağırıyoruz.
    // Bu fonksiyon içinde EXTENDED_BOTTOM_UP_CUT_ROD çağrılacak ve 'kesim_noktasi' dizisi dolacak.
    PRINT_CUT_ROD_SOLUTION(p,kesim_noktasi,uzunluk);

    // Hafızalı (Memoized) yöntemi çağırıp sonucu yazdırıyoruz.
    printf("Maksimum kazanc (MEMOIZED_CUT_ROD): %d\n",MEMOIZED_CUT_ROD(p,uzunluk));

    // Kaba kuvvet (Recursive) yöntemi.
    //printf("Maksimum kazanc (CUT_ROD): %d\n",CUT_ROD(p,uzunluk));

    return 0;
}

// İki tamsayıyı karşılaştırıp büyük olanı döndüren yardımcı fonksiyon.
int max(int num1,int num2){
    // Eğer birinci sayı büyük veya eşitse onu döndür.
    if(num1 >= num2)
        return num1;
    // Değilse ikinci sayıyı döndür.
    return num2;
}

// 1. YÖNTEM: RECURSIVE (ÖZYİNELEMELİ) ÇÖZÜM
int CUT_ROD(int p[],int n){
    // Temel durum (Base Case): Eğer çubuk uzunluğu 0 ise kazanç 0'dır.
    if (n == 0) {
        return 0;
    }

    // q değişkenini olabilecek en küçük tamsayı (INT_MIN) olarak başlatıyoruz.
    // Bu değişken o anki uzunluk için bulunan maksimum kazancı tutacak.
    int q = INT_MIN;

    // 1'den n'e kadar olası tüm ilk kesim noktalarını deniyoruz.
    // i: İlk kesilen parçanın uzunluğu.
    for(int i = 1;i <= n;i++) {

        // Fiyat listemiz (p dizisi) sadece 10 elemanlı olduğu için (1..10 birimlik fiyatlar var),
        // i'nin 10'dan küçük veya eşit olup olmadığını kontrol etmemiz lazım.
        if (i <= 10) {
            // p[i-1]: i uzunluğundaki parçanın fiyatı. (Dizi 0 tabanlı olduğu için i-1).
            // CUT_ROD(p, n-i): Geriye kalan (n-i) uzunluğundaki parçanın en iyi fiyatı için fonksiyonu tekrar çağırıyoruz.
            // Bu ikisinin toplamı ile mevcut 'q' değerini karşılaştırıp büyük olanı alıyoruz.
            q = max(q, p[i-1] + CUT_ROD(p, n-i));
        }
        else {
            // Eğer kesilen parça (i) 10'dan büyükse, fiyat listesinde karşılığı yoktur.
            // Bu parçanın satış fiyatını 0 kabul edip, sadece geriye kalan (n-i) kısmın kazancına bakıyoruz.
            q = max(q, CUT_ROD(p, n-i));
        }
    }
    // Döngü bittiğinde bulunan en yüksek kazancı döndürüyoruz.
    return q;
}

// 2. YÖNTEM: BOTTOM-UP (AŞAĞIDAN YUKARIYA) DP ÇÖZÜMÜ
int BOTTOMUP_CUT_ROD(int p[], int n) {
    // Sonuçları saklamak için bir r dizisi oluşturuyoruz (Memoization tablosu).
    // n uzunluğu için n+1 boyutlu dizi lazım (0..n).
    int r[n + 1];

    // 0 uzunluğundaki çubuğun geliri 0'dır. Bu bizim başlangıç noktamız.
    r[0] = 0;

    // j döngüsü: Problemi 1 birimden başlayarak n birime kadar sırayla çözüyoruz.
    // j: Şu an çözümünü hesapladığımız çubuk uzunluğu.
    for (int j = 1; j <= n; j++) {

        // Bu 'j' uzunluğu için maksimum kazancı tutacak geçici değişken.
        int q = INT_MIN;

        // i döngüsü: j uzunluğundaki çubuk için olası ilk kesim noktalarını (1..j) deniyoruz.
        for (int i = 1; i <= j; i++) {

            // Fiyat listesi sınır kontrolü (max 10 birimlik fiyat var).
            if (i <= 10) {
                // p[i-1]: i uzunluğundaki parçanın anlık fiyatı.
                // r[j-i]: Geriye kalan (j-i) uzunluğunun DAHA ÖNCE HESAPLANMIŞ maksimum değeri.
                // Recursive çağrı yerine r dizisinden hazır değeri okuyoruz (Hız buradan geliyor).
                q = max(q, p[i-1] + r[j - i]);
            }
            else {
                // i > 10 ise o parçanın fiyatı yoktur, sadece kalanın (r[j-i]) değerine bakıyoruz.
                q = max(q, r[j - i]);
            }
        }
        // İç döngü bittiğinde, j uzunluğu için bulunan en iyi kazancı r dizisine kaydediyoruz.
        r[j] = q;
    }
    // Döngüler bitince, n uzunluğu için hesaplanan nihai değeri döndürüyoruz.
    return r[n];
}

// 3. YÖNTEM: ÇÖZÜMÜ KAYDEDEN GENİŞLETİLMİŞ BOTTOM-UP
// s[] dizisi parametre olarak geliyor, kesim noktalarını buna yazacağız.
int EXTENDED_BOTTOM_UP_CUT_ROD(int p[], int s[], int n) {
    // Gelirleri tutacak dizi.
    int r[n + 1];
    // 0 uzunluğu için gelir 0.
    r[0] = 0;

    // 1'den n'e kadar tüm uzunlukları hesapla (j: çubuk uzunluğu).
    for (int j = 1; j <= n; j++) {

        // q: j uzunluğu için şu ana kadar bulunan en iyi gelir.
        int q = INT_MIN;

        // 1'den j'ye kadar kesim noktalarını dene (i: kesilen parça).
        for (int i = 1; i <= j; i++) {

            // O anki denemenin (current_val) değerini hesaplayacağız.
            int current_val;

            // Fiyat listesi kontrolü.
            if (i <= 10) {
                // Kesilen parça fiyatı + kalan kısmın tablodaki değeri.
                current_val = p[i - 1] + r[j - i];
            } else {
                // Fiyat listesinde yoksa sadece kalanın değeri.
                current_val = r[j - i];
            }

            // Eğer bu kesimden elde edilen gelir (current_val), şu ana kadarki en iyiden (q) büyükse:
            if (q < current_val) {
                // En iyi geliri güncelle.
                q = current_val;

                // KRİTİK ADIM: j uzunluğundaki çubuk için en karlı ilk kesimin 'i' boyutu olduğunu kaydediyoruz.
                // Örneğin: s[j] = i -> "j boyundaki çubuğu önce i kadar kes".
                s[j] = i;
            }
        }
        // j uzunluğu için en iyi geliri tabloya yaz.
        r[j] = q;
    }
    // Maksimum geliri döndür.
    return r[n];
}

// ÇÖZÜMÜ YAZDIRAN FONKSİYON
void PRINT_CUT_ROD_SOLUTION(int p[], int s[], int n) {
    // Önce EXTENDED fonksiyonunu çağırıyoruz ki hem maksimum geliri bulsun
    // hem de s[] dizisini (kesim noktalarını) doldursun.
    int max_gelir = EXTENDED_BOTTOM_UP_CUT_ROD(p, s, n);

    // Maksimum geliri ekrana basıyoruz.
    printf("\nMaksimum Gelir: %d\n", max_gelir);
    printf("Kesilecek Parcalar:\n");

    // Çubuk bitene kadar (uzunluk 0'dan büyük olduğu sürece) döngü kuruyoruz.
    while (n > 0) {
        // s[n], n uzunluğundaki çubuk için yapılması gereken ilk kesim miktarını verir.
        printf("Kesim Parcasi = %d\n", s[n]);

        // Çubuktan o parçayı kesip atıyoruz. Geriye kalan uzunlukla döngü devam ediyor.
        // Örneğin 10 birimden 3 birim kestiysek, kalan 7 birim için s[7]'ye bakacağız.
        n = n - s[n];
    }
    // Alt satıra geç.
    printf("\n");
}

// 4. YÖNTEM: MEMOIZED (HAFIZALI / YUKARIDAN AŞAĞIYA) - BAŞLATICI FONKSİYON
int MEMOIZED_CUT_ROD(int p[],int n) {
    // Sonuçları saklayacak r dizisini (Cache) oluşturuyoruz.
    int r[n + 1];

    // Dizinin içini başlangıçta negatif bir sayıyla (INT_MIN) dolduruyoruz.
    // Bu, "henüz bu uzunluk için hesaplama yapmadık" anlamına gelecek.
    for(int i = 0; i <= n;i++) {
        r[i] = INT_MIN;
    }

    // Asıl işi yapacak yardımcı (AUX) fonksiyonu çağırıyoruz.
    return MEMOIZED_CUT_ROD_AUX(p,n,r);
}

// 4. YÖNTEM: MEMOIZED - YARDIMCI (AUX) FONKSİYON
int MEMOIZED_CUT_ROD_AUX(int p[],int n,int r[]) {
    // İLK KONTROL (MEMOIZATION):
    // Eğer r[n] negatif değilse (daha önce hesaplanıp buraya yazılmışsa),
    // tekrar hesaplama yapma, direkt dizideki değeri döndür.
    if(r[n] >= 0) {
        return r[n];
    }

    // Hesaplayacağımız maksimum değeri tutacak değişken.
    int q;

    // Temel durum: Uzunluk 0 ise gelir 0'dır.
    if(n == 0) {
        q = 0;
    }
    else {
        // Başlangıçta q'yu çok küçük bir sayı yapıyoruz.
        q = INT_MIN;

        // 1'den n'e kadar kesim ihtimallerini deniyoruz (Recursive döngü).
        for (int i = 1; i <= n;i++) {

            // Fiyat listesi kontrolü (10 elemanlı).
            if (i <= 10) {
                // p[i-1] + recursive çağrı.
                // Ama recursive çağrıyı bu AUX fonksiyonuna yapıyoruz ki r dizisini (hafızayı) kullansın.
                q = max(q, p[i-1] + MEMOIZED_CUT_ROD_AUX(p, n-i,r));
            }
            else {
                // Fiyat listesi dışındaysa sadece kalanın değerine bak.
                q = max(q, MEMOIZED_CUT_ROD_AUX(p, n-i,r));
            }
        }
    }

    // HESAPLANAN DEĞERİ KAYDETME:
    // Bulduğumuz sonucu r[n]'e yazıyoruz ki bir dahaki sefere tekrar hesaplamayalım.
    r[n] = q;

    // Sonucu döndür.
    return q;
}