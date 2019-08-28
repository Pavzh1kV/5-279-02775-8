/* *************************************************** */
/*  Умножение матрицы на вектор: С = А * B. \umn_m_v.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define m 3
#define n 4
long int A[m][n];
long int B[n];
long int C[m];
void umn_mat2(long a[][n], long b[], long c[], int mm, int nn);
void pr_mas(long int *ar, int mm);
/* ====== ГЛАВНАЯ ФУНКЦИЯ ============================ */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, j;
    system("clear");
    printf("\n Умножение матрицы на вектор");
    /* Инициализация элементов массивов */
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            A[i][j] = i + 1 + j;
    for (i = 0; i < n; i++)
        B[i] = (i + 1);
    printf("\n Матрица A:");
    for (i = 0; i < m; i++)
    {
        printf("\n");
        for (j = 0; j < n; j++)
            printf("%  ld", A[i][j]);
    }
    printf("\n Вектор В:");
    pr_mas(B, n);
    /* Умножение матрицы на вектор и печать */
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
/* УМНОЖЕНИЕ МАТРИЦЫ НА ВЕКТОР */
void umn_mat2(long a[][n], long b[], long c[], int mm, int nn)
{
    int i, k;
    for (i = 0; i < mm; i++)
    {
        c[i] = 0;
        for (k = 0; k < nn; k++)
            c[i] += a[i][k] * b[k];
    }
}

/* ***************************************************** */
