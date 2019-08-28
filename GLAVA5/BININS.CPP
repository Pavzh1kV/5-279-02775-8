/* *************************************************** */
/*  СОРТИРОВКА МЕТОДОМ ПРЯМОГО ВКЛЮЧЕНИЯ
	 С ДЕЛЕНИЕМ ПОПОЛАМ   \binins.cpp */
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
    void BinIns(int A[], int nn);
    int j;
    printf
    ("\n Сортировка методом прямого включения с делением пополам");
    printf("\n  Исходный  массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    BinIns(A, n);
    printf("\n  Отсортированный  массив \n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ===================================================== */
/*  ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВЫБОРОМ С ДЕЛЕНИЕМ ПОПОЛАМ */
void BinIns(int A[], int nn)
{
    int i, j, x, m, L, R;
    printf
    ("\n Отладочная печать по шагам сортировки ");
    for (i = 1; i < nn; i++)
    {
        x = A[i];
        L = 0;
        R = i;
        while (L < R)
        {
            m = (L + R) / 2;
            if (A[m] <= x)
                L = m + 1;
            else
                R = m;
        }
        for (j = i; j >= R; j--)
            A[j] = A[j - 1];
        A[R] = x;
        /* отладочная печать */
        printf("\ni=%d", i);
        for (j = 0; j < nn; j++)
            printf("\t %d", A[j]);
    }
}

/* ******************************************** */
