/* ВЫЧИСЛЕНИЕ ОСТОВНОГО ДЕРЕВА ДЛЯ НЕОРИЕНТИРОВАННОГО ГРАФА */
/* ПО АЛГОРИТМУ ПОИСКА В ГЛУБИНУ \ostdfs.cpp.               */
/*	массивы динамические, проверка исходных данных           */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
int P, Q, T, u, v, words, i, m, k, j;
int DFS(int *ADJ, int *NEXT, int v, int *TREE, int P, int *T);
/* ======================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int P, Q, N, u, v, i, m, s;
    int *ADJ, *NEXT, *TREE;	/* ADJ - массив смежных вершин */
    /* NEXT - массив указателей списка */
    /* TREE - двухмерный массив ребер дерева */
    printf
    ("\n\n Вычисление остовного дерева неориентированного графа");
    /* Ввод числа вершин P и ребер Q */
    while (1)
    {
        printf("\n Введите число вершин P => ");
        fflush(NULL);
        if ((s = scanf("%d", &P)) == 0 || P < 2)
        {
            printf("\n ОШИБКА");
            continue;
        }
        break;
    }
    while (1)
    {
        printf(" \n Введите число ребер Q => ");
        fflush(NULL);
        if ((s = scanf("%d", &Q) == 0) || Q < 1)
        {
            printf("\n ОШИБКА");
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
    TREE = (int *) calloc(P * 2, sizeof(int));
    /* Инициализация массивов cписков смежности ADJ и NEXT  */
    for (m = 1; m <= P; m++)
    {
        ADJ[m] = 0;
        NEXT[m] = 0;
    }
    /* Ввод Q ребер и организация  списков смежности */
    for (m = 1; m <= Q; m++)
    {
        while (1)
        {
            printf
            ("\nВведите вершины u и v для %d-го ребра\n",
             m);
            fflush(NULL);
            s = scanf("%d %d", &u, &v);
            if (s != 2 || u > P || u < 1 || v > P || v < 1)
            {
                printf
                ("\n ОШИБКА в номере вершины!!!");
                continue;
            }
            break;
        }
        ADJ[i] = v;
        ADJ[i + 1] = u;
        NEXT[i] = NEXT[u];
        NEXT[u] = i;
        NEXT[i + 1] = NEXT[v];
        NEXT[v] = i + 1;
        i = i + 2;
        u = 0;
        v = 0;			/* для исключения ошибок ввода */
    }

    /* Печать массивов представления графа */
    printf("\n   Представление графа \n");
    for (i = 1; i <= N; i++)
        printf(" i=%d     ADJ = %d  NEXT = %d \n", i, ADJ[i], NEXT[i]);
    getchar();
    /* Вызов функции построения остовного дерева для заданной вершины */
    while (1)
    {
        while (2)
        {
            printf
            ("\n Введите начальную вершину графа");
            printf
            ("\n или 0 для завершения работы=>");
            fflush(NULL);
            if (!scanf("%d", &v))
            {
                printf("\n ОШИБКА!");
                continue;
            }
            if (v == 0)
                return 0;
            if (v < 1 || v > P)
            {
                printf
                ("\n ОШИБКА в номере вершины !!!");
                continue;
            }
            break;
        }
        /* Вызов функции DFS для нахождения остовного дерева */
        DFS(ADJ, NEXT, v, TREE, P, &T);

        /* Печать остовного дерева */
        printf
        ("\n Печать ребер остовного дерева \n");
        printf("\n    Остовное дерево \n");
        k = T - 1;
        for (i = 1; i <= k; i++)
        {
            for (j = 0; j < 2; j++)
                printf(" TREE[%d,%d] = %d ", i, j, TREE[i * 2 + j]);
            printf("\n");
        }
        getchar();
        if (T != P)
        {
            printf("\n Сеть не связна\n ");
            getchar();
        }
    }
}

/* ==================================================== */
/* ФУНКЦИЯ НАХОЖДЕНИЯ ОСТОВНОГО ДЕРЕВА */
int DFS(int *ADJ, int *NEXT, int v, int *TREE, int P, int *TT)
{
    int *VISIT, *STORE;
    int PTR, w;
    VISIT = (int *) calloc(P + 1, sizeof(int));
    STORE = (int *) calloc(P * 2 + 1, sizeof(int));
    PTR = 0;
    T = 1;
    /* Просмотр и обработка всех вершин */
    for (i = 1; i <= P; i++)
    {
        VISIT[v] = i;
        k = v;
        while (1)
        {
            k = NEXT[k];	/* следующая смежная с v вершина */
            if (k > 0)  	/* есть ли смежные вершины */
            {
                w = ADJ[k];	/* следующая смежная с v вершина */
                if (VISIT[w] > 0)	/* проверена ли вершина w? */
                    continue;
                else
                    break;
            }
            if (PTR == 0)
            {
                *TT = T;
                return 0;
            }
            /* стек пуст */
            /* Удалим два верхних элемента из стека */
            v = STORE[PTR];
            k = STORE[PTR - 1];
            STORE[PTR] = 0;
            STORE[PTR - 1] = 0;
            PTR = PTR - 2;
        }
        /* Присоединение ребра (v,w) к остовному дереву */
        TREE[T * 2 + 0] = v;
        TREE[T * 2 + 1] = w;
        T = T + 1;
        /* Имеем ли уже остовное дерево ? */
        if (T == P)
        {
            *TT = T;
            return 0;
        }
        /* Заносим k,v в стек и проверяем w */
        STORE[PTR + 1] = k;
        STORE[PTR + 2] = v;
        PTR = PTR + 2;
        v = w;
    }				/* конец основного цикла */
}

/* ****************************************************** */
