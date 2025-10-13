# Yapılacaklar: InsertionSort fonksiyonunun içeriğini doldurunuz ve
# örnek sayı dizilerini sıralayıp çalıştığını gösteriniz.

import random
import time

ARRAYSIZE = 100

def InsertionSort(A):
    for j in range(1,ARRAYSIZE): # Başlangıcın bir fazlasından sona kadar başladık.
        key = A[j-1] # Sonraki eleman hep bizim anahtarımızdır.
        i = j - 1 # Anahtar, solundaki dizide yer bulana kadar yer değişimi yapacağız.
        while i > 0 and A[i-1] > key:
            A[i] = A[i-1]
            i -= 1
        A[i] = key # Bİr sonraki anahtara geçtik.


def main():
    numbers1 = [random.randint(0, 2**31 - 1) for _ in range(ARRAYSIZE)]

    for i, num in enumerate(numbers1, start=1):
        print(f"{i}:\t{num}")

    start_t = time.time()
    InsertionSort(numbers1)
    end_t = time.time()
    cpu_time_used = end_t - start_t

    print(f"Toplam gecen sure (Eklemeli Siralama): {cpu_time_used:.6f} saniyedir.")
    print("********************SIRALAMA SONRASI****************************")

    for i, num in enumerate(numbers1, start=1):
        print(f"{i}:\t{num}")

if __name__ == "__main__":
    main()