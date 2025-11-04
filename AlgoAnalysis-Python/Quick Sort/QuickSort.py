import random
import time
import math  # INT_MAX yerine math.inf kullanmak için
import random


# C kodundaki #define ARRAYSIZE 100000
ARRAY_SIZE = 100


def InsertionSort(A):
    for j in range(1, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
            A[i + 1] = A[i]
            i = i - 1
        A[i + 1] = key


def Merge(A, p, q, r):
    n1 = q - p + 1
    n2 = r - q

    L = A[p: q + 1]
    R = A[q + 1: r + 1]

    # INT_MAX (sentinel/nöbetçi) değerleri
    L.append(math.inf)
    R.append(math.inf)

    i = 0
    j = 0
    for k in range(p, r + 1):  # for(k = p; k <= r; k++)
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1




def MergeSort(A, p, r):

    if p < r:
        q = (p + r) // 2  # Python'da tam sayı bölmesi için // kullanılır
        MergeSort(A, p, q)
        MergeSort(A, q + 1, r)
        Merge(A, p, q, r)


# --- İstenen boş fonksiyonlar ---



def QUICKSORT(A, p, r):
    """
    Standart Hızlı Sıralama (Quicksort) algoritmasını özyineli olarak çalıştırır.
    Pivot olarak her zaman alt dizinin son elemanını kullanır (PARTITION fonksiyonu aracılığıyla).

    Parametreler:
    A (list): Sıralanacak dizi.
    p (int): Alt dizinin başlangıç indeksi.
    r (int): Alt dizinin bitiş indeksi.
    """

    # Özyinelemenin durma koşulu:
    # Alt dizide 1'den fazla eleman varsa (p < r) sıralamaya devam et.
    if (p < r):
        # q = PARTITION(A,p,r)
        # Diziyi pivot etrafında bölümlere ayır (küçükler, pivot, büyükler)
        # ve pivotun son dizideki doğru konumunu (indeksini) 'q'ya ata.
        q = PARTITION(A, p, r)

        # Sol alt diziyi (pivottan küçükler) özyineli olarak sırala
        QUICKSORT(A, p, q - 1)

        # Sağ alt diziyi (pivottan büyükler) özyineli olarak sırala
        QUICKSORT(A, q + 1, r)


def PARTITION(A, p, r):
    """
    Dizinin bir alt bölümünü (p'den r'ye) A[r]'yi pivot olarak kullanarak böler.
    Tüm küçük elemanları pivotun soluna, büyük elemanları sağına taşır.

    Parametreler:
    A (list): Sıralanacak dizi.
    p (int): Alt dizinin başlangıç indeksi.
    r (int): Alt dizinin bitiş indeksi (ve pivotun indeksi).

    Döndürür:
    int: Pivotun bölümleme sonrası dizideki son (doğru) indeksi.
    """

    # x = A[r]
    # Pivot elemanını (x) alt dizinin son elemanı olarak seç.
    x = A[r]

    # i = p - 1
    # 'i' indeksi, pivottan küçük veya eşit olan elemanların oluşturduğu
    # bölgenin *son elemanının* indeksini izler.
    # Başlangıçta, bu bölgenin "dışında" (p-1) olarak ayarlanır.
    i = p - 1

    # 'j' indeksi, p'den r-1'e kadar (pivot hariç) tüm alt diziyi tarar.
    for j in range(p, r, 1):
        # Eğer o an taranan eleman (A[j]) pivottan küçük veya eşitse...
        if (A[j] <= x):
            # i = i + 1
            # 'Küçükler' bölgesinin sınırını bir ileri taşı.
            i = i + 1

            # A[j]'yi bu 'küçükler' bölgesinin içine al (A[i] ile yer değiştir).
            # Bu, A[j]'nin olması gereken yere (sol tarafa) taşınmasını sağlar.
            temp = A[i]
            A[i] = A[j]
            A[j] = temp

    # Tarama bittiğinde, pivot elemanını (A[r]) 'küçükler' bölgesinin
    # hemen sağına (i+1) yerleştir. Bu, pivotun son ve doğru konumudur.
    temp = A[i + 1]
    A[i + 1] = A[r]
    A[r] = temp

    # return i + 1
    # Pivotun yeni ve son indeksini döndür.
    return i + 1


def RANDOMIZE_QUICKSORT(A, p, r):
    """
    Rastgele pivot seçimi kullanan Hızlı Sıralama (Quicksort) algoritması.
    Bu yaklaşım, en kötü durum ($O(n^2)$) performansından kaçınmayı sağlar.

    Parametreler:
    A (list): Sıralanacak dizi.
    p (int): Alt dizinin başlangıç indeksi.
    r (int): Alt dizinin bitiş indeksi.
    """

    # Özyinelemenin durma koşulu
    if (p < r):
        # q = RANDOMIZE_PARTITION(A,p,r)
        # Diziyi *rastgele seçilmiş* bir pivot etrafında bölümlere ayır
        # ve pivotun son konumunun indeksini 'q'ya ata.
        q = RANDOMIZE_PARTITION(A, p, r)

        # Sol alt diziyi (pivottan küçükler) özyineli olarak sırala
        RANDOMIZE_QUICKSORT(A, p, q - 1)

        # Sağ alt diziyi (pivottan büyükler) özyineli olarak sırala
        RANDOMIZE_QUICKSORT(A, q + 1, r)


def RANDOMIZE_PARTITION(A, p, r):
    """
    Alt diziden (p'den r'ye) rastgele bir elemanı pivot olarak seçer.
    Bu elemanı son elemanla (A[r]) değiştirir ve ardından standart
    PARTITION fonksiyonunu çağırır.

    Parametreler:
    A (list): Sıralanacak dizi.
    p (int): Alt dizinin başlangıç indeksi.
    r (int): Alt dizinin bitiş indeksi.

    Döndürür:
    int: Pivotun bölümleme sonrası dizideki son (doğru) indeksi.
    """

    # randomNum = random.randint(p, r)
    # p (dahil) ile r (dahil) arasında rastgele bir indeks üret.
    randomNum = random.randint(p, r)

    # Rastgele seçilen elemanı (A[randomNum]) son elemanla (A[r]) yer değiştir.
    # Bu, standart PARTITION fonksiyonunun bu rastgele elemanı pivot olarak
    # kullanmasını sağlar (çünkü PARTITION her zaman son elemanı pivot olarak alır).
    temp = A[randomNum]
    A[randomNum] = A[r]
    A[r] = temp

    # return PARTITION(A, p, r)
    # Şimdi standart bölümleme fonksiyonunu çağır.
    return PARTITION(A, p, r)
# --- C'deki main() fonksiyonunun Python karşılığı ---

def main():
    # C'deki srand((unsigned) time(&t));
    # Python'da random.seed() bu işi yapar (genellikle zamana göre otomatik başlar)
    # Ama C'dekiyle aynı mantıkta olması için time ile seed edebiliriz:
    random.seed(time.time())

    # Dizileri oluştur ve aynı rastgele sayılarla doldur
    A1 = []
    # C'deki rand() 0 ile RAND_MAX arasında üretir. Biz de büyük bir aralık seçelim.
    for _ in range(ARRAY_SIZE):
        A1.append(random.randint(0, 2 ** 31 - 1))

    # Python'da dizileri kopyalamak önemlidir.
    # A2 = A1 yazmak sadece referansı kopyalar!
    A2 = A1.copy()
    A3 = A1.copy()

    # --- InsertionSort Zamanlaması ---
    # C'deki clock() yerine time.perf_counter() daha hassastır
    start_t = time.perf_counter()
    InsertionSort(A1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Eklemeli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- MergeSort Zamanlaması ---
    start_t = time.perf_counter()
    MergeSort(A2, 0, ARRAY_SIZE - 1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Birlestirmeli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- QUICKSORT Zamanlaması ---
    start_t = time.perf_counter()
    QUICKSORT(A3, 0, ARRAY_SIZE - 1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Hizli Siralama): {cpu_time_used:.6f} saniyedir.")

    # --- RANDOMIZE_QUICKSORT Zamanlaması ---
    # Not: C kodundaki gibi, bu sıralama zaten sıralanmış olan A1 dizisi üzerinde çalıştırılıyor.
    start_t = time.perf_counter()
    RANDOMIZE_QUICKSORT(A1, 0, ARRAY_SIZE - 1)
    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t
    print(f"Toplam gecen sure (Random Hizli Siralama): {cpu_time_used:.6f} saniyedir.")


# Python'da main fonksiyonunu çağırmak için standart yöntem:
if __name__ == "__main__":
    main()