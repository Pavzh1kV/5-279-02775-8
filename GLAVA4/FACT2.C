/* Факториал, прослеживание рекурсий \fact2.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
double f(int n)
{
    double x = 0;
    printf(" %d ", n);
    if (n < 0)
        return n;
    if ((n == 0) || (n == 1))
        return 1;
    x = n * f(n - 1);
    printf("\n n=%d x=%le ", n, x);
    return (x);
}

main()
{
    setlocale(LC_ALL,"Russian");
    double a;
    a = f(20);
    printf("\n %le \n", a);
    getchar();
}
