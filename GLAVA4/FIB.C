/* ************************************** */
/* Числа Фибоначчи, нерекурсивный вариант */
/* \Fib.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
/* ===================================== */
int Fib(int n)
{
    int i, x, y, z;
    if (n < 2)
        return n;
    x = 0;
    y = 1;
    for (i = 2; i <= n; i++)
    {
        z = x + y;
        x = y;
        y = z;
    }
    return z;
}

/* ========================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    int j;
    for (j = -1; j < 24; j++)
        printf("\n n=%d  Fib=%d ", j, Fib(j));
    getchar();
}

/* ***************************************** */
