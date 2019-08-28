/* Факториал, прослеживание рекурсий
   d:\tc\xbs\massiv\fact.c Хусаинов Б.С. */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
long fact(int n) /* уже при n=13 ошибки */
{
    long f;

    printf(" %d ", n);

    if (n < 0)
        return n;

    if (n == 0)
        return 1;

    f = n * fact(n - 1);
    printf("n=%d f=%ld ", n, f);

    return (f);

}


main()
{
    setlocale(LC_ALL,"Russian");
    long a;

    a = fact(20);

    printf("\n %ld \n", a);

    getchar();

}
