/* СОЗДАНИЕ НЕВЗВЕШЕННОЙ МАТРИЦЫ СМЕЖНОСТИ ДЛЯ ОРИЕНТИРО- */
/* ВАННОГО И НЕОРИЕНТИРОВАННОГО ГРАФА \matsmz.cpp         */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
/* ===================================================== */
/* ФУНКЦИЯ ЗАПОЛНЕНИЯ  МАТРИЦЫ СМЕЖНОСТИ */
/* p=1 - ориентированный граф,
	р=2 - неориентированный граф */
int *matrsmz(int k, int m, int p)
{
    int u = 0, v = 0, i = 0, s;
    int *A;
    A = (int *) calloc(m * m, sizeof(int));
    while (i != k)
    {
        printf("\nВведите вершины %d дуги=>", i + 1);
        fflush(NULL);
        s = scanf("%d%d", &u, &v);
        if (s != 2 || u == v || u < 1 || v < 1 || u > m || v > m)
        {
            printf("Неверно!\n");
            continue;
        }
        A[(u - 1) * m + (v - 1)] = 1;
        if (p == 2)		/* неориентированный граф */
            A[(v - 1) * m + (u - 1)] = 1;
        i++;
    }
    return A;
}

/* =================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ */
int main(void)
{
    setlocale(LC_ALL,"Russian");
    int P, Q, i, j, s, *MS;
    char L;
    system("clear");
    printf
    ("\n Создание матрицы смежности графа\n");
    while (1)
    {
        printf("\nОриентирован ли граф? (д/н) =>");
        fflush(NULL);
        L = getchar();
        if (L != 'д' && L != 'н' && L != 'Д' && L != 'Н')
        {
            printf("Неверно!\n");
            continue;
        }
        break;
    }
    if (L == 'д' || L == 'Д')
        s = 1;			/* s=1 - ориентированный граф */
    else
        s = 2;			/* p=2 - неориентированный граф */
    /* Ввод числа вершин P и ребер Q */
    while (1)
    {
        printf("\n Введите число вершин P => ");
        fflush(NULL);
        if (!scanf("%d", &P) || P < 2)
        {
            printf("\n ОШИБКА!");
            continue;
        }
        break;
    }
    while (1)
    {
        printf(" \n Введите число ребер Q => ");
        fflush(NULL);
        if (!scanf("%d", &Q))
        {
            printf("\n ОШИБКА!");
            continue;
        }
        if (Q > P * (P - 1) / s)
        {
            printf
            ("\n ОШИБКА !! слишком много ребер");
            continue;
        }
        break;
    }
    MS = matrsmz(Q, P, s);
    printf
    ("Невзвешенная матрица смежности:\n");
    for (i = 0; i < P; i++)
    {
        for (j = 0; j < P; j++)
            printf("%6d", MS[i * P + j]);
        printf("\n");
    }
    getchar();
    return 0;
}

/* ********************************************************* */
