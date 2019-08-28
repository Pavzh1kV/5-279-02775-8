/* ********************************************** */
/* Копирование массивов, одномерных и многомерных.
		 \copyar.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define m 4
#define n 3
long M1[10];
long M2[m][n];
void pr_mas(long int *ar, int numb);
long M3[10];
long M4[m][n];
long M5[m * n];
void copy_arr(long *From, long *To, int numb);
/* ================================================ */
/*    ГЛАВНАЯ ФУНКЦИЯ   */
int main()
{
    setlocale(LC_ALL,"Russian");				/* Инициализация элементов массивов */
    int i, j;
    system("clear");
    for (i = 0; i < 10; i++)
        M1[i] = i * i + 3;
    for (i = 0; i < m; i++)
        for (j = 0; j < 3; j++)
            M2[i][j] = (i + 1) * (j + 2);
    /* Вызов функции копирования */
    printf("\n Вариант 1:");
    copy_arr(M1, M3, 10);
    pr_mas(M1, 10);
    pr_mas(M3, 10);
    printf("\n Вариант 2:");
    copy_arr(M2[0], M4[0], m * n);
    pr_mas(M2[0], m * n);
    pr_mas(M4[0], m * n);
    printf("\n Вариант 3:");
    copy_arr(M2[0], M5, m * n);
    pr_mas(M2[0], m * n);
    pr_mas(M5, m * n);
    return 0;
}

/* =============================================== */
/* ВЫВОД МАССИВА НА ЭКРАН */
void pr_mas(long *ar, int numb)
{
    printf("\n Значения элементов массивa:\n");
    while (numb--)
        printf(" %ld", *(ar++));
    getchar();
}

/* =============================================== */
/* КОПИРОВАНИЕ МАССИВОВ */
void copy_arr(long *From, long *To, int numb)
{
    while (numb--)
        *To++ = *From++;
    printf("\n Массив скопирован");
    getchar();
}

/* *********************************************** */
