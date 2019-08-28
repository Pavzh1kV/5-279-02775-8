/* ******************************************* */
/* Расстановка ферзей, Олимпиада, Бейсик */
/* d:\tc\xbs\algoritm\ferzi.c 28.10.2000 */
/* без функции, нерекурсивный вариант */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define a 8
#define b 8
#define n a
int Poza[b], Z[n], Vos[a + b - 1], Zak[a + b - 1];
main()
{
    setlocale(LC_ALL,"Russian");
    int i, j, k = 0, q, p;
    for (i = 0; i < b; i++)
        Poza[i] = i + 1;
    for (i = 0; i < a + b - 1; i++)
    {
        Vos[i] = 0;
        Zak[i] = 0;
    }
    i = 0;
PER:
    i = i + 1;
    j = i - 1;
    if (i > n)
        goto ZAP;
BOK:
    j = j + 1;
    if (j > b)
        goto ZAD;
    p = Poza[j - 1];
PRV:
    if (Vos[p - i + a - 1] || Zak[p + i - 1])
        goto BOK;
PRP:
    Vos[p - i + a - 1] = 1;
    Zak[p + i - 1] = 1;
    Poza[j - 1] = Poza[i - 1];
    Poza[i - 1] = p;
    Z[i - 1] = j;
    goto PER;
ZAP:
    k = k + 1;
    printf("\n");
    for (q = 0; q < n; q++)
        printf("%d ", Poza[q]);
ZAD:
    i = i - 1;
    if (i == 0)
        goto END;		/* i==0 - все варианты, i==n - только один */
VYP:
    j = Z[i - 1];
    p = Poza[i - 1];
    Poza[i - 1] = Poza[j - 1];
    Poza[j - 1] = p;
    Vos[p - i + a - 1] = 0;
    Zak[p + i - 1] = 0;
    goto BOK;
END:
    printf("\n Variants k=%d ", k);
    getchar();
}


/* ********************************************************** */
