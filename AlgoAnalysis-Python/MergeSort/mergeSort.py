import random
import time
import sys

ARRAYSIZE = 100

def Merge(A, p, q, r):
    n1 = q - p + 1 # İlk yarımın sayısını hesapla
    n2 = r - q # Son yarımın sayısını hesapladık.
    L = list() # Solu boş dizi olarak oluşturduk.
    R = list() # Sağı boş dizi olarak oluşturduk.
    for i in range(0,n1): # Sol diziye ana dizinin ilk yarısını ekledik.
        L.append(A[p+i])
    for j in range(0,n2): # Sağ diziye ana dizinin son yarısını ekledik.
        R.append(A[q+j+1])
    L.append(sys.maxsize) # Sentinel (Gözcü) Değer
    R.append(sys.maxsize) # Sentinel (Gözcü) Değer

    i = j = 0 #Her iki dizi için başlangıç noktası belirledik.
    for k in range(p,r+1): # k = başlangıç olacak ve bitişe kadar bir artacak
        if(L[i] <= R[j]): # Eğer sağ soldan büyük ya da eşitse solu ana diziye yazacaktır.
            A[k] = L[i]
            i = i + 1
        else: # Tam tersinde ise sağı ana diziye yazacaktır.
            A[k] = R[j]
            j = j + 1

# Tek elemanlı dizi oluşuncaya kadar yinelemeli devam et
def MergeSort(A, p, r):
    if(p < r):
        q = (p + r) // 2
        MergeSort(A,p,q)
        MergeSort(A,q+1,r)
        Merge(A,p,q,r)


def main():
    A2 = [0] * ARRAYSIZE

    random.seed(time.time())

    for i in range(ARRAYSIZE):
        num = random.randint(0, sys.maxsize)
        A2[i] = num

    for i in range(ARRAYSIZE):
        print(f"{i+1}: {A2[i]}")

    start_t = time.time()
    # MergeSort çağrılma şekli değiştirilebilir.
    MergeSort(A2, 0, ARRAYSIZE - 1)
    end_t = time.time()

    cpu_time_used = end_t - start_t
    print(f"Toplam geçen süre (Birleştirmeli Sıralama): {cpu_time_used:.6f} saniyedir.")

    for i in range(ARRAYSIZE):
        print(f"{i+1}: {A2[i]}")


if __name__ == "__main__":
    main()