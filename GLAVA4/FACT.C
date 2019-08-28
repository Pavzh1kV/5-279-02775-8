/* ******************************************** */
/* Факториал, прослеживание рекурсий \fact.c    */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define k 6
int g;
/* ============================================ */
double fact(int n)
{
    double f;
    printf("\n nf=%d an=%p ff=%lf af=%p", n, &n, f, &f);
    /* при движении в глубину */
    if (n < 0)
        return n;		/* ошибка в параметре */
    if (n == 0)
        return 1;
    else
    {
        f = n * fact(n - 1);
        printf("\n nb=%d an=%p fb=%lf af=%p", n, &n, f, &f);
        /* при движении назад */
        return (f);
    }
}

int main(void)
{
    setlocale(LC_ALL,"Russian");
    double a;
    int *p, *r;
    double (*fac) (int);
    int (*mai) (void);
    mai = main;
    fac = fact;
    p = &g;
    printf("\n befor a=%lf aa=%p ag=%p", a, &a, p);
    printf("\n fact=%p main=%p", fac, mai);
    a = fact(7);
    printf("\n after a=%lf aa=%p", a, &a);
    printf("\n %lf \n", a);
    getchar();
}

/* ************************************************ */
