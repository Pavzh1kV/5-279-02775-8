/* ******************************************************* */
/* Сортировка файла прямым слиянием, однофазная сортировка */
/* Функция слияния-разделения - рекурсивная, 4 вспомогательных
	файла  \vsort18.cpp */
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
    n = 128;
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
/* ВНЕШНЯЯ ОДНОФАЗНАЯ СОРТИРОВКА ПРЯМЫМ СЛИЯНИЕМ,
	фаза начального разделения и вызов фазы слияния-разделения */
int vsort1(char *ff)
/* ff - исходный файл, подлежащий сортировке */
{
    int vsort2(char *f, int k);	/*функция фазы слияния-разделения */
    FILE *A, *B, *C;		/* файловые переменные */
    int a;			/* для чтения из исходного файла */
    int nb, nc;			/* счетчики элементов в формируемых группах */
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
        /* файлы "B", "C", "D", "E" - временные */
        if ((B = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            getchar();
            return -1;
        }
        if ((C = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
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
        vsort2(ff, k);		/* вызов функции слияния-разделения */
        return 0;
        m = m * 2;
        k = 0;
    }
}

/* ====================================================== */
/* ВНЕШНЯЯ ОДНОФАЗНАЯ СОРТИРОВКА ПРЯМЫМ СЛИЯНИЕМ,
	фаза слияния-разделения. Функция рекурсивная */
int vsort2(char *f, int k)
{
    FILE *B, *C, *D, *E;	/* файловые переменные */
    int b, c;			/* для считывания данных из файлов В и С */
    int nb, nc;			/*счетчики считанных из групп элементов файлов В и С */
    int nd, ne;			/* счетчики сливаемых в группы элементов */
    int rb, rc;			/* коды завершения операции считывания из файлов В и С */
    int sm;			/* число элементов в сливаемой группе: sm=2*m */
    static int m = 1;		/* число элементов в исходной группе */
    static int p = 1;		/* переключатель */
    if (p % 2)
    {
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
        if ((D = fopen("D", "w")) == NULL)
        {
            printf("\n Файл D не открывается");
            getchar();
            return -1;
        }
        if ((E = fopen("E", "w")) == NULL)
        {
            printf("\n Файл E не открывается");
            getchar();
            return -1;
        }
    }
    else
    {
        if ((B = fopen("D", "r")) == NULL)
        {
            printf("\n Файл D не открывается");
            getchar();
            return -1;
        }
        if ((C = fopen("E", "r")) == NULL)
        {
            printf("\n Файл E не открывается");
            getchar();
            return -1;
        }
        if ((D = fopen("B", "w")) == NULL)
        {
            printf("\n Файл B не открывается");
            getchar();
            return -1;
        }
        if ((E = fopen("C", "w")) == NULL)
        {
            printf("\n Файл C не открывается");
            getchar();
            return -1;
        }
    }
    sm = 2 * m;
    rb = fscanf(B, "%d", &b);
    rc = fscanf(C, "%d", &c);
    nb = 1;
    nc = 1;
    nd = 0;
    ne = 0;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))  	/* конец файла С */
        {
            if (nd < sm)  	/* формируем группу для файла D */
            {
                fprintf(D, " %d ", b);
                nd++;
            }
            else
            {
                fprintf(E, " %d ", b);
                ne++;
            }
            while (fscanf(B, "%d", &b) > 0)
            {
                if (nd < sm)  	/* формируем группу для файла D */
                {
                    fprintf(D, " %d ", b);
                    nd++;
                }
                else
                {
                    fprintf(E, " %d ", b);
                    ne++;
                }
            }
            fclose(B);
            fclose(C);
            break;
        }
        else
        {
            if ((rb <= 0) && (rc > 0))  	/* конец файла В */
            {
                if (nd < sm)  	/* формируем группу для файла D */
                {
                    fprintf(D, " %d ", c);
                    nd++;
                }
                else
                {
                    fprintf(E, " %d ", c);
                    ne++;
                }
                while (fscanf(C, "%d", &c) > 0)
                {
                    if (nd < sm)  	/* формируем группу для файла D */
                    {
                        fprintf(D, " %d ", c);
                        nd++;
                    }
                    else
                    {
                        fprintf(E, " %d ", c);
                        ne++;
                    }
                }
                fclose(B);
                fclose(C);
                break;
            }
            else if ((rb <= 0) && (rc <= 0))
            {
                /* конец обоих файлов В и С,
                					   случается, если они оба пустые */
                fclose(B);
                fclose(C);
                break;
            }
        }
        if (nb <= m && nc <= m)
        {
            if (b <= c)
            {
                if (nd == sm && ne == sm)
                {
                    nd = 0;
                    ne = 0;
                }
                if (nd < sm)  	/* формируем группу для файла D */
                {
                    fprintf(D, " %d ", b);
                    nd++;
                }
                else
                {
                    fprintf(E, " %d ", b);
                    ne++;
                }
                rb = fscanf(B, "%d", &b);
                nb++;
                continue;
            }
            else
            {
                if (nd == sm && ne == sm)
                {
                    nd = 0;
                    ne = 0;
                }
                if (nd < sm)  	/* формируем группу для файла D */
                {
                    fprintf(D, " %d ", c);
                    nd++;
                }
                else
                {
                    fprintf(E, " %d ", c);
                    ne++;
                }
                rc = fscanf(C, "%d", &c);
                nc++;
                continue;
            }
        }
        if (nb <= m && nc > m)
        {
            if (nd == sm && ne == sm)
            {
                nd = 0;
                ne = 0;
            }
            if (nd < sm)  	/* формируем группу для файла D */
            {
                fprintf(D, " %d ", b);
                nd++;
            }
            else
            {
                fprintf(E, " %d ", b);
                ne++;
            }
            rb = fscanf(B, "%d", &b);
            nb++;
            continue;
        }
        if (nb > m && nc <= m)
        {
            if (nd == sm && ne == sm)
            {
                nd = 0;
                ne = 0;
            }
            if (nd < sm)  	/* формируем группу для файла D */
            {
                fprintf(D, " %d ", c);
                nd++;
            }
            else
            {
                fprintf(E, " %d ", c);
                ne++;
            }
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
    }				/* конец цикла */
    fclose(B);
    fclose(C);
    fclose(D);
    fclose(E);
    if (m >= (k - k / 2))
    {
        remove(f);

        if (p % 2)
            rename("D", f);
        else
            rename("B", f);
        remove("B");
        remove("C");
        remove("D");
        remove("E");
        return 0;
    }
    m = 2 * m;
    p++;
    vsort2(f, k);
}

/* ****************************************************** */
