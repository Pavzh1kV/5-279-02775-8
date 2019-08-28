/* **************************************************** */
/*   СОРТИРОВКА МЕТОДОМ ПУЗЫРЬКА   \BblSort.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 8
int A[n] = { 27, 412, 71, 81, 59, 14, 273, 87 };

/* =================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    void BblSort(int A[], int nn);
    int j;
    printf("\n Сортировка методом пузырька");
    printf("\n  Исходный массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    BblSort(A, n);
    printf("\n  Отсортированный  массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* =========================================== */
/*  ФУНКЦИЯ СОРТИРОВКИ МЕТОДОМ ПУЗЫРЬКА  */
void BblSort(int A[], int nn)
{
    int i, j, k, p;
    printf
    ("\n Отладочная печать по шагам сортировки");
    for (i = 0; i < nn - 1; i++)
    {
        p = 0;
        for (j = nn - 1; j > i; j--)
            if (A[j] < A[j - 1])
            {
                k = A[j];
                A[j] = A[j - 1];
                A[j - 1] = k;
                p = 1;
            }
        /* Если перестановок не было, то сортировка выполнена */
        if (p == 0)
            break;

        printf(" \ni = %d", i);
        for (j = 0; j < nn; j++)
            printf("\t %d", A[j]);
    }
}

/* ****************************************************** */
