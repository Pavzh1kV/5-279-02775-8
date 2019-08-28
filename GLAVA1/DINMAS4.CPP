/* ************************************************* */
/* ДВУХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ (n*n) \dinmas4.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
/* ======================================== */
/* ПЕЧАТЬ ДВУХМЕРНОГО ДИНАМИЧЕСКОГО МАССИВА */
void prntarray(float *a, int q, int p)
{
    int i, j;
    for (i = 0; i < q; i++)
    {
        printf("\n строка %d:", i + 1);
        for (j = 0; j < p; j++)
            printf("\t %f", a[i * p + j]);
    }
}

/* ================================================ */
/* ВВОД ДАННЫХ В ДВУХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ */
void inarr(float *M, int mm, int nn)
{
    int i, j;
    for (i = 0; i < mm; i++)
        for (j = 0; j < nn; j++)
            if (i != j)
            {
                printf("\n Введите M[%d][%d]=", i + 1, j + 1);
                scanf("%f", &M[i * nn + j]);
            }
            else
                M[i * nn + j] = i;
    /* Отладочная печать */
    printf
    ("\n\n Печать элементов массива в функции ввода элементов:");
    prntarray(M, mm, nn);
}

/* =================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ */
int main()
{
    setlocale(LC_ALL,"Russian");
    int m, n, i, j;
    float *matr;
    printf
    ("\n Работа с двухмерным динамическим массивом");
    printf("\n Введите число строк массива =>");
    scanf("%d", &m);
    printf
    ("\n Введите число столбцов массива =>");
    scanf("%d", &n);
    matr = (float *) calloc(m * n, sizeof(float));
    if (matr == NULL)		/* память не выделена */
        return -1;
    printf("\n Ввод элементов массива");
    inarr(matr, m, n);
    printf
    ("\n\n Печать элементов массива в главной функции: ");
    prntarray(matr, m, n);
    free(matr);
    getchar();
    return 0;
}

/***************************************************/
