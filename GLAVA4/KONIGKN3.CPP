/* ***************************************************** */
/* Обход конем шахматной доски.  Хусаинов Б.С. 30.11.02 */
/* c:\bc\xbs\algoritm\konigkn3.cpp */
#include <stdio.h>
#include <locale.h>
//#include <conio.h>
int d[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2},
    {1, -2}, {-1, 2}, {-1, -2}
};				/* возможные перемещения коня
				   относительно текущей клетки */
int M[20][20];			/* матрица числа возможных переходов к каждой клетке */
int field[20][20];		/* матрица шахматной доски */
int cnt1 = 0, cnt2 = 0;		/* счетчики для определения сложности задачи */
int x, y;			/* координаты клетки доски */
int size;			/* размер стороны доски - от 5 до 20 */
int order = 1;			/* номер хода, при котором конь попадает в клетку (x,y) */
int p;
FILE *fout;			/* файл для отладочных данных о движении коня */
void set(int, int);		/* функция для корректировки матрицы числа переходов */
/* ================================================================== */
/* ПЕЧАТЬ ХОДОВ КОНЯ ПО ДОСКЕ И МАТРИЦЫ ЧИСЛА ПЕРЕХОДОВ */
void printall()
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%3d ", field[i][j]);
        /*		  printf("   \t");
        		  for (j=0;j<size;j++)
        			 printf("%3d ",M[i][j]);*/
        if (size < 20)
            printf("\n");
    }
}

/* ============================================= */
/* ШАГ КОНЯ НА СЛЕДУЮЩУЮ КЛЕТКУ ДОСКИ */
void go_next()
{
    int k, xn, yn;
    int min = -1;
    p = 0;
    for (k = 0; k <= 7; k++)
    {
        xn = x + d[k][0];
        yn = y + d[k][1];
        cnt2++;
        if ((xn < 0) || (xn >= size) || (yn < 0) || (yn >= size))
            continue;
        if (((min == -1) || (M[xn][yn] < M[x + d[min][0]][y + d[min][1]]))
                && (M[xn][yn] != 0) && (field[xn][yn] == 0))
            min = k;
        cnt1++;
    }
    x += d[min][0];
    y += d[min][1];
    field[x][y] = ++order;
    M[x][y] = 0;
    p = 1;
    /*  fprintf(fout,"ход=%d  cnt1=%d\n",order,cnt1); printall();*/
    set(x, y);
}

/* ====================================================== */
/* КОРРЕКТИРОВКА ТАБЛИЦЫ ПЕРЕХОДОВ ПОСЛЕ ХОДА КОНЯ  */
void set(int i, int j)
{
    int k, in, jn;
    for (k = 0; k <= 7; k++)
    {
        in = i + d[k][0];
        jn = j + d[k][1];
        cnt2++;
        if ((in < 0) || (in >= size) || (jn < 0) || (jn >= size))
            continue;
        if ((M[in][jn] != 0) && (field[in][jn] != 0))
            M[in][jn]--;
        cnt1++;
    }
}

/* ====================================================== */
/* НАЧАЛЬНАЯ УСТАНОВКА МАТРИЦЫ ПЕРЕХОДОВ */
void setchanges()
{
    int i, j, in, jn, k;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
        {
            M[i][j] = 0;
            if (field[i][j] == 0)
                for (k = 0; k <= 7; k++)
                {
                    in = i + d[k][0];
                    jn = j + d[k][1];
                    cnt2++;
                    if ((in < 0) || (in >= size) || (jn < 0)
                            || (jn >= size))
                        continue;
                    if ((field[in][jn] == 0) || (field[in][jn] == order))
                        M[i][j]++;
                    cnt1++;
                }
        }
}

/* ========================================================= */
/* ОБХОД КОНЕМ ШАХМАТНОЙ ДОСКИ */
void go_kon(int x, int y)
{
    setchanges();
    do
        go_next();
    while (order < size * size);
}

/* ==========================================================*/
main()
{
    setlocale(LC_ALL,"Russian");
    system("clear");
    printf
    ("Обход конем шахматной доски размером от 5*5 до 20*20 клеток\n");
    printf
    ("Введите размерность шахматного поля (от 5 до 20) => ");
    scanf("%d", &size);
    if ((size > 20) || (size < 5))
        return 0;
    printf
    ("Введите координаты нач. клетки\nСтрока => ");
    scanf("%d", &x);
    printf("Столбец => ");
    scanf("%d", &y);
    x--;
    y--;
    if ((x < size) && (x >= 0) && (y < size) && (y >= 0))
        field[x][y] = 1;
    else
        return 0;
    fout = fopen("ff", "w");
    go_kon(x, y);
    if (size == 20)
        textmode(64);
    printf("\nПорядок обхода имеет вид:\n");
    printall();
    fprintf(fout, "cnt1=%d cnt2=%d", cnt1, cnt2);
    printf("\n Конец задачи ");
    getchar();
    return 0;
}

/* ********************************************************* */
