/* ОСТОВНОЕ ДЕРЕВО НАИМЕНЬШЕГО ВЕСА ПО АЛГОРИТМУ        */
/* КРУСКАЛА. Неориентированные графы. \graf\crusc03.cpp */
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#define SIZE 9
/* ================================================= */
/* МЕНЬШЕЕ ИЗ ДВУХ ЦЕЛЫХ ЧИСЕЛ                       */
int mini(int value1, int value2)
{
    setlocale(LC_ALL,"Russian");
    return ((value1 < value2) ? value1 : value2);
}

/* ================================================== */
/* ВЫЧИСЛЕНИЕ ОСТОВНОГО ДЕРЕВА ПО АЛГОРИТМУ КРУСКАЛА  */
void Crusc(int A[][SIZE], int B[][SIZE], int R[][3])
{
    int i, j, k, xmin, min, En = 0, Cn = SIZE;
    int E[SIZE * (SIZE - 1) / 2][3];
    int C[SIZE];
    for (i = 0; i < Cn; i++)
        C[i] = i;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            B[i][j] = -1;
    for (i = 0; i < SIZE; i++)
        for (j = i; j < SIZE; j++)
        {
            if (A[i][j])
            {
                E[En][0] = i;
                E[En][2] = A[i][j];
                E[En++][1] = j;
            }
        }
    printf("\n Ребра исходного графа:\n");	/* для любопытных */
    for (i = 0; i < En; i++)
        printf(" E[%d] %d %d %d\n", i, E[i][0], E[i][1], E[i][2]);
    getchar();
    while (Cn >= 0)
    {
        min = 1000;
        for (i = 0; i < En; i++)
            if ((E[i][2] < min) && (C[E[i][0]] != C[E[i][1]]))
            {
                xmin = i;
                min = E[i][2];
            }
        B[E[xmin][1]][E[xmin][0]] = B[E[xmin][0]][E[xmin][1]] = E[xmin][2];
        C[E[xmin][0]] = C[E[xmin][1]] = mini(C[E[xmin][0]], C[E[xmin][1]]);
        Cn--;
    }
    k = 0;
    for (i = 0; i < SIZE; i++)
        for (j = i; j < SIZE; j++)
            if (B[i][j] > 0)
            {
                R[k][0] = i;
                R[k][1] = j;
                R[k++][2] = B[i][j];
            }
}

/* ========================================= */
int main(void)
{
    int i, j;
    /*int A[SIZE][SIZE]=
    {
    {0,6,1,5,0,0},
    {6,0,5,0,3,0},
    {1,5,0,5,6,4},
    {5,0,5,0,0,2},
    {0,3,6,0,0,6},
    {0,0,4,2,6,0}
    };*/
    int A[SIZE][SIZE] = { 0, 7, 10, 0, 0, 0, 0, 0, 0,
                          7, 0, 0, 9, 27, 0, 0, 0, 0,
                          10, 0, 0, 8, 0, 0, 0, 0, 31,
                          0, 9, 8, 0, 0, 11, 0, 0, 0,
                          0, 27, 0, 0, 0, 0, 15, 0, 0,
                          0, 0, 0, 11, 0, 0, 15, 17, 0,
                          0, 0, 0, 0, 15, 15, 0, 21, 0,
                          0, 0, 0, 0, 0, 17, 21, 0, 32,
                          0, 0, 31, 0, 0, 0, 0, 32, 0
                        };
    int B[SIZE][SIZE], R[SIZE - 1][3];
    printf
    ("\n\n Остовное дерево наименьшего веса по Крускалу");
    getchar();
    Crusc(A, B, R);
    printf
    ("\n Взвешенная матрица смежности исходного графа:");
    for (i = 0; i < SIZE; i++)
    {
        printf("\n");
        for (j = 0; j < SIZE; j++)
            printf("%4d", A[i][j]);
    }
    getchar();
    printf
    ("\n Матрица смежности графа с остовным деревом:");
    for (i = 0; i < SIZE; i++)
    {
        printf("\n");
        for (j = 0; j < SIZE; j++)
            printf("%4d", B[i][j]);
    }
    getchar();
    printf("\n Ребра графа в остовном дереве:");
    for (i = 0; i < SIZE - 1; i++)
        printf("\n R[%d][%d]=%d", R[i][0] + 1, R[i][1] + 1, R[i][2]);
    getchar();
    return 0;
}

/* ****************************************************** */
