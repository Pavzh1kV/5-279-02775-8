/* *************************************************** */
/* Формирование векторов смежности для гpафа           */
/* На входе: число дуг, число веpшин и дуги:(u,v)      */
/* u-начальная веpшина, v-конечная, неориентированное  */
/* ребро задавать как 2 дуги   \vectsmez.cpp           */
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
/* ===================================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int ver, dug, i, j, u, v, p, *s;
    system("clear");
    printf
    ("\n Формирование векторов смежности для графа");
    printf
    ("\n Неориентированное ребро задавать как 2 дуги");
    /* Ввод числа вершин ver и дуг dug */
    while (1)
    {
        printf("\n Введите число вершин => ");
        fflush(NULL);
        if (!scanf("%d", &ver) || ver < 2)
        {
            printf("\n ОШИБКА!");
            continue;
        }
        break;
    }
    while (1)
    {
        printf(" \n Введите число дуг => ");
        fflush(NULL);
        if (!scanf("%d", &dug))
        {
            printf("\n ОШИБКА!");
            continue;
        }
        if (dug > ver * (ver - 1))
        {
            printf("\n ОШИБКА !! слишком много дуг");
            continue;
        }
        break;
    }
    while (1)
    {
        printf
        ("\nВведите максимальную полустепень исхода в графе=>");
        fflush(NULL);
        if (!scanf("%d", &p) || p > (ver - 1))
        {
            printf("\nОШИБКА!");
            continue;
        }
        break;
    }
    /* Память под списки смежности: */
    s = (int *) calloc(ver * p, sizeof(int));
    for (j = 0; j < dug; j++)
    {
        while (1)
        {
            printf("\nВведите вершины %d-й дуги: =>",
                   j + 1);
            fflush(NULL);
            if ((scanf("%d %d", &u, &v) != 2) || v < 1 || v > ver || u < 1
                    || u > ver)
            {
                printf("\n ОШИБКА!");
                continue;
            }
            break;
        }
        for (i = 0; i < ver; i++)
            if (s[(u - 1) * p + i] == 0)
            {
                s[(u - 1) * p + i] = v;
                break;
            }
    }
    printf("\n Вектора смежности: по строкам");
    for (i = 0; i < ver; i++)
    {
        printf("\n");
        for (j = 0; j < p; j++)
            printf(" %d ", s[i * p + j]);
    }
    getchar();
    return 0;
}

/* ********************************************************* */
