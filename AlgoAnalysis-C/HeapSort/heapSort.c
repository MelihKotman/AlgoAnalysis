/*
Yapılacaklar:
1. Yığın Sıralaması (Heap Sort) için gerekli olan 'Heap' struct yapısı tanımlanacak.
2. 'Max_Heapify' fonksiyonu yazılacak: Bu fonksiyon, bir alt ağacın
   Maks-Yığın özelliğini korumasını sağlar.
3. 'Build_Max_Heap' fonksiyonu yazılacak: Bu fonksiyon, rastgele bir diziyi
   'Max_Heapify' kullanarak bir Maks-Yığına dönüştürür.
4. 'Heap_Sort' fonksiyonu yazılacak: Bu fonksiyon, 'Build_Max_Heap'
   ile yığını kurar ve ardından diziyi yerinde (in-place) sıralar.
5. main() fonksiyonuna Heap_Sort zamanlaması eklenecek.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ARRAYSIZE 100000

// Yığın (Heap) veri yapısını tanımlıyoruz.
// 'A' dizinin kendisini (veriyi) işaret eder.
// 'size' yığının o anki mantıksal boyutunu tutar.
typedef struct Heap
{
    int size;
    int *A;
}Heap;

// Fonksiyon prototipleri
void InsertionSort(int A[]);
void Merge(int A[], int p, int q, int r);
void MergeSort(int A[],int p, int r);

void QUICKSORT(int A[], int p, int r);
int PARTITION(int A[], int p, int r);

void RANDOMIZED_QUICKSORT(int A[], int p, int r);
int RANDOMIZED_PARTITION(int A[], int p, int r);

// --- Yığın Sıralaması Protototipleri ---
void Max_Heapify(Heap myHeap, int i);
void Build_Max_Heap(Heap myHeap);
void Heap_Sort(Heap myHeap);

int main()
{
    // 4 algoritma için 4 kopya dizi
    int A1[ARRAYSIZE];
    int A2[ARRAYSIZE];
    int A3[ARRAYSIZE];
    int A4[ARRAYSIZE];
    int i;
    int num;
    time_t t;
    srand((unsigned) time(&t)); // Rastgele sayı üretecini başlat

    // Tüm dizileri aynı rastgele sayılarla doldur
    for(i = 0; i < ARRAYSIZE; i++)
    {
        num = rand();
        A1[i] = num;
        A2[i] = num;
        A3[i] = num;
        A4[i] = num;
    }

    clock_t start_t, end_t;
    double cpu_time_used;

    // 1. Eklemeli Sıralama Testi
    start_t = clock();
    InsertionSort(A1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Eklemeli Siralama): %f saniyedir.\n", cpu_time_used);

    // 2. Birleştirmeli Sıralama Testi
    start_t = clock();
    MergeSort(A2,0,ARRAYSIZE-1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Birlestirmeli Siralama): %f saniyedir.\n", cpu_time_used);

    // 3. Hızlı Sıralama Testi
    start_t = clock();
    QUICKSORT(A3,0,ARRAYSIZE-1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Hizli Siralama): %f saniyedir.\n", cpu_time_used);

    // 4. Yığın Sıralaması Testi
    start_t = clock();
    Heap myHeap;      // Yığın yapısını oluştur
    myHeap.A = A4;     // Yığının dizisi A4'ü göstersin
    myHeap.size = ARRAYSIZE; // Yığının başlangıç boyutu
    Heap_Sort(myHeap); // Sıralamayı başlat
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Yigin Siralama): %f saniyedir.\n", cpu_time_used);

    return 0;
}

// ... InsertionSort, MergeSort, Merge, QUICKSORT, PARTITION,
// ... RANDOMIZED_QUICKSORT, RANDOMIZED_PARTITION fonksiyonları
// ... (Bu fonksiyonlar önceki adımlarda mevcuttu, değişiklik yok)

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
    free(L); // Ayrılan hafızayı serbest bırak
    free(R); // Ayrılan hafızayı serbest bırak
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

void QUICKSORT(int A[], int p, int r)
{
    int q;
    if(p < r)
    {
       q = PARTITION(A, p, r);
       QUICKSORT(A, p, q-1);
       QUICKSORT(A, q+1, r);
    }
}

int PARTITION(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    int j;
    int temp;
    for(j = p; j < r; j++)
    {
       if(A[j] <= x)
       {
          i = i + 1;
          temp = A[i];
          A[i] = A[j];
          A[j] = temp;
       }
    }
    temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

void RANDOMIZED_QUICKSORT(int A[], int p, int r)
{
    int q;
    if(p < r)
    {
       q = RANDOMIZED_PARTITION(A, p, r);
       RANDOMIZED_QUICKSORT(A, p, q-1);
       RANDOMIZED_QUICKSORT(A, q+1, r);
    }
}

int RANDOMIZED_PARTITION(int A[], int p, int r)
{
    int i = (rand() % (r - p + 1)) + p;
    int temp = A[r];
    A[r] = A[i];
    A[i] = temp;
    return PARTITION(A,p,r);
}

// --- Yığın Sıralaması Fonksiyonları (Yorumlu) ---

/**
 * @brief Bir alt ağacın 'i' indeksindeki kök düğümünde
 * Maks-Yığın (Max-Heap) özelliğini korur.
 * Varsayım: 'i'nin sol ve sağ alt ağaçları zaten birer Maks-Yığındır.
 * * @param myHeap Yığın yapısı (diziyi ve boyutunu içerir).
 * @param i Maks-Yığın özelliğinin kontrol edileceği kök indeksi.
 */
