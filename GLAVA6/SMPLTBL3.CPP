/* **************************************************** */
/* РАБОТА С 3 ТАБЛИЦАМИ - данные о государствах. Таблица*/
/* последовательная, неупорядоченная, первоначально     */
/* создается в файле, для обработки	считывается в основ-*/
/* ную память.Работа пользователя в режиме меню. Разра- */
/* ботка многих функций оставлена для упражнений        */
/* \smpltbl3.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
//#include <io.h>
#define k 15
#define Rec struct r_e
Rec
{
    char Gos[20];
    char Stl[20];
    int Pl, Nas;
} El;

static Rec *T, *TA, *TB, *TC, *RAB;
char *menu[k][60];
int pp,				/* для вывода меню */
    ts = 1,			/* номер выбранной таблицы */
    m,				/* число элементов в выбранной таблице */
    m1, m2, m3;			/* число элементов в таблицах 1,2,3 */
char key[20];			/* ключ записи */
char name[40];			/* имя файла */
FILE *fin, *fout;		/* файловые переменные */
int Main_Menu(void);		/* вывод меню */
void Select_Tbl(void);		/* выбор таблицы */
int Crt_Tbl_Fl(void);		/* создание таблицы в файле */
int In_Tbl(Rec ** T);		/* чтение таблицы из файла */
int Out_Tbl(Rec * T);		/* сохранение таблицы в файле */
int Insrt_El(Rec El, Rec ** T);	/* включение эл-та в таблицу */
int Del_El(char *key, Rec ** T);	/* удаление эл-та из таблицы */
int Move_El(Rec * A, Rec ** B, char *key);	/* перенос эл-та в другую таблицу */
int Uni_Tbls(Rec * A, Rec * B, Rec ** C);	/* объединение таблиц */
int Cross_Tbls(Rec * A, Rec * B, Rec ** C);	/* пересечение таблиц */
int Dif_Tbls(Rec * A, Rec * B, Rec ** C);	/* разность таблиц */
void Del_Tbl(Rec ** T);		/* удаление таблицы */
int Out_El(Rec * E);		/* вывод элемента */
int Show_El(void);		/* показ элемента */
void Prnt_El(void);		/* вывод эл-та на экран */
void Wrt_El(void);		/* вывод эл-та в файл */
int Loc_El(char *key, Rec * T, Rec ** EL);	/* поиск эл-та в таблице */
void Wait_Entr(void);
void In_Gos(void);		/* ввод названия гос-ва */
int In_Data(void);		/* ввод данных о государстве */
void Scrn_El(Rec * El);		/* вывод элемента на экран */
int Show_Tbl(Rec * T);		/* показ таблицы */
void Prnt(void);		/* "на стадии разработки" */
int Add_Tabl(void);		/* добавление эл-та в файл */
/* ================================================================ */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    pp = 1;
    m1 = m2 = m3 = 0;
    T = RAB = TA = TB = TC = NULL;
    T = TA;
    *menu[0] = "1. Выбор таблицы";
    *menu[1] = "2. Создание таблицы в файле";
    *menu[2] = "3. Чтение таблицы из файла";
    *menu[3] = "4. Сохранение таблицы в файле";
    *menu[4] = "5. Включение элемента в таблицу";
    *menu[5] =
        "6. Добавление элемента в таблицу";
    *menu[6] =
        "7. Вывод данных элемента на экран";
    *menu[7] =
        "8. Перенос элемента из одной таблицы в другую";
    *menu[8] =
        "9. Объединение двух таблиц как множеств";
    *menu[9] =
        "10.Пересечение двух таблиц как множеств";
    *menu[10] =
        "11.Разность двух таблиц как множеств";
    *menu[11] = "12.Уничтожение таблицы";
    *menu[12] = "13.Показ таблицы";
    *menu[13] = "14.Конец работы";
    *menu[14] = "         Введите номер строки";
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

/*  ================================================= */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    int ns, i;
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
        break;
    }
    switch (ns)
    {
    case 1:
        Select_Tbl();
        break;
    case 2:
        Crt_Tbl_Fl();
        break;
    case 3:
        In_Tbl(&T);
        Show_Tbl(T);
        break;
    case 4:
        Out_Tbl(T);
        break;
    case 5:
        Insrt_El(El, &T);
        break;
    case 6:
        Add_Tabl();
        break;
    case 7:
        Show_El();
        break;
    case 8:
        Move_El(TA, &TB, key);
        break;
    case 9:
        Uni_Tbls(TA, TB, &TC);
        break;
    case 10:
        Cross_Tbls(TA, TB, &TC);
        break;
    case 11:
        Dif_Tbls(TA, TB, &TC);
        break;
    case 12:
        Del_Tbl(&T);
        break;
    case 13:
        Show_Tbl(T);
        break;
    case 14:
        pp = 0;
    }
    return 0;
}

