#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPRAZ 5
#define YUKARI 4
#define SOLA 3

void LCS_LENGTH(char * s1, char *s2, int **b, int **c);
void PRINT_LCS(int **b, char * s1, int i, int j);

int main(){

    char *s1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char *s2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    printf("s1: %s\n",s1);
    printf("s2: %s\n",s2);
    int m = strlen(s1);
    int n = strlen(s2);
    int i,j;

    int **b = (int **)malloc((m+1) * sizeof(int *));
    for (i=0; i<m+1; i++)
        b[i] = (int *)malloc((n+1) * sizeof(int));
    int **c = (int **)malloc((m+1) * sizeof(int *));
    for (i=0; i<m+1; i++)
        c[i] = (int *)malloc((n+1) * sizeof(int));


    LCS_LENGTH(s1,s2,b,c);
    printf("S3: ");
    PRINT_LCS(b,s1,m,n);
    printf("\n");

    return 0;
}

// --- MOTOR KISMI: Tabloları Doldurma ---
void LCS_LENGTH(char * s1, char *s2, int **b, int **c){

    // 1. Stringlerin gerçek uzunluklarını al
    int s1_length = strlen(s1);
    int s2_length = strlen(s2);

    // 2. Tablonun "Duvarlarını" Ör (Initialization)
    // Boş bir string ile herhangi bir stringin LCS'si 0'dır.
    // Bu yüzden 0. satır ve 0. sütun tamamen 0 yapılır.
    for (int i = 0; i <= s1_length; i++) {
        c[i][0] = 0;
    }
    for (int i = 0; i <= s2_length; i++) {
        c[0][i] = 0;
    }

    // 3. Ana Döngü: Tabloyu doldurmaya başla
    // i: 1'den m'ye (Tablo satırları)
    // j: 1'den n'ye (Tablo sütunları)
    for (int i = 1; i <= s1_length; i++) {
        for (int j = 1; j <= s2_length; j++) {

            // --- KRİTİK NOKTA (BİT YENİĞİ) ---
            // Tabloda 'i'nci sıradayız ama String'de 'i-1'e bakmalıyız.
            // Çünkü Tablo 1'den, String 0'dan başlar.
            if (s1[i - 1] == s2[j - 1]) {

                // EŞLEŞME VAR! (Harfler aynı)
                // Sol-Üst köşedeki değere 1 ekle.
                c[i][j] = c[i - 1][j- 1] + 1;
                b[i][j] = 5; // Yön: Diagonal (Çapraz/Sol-Üst)
            }
            // EŞLEŞME YOKSA: En büyük komşuyu seç
            else if (c[i - 1][j] >= c[i][j - 1]) {

                // Üstteki değer daha büyük (veya eşit)
                c[i][j] = c[i - 1][j];
                b[i][j] = 4; // Yön: Up (Yukarı)
            }
            else {

                // Soldaki değer daha büyük
                c[i][j] = c[i][j - 1];
                b[i][j] = 3; // Yön: Left (Sol)
            }
        }
    }
}

// --- RAPORTÖR KISMI: Sonucu Yazdırma ---
void PRINT_LCS(int **b, char * s1, int i, int j){

    // 1. Taban Durumu (Base Case)
    // Duvara (0. satır veya 0. sütun) çarparsak dur.
    if (i == 0 || j == 0) {
        return;
    }

    // 2. Yönleri Takip Et (Backtracking)
    if (b[i][j] == 5) { // Eğer yön Çapraz ise...
        // Bu harf (X[i-1]) ortak harftir!

        // ÖNCE: Daha önceki harfleri bulmak için geriye (çapraz) git.
        PRINT_LCS(b,s1,i - 1, j - 1);

        // SONRA: Harfi yazdır.
        // (Bu sıra sayesinde tersten değil, düzgün sırada yazarız)
        printf("%c",s1[i - 1]);
    }
    else if (b[i][j] == 4) { // Eğer yön Yukarı ise...
        // Bu harf eşleşmedi, yukarı git.
        PRINT_LCS(b,s1,i-1,j);
    }
    else if (b[i][j] == 3){ // Eğer yön Sol ise...
        // Bu harf eşleşmedi, sola git.
        PRINT_LCS(b,s1,i,j-1);
    }
}
