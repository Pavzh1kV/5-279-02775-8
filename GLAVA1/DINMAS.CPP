/* *************************************************** */
/* ДВУХМЕРНЫЙ ДИНАМИЧЕСКИЙ МАССИВ С МАССИВОМ
	 УКАЗАТЕЛЕЙ СТРОК   \dinmas.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
/* ===================================================*/
int main()
{
    setlocale(LC_ALL,"Russian");
    int m, n, i, j;
    float **matr, *t;
    float mat1[5][4];
    printf
    ("\n Работа с динамическим двумерным массивом");
    printf("\n Введите число строк массива =>");
    scanf("%d", &m);
    /* Память под массив указателей строк */
    matr = (float **) calloc(m, sizeof(float *));
    printf("\n %p", matr);
    if (matr == NULL)
    {
        printf("\n Нет доступной памяти ");
        getchar();
        return -1;
    }
    printf
    ("\n Введите число элементов в строке =>");
    scanf("%d", &n);
    for (i = 0; i < m; i++)  	/* Для каждой строки - отдельная память */
    {
        matr[i] = (float *) calloc(n, sizeof(float));
        printf(" i=%d p=%p", i + 1, matr[i]);
        if (matr[i] == NULL)
            return -1;
        /* Инициализация строки массива */
        for (j = 0; j < n; j++)
            matr[i][j] = i + 1;
    }
    printf
    ("\n Массив до перестановки указателей:");
    for (i = 0; i < m; i++)
    {
        printf("\n строка %d %p :", i + 1, &matr[i]);
        for (j = 0; j < n; j++)
        {
            printf("  %.0e", matr[i][j]);
            printf("  %p", &matr[i][j]);
        }
    }
    /* Перестановка указателей строк - псевдоперестановка
       строк массива: 0 <--> 1; 2 <--> 3 */
    t = matr[0];
    matr[0] = matr[1];
    matr[1] = t;
    t = matr[2];
    matr[2] = matr[3];
    matr[3] = t;
    printf
    ("\n Массив после перестановки указателей:");
    for (i = 0; i < m; i++)
    {
        printf("\n строка %d %p:", i + 1, &matr[i]);
        for (j = 0; j < n; j++)
        {
            printf("\t%.0e", matr[i][j]);
            printf("  %p", &matr[i][j]);
        }
    }
    for (i = 0; i < m; i++)
        free(matr[i]);
    free(matr);
    getchar();
}

/* ********************************************************* */
