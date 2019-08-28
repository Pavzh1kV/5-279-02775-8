/* ************************************************* */
/*  ПОИСК ПО СОВПАДЕНИЮ КЛЮЧА - ЗАГРАЖДАЮЩИЙ ЭЛЕМЕНТ */
/*  \poisk2.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define size 10
int A[size + 1] = { 1, 7, 3, 4, 0, 5, 2, 6, 9, 8 };

main()
{
    setlocale(LC_ALL,"Russian");
    int poisk2(int A[], int n, int k);
    int key;
    int ind, i;
    printf("\n   Поиск элемента по совпадению ");
    printf("\n Исходный массив:");
    for (i = 0; i < size; i++)
        printf("%5d", A[i]);
    key = 8;
    ind = poisk2(A, size, key);
    if (ind == -1)
        printf("\nЭлемент %d не найден\n", key);
    else
        printf("\n Элемент %d имеет индекс %d\n", key,
               ind);
    getchar();
    return 0;
}

/* ====================================================== */
/* ПОИСК ЭЛЕМЕНТА ПО СОВПАДЕНИЮ С ЗАГРАЖДАЮЩИМ ЭЛЕМЕНТОМ */
int poisk2(int A[], int n, int k)
{
    int i = 0;
    A[n] = k;
    while (A[i] != k)
        i++;
    return (i == n) ? -1 : i;
}

/* ****************************************************** */
