/* ************************************************ */
/*   СОРТИРОВКА ПИРАМИДОЙ   \HpSrt.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 9
int A[n] = { 5, 3, 7, 27, 9, 11, 14, 2, 8 };

void HpSrt(int A[], int nn);
void Heap(int A[], int ii, int nn);
/* =================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int j;
    printf
    ("\n Сортировка пирамидой, вариант второй");
    printf("\n  Исходный  массив \n\t");
    for (j = 0; j < n; j++)
        printf("%d   ", A[j]);
    printf("\n Отсортированный массив");
    HpSrt(A, n);
    printf("\n  Отсортированный  массив \n\t");
    for (j = 0; j < n; j++)
        printf("%d   ", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ================================================= */
void HpSrt(int A[], int nn)
{
    int L, x, i, m, k, j;
    /* Построение пирамиды из исходного массива */
    i = nn / 2;
    m = nn;
    L = i;
    for (k = 0; k <= L; k++)
    {
        printf("\ni=%d:     ", i);	/* отладочная печать */
        Heap(A, i, m);
        i--;
        for (j = 0; j < n; j++)	/* отладочная */
            printf("%d   ", A[j]);	/* печать     */
    }
    /* Сортировка массива: пирамида => отсортированный массив */
    for (k = 1; k < nn; k++)
    {
        x = A[0];
        A[0] = A[m - 1];
        A[m - 1] = x;
        m--;
        Heap(A, 0, m);
        printf("\nm=%d:     ", m);	/* отладочная печать */
        for (j = 0; j < n; j++)
            printf("%d   ", A[j]);
    }
}

/* ============================================= */
void Heap(int A[], int ii, int nn)
{
    int x, j, k, L;
    int p = 1;
    j = ii;
V:
    k = 2 * j + 1;
    L = k + 1;
    if ((L < nn) && ((A[j] < A[k]) || (A[j] < A[L])))
    {
        if (A[k] > A[L])
        {
            x = A[j];
            A[j] = A[k];
            A[k] = x;
            j = k;
            goto V;
        }
        else
        {
            x = A[j];
            A[j] = A[L];
            A[L] = x;
            j = L;
            goto V;
        }
    }
    else if ((k == nn - 1) && (A[j] < A[k]))
    {
        x = A[j];
        A[j] = A[nn - 1];
        A[nn - 1] = x;
    }
}

/* ***************************************************** */
