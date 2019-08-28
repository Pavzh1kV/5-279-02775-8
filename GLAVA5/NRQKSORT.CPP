/* ************************************************** */
/*НЕРЕКУРСИВНАЯ ФУНКЦИЯ БЫСТРОЙ СОРТИРОВКИ ХОАРА */
/*  \NrqkSort.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 15
int A[n] = { 12, 2, 13, 4, 15, 6, 9, 11, 3, 7, 5, 10, 1, 8, 14 };

/* ================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    void NRQuickSort(int A[], int nn);
    int j;
    printf
    ("\n Нерекурсивная процедура быстрой сортировки");
    printf("\n Исходный  массив: \n\t\t");
    for (j = 0; j < n; j++)
        printf("%d ", A[j]);
    printf("\n Отладочная печать");
    NRQuickSort(A, n);
    printf("\n Отсортированный массив :\n");
    for (j = 0; j < n; j++)
        printf("%d ", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ================================================== */
/* НЕРЕКУРСИВНАЯ ФУНКЦИЯ БЫСТРОЙ СОРТИРОВКИ QuickSort */
void NRQuickSort(int A[], int nn)
{
    int i, j, k, x, m, s, L, R;
#define d 16
    struct stack
    {
        int L;
        int R;
    } st[d];
    s = 1;
    st[1].L = 0;
    st[1].R = nn - 1;
    do
    {
        L = st[s].L;
        R = st[s].R;
        s--;
        do
        {
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
            if (i < R)
            {
                s++;
                st[s].L = i;
                st[s].R = R;
                printf("  i=%d R=%d s=%d", i, R, s);
            }
            R = j;
        }
        while (L < R);
    }
    while (s != 0);
}

/* ***************************************************** */
