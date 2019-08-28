/* *************************************************** */
/*БЫСТРАЯ СОРТИРОВКА ХОАРА   \QuickSrt.c*/
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 15
int A[n] = { 12, 22, 13, 4, 15, 6, 9, 11, 13, 7, 15, 10, 11, 8, 14 };

/* ==================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    void QuickSort(int A[], int L, int R);
    int j;
    printf
    ("\n Быстрая сортировка, рекурсивная функция");
    printf("\n Исходный  массив: \n\t\t");
    for (j = 0; j < n; j++)
        printf("%d ", A[j]);
    printf("\n Отладочная печать");
    QuickSort(A, 0, n - 1);
    printf("\n Отсортированный массив :\n");
    for (j = 0; j < n; j++)
        printf("%d ", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ============================================= */
/*   ФУНКЦИЯ  БЫСТРОЙ СОРТИРОВКИ QuickSort */
void QuickSort(int A[], int L, int R)
{
    int i, j, k, x, m;
    i = L;
    j = R;
    x = A[(L + R) / 2];
    do
    {
        while (A[i] < x)
            i++;
        while (x < A[j])
            j--;
        if (i <= j)
        {
            k = A[i];
            A[i] = A[j];
            A[j] = k;
            i++;
            j--;
            /* Отладочная печать */
            printf("\n i=%d j=%d x=%d: ", i - 1, j + 1, x);
            for (m = 0; m < n; m++)
                printf(" %d", A[m]);
        }
    }
    while (i < j);
    if (L < j)
    {
        printf("\t L=%d j=%d", L, j);
        QuickSort(A, L, j);
    }
    if (i < R)
    {
        printf("\t i=%d R=%d", i, R);
        QuickSort(A, i, R);
    }
}

/* **************************************************** */
