/* ************************************************ */
/*  СОРТИРОВКА МЕТОДОМ ПРЯМОГО ВКЛЮЧЕНИЯ    \sis.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdlib.h>
//#include <conio.h>
#define n 3000
int A[n];
/* ============================================= */
main()
{
    setlocale(LC_ALL,"Russian");
    void Sis(int A[], int nn);
    int j;
    printf
    ("\n Сортировка методом прямого включения");
    printf("\n Исходный  массив: \n\t");
    for (j = 0; j < n; j++)
        A[j] = rand();
    /*     printf("%d\t",A[j]);
       printf("\n"); */
    Sis(A, n);
    printf("\n Отсортированный массив :\n\t");
    for (j = 0; j < n; j++)
        printf("%d\t", A[j]);
    printf("\n");
    getchar();
    return 0;
}

/* ============================================== */
/* ФУНКЦИЯ СОРТИРОВКИ ПРЯМЫМ ВКЛЮЧЕНИЕМ  */
void Sis(int A[], int nn)
{
    int i, j, k;
    /* printf("\n Отладочная печать по шагам сортировки");*/
    for (j = 1; j < nn; j++)
    {
        k = A[j];
        i = j - 1;
        while (k < A[i] && i >= 0)
        {
            A[i + 1] = A[i];
            i -= 1;
        }
        A[i + 1] = k;
        /*	 /* Отладочная печать */
        printf("\n j = %d", j);
        for (i = 0; i < nn; i++)
            printf("\t%d", A[i]);
        /**/
    }
}

/* *********************************************** */
