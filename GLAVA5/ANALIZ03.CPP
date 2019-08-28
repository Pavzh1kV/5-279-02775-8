/* *************************************************** */
/* Исследование сложности алгоритмов сортировки по времени
упорядочения одного и того же массива случайных чисел.
Сгенерирован массив из 15000 случайных чисел. Начальное
кол-во  элементов  в  массиве  для  сортировки прямыми и
улучшенными методами - 1000, шаг нарастания - 1000.
Результаты сведены в таблицу, файл \analiz.txt */
/*  1-ый столбик - кол-во сортируемых элементов,
	 следующие - время сортировки в мсек:
 2	- сортировка прямым выбором;
 3	- сортировка прямым включением;
 4	- сортировка методом пузырька;
 5	- шейкерная сортировка;
 6 - обменная сортировка [37, c.85];
 7	- сортировка методом Шелла;
 8	- сортировка деревом;
 9	- быстрая сортировка Хоара.
*/
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#include <time.h>
//#include <alloc.h>
#include <stdlib.h>
#define Maxn 15000		/* макс. кол-во сортируемых элементов */
#include "INCL_SRT.CPP"
void Analis(void);
void ExchngSort(int A[], int mm);
/* ===================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    system("clear");
    printf
    ("\nИсследование сложности алгоритмов сортировки");
    Analis();			/* вызов функции исследования алгоритмов */
    return 0;
}

/* ****************************************************** */
void Analis(void)
{
    int i, j;
    FILE *fout;
    fout = fopen("c:\\bc\\xbs\\sort\\analiz.txt", "w");
    int a[Maxn], b[Maxn];	/* b - массив случайных чисел,
				   a - массив на вход функций сортировки */
    int N = 1000;		/* начальное кол-во элементов */
    clock_t t1, t2, tt, ts;
    int ttt = 100;
    system("clear");
    printf
    ("\nЗаполнение массива b случайными числами");
    for (i = 0; i < Maxn; i++)
        b[i] = rand();
    printf
    ("\nПОДОЖДИТЕ! Идёт анализ методов сортировки\n");

    while (1)
    {
        printf("\n %7d", N);
        fprintf(fout, "\n %d", N);
        /* СОРТИРОВКА ПРЯМЫМ ВЫБОРОМ  */
        for (i = 1; i <= N; i++)
            a[i] = b[i];
        t1 = clock();
        StrSel(a, N);
        t2 = clock();
        tt = t2 - t1;
        printf("%5ld", tt);
        fprintf(fout, "%5ld", tt);
        /* СОРТИРОВКА ПРЯМЫМ ВКЛЮЧЕНИЕМ  */
        for (i = 1; i <= N; i++)
            a[i] = b[i];
        t1 = clock();
        Sis(a, N);
        t2 = clock();
        tt = t2 - t1;
        printf("%5ld", tt);
        fprintf(fout, "%5ld", tt);
        /* СОРТИРОВКА МЕТОДОМ ПУЗЫРЬКА  */
        for (i = 1; i <= N; i++)
            a[i] = b[i];
        t1 = clock();
        BblSort(a, N);
        t2 = clock();
        tt = t2 - t1;
        printf("%5ld", tt);
        fprintf(fout, "%5ld", tt);
        /* ШЕЙКЕРНАЯ СОРТИРОВКА */
        for (i = 1; i <= N; i++)
            a[i] = b[i];
        t1 = clock();
        ShkrSort(a, N);
        t2 = clock();
        tt = t2 - t1;
        printf("%5ld", tt);
        fprintf(fout, "%5ld", tt);
        /* ОБМЕННАЯ СОРТИРОВКА по Топпу */
        for (i = 1; i <= N; i++)
            a[i] = b[i];
        t1 = clock();
        ExchngSort(a, N);
        t2 = clock();
        tt = t2 - t1;
        printf("%5ld", tt);
        fprintf(fout, "%5ld", tt);
        /* СОРТИРОВКА МЕТОДОМ ШЕЛЛА */
        ts = 0;
        for (j = 0; j < ttt; j++)
        {
            for (i = 1; i <= N; i++)
                a[i] = b[i];
            t1 = clock();
            Shell(a, N);
            t2 = clock();
            tt = t2 - t1;
            ts = ts + tt;
        }
        printf("%5ld/100", ts);
        fprintf(fout, "%5ld/100", ts);
        /* СОРТИРОВКА ПИРАМИДОЙ (ДЕРЕВОМ) */
        ts = 0;
        for (j = 0; j < ttt; j++)
        {
            for (i = 1; i <= N; i++)
                a[i] = b[i];
            t1 = clock();
            HeapSort(a, N);
            t2 = clock();
            tt = t2 - t1;
            ts = ts + tt;
        }
        printf("%5ld/100", ts);
        fprintf(fout, "%5ld/100", ts);
        /* БЫСТРАЯ СОРТИРОВКА ХОАРА */
        ts = 0;
        for (j = 0; j < ttt; j++)
        {
            for (i = 1; i <= N; i++)
                a[i] = b[i];
            t1 = clock();
            QuickSort(a, 0, N - 1);
            t2 = clock();
            tt = t2 - t1;
            ts = ts + tt;
        }
        printf("%5ld/100", ts);
        fprintf(fout, "%5ld/100", ts);

        N = N + 1000;
        if (N > Maxn)
            break;
    }
    printf("\n Конец вычислений");
    getchar();
}

/* ******************************************************** */
