/* Yapılacaklar: Birleştirmeli sıralama fonksiyonun içeriğini doldurunuz ve
örnek sayı dizilerini sıralayıp çalıştığını gösteriniz.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ARRAYSIZE 100


void Merge(int A[], int p, int q, int r);
void MergeSort(int A[],int p, int r);

int main()
{
    int A1[ARRAYSIZE];
    int A2[ARRAYSIZE];
    int i;
    int num;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++){
        num = rand();
        A1[i] = num;
        A2[i] = num;
    }

    for(i = 0; i < ARRAYSIZE; i++){
        printf("%d: %d\n", i+1, A2[i]);
    }

    clock_t start_t, end_t;
    double cpu_time_used;
    start_t = clock();
    // MergeSort cagirilma seklini degistirebilirsiniz.
    MergeSort(A2,0,ARRAYSIZE-1);
    end_t = clock();
    cpu_time_used = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Toplam gecen sure (Birlestirmeli Siralama): %f saniyedir.\n", cpu_time_used);

    for(i = 0; i < ARRAYSIZE; i++){
        printf("%d: %d\n", i+1, A2[i]);
    }

    return 0;
}

void Merge(int A[], int p, int q, int r){
    int n1 = q - p + 1; //İlk yarım dizinin boyutu (yarısı-başlangıç+1)
    int n2 = r - q; //İkinci yarım dizinin boyutu (bitiş-yarısı)
    //İKİ BİÇİMDE DİZİ OLUŞTURULABİLİR
    //NOT: Oluştururken sentinel değerlerinde olacağı için bir fazlası kadar ekle!
    //1-Sabit dizi oluşturabilirsiniz.
    //int L[n1+1],R[n2+1];
    //2-Ya da malloc ile bellek işlemi yapabilirsiniz.
    int *L = (int *)malloc((n1 + 1) * sizeof(int));
    int *R = (int *)malloc((n2 + 1) * sizeof(int));
    //İlk yarım diziyi sol dizisine kopyalıyoruz.
    for (int i = 0; i < n1; i++){
        L[i] = A[p+i];
    }
    //Son yarım diziyi sağ dizisine kopyalıyoruz.
    for (int j = 0; j < n2; j++){
        R[j] = A[q+j+1];
    }

    L[n1] = INT_MAX; //Sentinel (Gözcü) Değer
    R[n2] = INT_MAX; //Sentinel (Gözcü) Değer

    int i = 0,j = 0; //Her iki dizi için başlangıç noktası belirledik.
    //k = başlangıç olacak ve bitişe kadar bir artacak
    for (int k = p; k <= r; k++){
        if (L[i] <= R[j]) {//Eğer sağ soldan büyük ya da eşitse solu ana diziye yaz
            A[k] = L[i];
            i = i + 1;
        }
        else { //Tam tersi ise sağdakini ana diziye yaz
            A[k] = R[j];
            j = j + 1;
        }
    }
    //Eğer (yukardaki 2. kısım) malloc() kullanımı varsa mutlaka free() kullanılmalıdır.
    free(L);
    free(R);
}

void MergeSort(int A[],int p, int r){ //tek elemanlı dizi oluşuncaya kadar yinelemeli devam et
    if (p < r) {
        int q = (p + r)/ 2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
