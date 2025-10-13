/* Yapılacaklar: Eklemeli sıralama fonksiyonun içeriğini doldurunuz ve
örnek sayı dizilerini sıralayıp çalıştığını gösteriniz.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define ARRAYSIZE 100

void InsertionSort(int A[]);

int main(){
    int numbers1[ARRAYSIZE];
    int i,j;

    //Rastgele sayı oluşturmayı aşağıdaki şekilde yapabiliriz.
    time_t t; // zaman değişkeni oluştur
    srand((unsigned) time(&t)); // Rastgele sayı oluşturucuyu bilgisayarın saati ile eşle

    for(i = 0; i < ARRAYSIZE; i++){
        numbers1[i] = rand(); // 0 ile max int arası sayı oluştur.
    }

    for(i = 0; i < ARRAYSIZE; i++) {
        printf("%d:\t%d\n",i+1,numbers1[i]);
    }

    clock_t start_t, end_t;
    double cpu_time_used;
    start_t = clock();
    InsertionSort(numbers1);
    end_t = clock();

    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Eklemeli Siralama): %f saniyedir.\n", cpu_time_used);

    printf("********************SIRALAMA SONRASI****************************\n");

   for(i = 0; i < ARRAYSIZE; i++) {
       printf("%d:\t%d\n",i+1,numbers1[i]);
   }
    return 0;

}

// Algoritmanın içini doldurunuz
void InsertionSort(int A[]){
for (int j = 1; j < ARRAYSIZE; j++) { //başlangıcın bir fazlasından sona kadar başla
    int key = A[j];//Sonraki eleman hep bizim anahtarımız
    int i = j - 1;//Anahtarın bir öncesini aldık
    //Anahtar, solundaki dizide yer bulana kadar yer değişimi yap
    while (i >= 0 && A[i] > key) {
        A[i+1] = A[i];
        i = i - 1;
    }
    A[i+1] = key;//Bir sonraki anahtara geç
}
}
