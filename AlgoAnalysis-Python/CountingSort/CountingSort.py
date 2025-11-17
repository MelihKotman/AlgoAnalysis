import random
import time
from array import array

ARRAYSIZE = 1000
COUNTING = 1000


def counting_sort(A, B, k):
    # 1. ADIM: SAYAÇ DİZİSİNİ OLUŞTURMA (INITIALIZATION)
    # 0'dan k-1'e kadar olan sayıların frekansını tutacak C listesini oluşturuyoruz.
    # Python'da '[0] * k' diyerek içi 0 dolu, k boyutunda bir liste tek satırda açılır.
    # (C'deki döngüyle 0'a eşitleme işleminin Pythoncası budur).
    C = [0] * k

    # 2. ADIM: FREKANSLARI SAYMA (COUNTING)
    # Giriş dizisi A'yı baştan sona tarıyoruz.
    for j in range(0, ARRAYSIZE):
        # A[j] değerini indeks olarak kullanıp, C dizisindeki karşılığını 1 artırıyoruz.
        # Yani "bu sayıdan bir tane daha buldum" diyerek sayacı güncelliyoruz.
        C[A[j]] = C[A[j]] + 1

    # 3. ADIM: KÜMÜLATİF TOPLAM (POZİSYON BELİRLEME)
    # C dizisindeki her elemanı kendinden öncekiyle topluyoruz.
    # Bu işlem sonucunda C[i], i sayısının sıralı B dizisinde yerleşeceği
    # "en son indeksi" (limit pozisyonunu) belirtir hale gelir.
    for i in range(1, k):
        C[i] = C[i] + C[i - 1]

    # 4. ADIM: SIRALI DİZİYİ (B) OLUŞTURMA (PLACING)
    # A dizisini SONDAN başa doğru tarıyoruz.
    # range(başlangıç, bitiş-hariç, adım) -> (ARRAYSIZE-1'den başla, -1'e kadar git, 1 azalt)
    # Sondan başlamamızın sebebi algoritmanın "kararlı" (stable) olmasını sağlamaktır.
    for j in range(ARRAYSIZE - 1, -1, -1):
        # Mantık zinciri:
        # 1. A[j]'yi al (Sıralanacak sayıyı seç).
        # 2. C[A[j]] değerine bak (Bu sayı B dizisinde hangi pozisyonda olmalı?).
        # 3. İndeksler 0'dan başladığı için 1 çıkar ve B dizisine yerleştir.
        B[C[A[j]] - 1] = A[j]

        # Aynı sayıdan bir daha gelirse (döngü devam ederken),
        # bir solundaki boşluğa yerleşsin diye pozisyon bilgisini 1 azaltıyoruz.
        C[A[j]] = C[A[j]] - 1


if __name__ == "__main__":
    numbers = [0] * ARRAYSIZE
    sorted_numbers = [0] * ARRAYSIZE

    for i in range(ARRAYSIZE):
        numbers[i] = random.randint(0, COUNTING - 1)

    for i in range(ARRAYSIZE):
        print(f"{i+1}: {numbers[i]}")

    start = time.time()
    counting_sort(numbers, sorted_numbers, COUNTING)
    end = time.time()

    cpu_time_used = end - start
    print(f"Time taken by Counting Sort: {cpu_time_used} sec")

    for i in range(ARRAYSIZE):
        print(f"{i+1}: {sorted_numbers[i]}")