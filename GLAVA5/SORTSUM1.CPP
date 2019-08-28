/* ***************************************************** */
/*   СОРТИРОВКА СТРОК МАССИВА ПО СУММАМ ИХ ЭЛЕМЕНТОВ -
	  МЕТОД ПУЗЫРЬКА    \SortSum1.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <stdlib.h>
#define n 8
#define m 5
float A[n][m];

/* ================================================= */
int main()
{
    setlocale(LC_ALL,"Russian");
    void SortSum1(float A[][m], int nn, int mm);
    int i, j;
    float s;
    printf
    ("\n Сортировка массива по суммам строк");

    /* Инициализация исходного массива случайными числами */
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            A[i][j] = rand() / 100;

    printf
    ("\n  Исходный массив  и суммы - отладочная печать\n");
    for (i = 0; i < n; i++)
    {
        s = 0;
        for (j = 0; j < m; j++)
        {
            printf(" %8.1f", A[i][j]);
            s += A[i][j];
        }
        printf("\t %8.1f\n", s);
    }

    /* Вызов процедуры сортировки */
    SortSum1(A, n, m);

    printf
    ("\n Использование упорядоченного массива - просто печать ");
    printf("\n  Отсортированный  массив\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf(" %8.1f", A[i][j]);
        printf("\n");
    }
    getchar();
    return 0;
}

/* ================================================ */
/*   ФУНКЦИЯ СОРТИРОВКИ МЕТОДОМ ПУЗЫРЬКА  */
void SortSum1(float A[][m], int nn, int mm)
{
    int i, j, p, f;
    float *S, k;
    float *R;
    R = (float *) calloc(mm, sizeof(float));	/* Рабочая строка */
    S = (float *) calloc(nn, sizeof(float));	/* Для массива сумм */

    /* Формирование массива сумм по строкам массива */
    for (i = 0; i < nn; i++)
    {
        S[i] = A[i][0];
        for (j = 1; j < mm; j++)
            S[i] = S[i] + A[i][j];
    }

    /* Сортировка исходного массива по массиву сумм */
    for (i = 0; i < nn - 1; i++)
    {
        p = 0;
        for (j = nn - 1; j > i; j--)
            if (S[j] < S[j - 1])  	/* Перестановка элементов массива сумм */
            {
                k = S[j];
                S[j] = S[j - 1];
                S[j - 1] = k;
                p = 1;
                /* Перестановка строк исходного массива */
                for (f = 0; f < mm; f++)
                {
                    R[f] = A[j][f];
                    A[j][f] = A[j - 1][f];
                    A[j - 1][f] = R[f];
                }
            }
        /* Если перестановок не было, то сортировка выполнена */
        if (p == 0)
            break;
    }
    printf
    ("\n Отладочная печать упорядоченных сумм\n");
    for (i = 0; i < nn; i++)
        printf("%7.1f", S[i]);
    free(R);
    free(S);
    getchar();
}

/* ******************************************************** */
