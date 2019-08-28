/* РАБОТА С ДВУМЯ СВЯЗАННЫМИ ТАБЛИЦАМИ - анкетные данные     */
/* и успеваемость студентов. Поиск студентов с средним баллом*/
/* не менее 4,5 по трем ведущим дисциплинам    \svzntbl2.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define k 7
#define Rec struct r_e
#define US struct el_type
Rec				/* структура элемента анкетных данных */
{
    char fam[20];
    char num[4];		/* учетный номер - для связи таблиц */
    char semya[20];
    int rost, ves;
} El;

US				/* структура элемента успеваемости */
{
    char num[4];		/* учетный номер */
    int STR, OS, TVPS, MTR, FK;
} uspev;

Rec *TA;
US *TB;
char *menu[k][60];
char name[40];
FILE *fout, *fin;		/* файловые переменные */
int Main_Menu(void);		/* вывод меню */
int Crt_Tbl1(void);		/* создание файла анкетных данных */
int Crt_Tbl2(void);		/* созданние файла успеваемости */
int In_Tbl1(Rec ** TA);		/* чтение файла анк. данных в таблицу */
int In_Tbl2(US ** TB);		/* чтение файла успеваемости в таблицу */
void Show_Tbl1(Rec * TA);	/* показ таблицы анк. данных */
void Show_Tbl2(US * TB);	/* показ таблицы успеваемости */
int Poisk(US * TB);		/* поиск в таблице успеваемости */
int In_Data1(void);		/* ввод анкетных данных */
int In_Data2(int z);		/* ввод данных об успеваемости */
void Wrt_El();			/* запись анкетных данных в файл */
void Wrt_uspev();		/* запись данных об успеваемости в файл */
int pp, n = 0, m = 0;
/* =============================================================== */
/* ГЛАВНАЯ ФУНКЦИЯ */
int main()
{
    setlocale(LC_ALL,"Russian");
    pp = 1;
    *menu[0] =
        "1. Создание файла с анкетными данными";
    *menu[1] =
        "2. Прочитать таблицу с анкетными данными из файла";
    *menu[2] = "3. Создание файла успеваемости";
    *menu[3] =
        "4. Прочитать таблицу успеваемости из файла";
    *menu[4] =
        "5. Выдать список студентов с средним баллом не менее 4,5";
    *menu[5] = "6. Конец работы";
    *menu[6] = "         Введите номер строки";
    system("clear");
    printf("    Работа с таблицами \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с таблицами\n");
    getchar();
    return 0;
}

/* ================================================================ */
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
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns > k - 1)
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
        Crt_Tbl1();
        break;
    case 2:
        In_Tbl1(&TA);
        Show_Tbl1(TA);
        break;
    case 3:
        Crt_Tbl2();
        break;
    case 4:
        In_Tbl2(&TB);
        Show_Tbl2(TB);
        break;
    case 5:
        Poisk(TB);
        break;
    case 6:
        pp = 0;
    }
    return 0;
}

/*========================================================================*/
/* СОЗДАНИЕ ТАБЛИЦЫ  С АНКЕТНЫМИ ДАННЫМИ В ФАЙЛЕ,
   данные вводятся в диалоге */