void Max_Heapify(Heap myHeap, int i){
    // Not: C'de diziler 0 tabanlıdır.
    // Bir 'i' düğümünün sol çocuğu: 2*i + 1
    // Bir 'i' düğümünün sağ çocuğu: 2*i + 2
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i; // En büyük elemanın indeksini (başlangıçta kök) tutar.

    // 1. Sol çocuk var mı (yığın sınırları içinde mi) VE
    //    sol çocuk kökten (A[i]) büyük mü?
    if (left < myHeap.size && myHeap.A[left] > myHeap.A[i]) {
       largest = left;
    }
    else {
       largest = i;
    }

    // 2. Sağ çocuk var mı (yığın sınırları içinde mi) VE
    //    sağ çocuk o anki 'largest' (kök veya sol çocuk) elemandan büyük mü?
    if (right < myHeap.size && myHeap.A[right] > myHeap.A[largest]) {
       largest = right;
    }

    // 3. Eğer en büyük eleman kök (i) değilse (yani çocuklardan biri büyükse):
    if (largest != i) {
       // Kök ile en büyük çocuğu yer değiştir (swap).
       int temp = myHeap.A[i];
       myHeap.A[i] = myHeap.A[largest];
       myHeap.A[largest] = temp;

       // Yer değiştirme işlemi alt ağacın yığın özelliğini bozmuş olabilir.
       // Bu yüzden, yer değiştirilen çocuğun indiği yeni konum (largest)
       // için Max_Heapify'ı özyineli olarak tekrar çağır.
       Max_Heapify(myHeap, largest);
    }
}

/**
 * @brief Rastgele dolu bir diziyi bir Maks-Yığın haline getirir.
 * Strateji: Dizideki son 'parent' (ebeveyn) düğümden başlayarak
 * geriye doğru (köke kadar) tüm ebeveyn düğümler için Max_Heapify çağırılır.
 * * @param myHeap Yığın yapısı.
 */
void Build_Max_Heap(Heap myHeap){
    // n elemanlı (0 tabanlı) bir dizide, son ebeveynin indeksi
    // (myHeap.size / 2) - 1 'dir.
    // (myHeap.size / 2)'den başlamak da çalışır (tamsayı bölmesi nedeniyle).
    // Kodunuza sadık kalıyoruz:
    for (int i = myHeap.size / 2; i >= 0; i--) {
        Max_Heapify(myHeap, i);
    }
}

/**
 * @brief Yığın Sıralaması algoritmasını çalıştırır (yerinde sıralama).
 * * @param myHeap Yığın yapısı.
 */
void Heap_Sort(Heap myHeap){
    // 1. Adım: Diziyi bir Maks-Yığın'a dönüştür.
    // Bu adımdan sonra, dizinin en büyük elemanı A[0]'dadır.
    Build_Max_Heap(myHeap);

    // 2. Adım: Yığından elemanları tek tek çıkar ve sırala
    // Dizinin son elemanından (ARRAYSIZE-1) başlayarak
    // ikinci elemanına (indeks 1) kadar döngüye gir.
    for (int i = ARRAYSIZE - 1; i >= 1; i--) {

       // a. En büyük elemanı (A[0]) al, dizinin sonuna (A[i]) taşı.
       // A[i]'deki elemanı da A[0]'a taşı (bu, yığını geçici olarak bozar).
       int temp = myHeap.A[0];
       myHeap.A[0] = myHeap.A[i];
       myHeap.A[i] = temp;

       // b. Yığının mantıksal boyutunu 1 azalt.
       // (A[i] artık sıralanmış bölgededir ve yığının parçası değildir).
       myHeap.size = myHeap.size - 1;

       // c. Yeni kök (A[0]) için Max_Heapify çağırarak
       //    yığın özelliğini onar.
       Max_Heapify(myHeap, 0);
    }
}