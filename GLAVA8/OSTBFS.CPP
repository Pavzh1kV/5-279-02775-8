/* **************************************************** */
/* ПОСТРОЕНИЕ ОСТОВНОГО ДЕРЕВА ГРАФА ПОИСКОМ В ШИРИНУ   */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
/* ==================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int *BFS(int ADJ[], int NEXT[], int P, int V);
    int P, Q, N, u, v, i, j, m, s;
    int *ADJ, *NEXT, *vector;	/* ADJ - массив смежных вершин */
    /* NEXT - массив указателей списка */
    /* vector - результаты вычисления остовного дерева */
    printf
    ("\n\n Поиск в ширину остовного дерева графа");
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
        if (Q > P * (P - 1) / 2)
        {
            printf
            ("\n ОШИБКА !! слишком много ребер");
            continue;
        }
        break;
    }
    i = P + 1;
    N = P + 2 * Q;		/* N - размер массивов ADJ и NEXT */
    ADJ = (int *) calloc(N + 1, sizeof(int));
    NEXT = (int *) calloc(N + 1, sizeof(int));
    /* Инициализация массивов ADJ и NEXT нулями */
    for (m = 1; m <= P; m++)
    {
        ADJ[m] = 0;
        NEXT[m] = 0;
    }
    /* Ввод Q ребер и организация связанного списка */
    for (m = 1; m <= Q; m++)
    {
        while (1)
        {
            printf("\nВведите вершины %d-го ребра =>",
                   m);
            fflush(NULL);
            s = scanf("%d%d", &u, &v);
            if (s != 2 || u == v || u < 1 || v < 1 || u > P || v > P)
            {
                printf("Неверно!\n");
                continue;
            }
            break;
        }
        /* KK:*/ ADJ[i] = v;
        ADJ[i + 1] = u;
        NEXT[i] = NEXT[u];
        NEXT[u] = i;
        NEXT[i + 1] = NEXT[v];
        NEXT[v] = i + 1;
        i = i + 2;
    }
    /* Печать массивов представления графа */
    /*   printf("\n   Представление графа \n");
      for (i=1; i<=N; i++)
    	printf(" i=%d     ADJ = %d  NEXT = %d \n",i,ADJ[i],NEXT[i]);
    	getchar();*/
    /*Вызов процедуры BFS для нахождения остовного дерева*/
PPP:
    printf
    ("\n Введите номер начальной вершины =>");
    scanf("%d", &v);
    if (v < 1 || v > P)
    {
        printf("\n Ошибка в номере вершины");
        goto PPP;
    }
    /*Вызов функции BFS */
    vector = BFS(ADJ, NEXT, P, v);
    /*Вывод остовного дерева*/
    printf("\n Остовное дерево \n");
    j = 0;
    for (i = 1; i <= P; i++)
    {
        if (vector[i] > 0)
        {
            j++;
            printf("\n%d-е ребро:  %d   %d", j, i, vector[i]);
        }
    }
    free(vector);
    getchar();
    return 0;
}

/*Процедура нахождения остовного дерева*/
int *BFS(int ADJ[], int next[], int P, int v)
{
    int *vizit, *list;
    int x, y, ptr, j, m, asd;
    int *vector;
    /*Инициализация массивов */
    vector = (int *) calloc(P, sizeof(int));
    list = (int *) calloc(P, sizeof(int));
    vizit = (int *) calloc(P, sizeof(int));
    for (j = 1; j <= P; j++)
    {
        list[j] = 0;
        vizit[j] = 0;
        vector[j] = 0;
    }
    list[P + 1] = 0;
    x = 1;
    y = 1;
    /*Первый просмотр начальной вершины */
    list[1] = v;
    vector[v] = 0;
    vizit[v] = 1;
    while (1)
    {
        m = list[x];
        ptr = m;
        asd = 0;
        while (asd == 0)
        {
            ptr = next[ptr];
            if (ptr != 0)
            {
                j = ADJ[ptr];
                if (vizit[j] == 0)
                {
                    y++;
                    list[y] = j;
                    vizit[j] = y;
                    vector[j] = m;
                }
            }
            else
            {
                x = x + 1;
                asd = 1;
            }
        }
        if (list[x] == 0)
            break;
    }
    return vector;
}

/* ************************************* */
