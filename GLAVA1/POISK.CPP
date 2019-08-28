/*  ПОИСК В ЦЕЛОЧИСЛЕННОМ МАССИВЕ ПО СОВПАДЕНИЮ КЛЮЧА */
/* \poisk.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#define size 12
int A[size] = { 1, 7, 3, 4, 0, 5, 2, 6, 9, 8, 3, 6 };
int B[3][4] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 4, 7 };

main()
{
    setlocale(LC_ALL,"Russian");
    int poisk1(int A[], int n, int k);
    int key, *M;
    int ind, i;
    printf("\n   Поиск элемента по совпадению ");
    /* Создание динамического массива */
    M = (int *) calloc(12, sizeof(int));
    for (i = 0; i < 12; i++)
        M[i] = i + 1;
    while (1)
    {
        printf
        ("\n Введите значение ключа или отрицательное число =>");
        scanf("%d", &key);
        if (key < 0)
        {
            printf("\ Конец работы ");
            getchar();
            break;
        }

        /* Поиск в одномерном статическом массиве */
        ind = poisk1(A, size, key);
        if (ind == -1)
            printf
            ("\nВ массиве А элемент %d не найден\n",
             key);
        else
            printf
            ("\nВ массиве А элемент %d имеет индекс %d\n",
             key, ind);

        /* Поиск в двумерном статическом массиве */
        ind = poisk1(B[4], size, key);
        if (ind == -1)
            printf
            ("\nВ массиве B элемент %d не найден\n",
             key);
        else
            printf
            ("\nВ массиве B элемент %d имеет индекс %d\n",
             key, ind);

        /* Поиск в динамическом массиве */
        ind = poisk1(M, size, key);
        if (ind == -1)
            printf
            ("\nВ массиве M элемент %d не найден\n",
             key);
        else
            printf
            ("\nВ массиве M элемент %d имеет индекс %d\n",
             key, ind);

        /* Поиск в части однормерного массива, начиная с заданного элемента */
        ind = poisk1(&A[2], 5, key);
        if (ind == -1)
            printf
            ("\nВ массиве А[2]...A[6] элемент %d не найден\n",
             key);
        else
            printf
            ("\nВ массиве А[2]...A[6] элемент %d имеет индекс %d\n",
             key, ind);

        /* Поиск в части двумерного массива, начиная с заданного элемента */
        ind = poisk1(&B[1][2], 5, key);
        if (ind == -1)
            printf
            ("\nВ массиве B[1][2]... элемент %d не найден\n",
             key);
        else
            printf
            ("\nВ массиве B[1][2]... элемент %d имеет индекс %d\n",
             key, ind);
    }
    return 0;
}

/* ******************************************** */
/* ПОИСК ЭЛЕМЕНТА ПО СОВПАДЕНИЮ */
int poisk1(int A[], int n, int k)
{
    int i = 0;
    while (A[i] != k && i < n)
        i++;
    return (A[i] == k) ? i : -1;
}

/* ********************************** */
