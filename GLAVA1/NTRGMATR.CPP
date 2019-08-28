/* ************************************************ */
/* РАБОТА С  ТРЕУГОЛЬНЫМИ МАССИВАМИ                 */
/* Вычисление суммы, разности, произведения и детер-*/
/* минанта массивов. \ntrgmatr.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
void umn_mtrn(float *a, float *b, float *c, int n);
void slog_matr(float *a, float *b, float *c, int n);
void razn_matr(float *a, float *b, float *c, int n);
double DETV(float *c, int n);
double DETN(float *c, int n);
void prn_mtrn(float *c, int n);
void umn_mtrv(float *a, float *b, float *c, int n);
void prn_mtrv(float *c, int n);
/* =========================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int n, nn, i, j, k;
    float *a, *b, *c;
    double det;
    system("clear");
    printf
    ("\n  Работа с нижними треугольными массивами,");
    printf
    ("\n представленными в виде одномерного массива ");
    printf
    ("\n Введите размер исходных (n*n)массивов: n=>");
    scanf("%d", &n);
    nn = (n * n + n) / 2;
    a = (float *) calloc(nn, sizeof(float));
    b = (float *) calloc(nn, sizeof(float));
    c = (float *) calloc(nn, sizeof(float));
    system("clear");
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
        {
            printf
            ("\nВведите элемент массива A[%d][%d]=>",
             i, j);
            scanf("%f", &a[(i * i + i) / 2 + j]);
        }
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
        {
            printf
            ("\nВведите злемент массива B[%d][%d]=>",
             i, j);
            scanf("%f", &b[(i * i + i) / 2 + j]);
        }
    printf("\n Исходный массив А:\n");
    prn_mtrn(a, n);
    getchar();
    printf("\n Исходный массив В:\n");
    prn_mtrn(b, n);
    getchar();
    slog_matr(a, b, c, n);
    printf("\n Сумма массивов С=А+В:");
    prn_mtrn(c, n);
    getchar();
    razn_matr(a, b, c, n);
    printf("\n Разность массивов С=А-В:");
    prn_mtrn(c, n);
    getchar();
    umn_mtrn(a, b, c, n);
    printf("\n Произведение массивов С=А*В:");
    prn_mtrn(c, n);
    getchar();
    det = DETN(c, n);
    printf("\n Детерминант массива С = %lf\n", det);
    getchar();
    /* ================================================== */
    system("clear");
    printf
    ("\n  Работа с верхними треугольными массивами,");
    printf
    ("\n представленными в виде одномерного массива ");
    printf
    ("\n Введите размер исходных (n*n) массивов: n=>");
    scanf("%d", &n);
    nn = (n * n + n) / 2;
    a = (float *) calloc(nn, sizeof(float));
    b = (float *) calloc(nn, sizeof(float));
    c = (float *) calloc(nn, sizeof(float));
    for (i = 0; i < n; i++)
    {
        k = i * n - (i * i + i) / 2;
        for (j = i; j < n; j++)
        {
            printf
            ("\nВведите элемент массива A[%d][%d]=>",
             i, j);
            scanf("%f", &a[k + j]);
        }
    }
    for (i = 0; i < n; i++)
    {
        k = i * n - (i * i + i) / 2;
        for (j = i; j < n; j++)
        {
            printf
            ("\nВведите элемент массива B[%d][%d]=>",
             i, j);
            scanf("%f", &b[k + j]);
        }
    }
    printf("\n Исходный массив А:\n");
    prn_mtrv(a, n);
    getchar();
    printf("\n Исходный массив В:\n");
    prn_mtrv(b, n);
    getchar();
    slog_matr(a, b, c, n);
    printf("\n Сумма массивов С=А+В:");
    prn_mtrv(c, n);
    getchar();
    razn_matr(a, b, c, n);
    printf("\n Разность массивов С=А-В:");
    prn_mtrv(c, n);
    getchar();
    umn_mtrv(a, b, c, n);
    printf("\n Произведение массивов С=А*В:");
    prn_mtrv(c, n);
    getchar();
    det = DETV(c, n);
    printf
    ("\n Детерминант массива произведения =%5.1lf",
     det);
    getchar();
    return 0;
}

/* =========================================== */
/* УМНОЖЕНИЕ НИЖНИХ ТРЕУГОЛЬНЫХ МАССИВОВ       */
void umn_mtrn(float *a, float *b, float *c, int n)
{
    int i = 0, j, k, p;
    for (i = 0; i < n; i++)
    {
        p = (i * i + i) / 2;
        for (j = 0; j <= i; j++)
        {
            c[p + j] = 0;
            for (k = j; k <= i; k++)
                c[p + j] += a[p + k] * b[(k * k + k) / 2 + j];
        }
    }
}

/* =========================================== */
/* ВЫВОД НИЖНЕГО ТРЕУГОЛЬНОГО МАССИВА НА ЭКРАН */
void prn_mtrn(float *c, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = 0; j <= i; j++)
            printf(" c[%d][%d]=%5.1f", i, j, c[(i * i + i) / 2 + j]);
    }
}

/* ============================================= */
/* ДЕТЕРМИНАНТ НИЖНЕГО ТРЕУГОЛЬНОГО МАССИВА              */
double DETN(float *c, int n)
{
    double dtr = 1;
    int i;
    for (i = 0; i < n; i++)
        dtr *= c[(i * i + i) / 2 + i];
    return dtr;
}

/* ============================================= */
/* СУММА ТРЕУГОЛЬНЫХ МАССИВОВ                    */
void slog_matr(float *a, float *b, float *c, int n)
{
    int i, nn;
    nn = (n * n + n) / 2;
    for (i = 0; i < nn; i++)
        c[i] = a[i] + b[i];
}

/* ============================================== */
/* РАЗНОСТЬ ТРЕУГОЛЬНЫХ МАССИВОВ                  */
void razn_matr(float *a, float *b, float *c, int n)
{
    int i, nn;
    nn = (n * n + n) / 2;
    for (i = 0; i < nn; i++)
        c[i] = a[i] - b[i];
}

/* ================================================= */
/* УМНОЖЕНИЕ ВЕРХНИХ ТРЕУГОЛЬНЫХ МАССИВОВ            */
void umn_mtrv(float *a, float *b, float *c, int n)
{
    int i, j, k, p;
    for (i = 0; i < n; i++)
    {
        p = i * n - (i * i + i) / 2;
        for (j = i; j < n; j++)
        {
            c[p + j] = 0;
            for (k = i; k <= j; k++)
                c[p + j] += a[p + k] * b[k * n - (k * k + k) / 2 + j];
        }
    }
}

/* =========================================== */
/* ВЫВОД НИЖНЕГО ТРЕУГОЛЬНОГО МАССИВА НА ЭКРАН */
void prn_mtrv(float *c, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("\n");
        for (j = i; j < n; j++)
            printf("\t %5.1f", c[i * n - (i * i + i) / 2 + j]);
    }
}

/* ============================================= */
/* ДЕТЕРМИНАНТ ВЕРХНЕГО ТРЕУГОЛЬНОГО МАССИВА              */
double DETV(float *c, int n)
{
    double dtr = 1;
    int i;
    for (i = 0; i < n; i++)
        dtr *= c[i * n - (i * i + i) / 2 + (n - 1)];
    return dtr;
}

/* ******************************************* */
