/* **************************************************** */
/*БЫСТРАЯ СОРТИРОВКА ХОАРА [Вирт-2, стр.117]
  Демонстрирует, что сортировка неустойчивая,
  т.е. исходный порядок элементов с одинаковыми
  ключами может быть нарушен   \QuicSrt1.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 15
int A[2][n] = { 12, 22, 13, 14, 15, 6, 29, 11, 13, 7, 15, 11, 11, 8, 14,
                1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
              };

/* ======================================================= */
main()
{
    setlocale(LC_ALL,"Russian");
    void QuickSort(int A[][n], int L, int R);
    int j;
    printf
    ("\n Быстрая сортировка, рекурсивная функция");
    printf("\n Исходный  массив: \n\t\t");
    for (j = 0; j < n; j++)
        printf(" %d %d ", A[0][j], A[1][j]);
    getchar();
    printf("\n Отладочная печать");
    QuickSort(A, 0, n - 1);
    printf("\n Отсортированный массив :\n");
    for (j = 0; j < n; j++)
        printf("\n%d %d", A[0][j], A[1][j]);
    printf("\n");
    getchar();
    return 0;
}

/* =================================================== */
/*   ФУНКЦИЯ  БЫСТРОЙ СОРТИРОВКИ QuickSort */
void QuickSort(int A[][n], int L, int R)
{
    int i, j, k, x, m;
    i = L;
    j = R;
    x = A[0][(L + R) / 2];
    do
    {
        while (A[0][i] < x)
            i++;
        while (x < A[0][j])
            j--;
        if (i <= j)
        {
            k = A[1][i];
            A[1][i] = A[1][j];
            A[1][j] = k;
            k = A[0][i];
            A[0][i] = A[0][j];
            A[0][j] = k;
            i++;
            j--;
            /* Отладочная печать */
            /*            printf("\n i=%d j=%d x=%d: ",i-1,j+1,x);
            				for (m=0; m<n; m++)
            					printf(" %d",A[m]);*/
        }
    }
    while (i < j);
    if (L < j)  		/* printf("\t L=%d j=%d",L,j); */
    {
        QuickSort(A, L, j);
    }
    if (i < R)  		/* printf("\t i=%d R=%d",i,R); */
    {
        QuickSort(A, i, R);
    }
}

/* ************************************************** */