int Crt_Tbl1(void)
{
    int i = 0;
    printf("\n Создание файла анкетных данных");
    printf
    ("\n Введите имя файла анкетных данных \n=>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "w+")) == 0)
    {
        printf(" Файл не открыт");
        getchar();
        return -1;
    }
    fprintf(fout, "%5d", 0);
    while (1)
    {
        if (In_Data1() != 0)
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

/* ============================================================= */
/* СОЗДАНИЕ ТАБЛИЦЫ УСПЕВАЕМОСТИ В ФАЙЛЕ,
   данные вводятся в диалоге */
int Crt_Tbl2(void)
{
    int i = 0, j = 0;
    printf("\n Создание файла успеваемости");
    printf("\n Введите имя файла \n =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "w+")) == 0)
    {
        printf(" Файл не открыт");
        getchar();
        return -1;
    }
    fprintf(fout, "%5d", 0);
    if (n == 0)
    {
        printf
        ("\nСначала выгрузите в таблицу анкетные данные(пункт 2)");
        getchar();
    }
    for (j = 0; j < n; j++)
        while (1)
        {
            if (In_Data2(j) != 0)
            {
                fseek(fout, 0L, 0);
                fprintf(fout, "%5d", i);
                fclose(fout);
                break;
            }
            else
            {
                i++;
                break;
            }
        }
    fseek(fout, 0L, 0);
    fprintf(fout, "%5d", i);
    fclose(fout);
    return 0;
}

/*=========================================================================*/
/* ВВОД АНКЕТНЫХ ДАННЫХ, данные вводятся в диалоге */
int In_Data1(void)
{
    fflush(NULL);
    printf
    ("\n Введите данные о студенте или ** для прекращения ввода:");
    printf("\n Фамилия=>");
    fflush(NULL);
    fgets(El.fam,20,stdin);
    if (strcmp(El.fam, "**") == 0)
        return 1;
    else
    {
        printf(" Учетный номер=>");
        fgets(El.num,4,stdin);
        printf(" Семейное положение=>");
        fgets(El.semya,20,stdin);
        printf(" Рост=>");
        scanf("%d", &El.rost);
        printf(" Вес=>");
        scanf("%d", &El.ves);
    }
    return 0;
}

/*========================================================================*/
/* ВВОД ДАННЫХ ОБ УСПЕВАЕМОСТИ, данные вводятся в диалоге */
int In_Data2(int z)
{
    printf
    ("\nВведите данные об успеваемости студента %s:",
     TA[z].fam);
    strcpy(uspev.num, TA[z].num);
    printf
    ("\n Структуры и алгоритмы обработки данных=> ");
    scanf("%d", &uspev.STR);
    while ((uspev.STR < 1) || (uspev.STR > 5))
    {
        printf
        (" Ошибка! Вводите оценки по пятибалльной шкале.\
		\nСтруктуры и алгоритмы обработки данных=> ");
        scanf("%d", &uspev.STR);
    }
    printf(" Операционные системы=> ");
    scanf("%d", &uspev.OS);
    while ((uspev.OS < 1) || (uspev.OS > 5))
    {
        printf
        (" Ошибка! Вводите оценки по пятибалльной шкале.\
		\nОперационные системы=> ");
        scanf("%d", &uspev.OS);
    }
    printf
    (" Теория вычислительных процессов и структур=> ");
    scanf("%d", &uspev.TVPS);
    while ((uspev.TVPS < 1) || (uspev.TVPS > 5))
    {
        printf
        (" Ошибка! Вводите оценки по пятибалльной шкале.\
		\nТеория вычислительных процессов и структур=> ");
        scanf("%d", &uspev.TVPS);
    }
    printf(" Метрология=> ");
    scanf("%d", &uspev.MTR);
    while ((uspev.MTR < 1) || (uspev.MTR > 5))
    {
        printf
        (" Ошибка! Вводите оценки по пятибалльной шкале.\
		\n Метрология=> ");
        scanf("%d", &uspev.MTR);
    }
    printf(" Физическая культура=> ");
    scanf("%d", &uspev.FK);
    while ((uspev.FK < 1) || (uspev.FK > 5))
    {
        printf
        (" Ошибка! Вводите оценки по пятибалльной шкале.\
		\nФизическая культура=> ");
        scanf("%d", &uspev.FK);
    }
    Wrt_uspev();
    return 0;
}

/*=====================================================================*/
/* ВЫВОД АНКЕТНЫХ ДАННЫХ СТУДЕНТА В ФАЙЛ */
void Wrt_El(void)
{
    fprintf(fout, "\n %s %s %s %d %d", El.fam, El.num, El.semya, El.rost,
            El.ves);
}

/*======================================================================*/
/* ВЫВОД  ДАННЫХ ОБ УСПЕВАЕМОСТИ СТУДЕНТА В ФАЙЛ */
void Wrt_uspev(void)
{
    fprintf(fout, "\n %s %d %d %d %d %d",
            uspev.num, uspev.STR, uspev.OS, uspev.TVPS, uspev.MTR,
            uspev.FK);
}

/*=========================================================================*/
/* ВЫВОД НА ЭКРАН ТАБЛИЦЫ С АНКЕТНЫМИ ДАННЫМИ */
void Show_Tbl1(Rec * TA)
{
    int i;
    for (i = 0; i < n; i++)
    {
        El = TA[i];
        printf("\n %s %s %s %d %d", El.fam, El.num, El.semya, El.rost,
               El.ves);
    }
    getchar();
}

/*==========================================================================*/
/* ВЫВОД НА ЭКРАН ТАБЛИЦЫ УСПЕВАЕМОСТИ */
void Show_Tbl2(US * TB)
{
    int i;
    for (i = 0; i < m; i++)
    {
        uspev = TB[i];
        printf("\n %s %d %d %d %d %d",
               uspev.num, uspev.STR, uspev.OS, uspev.TVPS, uspev.MTR,
               uspev.FK);
    }
    getchar();
}

/*=========================================================================*/
/* ЧТЕНИЕ ФАЙЛА С АНКЕТНЫМИ ДАННЫМИ */
int In_Tbl1(Rec ** TA)
{
    int i;
    Rec El, *R;
    n = 0;
    printf
    ("\n Введите имя файла с анкетными данными\n =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n %s не открыт", name);
        return -1;
    }
    else
    {
        fscanf(fin, " %d", &n);
        printf("\n n=%d", n);
        getchar();
        R = (Rec *) calloc(n, sizeof(Rec));
        for (i = 0; i < n; i++)
        {
            fscanf(fin, "%s %s %s %d %d",
                   &El.fam, &El.num, &El.semya, &El.rost, &El.ves);
            R[i] = El;
        }
    }
    *TA = R;
    return 0;
}

/*========= ==================================================*/
/* ЧТЕНИЕ ФАЙЛА УСПЕВАЕМОСТИ */
int In_Tbl2(US ** TB)
{
    int i;
    US uspev, *R;
    m = 0;
    printf
    ("\n Введите имя файла успеваемости\n =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n %s не открыт", name);
        return -1;
    }
    else
    {
        fscanf(fin, " %d", &m);
        printf("\n m=%d", m);
        getchar();
        R = (US *) calloc(m, sizeof(US));
        for (i = 0; i < m; i++)
        {
            fscanf(fin, "%s %d %d %d %d %d",
                   &uspev.num, &uspev.STR, &uspev.OS, &uspev.TVPS,
                   &uspev.MTR, &uspev.FK);
            R[i] = uspev;
        }
    }
    *TB = R;
    return 0;
}

/*=================================================================*/
/* ПОИСК СТУДЕНТОВ, ИМЕЮЩИХ СРЕДНИЙ БАЛЛ НЕ МЕНЕЕ 4,5 */
/* ПО ТРЕМ ВЕДУЩИМ ДИСЦИПЛИНАМ */
int Poisk(US * TB)
{
    float s;
    int x = 0, j, i;
    for (i = 0; i < m; i++)
    {
        s = TB[i].STR + TB[i].OS + TB[i].TVPS;
        s = s / 3;
        if (s >= 4.5)
            for (j = 0; j < n; j++)
                if (strcmp(TA[j].num, TB[i].num) == NULL)
                {
                    printf("\n%s\nСредний бал =>%f\n\
	  Структуры и алгоритмы обработки данных =>%d\n\
	  Операционные системы =>%d\n\
	  Теория вычислительных процессов и структур =>%d", TA[j].fam, s, TB[i].STR, TB[i].OS, TB[i].TVPS);
                    x++;
                }
    }
    if (x == 0)
        printf
        ("\nК сожалению, студентов с средним баллом >=4.5 нет.");
    getchar();
    return 0;
}

/* *********************************************************************** */
