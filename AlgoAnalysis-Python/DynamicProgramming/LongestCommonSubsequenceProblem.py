# Maksimum dizi boyutu sabiti (C tarzı statik bellek yönetimi simülasyonu)
MAX_LEN = 100

# c tablosu: LCS uzunluklarını saklar. c[i][j], X'in ilk i karakteri ile
# Y'nin ilk j karakteri arasındaki LCS uzunluğudur.
c = [[0] * MAX_LEN for _ in range(MAX_LEN)]

# b tablosu: Yön bilgilerini (okları) saklar. Çözümü geriye doğru izlemek için kullanılır.
# 'D' (Diagonal/Çapraz), 'U' (Up/Yukarı), 'L' (Left/Sol) değerlerini alır.
b = [[0] * MAX_LEN for _ in range(MAX_LEN)]


# =============================================================================
# FONKSİYON: LCS_LENGTH
# AMAÇ: X ve Y dizilerinin LCS uzunluğunu hesaplar ve tabloları doldurur.
# =============================================================================
def LCS_LENGTH(X, Y):
    m = len(X)  # X dizisinin uzunluğu
    n = len(Y)  # Y dizisinin uzunluğu

    # 1. ADIM: Tablonun ilk sütununu 0 yap (Y boş küme ise LCS 0'dır).
    # range(0, m + 1) -> 0'dan m'e kadar.
    for i in range(0, m + 1, 1):
        c[i][0] = 0

    # 2. ADIM: Tablonun ilk satırını 0 yap (X boş küme ise LCS 0'dır).
    # range(0, n + 1) -> 0'dan n'e kadar.
    for j in range(0, n + 1, 1):
        c[0][j] = 0

    # 3. ADIM: Tabloları doldurma (Ana Döngü)
    # i, X dizisindeki karakterleri; j, Y dizisindeki karakterleri temsil eder.
    # Dikkat: Tablo indeksleri 1'den başlar, dizi indeksleri 0'dan.
    # Bu yüzden c[i][j] için X[i-1] ve Y[j-1]'e bakarız.
    for i in range(1, m + 1, 1):
        for j in range(1, n + 1, 1):

            # DURUM 1: Karakterler Eşleşirse (X[i-1] == Y[j-1])
            if X[i - 1] == Y[j - 1]:
                # Sol üst çaprazdaki (i-1, j-1) değeri 1 artır.
                # Çünkü bu karakteri LCS'ye ekledik.
                c[i][j] = c[i - 1][j - 1] + 1
                b[i][j] = 'D'  # Yön: Diagonal (Sol Üst Çapraz)

            # DURUM 2: Eşleşme Yoksa ve Üstteki Değer Soldakinden Büyük veya Eşitse
            elif c[i - 1][j] >= c[i][j - 1]:
                # Üstteki değeri aynen al (uzunluk değişmez).
                c[i][j] = c[i - 1][j]
                b[i][j] = 'U'  # Yön: Up (Yukarı)

            # DURUM 3: Eşleşme Yoksa ve Soldaki Değer Daha Büyükse
            else:
                # Soldaki değeri aynen al.
                c[i][j] = c[i][j - 1]
                b[i][j] = 'L'  # Yön: Left (Sol)


# =============================================================================
# FONKSİYON: PRINT_LCS
# AMAÇ: b tablosundaki yönleri takip ederek LCS'yi ekrana yazdırır.
# YÖNTEM: Geri izleme (Backtracking) ve Recursion (Özyineleme).
# =============================================================================
def PRINT_LCS(X, i, j):
    # Temel Durum: Tablonun kenarına (0. satır veya 0. sütun) ulaştıysak dur.
    if i == 0 or j == 0:
        return

    # Eğer yön 'D' (Diagonal) ise:
    # Bu, X[i-1] ve Y[j-1]'in eşleştiği ve LCS'nin bir parçası olduğu anlamına gelir.
    if b[i][j] == 'D':
        # Önce özyinelemeli olarak daha öncesini yazdır (Sıralı çıktı için).
        PRINT_LCS(X, i - 1, j - 1)
        # Dönüşte karakteri yazdır.
        print(f"{X[i - 1]}")

    # Eğer yön 'U' (Yukarı) ise:
    # Bu karakter eşleşmedi, yukarıdaki hücreye git.
    elif b[i][j] == 'U':
        PRINT_LCS(X, i - 1, j)

    # Eğer yön 'L' (Sol) ise:
    # Bu karakter eşleşmedi, soldaki hücreye git.
    elif b[i][j] == 'L':
        PRINT_LCS(X, i, j - 1)


# =============================================================================
# ANA BLOK (MAIN)
# =============================================================================
if __name__ == "__main__":
    # Test Dizileri
    # X = "ABCBDAB"
    X = ['A', 'B', 'C', 'B', 'D', 'A', 'B']
    # Y = "BDCABA"
    Y = ['B', 'D', 'C', 'A', 'B', 'A']

    print(f"Dizi X: {X}")
    print(f"Dizi Y: {Y}")

    # Uzunlukları hesapla ve tabloları doldur
    LCS_LENGTH(X, Y)

    print("\n En Uzun Ortak Altdizi (LCS):")
    # PRINT_LCS fonksiyonunu dizilerin son indeksinden başlatıyoruz.
    PRINT_LCS(X, len(X), len(Y))

    # c tablosunun sağ alt köşesi (c[m][n]) her zaman LCS'nin uzunluğunu verir.
    print(f"\nLCS Uzunluğu (c tablosundan): {c[len(X)][len(Y)]}")