/* Числа Фибоначчи, рекурсивный вариант.  \Fibr/c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int Fib(int n);
/* ================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    int j;
    for (j = -1; j < 15; j++)
        printf("\n n=%d  Fib=%d ", j, Fib(j));
    getchar();
}

/* ================================================== */
int Fib(int n)
{
    int x;
    if (n < 2)
        return n;
    return (Fib(n - 2) + Fib(n - 1));	/* Двойное вычисление */
}

/******************************************************/
