/* ************************************************ */
/* СОРТИРОВКА ПИРАМИДОЙ ПО УБЫВАНИЮ. \RVRHPSRT.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 9
int A[n] = { 5, 3, 7, 27, 9, 11, 14, 2, 8 };

void HeapSort(int A[], int nn);
void Sift(int A[], int L, int R);
/* ================================================ */
main()
{
    setlocale(LC_ALL,"Russian");
    int j;
    printf
    ("\n  Сортировка пирамидой по убыванию");
    printf("\n  Исходный  массив \n\t");
    for (j = 0; j < n; j++)
        printf("%d    ", A[j]);
    printf("\n Отладочная печать");
    HeapSort(A, n);
    printf("\n  Отсортированный  массив \n\t");
    for (j = 0; j < n; j++)
        printf("%d    ", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ================================================ */
/* СОРТИРОВКА ПО УБЫВАНИЮ */
void HeapSort(int A[], int nn)
{
    int L, R, x, i;
    L = nn / 2;
    R = nn - 1;
    /*  Построение пирамиды из исходного массива */
    while (L > 0)
    {
        L = L - 1;
        Sift(A, L, R);
        /*  Отладочная печать */
        printf("\nL=%d:    ", L);
        for (i = 0; i < nn; i++)
            printf("%d   ", A[i]);
    }
    /* Сортировка: пирамида => отсортированный массив */
    while (R > 0)
    {
        x = A[0];
        A[0] = A[R];
        A[R] = x;
        R--;
        /* Отладочная печать */
        printf("\nR=%d:    ", R);
        for (i = 0; i < nn; i++)
            printf("%d   ", A[i]);
        Sift(A, L, R);
    }
}

/* ============================================== */
void Sift(int A[], int L, int R)
{
    int i, j, x, k;
    i = L;
    j = 2 * L + 1;
    x = A[L];
    if ((j < R) && (A[j] > A[j + 1]))
        j++;
    while ((j <= R) && (x > A[j]))
    {
        k = A[i];
        A[i] = A[j];
        A[j] = k;
        i = j;
        j = 2 * j + 1;
        if ((j < R) && (A[j] > A[j + 1]))
            j++;
    }
}

/* ************************************************ */
