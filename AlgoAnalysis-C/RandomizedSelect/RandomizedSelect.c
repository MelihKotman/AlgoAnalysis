#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<limits.h>

#define ARRAYSIZE 2000000

void RANDOMIZED_QUICKSORT(int A[], int p, int r);
int PARTITION(int A[], int p, int r);
int RANDOMIZED_PARTITION(int A[], int p, int r);
int RANDOMIZED_SELECT(int A[], int p, int r, int i);

int main()
{
    int numbers5[ARRAYSIZE];
    int i,j;
    int num;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0; i < ARRAYSIZE; i++)
    {
        num = rand();
        numbers5[i] = num;
    }
/*    for (int i = 0; i< ARRAYSIZE; i++) {
        printf("%d\n",numbers5[i]);
    }
*/
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int res = RANDOMIZED_SELECT(numbers5,0,ARRAYSIZE-1,10);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by Randomized select: %f sec\n", cpu_time_used);
    printf("res: %d\n", res);

    return 0;
}

int RANDOMIZED_PARTITION(int A[], int p, int r)
{
    int i = (rand() % (r - p + 1)) + p;
    //printf("p: %d, r: %d, i: %d\n,",p,r,i);
    int temp = A[r];
    A[r] = A[i];
    A[i] = temp;
    return PARTITION(A,p,r);
}

int PARTITION(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    int j;
    int temp;
    for(j = p; j < r; j++)
    {
        if(A[j] <= x)
        {
            i = i + 1;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

int RANDOMIZED_SELECT(int A[], int p, int r, int i){
    if (p == r) {
        return A[p];
    }
    int q = RANDOMIZED_PARTITION(A, p, r);
    int k = q - p + 1;
    if (i == k) {
        return A[q];
    }
    else if (i < k) {
        return RANDOMIZED_SELECT(A, p, q - 1, i);
    }
    else {
        return RANDOMIZED_SELECT(A, q + 1, r, i - k);
    }
}
