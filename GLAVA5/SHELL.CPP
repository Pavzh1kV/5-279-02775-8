/* *********************************************** */
/* СОРТИРОВКА МЕТОДОМ ШЕЛЛА  \Shell.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define n 9
int A[n] = { 5, 6, 2, 4, 9, 8, 3, 1, 7 };

/* ==================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    void Shell(int A[], int nn);
    int j;
    printf("\n Сортировка методом Шелла");
    printf("\n Исходный  массив: \n");
    printf("\t");
    for (j = 0; j < n; j++)
        printf("%d   ", A[j]);
    printf("\n");
    Shell(A, n);
    printf("\n Отсортированный массив :\n");
    for (j = 0; j < n; j++)
        printf("%d   ", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ============================================= */
/*   ФУНКЦИЯ  СОРТИРОВКИ МЕТОДОМ ШЕЛЛА */
void Shell(int A[], int nn)
{
    int i, j, k, x, ii;
    k = (nn + 1) / 2;
    while (k >= 1)
    {
        for (i = k; i < nn; i++)
        {
            if (A[i - k] > A[i])
            {
                x = A[i];
                j = i - k;
M:
                A[j + k] = A[j];
                if (j > k)
                {
                    if (A[j - k] > x)
                    {
                        j = j - k;
                        goto M;
                    }
                }
                A[j] = x;

                /*				  printf(" \nk = %d x=%d: ",k,x);
                				  for (ii=0; ii<nn; ii++)
                				  printf(" %d  ",A[ii]);*/

            }
        }
        /* Отладочная печать */
        printf(" \nk = %d ", k);
        for (ii = 0; ii < nn; ii++)
            printf(" %d  ", A[ii]);

        if (k > 2)
            k = (k + 1) / 2;
        else
            k = k / 2;
    }
}

/* ************************************************** */
