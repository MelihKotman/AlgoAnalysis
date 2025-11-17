import random
import time
import math  # MergeSort'taki 'sonsuz' (INT_MAX) değeri için
import sys

# Python'un özyineleme (recursion) limitini artıralım
# Quicksort ve Mergesort'un 100.000 eleman için çalışması gerekir.
# C'deki 'segmentation fault' hatasının Python'daki karşılığıdır.
sys.setrecursionlimit(200000)

# C kodundaki #define ARRAYSIZE 100000
ARRAY_SIZE = 200


# --- InsertionSort Fonksiyonu ---

def InsertionSort(A):
    """C'deki InsertionSort fonksiyonunun Python karşılığı."""
    # ARRAYSIZE yerine len(A) kullanmak daha esnektir
    for j in range(1, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
            A[i + 1] = A[i]
            i = i - 1
        A[i + 1] = key


# --- MergeSort Fonksiyonları ---

def Merge(A, p, q, r):
    """C'deki Merge fonksiyonunun Python karşılığı."""
    n1 = q - p + 1
    n2 = r - q

    # C'deki L ve R dizileri (Python'da list slicing ile)
    L = A[p: q + 1]
    R = A[q + 1: r + 1]

    # C'deki INT_MAX (nöbetçi/sentinel) değerleri
    L.append(math.inf)
    R.append(math.inf)

    i = 0
    j = 0
    # C'deki for(k = p; k <= r; k++)
    for k in range(p, r + 1):
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1

    # Python'da C'deki gibi 'free(L)' ve 'free(R)' yapmaya gerek yoktur.


def MergeSort(A, p, r):
    """C'deki MergeSort fonksiyonunun Python karşılığı."""
    if p < r:
        q = (p + r) // 2  # Python'da tam sayı bölmesi
        MergeSort(A, p, q)
        MergeSort(A, q + 1, r)
        Merge(A, p, q, r)


# --- Quicksort Fonksiyonları ---

def QUICKSORT(A, p, r):
    """C'deki QUICKSORT fonksiyonunun Python karşılığı."""
    if p < r:
        q = PARTITION(A, p, r)
        QUICKSORT(A, p, q - 1)
        QUICKSORT(A, q + 1, r)


def PARTITION(A, p, r):
    """C'deki PARTITION fonksiyonunun Python karşılığı."""
    x = A[r]
    i = p - 1
    # C'deki for(j = p; j < r; j++)
    for j in range(p, r):
        if A[j] <= x:
            i = i + 1
            # Python'da temp kullanmadan yer değiştirme (swap)
            A[i], A[j] = A[j], A[i]

    # Pivotu (x) doğru yerine taşı
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1


# --- Randomized Quicksort Fonksiyonları ---

def RANDOMIZED_QUICKSORT(A, p, r):
    """C'deki RANDOMIZED_QUICKSORT fonksiyonunun Python karşılığı."""
    if p < r:
        q = RANDOMIZED_PARTITION(A, p, r)
        RANDOMIZED_QUICKSORT(A, p, q - 1)
        RANDOMIZED_QUICKSORT(A, q + 1, r)


def RANDOMIZED_PARTITION(A, p, r):
    """C'deki RANDOMIZED_PARTITION fonksiyonunun Python karşılığı."""
    # C'deki (rand() % (r - p + 1)) + p ifadesi
    i = random.randint(p, r)
    # Pivotu (rastgele seçileni) son elemanla yer değiştir
    A[r], A[i] = A[i], A[r]
    # Standart PARTITION'ı çağır
    return PARTITION(A, p, r)


# --- Heap Sort Fonksiyonları ---
def Max_Heapify(A, heap_size, i):
    """
    Bir alt ağacın 'i' indeksindeki kök düğümünde
    Maks-Yığın (Max-Heap) özelliğini korur (onarmak için kullanılır).

    Varsayım: 'i'nin sol ve sağ alt ağaçları zaten birer Maks-Yığındır.

    Parametreler:
    A (list): Dizimiz (yığını temsil eder).
    heap_size (int): Yığının mevcut (mantıksal) boyutu (dizinin tamamı olmayabilir).
    i (int): Maks-Yığın özelliğinin kontrol edileceği kök indeksi.
    """

    # 0-tabanlı indeksleme için sol ve sağ çocukların indekslerini hesapla
    left = 2 * i + 1
    right = 2 * i + 2

    # Başlangıçta en büyük elemanın kök (i) olduğunu varsay
    largest = i

    # 1. Sol çocuk var mı (yığın sınırları içinde mi) VE
    #    sol çocuk kökten büyük mü?
    if left < heap_size and A[left] > A[largest]:
        largest = left
    else:
        # Bu 'else' bloğu aslında gereksizdir, çünkü 'largest' zaten
        # 'i' olarak ayarlanmıştı. C kodundan kalma olabilir.
        largest = i

    # 2. Sağ çocuk var mı (yığın sınırları içinde mi) VE
    #    sağ çocuk o anki 'largest' (kök veya sol çocuk) elemandan büyük mü?
    if right < heap_size and A[right] > A[largest]:
        largest = right

    # 3. Eğer en büyük eleman kök (i) değilse (yani çocuklardan biri büyükse):
    if largest != i:
        # Kök ile en büyük çocuğu yer değiştir (swap).
        temp = A[i]
        A[i] = A[largest]
        A[largest] = temp

        # Yer değiştirme işlemi alt ağacın yığın özelliğini bozmuş olabilir.
        # Bu yüzden, yer değiştirilen çocuğun indiği yeni konum (largest)
        # için Max_Heapify'ı özyineli olarak tekrar çağır.
        Max_Heapify(A, heap_size, largest)


def Build_Max_Heap(A, heap_size):
    """
    Rastgele dolu bir diziyi (A) bir Maks-Yığın haline getirir.

    Strateji: Dizideki son 'parent' (ebeveyn) düğümden başlayarak
    geriye doğru (köke kadar) tüm ebeveyn düğümler için
    Max_Heapify çağırılır.
    """

    # 0-tabanlı bir dizide, son ebeveynin indeksi (heap_size // 2 - 1)'dir.
    # Bu döngü, son ebeveynden başlayarak kök düğüme (indeks 0) kadar
    # geriye doğru gider.
    for i in range(heap_size // 2 - 1, -1, -1):
        # Her ebeveyn düğüm için Max_Heapify çağırarak
        # o düğümün alt ağacının yığın özelliğini sağladığından emin ol.
        Max_Heapify(A, heap_size, i)


def Heap_Sort(A):
    """
    Yığın Sıralaması (Heap Sort) algoritmasını çalıştırır.

    Algoritma 2 adımdan oluşur:
    1. Build_Max_Heap: Diziyi bir Maks-Yığın'a dönüştürür.
    2. Döngü:
       a. Yığının en büyük elemanını (A[0]) alıp dizinin sonuna (A[i]) taşır.
       b. Yığının boyutunu 1 azaltır.
       c. Kök (A[0]) için Max_Heapify çağırarak yığın özelliğini onarır.
    """
    # Başlangıçta yığının mantıksal boyutu tüm dizinin boyutudur.
    heap_size = len(A)

    # 1. Adım: Diziyi bir Maks-Yığın'a dönüştür.
    # Bu işlemden sonra A[0] dizideki en büyük eleman olur.
    Build_Max_Heap(A, heap_size)

    # 2. Adım: Yığından elemanları tek tek çıkar ve sırala
    # Döngü, dizinin son elemanından (n-1) başlayarak
    # ikinci elemanına (indeks 1) kadar geriye doğru gider.
    # (indeks 0'a gitmeye gerek yoktur, son eleman zaten yerindedir).
    for i in range(len(A) - 1, 0, -1):
        # a. En büyük elemanı (A[0]) al, dizinin sıralanmamış
        #    bölümünün sonuna (A[i]) taşı.
        temp = A[0]
        A[0] = A[i]
        A[i] = temp

        # b. Yığının mantıksal boyutunu 1 azalt.
        #    (A[i] artık sıralanmış bölgededir ve yığının parçası değildir).
        heap_size = heap_size - 1

        # c. Yer değiştirme sonucu A[0]'a gelen yeni eleman
        #    yığın özelliğini bozdu. Yığını kökten (0) başlayarak
        #    ve azalan boyuta göre (heap_size) onar.
        Max_Heapify(A, heap_size, 0)

    # Not: Bu fonksiyon doldurulduğunda, Max_Heapify özyineli olsa bile
    # derinliği O(log n) olacağı için stack sorunu yaşatmaz.


# --- ANA (main) FONKSİYON ---

# ... [Diğer tüm fonksiyonlar (InsertionSort, MergeSort, Quicksort, Heap_Sort)
# ...  önceki cevaptaki DÜZELTİLMİŞ halleriyle aynı kalacak] ...


def main():
    """C'deki main() fonksiyonunun Python karşılığı."""

    A1 = []
    random.seed(time.time())

    for _ in range(ARRAY_SIZE):
        A1.append(random.randint(0, 2 ** 31 - 1))

    # Diğer dizileri A1'in *kopyası* olarak oluştur
    A2 = A1.copy()
    A3 = A1.copy()
    A4= A1.copy()  # Heap Sort (Sırasız) için

    print(f"Dizi Boyutu: {ARRAY_SIZE}\n")

    # --- Eklemeli Sıralama ---
    #start_t = time.perf_counter()
    #InsertionSort(A1)
    #end_t = time.perf_counter()
    #cpu_time_used = end_t - start_t
    #print(f"Toplam gecen sure (Eklemeli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- Birleştirmeli Sıralama ---
    start_t = time.perf_counter()
    MergeSort(A2, 0, ARRAY_SIZE - 1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Birlestirmeli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- Hızlı Sıralama ---
    start_t = time.perf_counter()
    QUICKSORT(A3, 0, ARRAY_SIZE - 1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Hizli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- Yığın Sıralama ---
    # C'deki 'for(i = 0; i < ARRAYSIZE; i++)' döngüsü
    #for i in range(ARRAY_SIZE):
        # C'deki 'printf("%d: %d\n", i+1, A4[i]);'
    #    print(f"{i + 1}: {A4[i]}")

    start_t = time.perf_counter()
    Heap_Sort(A4)  # Sıralama işlemi
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"\nToplam gecen sure (Yigin Siralama): {cpu_time_used:.6f} saniyedir.\n")

    # C'deki 'for(i = 0; i < ARRAYSIZE; i++)' döngüsü
    #for i in range(ARRAY_SIZE):
        # C'deki 'printf("%d: %d\n", i+1, A4[i]);'
    #    print(f"{i + 1}: {A4[i]}")

# Python kodunu çalıştırmak için standart giriş noktası
if __name__ == "__main__":
    # ÖNEMLİ: Diğer tüm sıralama fonksiyonları (Heap_Sort dahil)
    # bu 'main' fonksiyonundan önce tanımlanmış olmalıdır.
    main()
