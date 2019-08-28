/* ********************************************** */
/* Подсчет счастливых билетов в k-значных номерах */
/* \Happyk.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
/* ===================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, j, k, *N, S1, S2, L;
    long Happy = 0, kt = 0;
    printf
    ("\n Подсчет счастливых билетов в к-значных номерах");
    printf
    ("\n Введите число цифр k (k<=9) в билетах =>");
    scanf("\ %d", &k);
    L = k / 2;
    N = (int *) calloc(k + 1, sizeof(int));
    for (i = 0; i <= k; i++)
        N[i] = 0;
    do
    {
        S1 = S2 = 0;
        kt++;
        for (j = 1; j <= L; j++)
        {
            S1 += N[j];
            S2 += N[k - j + 1];
        }
        if (S1 == S2)
            Happy++;
        i = k;
        while (N[i] == 9)
            N[i--] = 0;
        N[i]++;
    }
    while (N[0] != 1);
    printf("\n Число счастливых билетов = %ld k=%ld",
           Happy, kt);
    getchar();
}

/* ********************************************************* */
