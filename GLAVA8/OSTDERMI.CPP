/* ************************************************* */
/*   ВЫЧИСЛЕНИЕ ОСТОВНОГО ДЕРЕВА МИНИМАЛЬНОГО ВЕСА   */
/* \ostdermi.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
void prim(int *C, int m, int *FROM, int *TO, int *COST, int *WEIGHT);
//#include <conio.h>
//#include <alloc.h>
/* =============================================== */
/* ФУНКЦИЯ ЗАПОЛНЕНИЯ ВЗВЕШЕННОЙ МАТРИЦЫ СМЕЖНОСТИ */
int *matgraf(int k, int m)
{
    int u = 0, v = 0, x, i = 0, s;
    int *A;
    A = (int *) calloc(m * m, sizeof(int));
    while (i != k)
    {
        while (1)
        {
            printf
            ("\nВведите вершины и вес %d дуги=>",
             i + 1);
            fflush(NULL);
            s = scanf("%d%d%d", &u, &v, &x);
            if (s != 3 || u == v || u < 1 || v < 1 || u > m || v > m)
            {
                printf("Неверно!\n");
                continue;
            }
            if (x == 0)
            {
                printf
                ("Невзвешенные дуги не вводить\n");
                continue;
            }
            break;
        }
        A[(u - 1) * m + (v - 1)] = x;
        A[(v - 1) * m + (u - 1)] = x;
        i++;
    }
    return A;
}

/* ========================================================= */
/*  ГЛАВНАЯ ФУНКЦИЯ */
int main()
{
    setlocale(LC_ALL,"Russian");
    int m, n, WEIGHT, i, j;
    int *C, *FROM, *TO, *COST;
    system("clear");
    printf
    (" \nВычисление остовного дерева минимального веса для \n");
    printf
    ("          неориентированного взвешенного графа");
    while (1)
    {
        printf("\nВведите число вершин =>");
        fflush(NULL);
        if (!scanf("%d", &n) || n < 2)
        {
            printf("\n ОШИБКА!");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("\nВведите число дуг =>");
        fflush(NULL);
        if (!scanf("%d", &m) || m < 1 || m > (n * (n - 1) / 2))
        {
            printf("\nНЕВЕРНО!");
            continue;
        }
        break;
    }
    FROM = (int *) calloc(n, sizeof(int));
    TO = (int *) calloc(n, sizeof(int));
    COST = (int *) calloc(n, sizeof(int));
    C = matgraf(m, n);
    printf("\n Взвешенная матрица смежности:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%6d", C[i * n + j]);
        printf("\n");
    }
    getchar();

    prim(C, n, FROM, TO, COST, &WEIGHT);
    for (i = 0; i < n - 1; i++)
        printf("\n i= %d   FROM=%d, TO=%d, COST=%d",
               i + 1, FROM[i], TO[i], COST[i]);
    printf("\n Вес = %d \n", WEIGHT);
    fflush(NULL);
    getchar();
    return 0;
}

/* ===================================================== */
/* ФУНКЦИЯ ВЫЧИСЛЕНИЯ ОСТОВНОГО ДЕРЕВА МИНИМАЛЬНОГО ВЕСА */
void prim(int *C, int m, int *FROM, int *TO, int *COST, int *WEIGHT)
{
    int i, j, jk, k, L, edges, next, numun;
    int *unchsn, *vertex, *light;
    unchsn = (int *) calloc(m - 1, sizeof(int));
    vertex = (int *) calloc(m - 1, sizeof(int));
    light = (int *) calloc(m - 1, sizeof(int));
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (C[i * m + j] == 0)
                C[i * m + j] = 10000;
            printf(" %d ", C[i * m + j]);
        }
        printf("\n");
    }
    /* Инициализация переменных */
    edges = 0;			/* число ребер ОДМВ */
    next = m;			/* очередная вершина, присоединяемая к ОДМВ */
    numun = m - 1;		/* число невыбранных вершин */
    *WEIGHT = 0;		/* общий вес ОДМВ */
    for (i = 1; i <= numun; i++)
    {
        unchsn[i] = i;		/* массив невыбранных вершин */
        vertex[i] = next;	/* вершины частичного ОДМВ, ближайшие  */
        /* к вершине unchsn[i]   */
        light[i] = C[(i - 1) * m + next - 1];	/* наименьший вес ребра из
						   vertex[i] к unchsn[t]; */
    }
    /* Основной цикл: обновление таблицы ребер нaименьшего веса,
       соединяющих каждую невыбранную вершину с какой-нибудь выбранной */
    while (1)
    {
        for (i = 1; i <= numun; i++)
        {
            j = unchsn[i];
            jk = C[(j - 1) * m + next - 1];
            if (light[i] <= jk)
                continue;
            vertex[i] = next;
            light[i] = jk;
        }
        /* Отыскание ребра с наименьшим весом, соединяющего невыбранную
           вершину с выбранной */
        k = 1;
        L = light[1];
        for (i = 1; i <= numun; i++)
        {
            if (light[i] >= L)
                continue;
            L = light[i];
            k = i;
        }
        /*  Включение ребра в ОДМВ */
        edges = edges + 1;
        FROM[edges - 1] = unchsn[k];
        TO[edges - 1] = vertex[k];
        COST[edges - 1] = L;
        *WEIGHT = *WEIGHT + L;
        next = unchsn[k];
        /* Исключение вновь выбранной вершины из списка невыбранных */
        light[k] = light[numun];;
        unchsn[k] = unchsn[numun];
        vertex[k] = vertex[numun];
        /* Остались ли невыбранные вершины? */
        numun = numun - 1;
        if (numun == 0)
            break;
    }
    free(unchsn);
    free(vertex);
    free(light);
}

/* ********************************************************** */
