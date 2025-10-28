import random
import sys
import time
from dataclasses import dataclass
from statistics import kde_random


# C'deki 'typedef struct subArray' yapısının Python'daki en modern karşılığı
# bir 'dataclass' kullanmaktır.
@dataclass
class SubArray:
    alis_gunu: int
    satis_gunu: int
    kar: int

# Toplam fiyat sayısı
ARRAYSIZE = 200


# Fonksiyon tanımı: 'A' (değişim dizisi), 'low', 'mid' ve 'high' indekslerini alır.
# Bir 'SubArray' nesnesi (alış, satış, kar bilgisi) döndürür.
def find_max_crossing_subarray(A: list, low: int, mid: int, high: int) -> SubArray:
    # --- Sol Tarafı Tarama ---
    # Sol tarafta bulunacak en iyi toplamı saklar.
    # '-float('inf')' (eksi sonsuz) ile başlatılır ki,
    # bulunan ilk değer (negatif bile olsa) bundan büyük olsun.
    leftSum = -float('inf')
    # Döngü içinde o anki sol toplamı tutmak için geçici bir değişken.
    sumLeft = 0
    # En iyi sol toplamın başladığı günü (indeksi) saklayacak değişken.
    maxLeft = mid  # Güvenli bir başlangıç değeri olarak 'mid' atanır.
    # Bir döngü başlat: 'i' değişkeni 'mid' (orta) noktasından başlar
    # ve 'low' (en sol) noktaya doğru geriye doğru ('-1' adımlarla) gider.
    # 'low - 1' yazılır çünkü range() bitiş değerini dahil etmez (yani 'low' dahil edilir).
    for i in range(mid, low - 1, -1):
        # Geriye doğru giderken, o günün değerini anlık toplama (sumLeft) ekle.
        sumLeft = sumLeft + A[i]
        # Eğer o anki toplam (sumLeft), bugüne kadar bulunan en iyi sol toplamdan (leftSum) daha büyükse...
        if (sumLeft > leftSum):
            # ...yeni en iyi sol toplamı 'sumLeft' olarak güncelle.
            leftSum = sumLeft
            # ...ve bu en iyi toplamın başladığı günü 'i' olarak kaydet.
            maxLeft = i

    # --- Sağ Tarafı Tarama ---
    # Sağ tarafta bulunacak en iyi toplamı saklar ('-float('inf')' ile başlar).
    rightSum = -float('inf')
    # Sağ taraf için anlık toplamı tutan geçici değişken.
    sumRight = 0
    # En iyi sağ toplamın bittiği günü (indeksi) saklayacak değişken.
    maxRight = mid + 1  # Güvenli bir başlangıç değeri olarak 'mid + 1' atanır.
    # Bir döngü başlat: 'j' değişkeni 'mid + 1' (ortanın bir sağı) noktasından başlar
    # ve 'high' (en sağ) noktaya doğru ileriye doğru ('1' adımlarla) gider.
    # 'high + 1' yazılır çünkü range() bitiş değerini dahil etmez (yani 'high' dahil edilir).
    for j in range(mid + 1, high + 1, 1):
        # İleriye doğru giderken, o günün değerini anlık sağ toplama (sumRight) ekle.
        sumRight = sumRight + A[j]
        # Eğer o anki sağ toplam (sumRight), bugüne kadar bulunan en iyi sağ toplamdan (rightSum) daha büyükse...
        if (sumRight > rightSum):
            # ...yeni en iyi sağ toplamı 'sumRight' olarak güncelle.
            rightSum = sumRight
            # ...ve bu en iyi toplamın bittiği günü 'j' olarak kaydet.
            maxRight = j

    # --- Sonuçları Birleştirme ---
    # Bulunan en iyi sol başlangıç günü (maxLeft), en iyi sağ bitiş günü (maxRight)
    # ve bu iki parçanın toplam kârı (leftSum + rightSum) ile yeni bir SubArray nesnesi oluştur ve döndür.
    return SubArray(alis_gunu=maxLeft,
                    satis_gunu=maxRight,
                    kar=leftSum + rightSum)


