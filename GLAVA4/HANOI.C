/* ************************************ */
/* Ханойские башни */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
FILE *out;
/* ============================================== */
void hanoi(int m, char A, char C, char B)
{
    printf("\n Ханойские башни, дисков %d", m);
    printf("\n m=%d %c %c %c ", m, A, B, C);
    getchar();
    fprintf(out, "\n m=%d %c %c %c ", m, A, B, C);
    if (m > 0)
    {
        hanoi(m - 1, A, B, C);
        printf(" %c => %c ", A, C);	/* getchar(); */
        fprintf(out, " %c => %c", A, C);
        hanoi(m - 1, B, C, A);
    }
}

/* ============================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    char a = 'A', b = 'B', c = 'C';
    printf("\n Ханойские башни:\n");
    out = fopen("c:\\bc\\hanoi3.rez", "w");
    if (out == NULL)
        printf("\n Не открылся");
    getchar();
    printf("\n");
    fprintf(out, "\n");
    hanoi(4, a, b, c);
    getchar();
    return 0;
}

/* ********************************************** */
