import math  # Matematiksel işlemler ve sonsuzluk değeri (-math.inf) için gerekli kütüphane.


# Yardımcı Fonksiyon: İki sayıdan büyük olanı bulur.
# Python'da gömülü 'max()' fonksiyonu vardır ama algoritma mantığını görmek için elle yazılmış.
def max(num1, num2):
    if num1 >= num2:
        return num1  # num1 büyük veya eşitse onu döndür.
    else:
        return num2  # Değilse num2'yi döndür.


# =============================================================================
# 1. YÖNTEM: RECURSIVE (ÖZYİNELEMELİ / KABA KUVVET) ÇÖZÜM
# =============================================================================
def CUT_ROD(p, n):
    # Temel Durum (Base Case):
    # Eğer çubuk uzunluğu 0 ise kazanç 0'dır. Özyinelemeyi durduran nokta.
    if n == 0:
        return 0

    # q değişkenini eksi sonsuz (-math.inf) olarak başlatıyoruz.
    # Bu değişken, o anki uzunluk (n) için bulunacak maksimum kazancı tutacak.
    q = -math.inf

    # i döngüsü: 1'den n'e kadar (n dahil) olası ilk kesim noktalarını dener.
    # range(1, n + 1, 1) -> 1, 2, ..., n
    for i in range(1, n + 1, 1):

        # Fiyat listemiz (p) sadece 10 elemanlı olduğu için (index 0-9),
        # eğer kesilecek parça (i) 10'dan büyükse listede fiyatı yoktur.
        if i <= 10:
            # p[i-1]: i uzunluğundaki parçanın fiyatı (Liste 0 tabanlı olduğu için i-1).
            # CUT_ROD(p, n-i): Kalan parçanın (n-i) en iyi fiyatını bulmak için
            # fonksiyon kendini tekrar çağırır (Recursive).
            # Bu toplam ile mevcut en iyi 'q' karşılaştırılır.
            q = max(q, p[i - 1] + CUT_ROD(p, n - i))
        else:
            # Eğer i > 10 ise, o parçanın satış fiyatı yoktur (0 kabul edilir).
            # Sadece kalanın (n-i) getirisine bakılır.
            q = max(q, CUT_ROD(p, n - i))

    # Bulunan en yüksek kazancı döndür.
    return q


# =============================================================================
# 2. YÖNTEM: BOTTOM-UP (AŞAĞIDAN YUKARIYA) DP ÇÖZÜMÜ
# =============================================================================
def BOTTOMUP_CUT_ROD(p, n):
    # Sonuçları saklamak için bir liste (tablo) oluşturuyoruz.
    # n uzunluğu için n+1 boyutlu liste lazım (indeks 0..n).
    # Başlangıçta hepsini 0 yapıyoruz. r[0] zaten 0 olmalı.
    r = [0] * (n + 1)

    # j döngüsü: Problemi 1 birimden başlayarak n birime kadar sırayla çözer.
    # j: Şu an çözümünü hesapladığımız alt çubuk uzunluğu.
    for j in range(1, n + 1, 1):

        # Bu 'j' uzunluğu için maksimum kazancı tutacak geçici değişken.
        q = - math.inf

        # i döngüsü: j uzunluğundaki çubuk için olası ilk kesim noktalarını (1..j) dener.
        for i in range(1, j + 1, 1):

            # Fiyat listesi sınır kontrolü (Maksimum 10 birimlik fiyat var).
            if i <= 10:
                # p[i-1]: Kesilen parçanın fiyatı.
                # r[j-i]: Kalan parçanın (j-i) DAHA ÖNCE HESAPLANMIŞ en iyi fiyatı.
                # Recursive çağrı yok, r listesinden hazır değeri okuyoruz.
                q = max(q, p[i - 1] + r[j - i])
            else:
                # i > 10 ise fiyat listesinde yok, sadece kalanın değerine bak.
                q = max(q, r[j - i])

        # İç döngü bittiğinde, j uzunluğu için bulunan en iyi kazancı r tablosuna kaydet.
        r[j] = q

    # n uzunluğu için hesaplanan nihai değeri döndür.
    return r[n]


# =============================================================================
# 3. YÖNTEM: ÇÖZÜMÜ KAYDEDEN GENİŞLETİLMİŞ BOTTOM-UP
# =============================================================================
def EXTENDED_BOTTOMUP_CUT_ROD(p, s, n):
    # current_val değişkeninin kapsamını belirtmek için (Python'da burada zorunlu değil
    # ama C mantığını korumak için yazılmış olabilir).
    global current_val

    # Gelirleri tutacak r tablosu.
    r = [0] * (n + 1)

    # j: 1'den n'e kadar tüm uzunlukları hesapla.
    for j in range(1, n + 1, 1):
        q = - math.inf

        # i: 1'den j'ye kadar kesim noktalarını dene.
        for i in range(1, j + 1, 1):

            # O anki denemenin değerini hesapla.
            if i <= 10:
                # Parça fiyatı + Kalanın tablodaki değeri
                current_val = p[i - 1] + r[j - i]
            else:
                # Fiyat yoksa sadece kalanın değeri
                current_val = r[j - i]

            # Eğer bu kesimden elde edilen gelir, şu ana kadarki en iyiden (q) büyükse:
            if q < current_val:
                q = current_val  # Maksimum geliri güncelle.
                s[j] = i  # KRİTİK: j uzunluğu için en iyi ilk kesimin 'i' olduğunu kaydet.
                # s[j] = i -> "j boyundaki çubuğu önce i kadar kes".

        # j uzunluğu için en iyi geliri tabloya yaz.
        r[j] = q

    # Maksimum geliri döndür (s listesi referans ile geldiği için dolmuş oldu).
    return r[n]


