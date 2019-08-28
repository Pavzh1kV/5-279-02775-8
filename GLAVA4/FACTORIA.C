/* ***************************************** */
/* Факториал, рекурсивный вариант \factoria.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
double fact(int n)
{
    if (n < 0)
        return n;		/* ошибка в параметре */
    if (n == 0)
        return 1;
    else
        return (n * fact(n - 1));
}

/* ============================================ */
main()
{
    setlocale(LC_ALL,"Russian");
    double a;
    a = fact(20);
    printf("\n %lf \n", a);
    getchar();
    exit(0);
}

/* ********************************************* */
