/* *************************************************** */
/*ШЕЙКЕРНАЯ СОРТИРОВКА.   \ShkrSort.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 8
int A[n] = { 27, 412, 71, 81, 59, 14, 273, 87 };

/* ========================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    void ShkrSort(int A[], int nn);
    int j;
    printf("\n Шейкерная сортировка");
    printf("\n Исходный  массив: \n");
    for (j = 0; j < n; j++)
        printf("%d\t", A[j]);
    printf("\n");
    ShkrSort(A, n);
    printf("\n Отсортированный массив :\n");
    for (j = 0; j < n; j++)
        printf("%d\t", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* =========================================== */
/*   ФУНКЦИЯ ШЕЙКЕРНОЙ СОРТИРОВКИ  */
void ShkrSort(int A[], int nn)
{
    int i, j, k, x, L, R;
    L = 1;
    R = nn - 1;
    k = nn - 1;
    printf("\n Отладочная печать");
    do
    {
        for (j = R; j >= L; j--)
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        L = k + 1;
        /* Отладочная печать */
        printf(" \nL = %d", L);
        for (i = 0; i < nn; i++)
            printf("\t%d", A[i]);
        for (j = L; j <= R; j++)
            if (A[j - 1] > A[j])
            {
                x = A[j - 1];
                A[j - 1] = A[j];
                A[j] = x;
                k = j;
            }
        R = k - 1;
        /* Отладочная печать */
        printf(" \nR = %d", R);
        for (i = 0; i < nn; i++)
            printf("\t%d", A[i]);
    }
    while (L < R);
}

/* *********************************************** */