# =============================================================================
# ÇÖZÜMÜ YAZDIRAN YARDIMCI FONKSİYON
# =============================================================================
def PRINT_CUT_ROD_SOLUTION(p, s, n):
    # Önce EXTENDED fonksiyonunu çağırıp hem max geliri alıyoruz hem de s listesini dolduruyoruz.
    max_gelir = EXTENDED_BOTTOMUP_CUT_ROD(p, s, n)

    # f-string kullanarak yazdırma.
    print(f"\nMaksimum Gelir: {max_gelir}\n")
    print("Kesilecek Parçalar\n")

    # Geri izleme (Backtracking) döngüsü.
    # Çubuk bitene kadar (n > 0) devam et.
    while n > 0:
        # s[n], n uzunluğundaki çubuk için en iyi ilk kesim miktarını verir.
        print(f"Kesim Parçası {s[n]}")

        # Kesilen parçayı toplam uzunluktan düş, kalan için döngüye devam et.
        n = n - s[n]

    print("\n")


# =============================================================================
# 4. YÖNTEM: MEMOIZED (HAFIZALI) - BAŞLATICI FONKSİYON
# =============================================================================
def MEMOIZED_CUT_ROD(p, n):
    # Sonuçları saklayacak r listesini (Cache) oluşturuyoruz.
    r = [0] * (n + 1)

    # Listenin içini başlangıçta eksi sonsuz ile dolduruyoruz.
    # Bu, "henüz bu uzunluk için hesaplama yapmadık" anlamına gelir.
    for i in range(0, n + 1, 1):
        r[i] = -math.inf

    # Asıl işi yapacak yardımcı (AUX) fonksiyonu çağırıyoruz.
    return MEMOIZED_CUT_ROD_AUX(p, n, r)


# =============================================================================
# 4. YÖNTEM: MEMOIZED - YARDIMCI (AUX) FONKSİYON
# =============================================================================
def MEMOIZED_CUT_ROD_AUX(p, n, r):
    # İLK KONTROL (MEMOIZATION):
    # Eğer r[n] eksi sonsuz değilse (yani 0 veya daha büyükse),
    # bu değer daha önce hesaplanmıştır. Tekrar hesaplama, direkt döndür.
    if r[n] >= 0:
        return r[n]

    # Temel durum: Uzunluk 0 ise gelir 0'dır.
    if n == 0:
        q = 0
    else:
        # Hesaplamaya başlıyoruz, q'yu çok küçük başlat.
        q = -math.inf

        # 1'den n'e kadar kesim ihtimallerini dene (Recursive).
        for i in range(1, n + 1, 1):
            if i <= 10:
                # Recursive çağrıyı yine AUX fonksiyonuna yapıyoruz ki r listesini kullansın.
                q = max(q, p[i - 1] + MEMOIZED_CUT_ROD_AUX(p, n - i, r))
            else:
                q = max(q, MEMOIZED_CUT_ROD_AUX(p, n - i, r))

    # HESAPLANAN DEĞERİ KAYDETME:
    # Bulunan sonucu r[n]'e yaz ki sonra tekrar kullanılabilsin.
    r[n] = q

    # Sonucu döndür.
    return q


# =============================================================================
# ANA BLOK (MAIN)
# =============================================================================
if __name__ == "__main__":
    # Fiyat listesi (index 0 -> 1 birimlik, index 9 -> 10 birimlik).
    p = [1, 5, 8, 9, 10, 17, 17, 20, 24, 30]

    # Kullanıcıdan input alma.
    uzunluk = int(input("Lütfen bir çubuk uzunluğu giriniz.."))

    # Kesim noktalarını tutacak s listesi (sadece PRINT fonksiyonu için lazım olacak).
    kesim_noktasi = [0] * (uzunluk + 1)

    # 1. Bottom-Up testi
    print(f"Maksimum Kazanç(BOTTOMUP_CUT_ROD) = {BOTTOMUP_CUT_ROD(p, uzunluk)}")

    # 2. Çözüm yazdırma testi
    PRINT_CUT_ROD_SOLUTION(p, kesim_noktasi, uzunluk)

    # 3. Memoized testi
    print(f"Maksimum Kazanç(MEMOIZED_CUT_ROD) = {MEMOIZED_CUT_ROD(p, uzunluk)}")

    # 4. Recursive testi (Büyük sayılarda çok yavaş çalışır!)
    print(f"Maksimum Kazanç(CUT_ROD) = {CUT_ROD(p, uzunluk)}")