# Ana "Böl ve Yönet" fonksiyonu. 'A' dizisini, 'low' (başlangıç) ve 'high' (bitiş)
# indekslerini alır ve o aralıktaki en kârlı 'subArray' yapısını döndürür.
def find_maximum_subarray(A: list, low: int, high: int) -> SubArray:
    # --- TEMEL DURUM (BASE CASE) ---
    # Özyinelemenin (recursion) durma noktasıdır.
    # Eğer 'high' ve 'low' indeksleri eşitse, dizide sadece 1 eleman kalmış demektir.
    if (high == low):

        # O tek elemanın bilgilerini (alış=low, satış=high, kar=A[low])
        # içeren bir SubArray nesnesi oluştur ve döndür.
        return SubArray(alis_gunu=low,
                        satis_gunu=high,
                        kar=A[low])

    # --- ÖZYİNELEMELİ DURUM (RECURSIVE CASE) ---
    else:  # Eğer dizide 1'den fazla eleman varsa:
        # --- 1. BÖL (DIVIDE) ADIMI ---
        # Dizinin tam orta noktasının indeksini hesapla (Python'da '//' tam sayı bölmesi yapar).
        mid = (high + low) // 2

        # --- 2. YÖNET (CONQUER) ADIMI ---
        # 3 olası senaryo için alt problemleri çöz:
        # 1. Senaryo (Sol Taraf): Fonksiyonun *kendisini* sadece sol yarı
        # ('low'dan 'mid'e kadar) için tekrar çağır. Gelen sonuca 'leftRes' de.
        leftRes = find_maximum_subarray(A, low, mid)
        # 2. Senaryo (Sağ Taraf): Fonksiyonun *kendisini* sadece sağ yarı
        # ('mid + 1'den 'high'a kadar) için tekrar çağır. Gelen sonuca 'rightRes' de.
        rightRes = find_maximum_subarray(A, mid + 1, high)
        # 3. Senaryo (Ortayı Kesen): Yukarıda açıkladığımız 'crossing' fonksiyonunu çağırarak
        # 'mid' noktasını kesen en iyi sonucu bul. Gelen sonuca 'crossRes' de.
        crossRes = find_max_crossing_subarray(A, low, mid, high)

        # --- 3. BİRLEŞTİR (COMBINE) ADIMI ---
        # Elimizdeki 3 sonucu ('leftRes', 'rightRes', 'crossRes') karşılaştır:
        # Eğer sol tarafın kârı, hem sağ tarafın kârından hem de ortayı kesen kârdan
        # büyük veya eşitse...
        if (leftRes.kar >= rightRes.kar and leftRes.kar >= crossRes.kar):
            # ...en iyi sonuç 'leftRes'tir, onu döndür.
            return leftRes
        # Değilse, bir de sağ tarafın kârına bak:
        # Eğer sağ tarafın kârı, hem sol tarafın kârından hem de ortayı kesen kârdan
        # büyük veya eşitse...
        elif (rightRes.kar >= rightRes.kar and rightRes.kar >= crossRes.kar):
            # ...en iyi sonuç 'rightRes'tir, onu döndür.
            return rightRes
        # Eğer en iyi kâr ne solda ne de sağdaysa,
        # o zaman en iyi kâr ortayı kesen 'crossRes' olmalıdır.
        else:
            # ...'crossRes'i döndür.
            return crossRes


# Fonksiyon tanımı: 'A' (fiyatlar listesi) adında bir liste alır
# ve bir 'SubArray' nesnesi (alış günü, satış günü, kâr bilgisi) döndürür.
def brute_force(A: list) -> SubArray:
    # Listenin toplam uzunluğunu (toplam gün sayısı) hesapla ve bir değişkende sakla.
    length_of_array = len(A)
    # Bulunacak en yüksek kârı saklamak için bir değişken oluştur.
    # '0' ile başlatılır, çünkü en kötü durumda (sürekli zarar) hiç işlem yapmayız ve kâr 0 olur.
    totalKar = 0
    # En iyi kârın bulunduğu "alış gününü" saklamak için bir değişken oluştur.
    alisGunu = 0
    # En iyi kârın bulunduğu "satış gününü" saklamak için bir değişken oluştur.
    satisGunu = 0
    # Dıştaki döngü: Olası "alış günlerini" ('i') gezer.
    # 0. günden başlar ve son güne kadar gider.
    for i in range(length_of_array):
        # İçteki döngü: Olası "satış günlerini" ('j') gezer.
        # Her zaman alış gününden ('i') bir sonraki günden ('i + 1') başlar,
        # çünkü satmak için önce almış olmanız gerekir.
        for j in range(i + 1, length_of_array):
            # Kâr kontrolü:
            # O anki satış fiyatı (A[j]) ile alış fiyatı (A[i]) arasındaki fark (kâr),
            # bugüne kadar bulduğumuz en iyi kârdan (totalKar) daha büyük mü?
            if (A[j] - A[i] > totalKar):
                # Eğer daha iyiyse, yeni en iyi kârı güncelle.
                totalKar = A[j] - A[i]
                # Bu kârı getiren "alış gününü" ('i') kaydet.
                alisGunu = i
                # Bu kârı getiren "satış gününü" ('j') kaydet.
                satisGunu = j
    # Tüm olası alış (i) ve satış (j) günü çiftlerini kontrol ettikten sonra,
    # bulunan en iyi sonuçları (alisGunu, satisGunu, totalKar)
    # içeren yeni bir SubArray nesnesi oluştur ve bunu döndür.
    return SubArray(alis_gunu=alisGunu,
                    satis_gunu=satisGunu,
                    kar=totalKar)


