/* *************************************************** */
/* РАБОТА С ТАБЛИЦАМИ - данные о служащих.
	Таблица последовательная, неупорядоченная,
	первоначально создается в файле, для обработки
	считывается в основную память.
	Работа пользователя в режиме меню */
/* \sorttbl.cpp*/
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define k 6
#define Rec struct r_e
Rec
{
    char Z[20];
    char F[20];
    int R;
    int P;
    char V[20];
} El;

Rec *T, *R;
char *menu[k][60];
int i, pp, m;
char key[20];
char name[40];
FILE *fin, *fout;
int Main_Menu(void);
int Crt_Tbl_Fl(void);
int In_Tbl(Rec ** T);
int Sort_Tbl(Rec * T, int nn);
void Wrt_El(void);
void Wait_Entr(void);
int In_Data(void);
void Show_Tbl(Rec * T, int m);
int Shell(Rec * A, int nn);
int strcmp1(char *s1, char *s2);
/* ================================================= */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    R = (Rec *) calloc(10, sizeof(Rec));
    pp = 1;
    T = 0;
    *menu[0] = "1. Создание таблицы в файле";
    *menu[1] = "2. Чтение таблицы из файла";
    *menu[2] = "3. Сортировка таблицы";
    *menu[3] = "4. Показ таблицы";
    *menu[4] = "5. Конец работы";
    *menu[5] = "         Введите номер строки";
    system("clear");
    printf("    Работа с таблицами \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с таблицами\n");
    Wait_Entr();
    return 0;
}

/* =================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    static int ns, m;
    fflush(NULL);			/* чистка буферов */
    while (1)
    {
        for (i = 0; i < k; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns > k)
        {
            fflush(NULL);
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        switch (ns)
        {
        case 1:
            Crt_Tbl_Fl();
            break;
        case 2:
            m = In_Tbl(&T);
            Show_Tbl(T, m);
            break;
        case 3:
            Sort_Tbl(T, m);
            Show_Tbl(T, m);
            break;
        case 4:
            Show_Tbl(T, m);
            break;
        case 5:
            pp = 0;
        }
        return 0;
    }
}

/* =============================================== */
/* СОЗДАНИЕ ТАБЛИЦЫ О СЛУЖАЩИХ В ФАЙЛЕ,
   данные вводятся в диалоге */
int Crt_Tbl_Fl(void)
{
    int i = 0;
    printf("\n Введите имя файла\n=>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "w+")) == 0)
    {
        printf(" Файл не открыт");
        Wait_Entr();
        return 0;
    }
    printf("\n Cоздание файла о служащих\n");
    fprintf(fout, "%5d", i);
    while (1)
    {
        if (In_Data() != 0)
        {
            fseek(fout, 0L, 0);
            fprintf(fout, "%5d", i);
            fclose(fout);
            break;
        }
        else
        {
            Wrt_El();
            i++;
        }
    }
    return 0;
}

/* ===================================================== */
/* ВВОД ДАННЫХ О СЛУЖАЩЕМ, данные вводятся в диалоге */
int In_Data(void)
{
    static int i;
    i = 0;
    fflush(NULL);
    printf
    ("\n Введите данные о служащем или ** для прекращения ввода:");
    printf("\n Должность =>");
    fflush(NULL);
    fgets(El.Z,20,stdin);
    if (strcmp1(El.Z, "**") == 0)
        return 1;
    else
    {
        printf(" Фамилия=>");
        fflush(NULL);
        fgets(El.F,20,stdin);
        printf(" Год рождения=>");
        fflush(NULL);
        scanf("%d", &El.R);
        printf("Год поступления=>");
        fflush(NULL);
        scanf("%d", &El.P);
        printf("Специальность=>");
        fflush(NULL);
        fgets(El.V,20,stdin);
        printf("\n%s %s %d %d %s", El.Z, El.F, El.R, El.P, El.V);
        Wait_Entr();
        i++;
        return 0;
    }
}

/* =================================================== */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА */
void Wait_Entr(void)
{
    printf("\n    Нажмите ввод ");
    fflush(NULL);
    getchar();
}

/* ==================================================== */
/* ВЫВОД ДАННЫХ ЭЛЕМЕНТА О СЛУЖАЩЕМ В ФАЙЛ */
void Wrt_El(void)
{
    fprintf(fout, "\n %d %s %d %s %s ", El.R, El.F, El.P, El.Z, El.V);
}

/* ====================================================== */
int Sort_Tbl(Rec * T, int nn)
{
    Shell(T, nn);
    return 0;
}

/* ====================================================== */
void Show_Tbl(Rec * T, int m)
{
    for (i = 0; i < m; i++)
    {
        printf("\n %s   %s %d %d %s", T[i].Z, T[i].F, T[i].R, T[i].P,
               T[i].V);
    }
    Wait_Entr();
}

/* ======================================================= */
int In_Tbl(Rec ** T)
{
    Rec El, *R;
    int static m = 0;
    printf("\n Введите имя файла =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n %s не открыт", name);
        getchar();
        return -1;
    }
    else
    {
        fscanf(fin, " %d ", &m);
        printf("\n m=%d", m);
        Wait_Entr();
        R = (Rec *) calloc(m, sizeof(Rec));
        for (i = 0; i < m; i++)
        {
            fscanf(fin, " %d %s %d %s %s ", &El.R, &El.F, &El.P, &El.Z,
                   &El.V);
            R[i] = El;
        }
    }
    *T = R;
    return m;
}

/* ============================================================ */
/*   ФУНКЦИЯ СОРТИРОВКИ МЕТОДОМ ШЕЛЛА */
int Shell(Rec * A, int nn)
{
    int i, j, kk;
    Rec x;
    if (nn <= 0)
    {
        printf("\n Таблица пуста");
        getchar();
        return -1;
    }
    kk = (nn + 1) / 2;
    x = A[1];
    while (kk >= 1)
    {
        for (i = kk; i < nn; i++)
        {
            if (strcmp1(A[i].F, A[i - kk].F) < 0)
            {
                x = A[i];
                j = i - kk;
M:
                A[j + kk] = A[j];
                if (j > kk)
                {
                    if (strcmp1(x.F, A[j - kk].F) < 0)
                    {
                        j = j - kk;
                        goto M;
                    }
                }
                A[j] = x;
            }
        }
        if (kk > 2)
            kk = (kk + 1) / 2;
        else
            kk = kk / 2;
    }
    return 0;
}

/* ======================================================= */
/* СРАВНЕНИЕ СИМВОЛЬНЫХ СТРОК */
int strcmp1(char *s1, char *s2)
{
    int i, len, l1, l2, r1 = 0, r2 = 0;
    l1 = strlen(s1);
    l2 = strlen(s2);
    len = (l1 < l2) ? l1 + 1 : l2 + 1;
    for (i = 0; i < len; i++)
        if (s1[i] != s2[i])
            return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

/* ******************************************************* */
