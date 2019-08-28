/* ********************************************** */
/* Генерация случайных чисел в интервале [0,1].   */
/* \rand1.cpp*/
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 184
/* ============================================== */
/* ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВКЛЮЧЕНИЕМ  */
void Sis(float A[], int nn)
{
    int i, j;
    float k;
    for (j = 1; j < nn; j++)
    {
        k = A[j];
        i = j - 1;
        while (k < A[i] && i >= 0)
        {
            A[i + 1] = A[i];
            i -= 1;
        }
        A[i + 1] = k;
    }
}

/* =========================================== */
/* ГЕНЕРАТОР СЛУЧАЙНЫХ ЧИСЕЛ */
void rand1(float *A, int nn)
{
    long M = 8192;
    long D = 67101323;
    long B = M * M - D;
    long R = 1;
    float RF;
    int i;
    int C;
    for (i = 0; i < n; i++)
    {
        C = R / M;
        R = B * C + M * (R - M * C);
        if (R > D)
            R = R - D;
        RF = (float) (R) / D;
        A[i] = RF;
    }
}

/* ============================================= */
main()
{
    setlocale(LC_ALL,"Russian");
    float a[n];
    int i;
    printf("\n Генерация случайных чисел \n");
    rand1(a, n);
    for (i = 0; i < n; i++)
        printf(" %f ", a[i]);
    getchar();
    Sis(a, n);
    printf
    ("\n Упорядоченный массив случайных чисел:\n");
    for (i = 0; i < n; i++)
        printf(" %f ", a[i]);
    getchar();
}

/* ******************************************************* */