# --- Ana Program ---

def main():
    """
    C kodundaki main() fonksiyonunun Python karşılığı.
    """

    # Fiyatları ve değişimleri tutacak listeler (Python'da diziler yerine liste kullanılır)
    fiyatlar = []

    # C'deki srand((unsigned) time(&t)) ile aynı işlevi görür.
    # Rastgele sayı üretecini başlatır.
    random.seed()

    # Fiyatları oluşturalım (1 ile 120 arasında rastgele fiyatlar)
    # Bu, C'deki ilk for döngüsünün "Pythonic" (Python'a özgü) karşılığıdır.
    fiyatlar = [random.randint(1, 120) for _ in range(ARRAYSIZE)]

    # Fiyat değişimlerini hesaplayalım.
    # C'deki gibi 0. indeksi boş bırakıp 1. indeksten başlamak için
    # önce listeyi 0 ile doldurup sonra değerleri atıyoruz.
    degisim = [0] * ARRAYSIZE
    for i in range(1, ARRAYSIZE):
        degisim[i] = fiyatlar[i] - fiyatlar[i - 1]

    # Fiyatları yazdırma döngüsü
    # NOT: 400,000 satır yazdırmak konsolu dondurabilir, bu yüzden
    # bu bölümü yorum satırı haline getirdim.
    #print("--- Fiyat Listesi ---")
    #for i, fiyat in enumerate(fiyatlar):
    #    print(f"{i}: {fiyat}")
    #print("---------------------")

    # --- Böl ve Yönet Yöntemi ---
    print("\nBöl ve Yönet Yöntemi Başlatılıyor...")

    # zaman.perf_counter(), C'deki clock() fonksiyonundan daha
    # hassas bir zaman ölçümü sağlar.
    start_t = time.perf_counter()

    # Böl ve Yönet fonksiyonu 'degisim' dizisi üzerinde çalışır.
    # C kodunuzdaki gibi 1. indeksten (ARRAYSIZE-1)'e kadar olan kısmı alıyoruz.
    res = find_maximum_subarray(degisim, 1, ARRAYSIZE - 1)

    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t

    print(f"Toplam geçen süre (Böl ve yönet yöntemi): {cpu_time_used:.6f} saniyedir.")

    # Sonuçların Yorumlanması (Böl ve Yönet):
    # 'degisim' dizisindeki j'den k'ya olan toplam = fiyatlar[k] - fiyatlar[j-1]
    # Bu yüzden 'alisGunu' (j), alım gününü j-1 olarak gösterir.
    print(f"Al: {res.alis_gunu - 1}")
    print(f"Sat: {res.satis_gunu}")
    print(f"Kar: {res.kar}")

    # --- Kaba Kuvvet Yöntemi ---
    print("\nKaba Kuvvet Yöntemi Başlatılıyor...")
    start_t = time.perf_counter()

    # Kaba kuvvet fonksiyonu doğrudan 'fiyatlar' dizisi üzerinde çalışır.
    res2 = brute_force(fiyatlar)

    end_t = time.perf_counter()
    cpu_time_used = end_t - start_t

    print(f"Toplam geçen süre (Kaba kuvvet): {cpu_time_used:.6f} saniyedir.")

    # Sonuçların Yorumlanması (Kaba Kuvvet):
    # Bu fonksiyon doğrudan fiyat listesinden alım ve satım günlerini bulur.
    print(f"Al: {res2.alis_gunu}")
    print(f"Sat: {res2.satis_gunu}")
    print(f"Kar: {res2.kar}")


# Python betiği doğrudan çalıştırıldığında 'main' fonksiyonunu çağırır.
# Bu, C'deki 'int main() { ... }' bloğunun standart Python karşılığıdır.
if __name__ == "__main__":
    main()