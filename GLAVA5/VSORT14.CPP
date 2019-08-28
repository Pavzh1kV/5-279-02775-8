/* ******************************************************* */
/* Сортировка файла прямым слиянием, двухфазная сортировка */
/* \vsort14.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdlib.h>
/* ======================================================= */
int main()
{
    setlocale(LC_ALL,"Russian");
    int vsort1(char *r);
    int n, b;
    char f[40] = "A";
    FILE *fin, *fout;
    printf("\n Создание файла А");
    if ((fout = fopen(f, "w")) == NULL)
    {
        printf("\n Файл %s не создан", f);
        getchar();
        return -1;
    }
    n = 10;
    printf("\n Исходный файл:\n");
    while (n--)
    {
        b = rand();		/* заполняем файл случайными целыми числами */
        fprintf(fout, " %d", b);
        printf("%d\t", b);
    }
    fclose(fout);
    vsort1(f);			/* вызов функции внешней сортировки */
    printf("\n Отсортированный файл:\n");
    fin = fopen(f, "r");
    while (fscanf(fin, "%d", &b) != EOF)
        printf("%d\t", b);
    fclose(fin);
    getchar();
    return 0;
}

/* ===================================================== */
/* ВНЕШНЯЯ ДВУХФАЗНАЯ СОРТИРОВКА ПРЯМЫМ СЛИЯНИЕМ,
	фаза разделения и вызов фазы слияния */
int vsort1(char *ff)
/* ff - исходный файл, подлежащий сортировке */
{
    int vsort2(char *a, int m);	/* функция фазы слияния */
    FILE *A, *B, *C;		/* файловые переменные */
    int a;			/* для чтения из исходного файла */
    int nb, nc;			/* счетчики элементов в фомируемых группах */
    int p;			/* p=1 - признак достижения конца исходного файла */
    int m = 1;			/* число элементов в группе: 1,2,4,8,... */
    int k = 0;			/*счетчик числа элементов в исходном файле */
    while (1)
    {
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            getchar();
            return -1;
        }
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B1 не открывается");
            getchar();
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C1 не открывается");
            getchar();
            return -1;
        }
        nb = 0;
        nc = 0;
        p = 0;
        while (1)
        {
            while (1)
            {
                if (fscanf(A, "%d", &a) == EOF)
                {
                    p = 1;
                    break;
                }
                else
                {
                    if (nb < m)  	/* формируем группу для файла В */
                    {
                        fprintf(B, " %d ", a);
                        k++;
                        nb++;
                        continue;
                    }
                    else
                    {
                        fprintf(C, " %d ", a);
                        k++;
                        nb = 0;
                        nc++;
                        break;
                    }
                }
            }
            if (p)
                break;
            while (1)
            {
                if (fscanf(A, "%d", &a) == EOF)
                {
                    p = 1;
                    break;
                }
                else
                {
                    if (nc < m)  	/* формируем группу для файла С */
                    {
                        fprintf(C, " %d ", a);
                        k++;
                        nc++;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %d ", a);
                        k++;
                        nc = 0;
                        nb++;
                        break;
                    }
                }
            }
            if (p)
                break;
        }
        fclose(A);
        fclose(B);
        fclose(C);
        vsort2(ff, m);		/* вызов функции слияния */
        if (m >= (k - k / 2))
        {
            /* конец сортировки *//* Удаление вспомогательных файлов */
            remove("B");
            remove("C");
            return 0;
        }
        m = m * 2;
        k = 0;
    }
}

/* ====================================================== */
/* ВНЕШНЯЯ ДВУХФАЗНАЯ СОРТИРОВКА ПРЯМЫМ СЛИЯНИЕМ,
	фаза слияния */
int vsort2(char *a, int m)
/* a - файл для слияния,
   m - число элементов в группах сливаемых файлов В и С */
{
    FILE *A, *B, *C;		/* файловые переменные */
    int b, c;			/* для считывания данных из файлов В и С */
    int nb, nc;			/*счетчики считанных из групп элементов файлов В и С */
    int rb, rc;			/* коды завершения операции считывания из файлов В и С */
    if ((A = fopen(a, "w")) == NULL)
    {
        printf("\n Файл %s не открывается", a);
        getchar();
        return -1;
    }
    if ((B = fopen("B", "r")) == NULL)
    {
        printf("\n Файл B не открывается");
        getchar();
        return -1;
    }
    if ((C = fopen("C", "r")) == NULL)
    {
        printf("\n Файл C не открывается");
        getchar();
        return -1;
    }
    rb = fscanf(B, "%d", &b);
    rc = fscanf(C, "%d", &c);
    nb = 1;
    nc = 1;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))  	/* конец файла С */
        {
            fprintf(A, " %d ", b);
            while (fscanf(B, "%d", &b) > 0)
                fprintf(A, " %d ", b);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else
        {
            if ((rb <= 0) && (rc > 0))  	/* конец файла В */
            {
                fprintf(A, " %d ", c);
                while (fscanf(C, "%d", &c) > 0)
                    fprintf(A, " %d ", c);
                fclose(A);
                fclose(B);
                fclose(C);
                return 0;
            }
            else if ((rb <= 0) && (rc <= 0))
            {
                /* конец обоих файлов В и С,
                					   случается, если они оба пустые */
                fclose(A);
                fclose(B);
                fclose(C);
                return 0;
            }
        }
        if (nb <= m && nc <= m)
        {
            if (b <= c)
            {
                fprintf(A, " %d ", b);
                rb = fscanf(B, "%d", &b);
                nb++;
                continue;
            }
            else
            {
                fprintf(A, " %d ", c);
                rc = fscanf(C, "%d", &c);
                nc++;
                continue;
            }
        }
        if (nb <= m && nc > m)
        {
            fprintf(A, " %d ", b);
            rb = fscanf(B, "%d", &b);
            nb++;
            continue;
        }
        if (nb > m && nc <= m)
        {
            fprintf(A, " %d ", c);
            rc = fscanf(C, "%d", &c);
            nc++;
            continue;
        }
        if (nb > m && nc > m)
        {
            nb = 1;
            nc = 1;
            continue;
        }
    }
}

/* ===================================================== */
