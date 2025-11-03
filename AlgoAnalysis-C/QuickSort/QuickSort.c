/*
Yapılacaklar:
1. Standart Hızlı Sıralama (Quicksort) ve Bölümleme (Partition) fonksiyonları yazılacak.
   (Bu implementasyonda pivot olarak her zaman alt dizinin son elemanı seçilecektir).
2. Rastgele bir pivot değeri seçen Hızlı Sıralama (Randomize Quicksort) ve
   Rastgele Bölümleme (Randomize Partition) fonksiyonları yazılacak.
3. Bu kodda önceki 2 sıralamada dahil edilmiştir onları öbür dosyalarda anlattık
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


#define ARRAYSIZE 100000

void InsertionSort(int A[]);
void Merge(int A[], int p, int q, int r);
void MergeSort(int A[],int p, int r);

void QUICKSORT(int A[], int p, int r);
int PARTITION(int A[], int p, int r);

void RANDOMIZE_QUICKSORT(int A[], int p, int r);
int RANDOMIZE_PARTITION(int A[], int p, int r);

int main()
{
    int A1[ARRAYSIZE];
    int A2[ARRAYSIZE];
    int A3[ARRAYSIZE];
    int i;
    int num;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++)
    {
        num = rand();
        A1[i] = num;
        A2[i] = num;
        A3[i] = num;
    }
/*
    for(i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d: %d\n", i+1, A3[i]);
    }
*/
    clock_t start_t, end_t;
    double cpu_time_used;
    start_t = clock();
    InsertionSort(A1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Eklemeli Siralama): %f saniyedir.\n", cpu_time_used);

    start_t = clock();
    MergeSort(A2,0,ARRAYSIZE-1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Birlestirmeli Siralama): %f saniyedir.\n", cpu_time_used);

    start_t = clock();
    QUICKSORT(A3,0,ARRAYSIZE-1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Hizli Siralama): %f saniyedir.\n", cpu_time_used);

    start_t = clock();
    RANDOMIZE_QUICKSORT(A1,0,ARRAYSIZE-1); // Not: A1 dizisi zaten InsertionSort ile sıralandı.
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Random Hizli Siralama): %f saniyedir.\n", cpu_time_used);
/*
    for(i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d: %d\n", i+1, A3[i]);
    }

    return 0;
}
*/
void InsertionSort(int A[])
{
    int i,j,key;
    for(j = 1; j < ARRAYSIZE; j++)
    {
        key = A[j];
        i = j - 1;
        while(i >= 0 && A[i] > key)
        {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = key;
    }
}

void Merge(int A[], int p, int q, int r)
{
    int i,j,k;
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int *)malloc((n1+1)*sizeof(int));
    int *R = (int *)malloc((n2+1)*sizeof(int));

    for(i = 0; i < n1; i++)
    {
        L[i] = A[p+i];
    }
    for(j = 0; j < n2; j++)
    {
        R[j] = A[q+j+1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    for(k = p; k <= r; k++)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}

void MergeSort(int A[],int p, int r)
{
    int q;
    if(p < r)
    {
        q = (p + r) / 2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}

void QUICKSORT(int A[], int p, int r){
    int q; // Pivotun bölümlemeden sonraki doğru indeksini tutacak değişken

    // Özyinelemenin durma koşulu: Alt dizide 1'den fazla eleman varsa devam et.
    if (p < r) {
        // Diziyi pivot etrafında bölümlere ayır (küçükler, pivot, büyükler)
        // ve pivotun son dizideki konumunu (indeksini) 'q'ya ata.
        q = PARTITION(A,p,r);

        QUICKSORT(A,p,q-1); // Sol alt diziyi (pivottan küçükler) özyineli olarak sırala
        QUICKSORT(A,q+1,r); // Sağ alt diziyi (pivottan büyükler) özyineli olarak sırala
    }
}

int PARTITION(int A[], int p, int r){
    int x = A[r]; // Pivot elemanını (x) alt dizinin son elemanı olarak seç.

    // 'i' indeksi, pivottan küçük veya eşit olan elemanların oluşturduğu
    // bölgenin *son elemanının* indeksini izler.
    // Başlangıçta, bu bölgenin "dışında" (p-1) olarak ayarlanır.
    int i = p - 1;

    // 'j' indeksi, p'den r-1'e kadar (pivot hariç) tüm alt diziyi tarar.
    for(int j = p;j <= r - 1;j++) {
        // Eğer o an taranan eleman (A[j]) pivottan küçük veya eşitse...
        if (A[j] <= x) {
            i++; // 'Küçükler' bölgesinin sınırını bir ileri taşı.

            // A[j]'yi bu 'küçükler' bölgesinin içine al (A[i] ile yer değiştir).
            // Bu, A[j]'nin olması gereken yere (sol tarafa) taşınmasını sağlar.
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    // Tarama bittiğinde, pivot elemanını (A[r]) 'küçükler' bölgesinin
    // hemen sağına (i+1) yerleştir. Bu, pivotun son ve doğru konumudur.
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1; // Pivotun yeni ve son indeksini döndür.
}

int RANDOMIZE_PARTITION(int A[], int p, int r) {
    // p (dahil) ile r (dahil) arasında rastgele bir indeks üret.
    // Adım adım açıklama:
    // 1. (r - p) : 'p' ve 'r' arasındaki *aralık genişliğini* bulur. (Örn: p=5, r=10 ise sonuç 5)
    // 2. (r - p + 1) : Bu aralıktaki *toplam eleman sayısını* verir. (Örn: 5,6,7,8,9,10 -> 6 eleman var)
    // 3. rand() % (r - p + 1) : 0 ile (eleman sayısı - 1) arasında rastgele bir sayı üretir.
    //    (Örn: 0 ile 5 (dahil) arasında bir sayı)
    // 4. p + ... : Üretilen bu rastgele sayıyı (ofseti), başlangıç indeksimiz olan 'p'ye ekleriz.
    //    (Örn: p=5 ise, 5 + [0..5] -> [5..10] aralığında rastgele bir indeks elde edilir)
    int random = p + (rand() % (r - p + 1));

    // Rastgele seçilen elemanı (A[random]) son elemanla (A[r]) yer değiştir.
    // Bu, standart PARTITION fonksiyonunun bu rastgele elemanı pivot olarak
    // kullanmasını sağlar (çünkü PARTITION her zaman son elemanı pivot olarak alır).
    int temp = A[random];
    A[random] = A[r];
    A[r] = temp;

    // Şimdi standart bölümleme fonksiyonunu çağır.
    return PARTITION(A,p,r);
}

void RANDOMIZE_QUICKSORT(int A[], int p, int r){
    int q; // Pivotun bölümlemeden sonraki doğru indeksini tutacak değişken

    // Özyinelemenin durma koşulu
    if (p < r) {
        // Diziyi *rastgele seçilmiş* bir pivot etrafında bölümlere ayır
        // ve pivotun son konumunun indeksini 'q'ya ata.
        q = RANDOMIZE_PARTITION(A,p,r);

        // Sol alt diziyi (pivottan küçükler) özyineli olarak sırala
        RANDOMIZE_QUICKSORT(A,p,q-1);
        // Sağ alt diziyi (pivottan büyükler) özyineli olarak sırala
        RANDOMIZE_QUICKSORT(A,q+1,r);
    }
}