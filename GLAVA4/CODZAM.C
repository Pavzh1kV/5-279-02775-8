/* **************************************************************** */
/* Кодовый замок, одновременное нажатие 3 кнопок из 9 */
/*   \algoritm\codzam.c */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
    setlocale(LC_ALL,"Russian");
    int i0 = 1, count = 0, i, j, k;
    int n = 9;
    printf
    ("\n Кодовый замок, одновременное нажатие 3 кнопок из %d \n",
     n);
    for (i = i0; i <= n; i++)
        for (j = i + 1; j <= n - 1; j++)
        {
            for (k = j + 1; k <= n; k++)
            {
                printf("   %d %d %d", i, j, k);
                count++;
            }
            getchar();
            printf("\n");
        }
    printf("\n Всего возможных ключей %d", count);
    getchar();
}

/* ********************************************************** */
