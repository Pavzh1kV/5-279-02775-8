/* ************************************************ */
/* Подсчет счастливых билетов для 6-значных билетов */
/* \Happy6.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
/* ================================================ */
int main()
{
    setlocale(LC_ALL,"Russian");
    int A, B, C, D, E, F, i;
    long k = 0, Happy = 0;
    for (A = 0; A <= 9; A++)
        for (B = 0; B <= 9; B++)
            for (C = 0; C <= 9; C++)
                for (D = 0; D <= 9; D++)
                    for (E = 0; E <= 9; E++)
                        for (F = 0; F <= 9; F++)
                        {
                            k++;
                            if ((A + B + C) == (D + E + F))
                                Happy++;
                        }
    printf
    ("\n Счастливых билетов %ld, всего билетов %ld",
     Happy, k);
    getchar();
}

/* ************************************************************** */
