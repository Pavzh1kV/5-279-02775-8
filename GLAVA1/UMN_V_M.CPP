/* *************************************************** */
/* Умножение вектора  на матрицу: С = B * A.
   Хусаинов Б.С. 20.04.2001     D:\TC\XBS\MASSIV\umn_v_m.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define m 3
#define n 4
long int A[n][m];
long int B[n];
long int C[m];
void umn_mat2(long a[][m], long b[], long c[], int mm, int nn);
void pr_mas(long int *ar, int mm);
/* ====== ГЛАВНАЯ ФУНКЦИЯ ============================ */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, j;
    system("clear");
    printf("\n Умножение вектора на матрицу");
    /* Инициализация массива и вектора */
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            A[i][j] = i + 1 + j;
    for (i = 0; i < n; i++)
        B[i] = (i + 1);
    printf("\n Матрица A:");
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j < m; j++)
            printf("%  ld", A[i][j]);
    }
    printf("\n Вектор В:");
    pr_mas(B, n);
    /* Умножение вектора на матрицу  и печать */
    umn_mat2(A, B, C, m, n);
    printf("\n Результат:");
    pr_mas(C, m);
}

/* ===================================================== */
/*  ПЕЧАТЬ ЭЛЕМЕНТОВ МАССИВА */
void pr_mas(long int *ar, int mm)
{
    int i;
    for (i = 0; i < mm; i++)
        printf("\n %ld", *(ar + i));
    getchar();
}

/* ===================================================== */
/* УМНОЖЕНИЕ ВЕКТОРА НА МАТРИЦУ */
void umn_mat2(long a[][m], long b[], long c[], int mm, int nn)
{
    int j, k;
    for (j = 0; j < mm; j++)
    {
        c[j] = 0;
        for (k = 0; k < nn; k++)
            c[j] = c[j] + b[k] * a[k][j];
    }
}

/* **************************************************** */
