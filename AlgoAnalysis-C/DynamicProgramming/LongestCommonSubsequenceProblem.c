#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100 // Tabloların maksimum boyutu

// Global Tablolar
// c: Uzunlukları tutar
// b: Yönleri tutar ('D': Diagonal/Çapraz, 'U': Up/Yukarı, 'L': Left/Sol)
int c[MAX_LEN][MAX_LEN];
char b[MAX_LEN][MAX_LEN];

// Prototipler
void LCS_LENGTH(char X[], char Y[]);
void PRINT_LCS(char X[], int i, int j);

int main() {
    // Slayt Sayfa 19'daki Örnek DNA Dizileri
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";

    printf("Dizi X: %s\n", X);
    printf("Dizi Y: %s\n", Y);

    // 1. Tabloları Doldur
    LCS_LENGTH(X, Y);

    // 2. Sonucu Yazdır
    printf("\nEn Uzun Ortak Altdizi (LCS): ");
    PRINT_LCS(X, strlen(X), strlen(Y)); // Sondan başa doğru yazdırır

    printf("\nLCS Uzunlugu (c tablosundan): %d\n", c[strlen(X)][strlen(Y)]);

    return 0;
}

// --- MOTOR KISMI: Tabloları Doldurma ---
void LCS_LENGTH(char X[], char Y[]) {
    // 1. Stringlerin gerçek uzunluklarını al
    int m = strlen(X);
    int n = strlen(Y);

    // 2. Tablonun "Duvarlarını" Ör (Initialization)
    // Boş bir string ile herhangi bir stringin LCS'si 0'dır.
    // Bu yüzden 0. satır ve 0. sütun tamamen 0 yapılır.
    for (int i = 0; i <= m; i++) {
        c[i][0] = 0;
    }
    for (int i = 0; i <= n; i++) {
        c[0][i] = 0;
    }

    // 3. Ana Döngü: Tabloyu doldurmaya başla
    // i: 1'den m'ye (Tablo satırları)
    // j: 1'den n'ye (Tablo sütunları)
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            // --- KRİTİK NOKTA (BİT YENİĞİ) ---
            // Tabloda 'i'nci sıradayız ama String'de 'i-1'e bakmalıyız.
            // Çünkü Tablo 1'den, String 0'dan başlar.
            if (X[i - 1] == Y[j - 1]) {
                // EŞLEŞME VAR! (Harfler aynı)
                // Sol-Üst köşedeki değere 1 ekle.
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'D'; // Yön: Diagonal (Çapraz/Sol-Üst)
            }
            // EŞLEŞME YOKSA: En büyük komşuyu seç
            else if (c[i - 1][j] >= c[i][j - 1]) {
                // Üstteki değer daha büyük (veya eşit)
                c[i][j] = c[i - 1][j];
                b[i][j] = 'U'; // Yön: Up (Yukarı)
            }
            else {
                // Soldaki değer daha büyük
                c[i][j] = c[i][j - 1];
                b[i][j] = 'L'; // Yön: Left (Sol)
            }
        }
    }
}

// --- RAPORTÖR KISMI: Sonucu Yazdırma ---
void PRINT_LCS(char X[], int i, int j) {
    // 1. Taban Durumu (Base Case)
    // Duvara (0. satır veya 0. sütun) çarparsak dur.
    if (i == 0 || j == 0) {
        return;
    }

    // 2. Yönleri Takip Et (Backtracking)
    if (b[i][j] == 'D') { // Eğer yön Çapraz ise...
        // Bu harf (X[i-1]) ortak harftir!

        // ÖNCE: Daha önceki harfleri bulmak için geriye (çapraz) git.
        PRINT_LCS(X, i - 1, j - 1);

        // SONRA: Harfi yazdır.
        // (Bu sıra sayesinde tersten değil, düzgün sırada yazarız)
        printf("%c", X[i - 1]);
    }
    else if (b[i][j] == 'U') { // Eğer yön Yukarı ise...
        // Bu harf eşleşmedi, yukarı git.
        PRINT_LCS(X, i - 1, j);
    }
    else if (b[i][j] == 'L'){ // Eğer yön Sol ise...
        // Bu harf eşleşmedi, sola git.
        PRINT_LCS(X, i, j - 1);
    }
}