/* ********************************************** */
/* ПОИСК В ДВУХМЕРНОМ ЦЕЛОЧИСЛЕННОМ МАССИВЕ ЭЛЕ-  */
/*	МЕНТА, ВСТРЕЧАЮЩЕГОСЯ ВО ВСЕХ СТРОКАХ          */
/* \shr_same.cpp */
/* ********************************************** */
#include <string.h>
//#include <alloc.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
/* ==============================================*/
/* ВВОД ЦЕЛОГО ЧИСЛА                             */
void in(int *a)
{
    while (1)
    {
        fflush(NULL);
        if (scanf("%d", a))
            break;
        else
            printf("\n ОШИБКА! Введите повторно =>");
    }
}

/* ============================================== */
/* ФУНКЦИЯ ВВОДА ИСХОДНЫХ ДАННЫХ                  */
/* nn, mm - размеры двухмерного массива           */
/*Элементы строк строго упорядочены по возрастанию*/
int *vvod_nm(int *nn, int *mm)
{
    int i, j, n, m;
    int f, *t;			/* char N[80]; */
    printf("\n Введите число строк n=>");
    in(&n);
    *nn = n;
    printf("\n Введите число столбцов m=>");
    in(&m);
    *mm = m;
    t = (int *) malloc(n * m * sizeof(int));
    printf
    ("\n Ввод элементов A[i][j] по возрастанию в строке");
    for (i = 0; i < n; i++)
    {
        printf("\n A[%d][%d]=", i + 1, 1);
        in(&t[i * m]);
        f = t[i * m];
        for (j = 1; j < m; j++)
        {
            while (1)
            {
                printf("\n A[%d][%d]=", i + 1, j + 1);
                in(&t[i * m + j]);
                if (f >= t[i * m + j])
                {
                    printf
                    ("\ ОШИБКА, введите повторно");
                    fflush(NULL);	/* почистим буфер клавиатуры */
                    /* gets(N); *//* можно так, вместо fflush(NULL) */
                    continue;
                }
                else
                {
                    f = t[i * m + j];
                    break;
                }
            }
        }
    }
    return t;
}

/* ================================================== */
int srch_equ(int *A, int n, int m, int *el)
{
    int i, j, s, p = 1;
    int f;
    for (s = 0; s < m; s++)
    {
        f = A[s];
        p = 1;			/* элементы первой строки */
        for (i = 1; i < n; i++)	/* поиск в остальных строках */
            for (j = 0; j < m; j++)
                if (f == A[i * m + j])  	/* в строке нашелся элемент */
                {
                    p = p + 1;
                    break;
                }
                else if (f < A[i * m + j])	/* остальные элементы больше */
                    break;
        if (p == n)
        {
            printf
            ("\n Элемент %d имеется во всех  %d строках",
             f, n);
            *el = f;
            return 0;
        }
    }
    printf("\n Нет повторяющегося элемента");
    return -1;

}

/* ============================================= */
int main()
{
    setlocale(LC_ALL,"Russian");
    int *A, e;
    int i, j, k, m1, n1, p, s;
    printf
    ("\n Поиск в двухмерном целочисленном\n\
	 массиве элемента, встречающегося в каждой строке");
    A = vvod_nm(&n1, &m1);
    for (i = 0; i < n1; i++)
    {
        printf("\n");
        for (j = 0; j < m1; j++)
            printf("%5d", A[i * m1 + j]);
    }
    k = srch_equ(A, n1, m1, &e);
    if (k == 0)
        printf("\n Нашли %d", e);
    else
        printf("\n Увы, элемент не найден");
    getchar();
    return 0;
}

/***************************************************/