/* =========================================================== */
/* ВЫБОР ТАБЛИЦЫ */
void Select_Tbl(void)
{
    char ns;
    while (1)
    {
        fflush(NULL);
        printf("  Введите таблицы (1,2,3)=>");
        ns = getchar();
        if (ns < '1' || ns > '3')
        {
            printf("Ошибка в номере, повторно \n");
            continue;
        }
        break;
    }
    switch (ns)
    {
    case '1':
        ts = 1;
        T = TA;
        m = m1;
        break;
    case '2':
        ts = 2;
        T = TB;
        m = m2;
        break;
    case '3':
        ts = 3;
        T = TC;
        m = m3;
    }
}

/* ======================================================= */
/* СОЗДАНИЕ ТАБЛИЦЫ О ГОСУДАРСТВАХ В ФАЙЛЕ,
   данные вводятся в диалоге */
int Crt_Tbl_Fl(void)
{
    m = 0;
    printf
    ("\n Введите имя файла, например: d:\\tc\\qq.txt \n=>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "w")) == 0)
    {
        printf(" Файл не открыт");
        Wait_Entr();
        return -1;
    }
    printf("\n Cоздание файла о государствах.\n");
    /* В начало файла запишем число записей=0 */
    fprintf(fout, "%5d", 0);
    while (1)
    {
        if (In_Data() == 0)  	/* очередную запись => в файл */
        {
            Wrt_El();
            m++;		/* m - счетчик записей */
        }
        else  		/* конец записей */
        {
            /* Запишем в начало файла число записей таблицы */
            fseek(fout, 0L, 0);
            fprintf(fout, "%5d", m);
            fclose(fout);
            break;
        }
    }
    switch (ts)
    {
    case 1:
        m1 = m;
        TA = T;
        break;
    case 2:
        m2 = m;
        TB = T;
        break;
    case 3:
        m3 = m;
        TC = T;
    }
    return 0;
}

/* ========================================================= */
/* ВВОД ДАННЫХ О ГОСУДАРСТВЕ, данные вводятся в диалоге */
int In_Data(void)
{
    fflush(NULL);
    printf
    ("\n Введите данные о государстве или ** для прекращения ввода:");
    printf("\n Государство=>");
    fflush(NULL);
    fgets(El.Gos,20,stdin);
    if (strcmp(El.Gos, "**") == 0)
        return 1;
    else
    {
        printf(" Столица=>");
        fgets(El.Stl,20,stdin);
        printf(" Площадь государства=>");
        scanf("%d", &El.Pl);
        printf(" Численность населения=>");
        scanf("%d", &El.Nas);
        return 0;
    }
}

/* ================================================= */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ТАБЛИЦУ */
/* E -переменная типа Rec с данными включаемого элемента.
	TT - указатель таблицы */
int Insrt_El(Rec E, Rec ** T)
{
    Prnt();
    return 0;
}

/* ==================================================== */
/*  ПОИСК ЭЛЕМЕНТА ПО ЗАДАННОМУ КЛЮЧУ В ТАБЛИЦЕ */
/* в EL возвращается указатель найденного элемента */
/* код возврата = 0, если элемент найден; =1, если не найден */
int Loc_El(char *key, Rec * T, Rec ** EL)
{
    Prnt();
    return 0;
}

/* ===================================================== */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА */
void Wait_Entr(void)
{
    printf("\n Нажмите ввод ");
    fflush(NULL);
    getchar();
}

/* ===================================================== */
/* УДАЛЕНИЕ ЭЛЕМЕНТА  */
int Del_El(char *key, Rec ** T)
{
    Prnt();
    return 0;
}

/* ===================================================== */
/* НА ПЕРИОД РАЗРАБОТКИ ПРОЦЕДУР */
void Prnt(void)
{
    printf("\nНа стадии разработки");
    Wait_Entr();
}

/* ===================================================== */
/* УНИЧТОЖЕНИЕ  ТАБЛИЦЫ  */
void Del_Tbl(Rec ** T)
{
    Prnt();
}

/* ===================================================== */
/* ПЕЧАТЬ ДАННЫХ ЭЛЕМЕНТА О ГОСУДАРСТВАХ */
void Prnt_El(void)
{
    printf("%s %s %d %d", El.Gos, El.Stl, El.Pl, El.Nas);
}

/* ===================================================== */
/* ВЫВОД ДАННЫХ ЭЛЕМЕНТА О ГОСУДАРСТВАХ В ФАЙЛ */
void Wrt_El(void)
{
    fprintf(fout, "\n%s %s %d %d", El.Gos, El.Stl, El.Pl, El.Nas);
}

/* ===================================================== */
/* ВВОД НАЗВАНИЯ ГОСУДАРСТВА */
void In_Gos(void)
{
    printf("\n Введите название государства=>");
    scanf("%s", &key);
}

/* ====================================================== */
/* ПОКАЗ ДАННЫХ ЭЛЕМЕНТА НА ЭКРАНЕ */
void Scrn_El(Rec * E)
{
    printf("\n Государство => %s", E->Gos);
    printf("\n Столица     => %s", E->Stl);
    printf("\n Площадь     => %d", E->Pl);
    printf("\n Численность населения => %d", E->Nas);
    Wait_Entr();
}

/* ====================================================== */
/* ВЫВОД ДАННЫХ ЭЛЕМЕНТА НА ЭКРАН */
int Show_El(void)
{
    In_Gos();			/* Ввод названия государства */
    Prnt();
    return 0;
}

/* ====================================================== */
/* ПЕРЕНОС ЭЛЕМЕНТА ИЗ ОДНОЙ ТАБЛИЦЫ В ДРУГУЮ */
int Move_El(Rec * A, Rec ** B, char *key)
{
    Prnt();
    return 0;
}

/* ======================================================= */
/* ОБЪЕДИНЕНИЕ ТАБЛИЦ */
int Uni_Tbls(Rec * A, Rec * B, Rec ** C)
{
    Prnt();
    return 0;
}

/* ======================================================= */
/* ПЕРЕСЕЧЕНИЕ ТАБЛИЦ */
int Cross_Tbls(Rec * A, Rec * B, Rec ** C)
{
    Prnt();
    return 0;
}

/* ======================================================= */
/* РАЗНОСТЬ ТАБЛИЦ */
int Dif_Tbls(Rec * A, Rec * B, Rec ** C)
{
    Prnt();
    return 0;
}

/* ======================================================= */
/* ВЫВОД ТАБЛИЦЫ В ФАЙЛ */
int Out_Tbl(Rec * T)
{
    Prnt();
    return 0;
}

/* ======================================================= */
/* ПОКАЗ ТАБЛИЦЫ */
int Show_Tbl(Rec * T)
{
    int i;
    if (T == NULL)
    {
        printf("\n Таблица %d пуста", ts);
        getchar();
        return -1;
    }
    for (i = 0; i < m; i++)
    {
        printf("\n %s %s %d %d", T[i].Gos, T[i].Stl, T[i].Pl, T[i].Nas);
    }
    Wait_Entr();
    return 0;
}

/* ======================================================= */
/* ЧТЕНИЕ ТАБЛИЦЫ ИЗ ФАЙЛА В ТАБЛИЦУ */
int In_Tbl(Rec ** T)
{
    Rec El, *R;
    long len;
    int i;
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
        fscanf(fin, "%d", &m);
        /* Отладочная печать числа записей файла */
        printf("\n В файле %s m=%d записей", name, m);
        /* Динамическая память для таблицы */
        R = (Rec *) calloc(m, sizeof(Rec));
        /* Чтение записей из файла */
        for (i = 0; i < m; i++)
        {
            fscanf(fin, "%s %s %d %d", &El.Gos, &El.Stl, &El.Pl, &El.Nas);
            R[i] = El;
        }
    }
    *T = R;
    switch (ts)
    {
    case 1:
        m1 = m;
        TA = *T;
        break;
    case 2:
        m2 = m;
        TB = *T;
        break;
    case 3:
        m3 = m;
        TC = *T;
    }
    return 0;
}

/* ======================================================= */
/* ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ В ФАЙЛ */
int Add_Tabl(void)
{
    int n;
    printf("\n Введите имя файла =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "r+")) == 0)
    {
        printf("\n %s не открыт", name);
        Wait_Entr();
        return -1;
    }
    else  			/* введем число записей в файле */
    {
        fscanf(fout, "%d", &n);
        printf("\n В файле %s n=%d записей", name, n);
        Wait_Entr();
    }

    /* Добавление записей, данные вводятся в диалоге */
    printf
    ("\n Добавление записей о государствах.\n");
    /* Указатель файла - в конец файла */
    fseek(fout, 0L, 2);
    while (1)
    {
        if (In_Data() == 0)  	/* добавляем запись */
        {
            Wrt_El();
            n++;
        }
        else  		/* Добавления закончены */
        {
            /* Запишем в начало файла число записей таблицы */
            fseek(fout, 0L, 0);
            fprintf(fout, "%5d", n);
            fclose(fout);
            break;
        }
    }
    return 0;
}

/* ****************************************************** */
