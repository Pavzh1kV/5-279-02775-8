/* ****************************************************** */
/* БИНАРНЫЙ ПОИСК В УПОРЯДОЧЕННОЙ ТАБЛИЦЕ    \bisearch.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define m 20
int bisearch(int A[], int n, int key);
int bisearch1(int A[], int n, int key);
/*  ==================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    int i, key, A[m];
    printf
    (" Бинарный поиск в упорядоченной таблице ");
    printf
    ("\n Введите %d целых чисел в возрастающем порядке",
     m);
    for (i = 0; i < m; i++)
        scanf("%d", &A[i]);
    printf
    ("\n Введите значение искомого ключа =>");
    scanf("%d", &key);
    i = bisearch1(A, m, key);
    if (i == -1)
        printf(" Ключ %d не найден", key);
    else
        printf(" %d-й элемент имеет ключ = %d \n", i,
               A[i]);
    getchar();
    return 0;
}

/* ====================================================== */
/* ФУНКЦИЯ БИНАРНОГО ПОИСКА В УПОРЯДОЧЕННОЙ ТАБЛИЦЕ  Вариант 1 */
int bisearch1(int A[], int n, int key)
{
    int li, rj, k;
    li = 0;
    rj = n - 1;
    while (li <= rj)
    {
        k = (li + rj) / 2;
        if (key > A[k])
            li = k + 1;
        else if (key < A[k])
            rj = k - 1;
        else
            return k;
        printf(" li=%d, rj=%d, k=%d ", li, rj, k);	/* отладочная печать */
    }
    return -1;
}

/* ============================================================= */
/*  ФУНКЦИЯ БИНАРНОГО ПОИСКА   Вариант 2,
	  оба варианта равноценны */
int bisearch(int A[], int n, int key)
{
    int li, rj, k;
    li = 0;
    rj = n - 1;
    k = li;
    while (li <= rj && A[k] != key)
    {
        k = (li + rj) / 2;
        if (key > A[k])
            li = k + 1;
        else if (key < A[k])
            rj = k - 1;
    }
    return (A[k] == key) ? k : -1;
}

/* ************************************************* */
