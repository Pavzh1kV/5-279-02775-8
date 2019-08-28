/*Программа создания и работы с хеш-таблицей государтв.            */
/*	Таблица с вычисляемыми входами с внутренними цепочками.     */
/*	Адрес входа - двоичное значение первой буквы государства-128 (0...31) */
/*	Конфликтные записи помещаются с начала таблицы в свободные ячейки.*/
/* Освободившиеся элементы повторно не используются \h_bgntbl.cpp */
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
#define k   8
#define n 32
#define Gs struct el
Gs				/* структура элемента */
{
    char Gos[20];		/* государство */
    char Stl[20];		/* столица */
    int sqr;			/* площадь */
    int ppl;			/* население */
    int ptr;			/* указатель (индекс) след. эл-та в цепочке */
} Ved[n], El;			/* Ved - хеш-таблица с внутренними цепочками */

char *menu[k][40];
static int m = 0;		/* число записей в таблице */
int p = 1;
char key[81];
void Main_Menu(void);		/* вывод меню */
void Init_tbl(Gs * T);		/* инициализация таблицы */
int Crt_tbl(Gs * T);		/* заполнение таблицы */
void Del_El(Gs * T);		/* удаление элемента */
Gs *Input(Gs * T);		/* ввод данных элемента */
void Show_tbl(Gs * T);		/* показ таблицы */
int Show_El(Gs * R);		/* показ элемента */
Gs *Search(Gs * T);		/* поиск элемента */
int Insert(Gs * T);		/* включение элемента в таблицу */
void Wait_Entr(void);		/* ждать */
int In_Gos(void);		/* ввод названия государства */
Gs *T, *R;			/* указатели таблицы (элемента) */
int In = 0;			/* признак инициализации таблицы */
/* ====================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
int main()
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    T = Ved;
    *menu[0] = "1.Инициализация таблицы";
    *menu[1] = "2.Заполнение таблицы данными";
    *menu[2] =
        "3.Включение государства в таблицу";
    *menu[3] =
        "4.Удаление государства из таблицы";
    *menu[4] = "5.Вывод таблицы на экран";
    *menu[5] = "6.Поиск государства в таблице";
    *menu[6] = "7.Конец работы";
    *menu[7] = "Введите номер строки";
    system("clear");
    printf
    ("\n ПРОГРАММА СОЗДАНИЯ И РАБОТЫ С ХЕШ-ТАБЛИЦЕЙ ГОСУДАРСТВ.");
    printf
    ("\n Таблица с вычисляемыми входами с внутренними цепочками.");
    printf
    ("\n Конфликтные записи помещаются с начала таблицы в \
  свободные ячейки.\n");
    while (p)
    {
        Main_Menu();
        system("clear");
    }
    printf("\n Конец работы с таблицей");
    return 0;
}

/* ================================================================= */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void Main_Menu(void)
{
    int ns, i;
    fflush(NULL);
    while (1)
    {
        for (i = 0; i < k; i++)
            printf("\n %s ", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns >= k)
        {
            fflush(NULL);
            system("clear");
            printf("\n Ошибка в номере");
            continue;
        }
        if (In == 0 && ns != 1 && ns != (k - 1))
        {
            system("clear");
            printf
            ("\n Сначала инициализируйте таблицу\n");
            continue;
        }
        break;
    }
    switch (ns)
    {
    case 1:
        Init_tbl(T);
        break;
    case 2:
        Crt_tbl(T);
        break;
    case 3:
        Insert(T);
        break;
    case 4:
        Del_El(T);
        break;
    case 5:
        Show_tbl(T);
        break;
    case 6:
        R = Search(T);
        Show_El(R);
        break;
    case 7:
        p = 0;
    }
}

/* ====================================================== */
/*  ИНИЦИАЛИЗАЦИЯ ТАБЛИЦЫ */
void Init_tbl(Gs * T)
{
    int i;
    for (i = 0; i < n; i++)
    {
        strcpy(T[i].Gos, "f");
        strcpy(T[i].Stl, "f");
        T[i].sqr = T[i].ppl = 0;
        T[i].ptr = -1;
    }
    In = 1;
}

/* ======================================================= */
/* ВВОД ДАННЫХ О ГОСУДАРСТВЕ */
Gs *Input(Gs * T)
{
    if (In_Gos())		/* отказ от ввода названия государства */
        return NULL;
    strcpy(T->Gos, key);
    printf("\n Введите столицу государства=>");
    fflush(NULL);
    scanf("%s", &T->Stl);
    printf("\n Введите площадь государства=>");
    fflush(NULL);
    scanf("%d", &T->sqr);
    printf
    ("\n Введите численность населения=>");
    fflush(NULL);
    scanf("%d", &T->ppl);
    return T;
}

