/* ******************************************* */
/*   СРАВНЕНИЕ МАССИВОВ    sravn.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 8
/* =========================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    int cmp_arrs(int a[], int b[], int nn, int *k);
    int A[n] = { 44, 55, 66, 66, 68, 69, 70, 75 };
    int B[n] = { 44, 55, 66, 67, 68, 69, 70, 75 };
    int C[n] = { 44, 55, 65, 67, 68, 70, 74, 78 };
    int j, r, k;
    printf("\n  Исходный массив A:\n");
    for (j = 0; j < n; j++)
        printf("\t%d", A[j]);
    printf("\n  Исходный массив B:\n");
    for (j = 0; j < n; j++)
        printf("\t%d", B[j]);
    printf("\n  Исходный массив C:\n");
    for (j = 0; j < n; j++)
        printf("\t%d", C[j]);
    printf("\n\n Cравнение массивов А и В:");
    r = cmp_arrs(A, B, n, &k);
    if (r == 0)
        printf("\n Массивы равны");
    else if (r > 0)
        printf("\n Первый массив больше: k=%d", k);
    else
        printf("\n Первый массив меньше: k=%d", k);
    printf("\n\n Cравнение массивов А и C:");
    r = cmp_arrs(A, C, n, &k);
    if (r == 0)
        printf("\n Массивы равны");
    else if (r > 0)
        printf("\n Первый массив больше: k=%d", k);
    else
        printf("\n Первый массив меньше: k=%d", k);
    printf("\n\n Cравнение массивов C и В:  ");
    r = cmp_arrs(C, B, n, &k);
    if (r == 0)
        printf("\n Массивы равны");
    else if (r > 0)
        printf("\n Первый массив больше: k=%d", k);
    else
        printf("\n Первый массив меньше: k=%d", k);
    printf("\n");
    getchar();
    return 0;
}

/* ============================================== */
/*  СРАВНЕНИЕ ЦЕЛОЧИСЛЕННЫХ МАССИВОВ  */
int cmp_arrs(int a[], int b[], int nn, int *k)
{
    int i, r;
    for (i = 0; i < nn - 1; i++)
        if (a[i] < b[i])
        {
            *k = i;
            r = -1;
            break;
        }
        else if (a[i] > b[i])
        {
            *k = i;
            r = 1;
            break;
        }
        else
            r = 0;
    return r;
}

/* ******************************************** */
