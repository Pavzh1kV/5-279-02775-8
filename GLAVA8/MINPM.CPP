/* ВЫЧИСЛЕНИЕ МИНИМАЛЬНОЙ ПУТЕВОЙ МАТРИЦЫ ПО ЗАДАННОЙ */
/* МАТРИЦЕ СМЕЖНОСТИ \minpm1.cpp                      */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 5
int A[n][n] = { 0, 0, 0, 1, 0,
                1, 0, 1, 0, 0,
                0, 0, 0, 0, 1,
                0, 1, 1, 0, 1,
                0, 0, 0, 0, 0
              };

int P[n][n];
/* ================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
int main()
{
    setlocale(LC_ALL,"Russian");
    void pm(int *a, int *p, int fn);
    int i, j;
    /* Матрицу смежности можно вводить в диалоге: */
    /* for (i=0;i<n;i++)
      for (j=0;j<n;j++)
    	{printf("\n A[%d,%d]=",i,j);
     scanf("%d",&A[i][j]);}   */
    printf
    ("\n\n Вычисление минимальной путевой матрицы\
 по заданной матрице смежности\n");
    printf("\n Матрица смежности:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }
    getchar();
    pm(A[0], P[0], n);
    printf("\n Минимальная путевая матрица:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%4d", (P[i][j] == 10000) ? 0 : P[i][j]);
        printf("\n");
    }
    getchar();
    return 0;
}

/* ================================================ */
/*  ФУНКЦИЯ ВЫЧИСЛЕНИЯ   МИНИМАЛЬНОЙ
 ПУТЕВОЙ МАТРИЦЫ ПО ЗАДАННОЙ МАТРИЦЕ СМЕЖНОСТИ */
void pm(int *a, int *p, int fn)
{
    int i, j, k;
    for (i = 0; i < fn; i++)
        for (j = 0; j < fn; j++)
            if (a[i * fn + j] == 0)
                p[i * n + j] = 10000;
            else
                p[i * fn + j] = a[i * fn + j];
    for (k = 0; k < fn; k++)
        for (i = 0; i < fn; i++)
            for (j = 0; j < fn; j++)
                p[i * n + j] =
                    (p[i * fn + j] <=
                     (p[i * fn + k] + p[k * fn + j])) ? p[i * n +
                             j] : (p[i * fn +
                                       k] +
                                   p[k * fn +
                                       j]);
}

/* ************************************************** */
