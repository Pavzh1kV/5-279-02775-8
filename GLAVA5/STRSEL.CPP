/* ************************************************** */
/*  СОРТИРОВКА ПОСРЕДСТВОМ ПРЯМОГО ВЫБОРА   \StrSel.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 8
int A[n] = { 27, 412, 71, 81, 59, 14, 273, 87 };

/* ============================================= */
int main()
{
    setlocale(LC_ALL,"Russian");
    void StrSel(int A[], int nn);
    int j;
    printf
    ("\n Сортировка методом прямого выбора");
    printf("\n  Исходный  массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    StrSel(A, n);
    printf("\n  Отсортированный  массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    getchar();
}

/* ===========================================  */
/* ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВЫБОРОМ  */
void StrSel(int A[], int nn)
{
    int i, j, x, k;
    printf
    ("\n Отладочная печать по шагам сортировки");
    for (i = 0; i < nn - 1; i++)
    {
        x = A[i];
        k = i;
        for (j = i + 1; j < nn; j++)
            if (A[j] < x)
            {
                k = j;
                x = A[k];
            }
        A[k] = A[i];
        A[i] = x;

        printf("\n i=%d", i);
        for (j = 0; j < nn; j++)
            printf("\t %d", A[j]);
    }
}

/* *********************************************** */
