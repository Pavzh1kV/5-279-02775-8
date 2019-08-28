/* РАБОТА СО СТЕКОМ В ВЕКТОРНОЙ ПАМЯТИ
   d:\tc\xbs\massiv\n10_n.c,  головной файл */
/* Хусаинов Б.С.   3.01.2002 */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
typedef int EL;
#include "incl_stc.c"	/*файл с дескриптором стека и
					   функциями для работы со стеком */
int In_el(EL * el);
int Show_stc(STC s);
static long N;
int B;
EL e;
/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int n, m, r;
    long M1;
    printf
    ("  Вывод десятичного числа как числа с другим основанием \n");
    if (Crt_stc(&s1) == -1)
        return -1;
    printf
    ("\n Введите через пробел неотрицательное десятичное число и \
основание (2<=B<=9) \n=>");
    scanf("%ld %d", &N, &B);
    M1 = N;
    while ((r = In_el(&e)) == 0)
    {
        n = Push_el(&s1, e);
        if (n == -1)
        {
            printf("\n Переполнение стека!!!");
            getchar();
            return -1;
        }
    }
    printf("\n Содержимое стека:");
    Show_stc(s1);
    getchar();
    printf
    ("\nДесятичное число %ld при основании %d будет:\n",
     M1, B);
    while (!Pop_el(&s1, &m))
        printf("%d", m);
    Destroy_stc(&s1);
    getchar();
    return 0;
}

/* ============================================================== */
int In_el(EL * el)
{
    if (N != 0)
    {
        *el = N % B;
        N = N / B;
        return 0;
    }
    else
        return -1;
}

/* ========================================================= */
int Show_stc(STC s)
{
    int i;
    if (s.un == NULL)
        return -1;
    for (i = 0; i <= s.uv; i++)
        printf(" %d", s.un[i]);
    getchar();
    return 0;
}

/* ********************************************************* */
