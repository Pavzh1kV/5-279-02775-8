/* ******************************************************* */
/* Сортировка файла естественным слиянием, двухфазная сортировка */
/*  \vnsort26.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdlib.h>
/* ======================================================= */
main()
{
    setlocale(LC_ALL,"Russian");
    int vnsort1(char *r);
    int n, b;
    char f[40] = "A";		/* имя файла может вводиться с клавиатуры */
    FILE *fin, *fout;
    printf("\n Создание файла А");
    if ((fout = fopen(f, "w")) == NULL)
    {
        printf("\n Файл %s не создан", f);
        getchar();
        return -1;
    }
    n = 327;
    printf("\n Исходный файл:\n");
    while (n--)
    {
        b = rand();		/* заполняем файл случайными целыми числами */
        fprintf(fout, " %d", b);
        printf("%d\t", b);
    }
    /* for (n=100; n>0;n--)
    	 { fprintf(fout," %d",n);
    		printf("%d\t",n);
    	 }*/
    /* for (n=0; n<100;n++)
    	 { fprintf(fout," %d",n);
    		printf("%d\t",n);
    	 }*/
    fclose(fout);
    vnsort1(f);			/* вызов функции внешней сортировки */
    printf("\n Отсортированный файл:\n");
    fin = fopen(f, "r");
    while (fscanf(fin, "%d", &b) != EOF)
        printf("%d\t", b);
    fclose(fin);
    getchar();
    return 0;
}

/* ===================================================== */
/* ВНЕШНЯЯ ДВУХФАЗНАЯ СОРТИРОВКА ЕСТЕСТВЕННЫМ СЛИЯНИЕМ,
	фаза  разделения и вызов фазы слияния */
int vnsort1(char *ff)
/* ff - исходный файл, подлежащий сортировке */
{
    int vnsort2(char *f);	/*функция фазы слияния */
    FILE *A, *B, *C;		/* файловые переменные */
    /* файлы "B", "C" в функциях - временные */
    int a1, a2;			/* для чтения из исходного файла */
    int pb, pc;			/* признаки записи в файлы разделения */
    int p;			/* p=1 - признак достижения конца исходного файла */
    while (1)
    {
        /* цикл 1, цикл повторения фаз разделения и слияния */
        /* Подготовительные операции */
        if ((A = fopen(ff, "r")) == NULL)
        {
            printf("\n Файл %s не открывается", ff);
            getchar();
            return -1;
        }
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
        p = 0;
        pb = 0;
        pc = 0;
        if (fscanf(A, "%d", &a1) == EOF)
        {
            printf("\n Сортируемый файл - пустой");
            getchar();
            return -1;
        }
        else
        {
            fprintf(B, " %d", a1);
            pb = 1;
        }
        while (1)  		/* цикл 2, цикл формирования серий в файлах В и С */
        {
            while (1)  		/* цикл 3, цикл формирования серии в файле В */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1;
                    break;	/* выход из цикла 3 */
                }
                else
                {
                    if (a2 >= a1)  	/* запишем в серию в файле В */
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        continue;
                    }
                    else  	/* запишем первую запись новой серии в файле С */
                    {

                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        break;	/* выход из цикла 3 */
                    }
                }
            }
            if (p)
                break;		/* выход из цикла 2 */
            while (1)  		/* цикл 4, формирование серии в файле С */
            {
                if (fscanf(A, "%d", &a2) == EOF)
                {
                    p = 1;
                    break;	/* выход из цикла 4 */
                }
                else
                {
                    if (a2 >= a1)  	/* запишем в серию в файле С */
                    {
                        fprintf(C, " %d", a2);
                        a1 = a2;
                        pc = 1;
                        continue;
                    }
                    else
                    {
                        fprintf(B, " %d", a2);
                        a1 = a2;
                        pb = 1;
                        break;	/* выход из цикла 4 */
                    }
                }
            }
            if (p)
                break;		/* выход из цикла 2 */
        }
        fclose(A);
        fclose(B);
        fclose(C);
        if (pb && pc)		/* исходный файл записан в оба
				   файла разделения */
            vnsort2(ff);	/* вызов функции слияния */
        else  			/* Удаление вспомогательных файлов */
        {
            remove("B");
            remove("C");
            return 0;		/* конец сортировки */
        }
    }
}

/* ====================================================== */
/* ВНЕШНЯЯ ДВУХФАЗНАЯ СОРТИРОВКА ЕСТЕСТВЕННЫМ СЛИЯНИЕМ,
	фаза слияния */
int vnsort2(char *a)
/* a - файл для слияния */
{
    FILE *A, *B, *C;		/* файловые переменные */
    int b1, b2, c1, c2;		/* для считывания данных из файлов В и С */
    int rb, rc;			/* коды завершения операции считывания из файлов В и С */
    /* Подготовительные операции */
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
    rb = fscanf(B, "%d", &b2);
    rc = fscanf(C, "%d", &c2);
    b1 = b2;
    c1 = c2;
    while (1)
    {
        if ((rb > 0) && (rc <= 0))  	/* конец файла С */
        {
            fprintf(A, " %d", b2);
            while (fscanf(B, "%d", &b2) > 0)
                fprintf(A, " %d", b2);
            fclose(A);
            fclose(B);
            fclose(C);
            return 0;
        }
        else
        {
            if ((rb <= 0) && (rc > 0))  	/* конец файла В */
            {
                fprintf(A, " %d", c2);
                while (fscanf(C, "%d", &c2) > 0)
                    fprintf(A, " %d", c2);
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
        if (b2 >= b1 && c2 >= c1)  	/* обе сливаемые серии не исчерпаны */
        {
            if (b2 <= c2)
            {
                fprintf(A, " %d", b2);
                b1 = b2;
                rb = fscanf(B, "%d", &b2);
                continue;
            }
            else
            {
                fprintf(A, " %d", c2);
                c1 = c2;
                rc = fscanf(C, "%d", &c2);
                continue;
            }
        }
        if (b2 >= b1 && c2 < c1)  	/* текущая серия из файла С исчерпана */
        {
            c1 = c2;
BB:
            fprintf(A, " %d", b2);
            b1 = b2;
            rb = fscanf(B, "%d", &b2);
            if (rb <= 0)	/* конец файла В */
                continue;
            if (b2 >= b1)
                goto BB;
            else
            {
                b1 = b2;
                continue;
            }
        }
        if (b2 < b1 && c2 >= c1)  	/*текущая серия из файла В исчерпана */
        {
            b1 = b2;
CC:
            fprintf(A, " %d", c2);
            c1 = c2;
            rc = fscanf(C, "%d", &c2);
            if (rc <= 0)	/* конец файла С */
                continue;
            if (c2 >= c1)
                goto CC;
            else
            {
                c1 = c2;
                continue;
            }
        }
    }
}

/* ************************************************************** */
