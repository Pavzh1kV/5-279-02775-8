/* ПРЕДСТАВЛЕНИЕ НЕОРИЕНТИРОВАННОГО ГРАФА С ПОМОЩЬЮ СПИСКОВ */
/*	 СМЕЖНОСТИ. Память для массивов получаем динамически     */
/* \graflist.cpp    */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
/* ========================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int P, Q, N, u, v, i, m;
    int *ADJ, *NEXT;		/* ADJ - массив смежных вершин */
    /* NEXT - массив указателей списка */
    void Wait_Entr(void);	/* ждать нажатия ввода */
    printf
    ("\n Представление неориентированного графа с помощью списков смежности ");
    /* Ввод числа вершин P и ребер Q */
    do
    {
        printf("\n Введите число вершин P => ");
        fflush(NULL);
    }
    while (!scanf("%d", &P));
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
        while (2)
        {
            printf
            ("\nВведите вершины u и v для %d-го ребра\n",
             m);
            fflush(NULL);
            if (scanf("%d %d", &u, &v) != 2)
            {
                printf("\nОШИБКА!");
                continue;
            }
            if (u > P || u < 1 || v > P || v < 1)
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
    }
    /* Печать массивов представления графа */
    printf("\n   Представление графа \n");
    for (i = 1; i <= N; i++)
        printf(" i=%d     ADJ = %d  NEXT = %d \n", i, ADJ[i], NEXT[i]);
    Wait_Entr();
    return 0;
}

/* ============================================================ */
void Wait_Entr(void)
{
    printf("Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ************************************************************ */
