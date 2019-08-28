/* ************************************************* */
/* ТРАНСПОНИРОВАНИЕ МАТРИЦЫ  \transp.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define m 3			/* число строк исходной матрицы */
#define n 5			/* число столбцов исх. матрицы */
/* ================================================= */
/* Ввод элементов исходной матрицы  */
void vvodmass(int a[][n], int mm, int nn)
{
    int i, j;
    for (i = 0; i < mm; i++)
        for (j = 0; j < nn; j++)
        {
            printf(" Введите a[%d][%d] \n", i, j);
            scanf("%d", &a[i][j]);
        }
}

/* ================================================= */
/* Транспонирование матрицы isx в матрицу trns  */
int transpon(int isx[][n], int trns[][m], int mm, int nn)
{
    int i, j;
    for (i = 0; i < mm; i++)
        for (j = 0; j < nn; j++)
            trns[j][i] = isx[i][j];
    return 0;
}

/* ================================================= */
/* Печать элементов матрицы */
int prntmas(int *mas, int mm, int nn)
{
    int i, j;
    for (i = 0; i < mm; i++)
    {
        printf("\n");
        for (j = 0; j < nn; j++)
            printf("%5d", mas[i * nn + j]);
    }
    return 0;
}

/*================================================== */
/* Главная функция */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, j;
    int A[m][n], AT[n][m];
    printf
    ("\n Программа транспонирования матрицы А \n");
    vvodmass(A, m, n);
    printf("Исходная матрица: \n");
    prntmas(A[0], m, n);
    getchar();
    transpon(A, AT, m, n);
    printf("\nТранспонированная матрица:\n");
    prntmas(AT[0], n, m);
    getchar();
    return 0;
}

/* ****************************************************** */
