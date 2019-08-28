/* *********************************************** */
/*  ПОИСК ПО СОВПАДЕНИЮ КЛЮЧА    \poisk1.cpp       */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define size 10
int A[size] = { 1, 7, 3, 4, 0, 5, 2, 6, 9, 8 };

/* =============================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int poisk1(int A[], int n, int k);
    int key;
    int ind, i;
    printf("\n   Поиск элемента по совпадению ");
    printf("\n Исходный массив:\n");
    for (i = 0; i < size; i++)
        printf("%5d", A[i]);
    key = 3;
    ind = poisk1(A, size, key);
    if (ind == -1)
        printf("\nЭлемент %d не найден\n", key);
    else
        printf("\n Элемент %d имеет индекс %d\n", key,
               ind);
    getchar();
    return 0;
}

/* ==================================================== */
/* ПОИСК ЭЛЕМЕНТА ПО СОВПАДЕНИЮ */
int poisk1(int A[], int n, int k)
{
    int i = 0;
    while (A[i] != k && i < n)
        i++;
    return (A[i] == k) ? i : -1;
}

/* *************************************************** */
