#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<limits.h>

#define ARRAYSIZE 100000
#define COUNTING 10000

void COUNTING_SORT(int A[], int B[], int k);

int main()
{
    int numbers[ARRAYSIZE];
    int sorted_numbers[ARRAYSIZE];
    int i,j;
    int num;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++)
    {
        num = rand()%COUNTING;
        numbers[i] = num;
    }

/*    for(i = 0; i < ARRAYSIZE; i++)
        printf("%d: %d\n", i+1, numbers[i]);
*/
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    COUNTING_SORT(numbers,sorted_numbers,COUNTING);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by Counting Sort: %f sec\n", cpu_time_used);
/*    for(i = 0; i < ARRAYSIZE; i++)
        printf("%d: %d\n", i+1, sorted_numbers[i]);
    return 0;
*/
}
void COUNTING_SORT(int A[], int B[], int k){

    // 1. ADIM: SAYAÇ DİZİSİNİ OLUŞTURMA VE SIFIRLAMA
    // Sayıların frekansını (kaç tane olduğunu) tutacak 'c' dizisi oluşturuluyor.
    int c[k];

    // c dizisinin içinde rastgele (çöp) değerler kalmasın diye
    // baştan sona tüm elemanları 0'a eşitliyoruz.
    for (int i = 0; i < k;i++) {
        c[i] = 0;
    }

    // 2. ADIM: FREKANSLARI SAYMA (COUNTING)
    // Asıl dizimiz olan A dizisini baştan sona geziyoruz.
    for (int j = 0; j < ARRAYSIZE; j++) {
        // A[j] değerini bir indis olarak kullanıyoruz.
        // Örneğin sayı 5 ise, c dizisinin 5. indisindeki değeri 1 artırıyoruz.
        // Böylece o sayıdan kaç tane olduğunu kaydetmiş oluyoruz.
        c[A[j]] = c[A[j]] + 1;
    }

    // 3. ADIM: KÜMÜLATİF TOPLAM (POZİSYON BELİRLEME)
    // Burada c dizisini güncelliyoruz. Her elemanı kendinden öncekiyle topluyoruz.
    // Bu işlem, sayıların sıralı dizide (B dizisinde) hangi son indiste
    // yer alacağını belirlememizi sağlar.
    for (int i = 1; i < k;i++) {
        c[i] = c[i] + c[i - 1];
    }

    // 4. ADIM: SIRALI DİZİYİ (B) OLUŞTURMA
    // A dizisini SONDAN başa doğru tarıyoruz (Algoritmanın kararlı olması için).
    for (int j = ARRAYSIZE - 1; j >= 0;j--) {

        // A[j]'deki sayıyı alıyoruz, c dizisinden bu sayının nereye konulacağına bakıyoruz.
        // İndisler 0'dan başladığı için 1 çıkarıp B dizisindeki yerine koyuyoruz.
        B[c[A[j]]- 1] = A[j];

        // Aynı sayıdan bir tane daha gelirse, bir önceki pozisyona (sola)
        // yerleşmesi için sayacın değerini 1 azaltıyoruz.
        c[A[j]] = c[A[j]] - 1;
    }

}

