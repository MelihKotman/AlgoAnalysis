#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 200
int minimum(int A[]);
int maximum(int A[]);
void minmax(int A[]);

int main()
{
    int dizi[ARRAYSIZE];
    time_t t;
    int i;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++)
    {
        dizi[i] = rand() % 100;
    }
    minmax(dizi);
    return 0;
}

int minimum(int A[]){
    int min = A[0];
    int sayac = 0;
    for (int i = 1; i < ARRAYSIZE; i++) {
        if (A[i] < min) {
            min = A[i];
            sayac++;
        }
    }
    return min;
}

int maximum(int A[]){
    int max = A[0];
    int sayac = 0;
    for (int i = 1; i < ARRAYSIZE; i++) {
        if (A[i] > max) {
            max = A[i];
            sayac++;
        }
    }
    return max;
}

void minmax(int A[]){
    int min,max;
    int sayac = 0;
    int start;
    if (ARRAYSIZE % 2 == 1) {
        min = max = A[0];
        start = 1;
    }
    else if (ARRAYSIZE % 2 == 0) {
        sayac++;
        if (A[0] >= A[1]) {
            max = A[0];
            min = A[1];
        }
        else if (A[0] < A[1]) {
            max = A[1];
            min = A[0];
        }
        start = 2;
    }
    for (start; start < ARRAYSIZE; start += 2) {
        sayac++;
        if (A[start + 1] > A[start]) {
            if (max < A[start + 1]) {
                max = A[start + 1];
            }
        }else{
            if (max < A[start]) {
                max = A[start];
            }
        }
        sayac++;
        if (A[start] < min) {
            min = A[start];
        }
        sayac++;
        if (A[start + 1] < min) {
            min = A[start + 1];
        }

    }
    printf("Min = %d\t Max = %d\tSayac = %d",min,max,sayac);
}
