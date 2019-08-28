/* **************************************************************** */
/* ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА СЕТИ - МЕТОД ФОРДА. Граф ациклический  */
/* Сеть представлена массивом вершин V[n] и двухмерным массивом дуг*/
/* GPO[k][2]. [36],c,125. \fordsort.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define sn 100
#define sk 150
void ford(int V[sn], int GPO[sk][2], int n, int k);
int main()
{
    setlocale(LC_ALL,"Russian");
    int n, k, i, s, e;
    int GPO[sk][2], V[sn];
    printf
    ("\n Топологическая сортировка сети методом Форда ");
    printf("\n Введите число вершин n=>");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        V[i] = i;
    printf("\n Введите число дуг k=>");
    scanf(" %d", &k);
    for (i = 1; i <= k; i++)
    {
        printf
        (" Введите номера вершин %d-й дуги u v =>",
         i);
        while (1)
        {
            if (scanf("%d %d", &s, &e) != 2)
            {
                printf
                ("Ошибка: введите 2 номера через пробел=>");
                fflush(NULL);
                continue;
            }
            if (s < 1 || s > n || e < 1 || e > n)
            {
                printf
                ("Ошибка: вершины должны лежать в пределах от 1 до %d=>",
                 n);
                continue;
            }
            else
                break;
        }
        GPO[i][1] = s;
        GPO[i][2] = e;
    }
    ford(V, GPO, n, k);
    /* Печать ранжированной сети */
    printf("\n Новая нумерация вершин\n");
    for (i = 1; i <= n; i++)
        printf("  %d ", V[i]);
    getchar();
    printf("\n Новые дуги\n ");
    for (i = 1; i <= k; i++)
        printf(" %d->%d", GPO[i][1], GPO[i][2]);
    getchar();
    printf("\n");
}

/*  ********************************************** */
void ford(int V[sn], int GPO[sk][2], int n, int k)
{
    int sumlam0, sumlam1, m, i, j;
    int lambda[sn], vh[sn];
    sumlam0 = 0;
    for (i = 1; i <= n; i++)
        lambda[i] = 0;
    sumlam1 = 1;
    /* Общий цикл - вычисление рангов */
    while (sumlam0 != sumlam1)  	/* изменились ли lambda[i] ? */
    {
        sumlam1 = sumlam0;
        /* Можно посмотреть, как меняются lambda[i] на каждом шаге */
        for (i = 1; i <= n; i++)
            if (lambda[i] >= n)
                printf(" %d ", lambda[i]);
        getchar();
        for (j = 1; j <= n; j++)
            for (i = 1; i <= k; i++)
                if (V[j] == GPO[i][2]
                        && lambda[j] < (lambda[GPO[i][1]] + 1))
                    lambda[j] = lambda[GPO[i][1]] + 1;
        sumlam0 = 0;
        for (i = 1; i <= n; i++)
            sumlam0 += lambda[i];
    }				/* конец общего цикла, ранги вычислены  */
    /*  Далее участок упорядочения вершин в исходной нумерации
       по возрастанию ранга */
    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++)
            if (lambda[i] > lambda[j])
            {
                m = lambda[i];
                lambda[i] = lambda[j];
                lambda[j] = m;
                m = V[i];
                V[i] = V[j];
                V[j] = m;
            }
    /* Вычисление новых номеров вершин */
    for (i = 1; i <= n; i++)
        vh[i] = i - 1;
    /* Восстановление возрастания вершин в исходной нумерации */
    for (i = 1; i < n; i++)
        for (j = i + 1; j <= n; j++)
            if (V[i] > V[j])
            {
                m = V[i];
                V[i] = V[j];
                V[j] = m;
                m = vh[i];
                vh[i] = vh[j];
                vh[j] = m;
            }
    /* Новая нумерация вершин после упорядочения */
    for (i = 1; i <= n; i++)
        V[i] = vh[i];
    /* Участок перекодирования сети новыми номерами вершин */
    for (j = 1; j <= k; j++)
    {
        GPO[j][1] = vh[GPO[j][1]];
        GPO[j][2] = vh[GPO[j][2]];
    }
    for (j = 0; j < n; j++)
        printf(" Rng[%d]=%d", j, lambda[j + 1]);
}

/* ****************************************************** */