/* ======================================================= */
/*  СОЗДАНИЕ ТАБЛИЦЫ  */
int Crt_tbl(Gs * T)
{
    int a, b, p;
    Gs *t;
    while (1)
    {
        printf("\n Ввод данных о %d -государстве",
               m + 1);
        if (!(t = Input(&El)))
            break;
        a = (unsigned char) t->Gos[0] - 128;
        /*Если строка свободна включаем туда */
        if (T[a].Gos[0] == 'f')
        {
            T[a] = *t;
            T[a].ptr = -1;
            m++;
            continue;
        }
        else
        {
            p = 1;
            for (b = 0; b < n; b++)
                if (T[b].Gos[0] == 'f')
                {
                    T[b] = *t;
                    T[b].ptr = T[a].ptr;
                    T[a].ptr = b;
                    m++;
                    ++p = 0;
                    break;
                }
            if (!p)
                continue;
            else
            {
                printf
                ("\n Таблица полна, элемент %s не включается",
                 key);
                getchar();
                return -2;
            }
        }
    }
    return 0;
}

/* ======================================================== */
/* ОЖИДАНИЕ НАЖАТИЯ ВВОДА */
void Wait_Entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ======================================================== */
/* ПОИСК ЭЛЕМЕНТА В ТАБЛИЦЕ */
Gs *Search(Gs * T)
{
    int a;
    Gs *TEK;
    printf("\n Поиск государства");
    if (In_Gos())		/* отказ от ввода названия государства */
        return NULL;
    a = (unsigned char) key[0] - 128;
    TEK = &T[a];
    while (1)
    {
        if (strcmp(TEK->Gos, key) == 0)
            return TEK;
        if (TEK->Gos[0] == 'f')
            break;
        if (TEK->ptr >= 0 && TEK->ptr != a)
            TEK = &T[TEK->ptr];
        else
            break;
    }
    printf("\n Государство %s не найдено", key);
    getchar();
    return NULL;
}

/* ========================================================== */
/*  ВЫВОД ТАБЛИЦЫ НА ЭКРАН  */
void Show_tbl(Gs * T)
{
    int i;
    printf("\n_______________________________________________________");
    printf
    ("\n|    Гос-во     |  Столица      | Площадь  | Числ-ть  | ");
    printf("\n ------------------------------------------------------");
    for (i = 0; i < n; i++)
    {
        printf("\n|%-15s|%-15s|%-10d|%-10d| %d  %d", T[i].Gos, T[i].Stl, T[i].sqr, T[i].ppl, i, T[i].ptr);	/* печать i и T[i].ptr - отладка */
        if (i && !(i % 20))
            Wait_Entr();
    }
    printf("\n_______________________________________________________");
    Wait_Entr();
}

/* ====================================================================== */
/*  УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ТАБЛИЦЫ  */
void Del_El(Gs * T)
{
    int i;
    Gs *TEK;
    printf
    ("\n Удаление государства из таблицы =>");
    TEK = Search(T);
    if (TEK)
    {
        strcpy(TEK->Gos, "t");
        printf("Запись %s удалена\n", key);
        getchar();
        m--;
        return;
    }
    printf("\n Государство %s не найдено\n", key);
    Wait_Entr();
}

/* ======================================================= */
/*  ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ТАБЛИЦУ */
int Insert(Gs * T)
{
    int a, b, c, p;
    Gs *t;
    printf("\n Ввод данных о %d-м государстве",
           m + 1);
    if (!(t = Input(&El)))
        return -1;
    a = (unsigned char) t->Gos[0] - 128;
    /*Если строка свободна включаем туда */
    if (T[a].Gos[0] == 'f')
    {
        T[a] = *t;
        T[a].ptr = -1;
        m++;
    }
    else
    {
        p = 1;
        for (b = 0; b < n; b++)
            if (T[b].Gos[0] == 'f')
            {
                T[b] = *t;
                T[b].ptr = T[a].ptr;
                T[a].ptr = b;
                m++;
                p = 0;
                break;
            }
        if (p)
        {
            printf("\n Таблица переполнена");
            getchar();
            return -2;
        }
    }
    return 0;
}

/* ============================================================ */
/*  ПОКАЗАТЬ ЭЛЕМЕНТ  */
int Show_El(Gs * R)
{
    if (R == NULL)
    {
        printf("\n Такого государства нет");
        Wait_Entr();
        return -1;
    }
    printf("\n Государство-%s \nСтолица-%s \nПлощадь-%d \n\
	Численность-%d P=%ld\n", R->Gos, R->Stl, R->sqr, R->ppl,
           R->ptr);
    Wait_Entr();
    return 0;
}

/* ====================================================== */
/* ВВОД НАЗВАНИЯ ГОСУДАРСТВА */
int In_Gos(void)
{
    while (1)
    {
        printf
        ("\n Введите название государства или ** =>");
        fflush(NULL);
        fgets(key,81,stdin);
        if (strcmp(key, "**") == 0)
            return -1;
        if ((key[0] < 'А') || (key[0] > 'Я'))
        {
            printf("\n ОШИБКА  ");
            continue;
        }
        break;
    }
    return 0;
}

/* ********************************************************* */
