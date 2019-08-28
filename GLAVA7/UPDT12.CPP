/* ************************************************ */
/* РАБОТА С ФАЙЛОМ: СОЗДАНИЕ, ЧТЕНИЕ И ОБНОВЛЕНИЕ   */
/* ЗАПИСЕЙ ФАЙЛА НА МЕСТЕ БЕЗ ИЗМЕНЕНИЯ ИХ ДЛИНЫ -  */
/*	данные о студентах. В символьных строках         */
/* пробелы не допускаются.  Работа пользователя в   */
/* режиме меню. 12.03.2003 Хусаинов Б.С.\updt12.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#include <stdlib.h>
#define k 6			/* число строк при выводе меню */
#define Rec struct r_e
Rec
{
    char Z[8];			/* группа */
    char F[20];			/* фамилия */
    int R;			/* год рождения */
    int P;			/* год поступления */
    char V[20];			/* специальность */
} El;

Rec *T, *R;
char *menu[k][60];
int i, pp, m;
char key[20];
char N[40];
FILE *fin, *fout;		/* файловые указатели */
int Main_Menu(void);
int Crt_Tbl_Fl(void);		/* создание таблицы в файле */
int In_Tbl(Rec ** T);		/* ввод таблицы из файла */
int Updatf();			/* обновление записей файла */
void Wrt_El(void);		/* запись элемента таблицы в файл */
void Wait_Entr(void);		/* ожидание нажатия клавиши ENTER */
int In_Data(void);		/* ввод данных о студенте */
void Show_Tbl(Rec * T, int m);	/* показ таблицы, считанной в ОП */
/* ====================================================== */
main()
{
    setlocale(LC_ALL,"Russian");
    R = (Rec *) calloc(10, sizeof(Rec));
    pp = 1;
    T = 0;
    *menu[0] = "1. Создание таблицы в файле";
    *menu[1] = "2. Чтение таблицы из файла";
    *menu[2] = "3. Обновление записей файла";
    *menu[3] = "4. Показ таблицы";
    *menu[4] = "5. Конец работы";
    *menu[5] = "         Введите номер строки";
    system("clear");
    printf
    ("\n РАБОТА С ФАЙЛОМ: СОЗДАНИЕ, ЧТЕНИЕ И ОБНОВЛЕНИЕ");
    printf
    ("\n ЗАПИСЕЙ ФАЙЛА НА МЕСТЕ БЕЗ ИЗМЕНЕНИЯ ИХ ДЛИНЫ -");
    printf
    ("\n данные о студентах. В символьных строках пробелы");
    printf
    ("\n не допускаются. Если в файле уже имеются записи,");
    printf
    ("\n они затираются новыми, т.е. новые записи помещаются");
    printf("\n с начала файла");
    Wait_Entr();
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с файлом\n");
    Wait_Entr();
    return 0;
}

/* ==================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    static int ns, r;
    fflush(NULL);			/* чистка буферов */
    do
    {
        for (i = 0; i < k; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if (r = (scanf("%d", &ns) < 1) || ns < 1 || ns > k - 1)
        {
            fflush(NULL);
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
        }
    }
    while (r);
    switch (ns)
    {
    case 1:
        Crt_Tbl_Fl();
        break;
    case 2:
        m = In_Tbl(&T);
        if (m > 0)
            Show_Tbl(T, m);
        break;
    case 3:
        Updatf();
        break;
    case 4:
        Show_Tbl(T, m);
        break;
    case 5:
        pp = 0;
    }
    return 0;
}

/* =================================================== */
/* СОЗДАНИЕ ФАЙЛА О СТУДЕНТАХ, данные вводятся в диалоге */
int Crt_Tbl_Fl(void)
{
    int i = 0;
    printf("\n Введите имя файла =>");
    fflush(NULL);
    fgets(N,40,stdin);
    /* Открываем файл в режиме записи с обновлением */
    if ((fout = fopen(N, "w+")) == NULL)
    {
        printf(" Файл %s  не открыт ", N);
        Wait_Entr();
        return -1;
    }
    printf("\n Cоздание файла о студентах\n");
    fprintf(fout, "%5d", 0);
    while (1)
    {
        if (In_Data() != 0)  	/* ввод данных завершен */
        {
            fseek(fout, 0L, 0);	/* установка на начало файла */
            fprintf(fout, "%5d", i);	/* число записей в файле */
            fclose(fout);
            break;
        }
        else
        {
            printf("\n%s %s %d %d %s", El.Z, El.F, El.R, El.P, El.V);
            Wait_Entr();
            Wrt_El();
            i++;		/* вывод данных о студенте в файл */
        }
    }
}

/* ===================================================== */
/* ВВОД ДАННЫХ О СТУДЕНТЕ, данные вводятся в диалоге */
int In_Data(void)
{
    int j, s;
    fflush(NULL);
    printf
    ("\n Введите данные о студенте или ** для прекращения ввода:\n");
    while (1)
    {
        printf(" Группа=>");
        fflush(NULL);
        scanf("%s", N);
        if (strcmp(N, "**") == 0)
            return 1;
        s = strlen(N);
        if (s > 8)
        {
            printf("\n Ошибка, введите повторно: ");
            continue;
        }
        else
        {
            strcpy(El.Z, N);
            break;
        }
    }
    while (1)
    {
        printf(" Фамилия=>");
        fflush(NULL);
        scanf("%s", N);
        s = strlen(N);
        if (s > 20)
        {
            printf("\n Ошибка, введите повторно:");
            continue;
        }
        else
        {
            strcpy(El.F, N);
            break;
        }
    }
    while (1)
    {
        printf(" Год рождения=>");
        fflush(NULL);
        fgets(N,40,stdin);
        s = strlen(N);
        j = 0;
        while (N[j] >= '0' && N[j] <= '9')
            j++;
        if (s == 0 || j < s || j != 4)
        {
            printf("\n Ошибка, повторно введите ");
            continue;
        }
        else
        {
            El.R = atoi(N);
            break;
        }
    }
    while (1)
    {
        printf(" Год поступления =>");
        fflush(NULL);
        fgets(N,40,stdin);
        s = strlen(N);
        j = 0;
        while (N[j] >= '0' && N[j] <= '9')
            j++;
        if (s == 0 || j < s || j != 4)
        {
            printf("\n Ошибка, повторно введите ");
            continue;
        }
        else
        {
            El.P = atoi(N);
            break;
        }
    }

    while (1)
    {
        printf(" специальность =>");
        fflush(NULL);
        scanf("\n%s", N);
        s = strlen(N);
        if (s == 0 || s > 20)
        {
            printf("\n Ошибка, введите повторно: ");
            continue;
        }
        else
        {
            strcpy(El.V, N);
            break;
        }
    }
    /*	  printf("\n%s %s %d %d %s",El.Z,El.F,El.R,El.P,El.V);
    	  Wait_Entr();*/
    return 0;
}

/* ======================================================= */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА */
void Wait_Entr(void)
{
    printf("\n    Нажмите ввод ");
    fflush(NULL);
    getchar();
}

/* =========================================== */
/* ВЫВОД ЗАПИСИ О СТУДЕНТЕ В ФАЙЛ */
void Wrt_El(void)
{
    fprintf(fout, "\n %s %s %5d %5d %s ", El.Z, El.F, El.R, El.P, El.V);
}

/* ============================================= */
void Show_Tbl(Rec * T, int m)
{
    for (i = 0; i < m; i++)
    {
        printf("\n %s %s %d %d %s", T[i].Z, T[i].F, T[i].R, T[i].P,
               T[i].V);
    }
    Wait_Entr();
}

/* ============================================== */
int In_Tbl(Rec ** T)
{
    Rec El, *R;
    printf("\n Введите имя файла =>");
    fflush(NULL);
    fgets(N,40,stdin);
    if ((fin = fopen(N, "r")) == 0)
    {
        printf("\n %s не открыт", N);
        return -1;
    }
    else
    {
        fscanf(fin, "%d", &m);
        printf("\n В файле %s имеется m=%d записей", N,
               m);
        Wait_Entr();
        R = (Rec *) calloc(m, sizeof(Rec));
        for (i = 0; i < m; i++)
        {
            fscanf(fin, "%s %s %d %d %s",
                   &R[i].Z, &R[i].F, &R[i].R, &R[i].P, &R[i].V);
        }
    }
    *T = R;
    return m;
}

/* =================================================== */
/*  ОБНОВЛЕНИЕ ЗАПИСЕЙ ФАЙЛА */
int Updatf()
{
    Rec El;
    char v;
    long Pos, p;
    int j, s, m = 0;
    printf("\n Введите имя файла =>");
    fflush(NULL);
    fgets(N,40,stdin);
    if ((fin = fopen(N, "r+")) == 0)
    {
        printf("\n %s не открыт", N);
        getchar();
        return -1;
    }
    else
    {
        printf
        ("\n ВНИМАНИЕ! Символьные строки вводить без пробелов");
        printf
        ("\n Для пропуска элемента без обновления нажмите ввод");
        rewind(fin);
        fscanf(fin, " %d ", &m);
        printf("\n В файле m=%d записей", m);
        p = ftell(fin);		/* или fgetpos(fin,&p), что равносильно */
        Wait_Entr();
        for (i = 0; i < m; i++)  	/* цикл обновления m записей */
        {
            fseek(fin, p, SEEK_SET);	/*или fsetpos(fin,&p), что равносильно */
            fscanf(fin, " %s %s %d %d %s ", &El.Z, &El.F, &El.R, &El.P,
                   &El.V);
            Pos = ftell(fin);
            printf("\n %s %s %d %d %s  ", El.Z, El.F, El.R, El.P, El.V);
            printf
            ("\n Будете ли обновлять запись? (д/н)");
            fflush(NULL);
            scanf("%c", &v);
            if (v != 'д')
            {
                p = Pos;
                continue;
            }
            while (1)
            {
                printf(" Группа=>");
                fflush(NULL);
                fgets(N,40,stdin);
                s = strlen(N);
                if (s == 0)
                    break;
                if (s != strlen(El.Z))
                {
                    printf("\n Ошибка!!! ");
                    continue;
                }
                strcpy(El.Z, N);
                break;
            }
            while (1)
            {
                printf(" Фамилия=>");
                fflush(NULL);
                fgets(N,40,stdin);
                s = strlen(N);
                if (s == 0)
                    break;
                if (s != strlen(El.F))
                {
                    printf("\n Ошибка!!! ");
                    continue;
                }
                strcpy(El.F, N);
                break;
            }
            while (1)
            {
                printf(" Год рождения=>");
                fflush(NULL);
                fgets(N,40,stdin);
                s = strlen(N);
                if (s == 0)
                    break;
                j = 0;
                while (N[j] >= '0' && N[j] <= '9')
                    j++;
                if (j < s || j != 4)
                {
                    printf
                    ("\n Ошибка, повторно введите ");
                    continue;
                }
                else
                {
                    El.R = atoi(N);
                    break;
                }
            }
            while (1)
            {
                printf(" Год поступления=>");
                fflush(NULL);
                fgets(N,40,stdin);
                s = strlen(N);
                if (s == 0)
                    break;
                j = 0;
                while (N[j] >= '0' && N[j] <= '9')
                    j++;
                if (j < s || j != 4)
                {
                    printf
                    ("\n Ошибка, повторно введите ");
                    continue;
                }
                else
                {
                    El.P = atoi(N);
                    break;
                }
            }

            while (1)
            {
                printf(" специальность=>");
                fflush(NULL);
                fgets(N,40,stdin);
                s = strlen(N);
                if (s == 0)
                    break;
                if (strlen(El.V) != s)
                {
                    printf("\n Ошибка!!! ");
                    continue;
                }
                strcpy(El.V, N);
                break;
            }
            printf("\n%s %s %5d %5d %s \n", El.Z, El.F, El.R, El.P, El.V);
            getchar();
            fseek(fin, p, SEEK_SET);
            fprintf(fin, "%s %s %5d %5d %s \n", El.Z, El.F, El.R, El.P,
                    El.V);
            p = Pos;
        }
        fclose(fin);
    }
    return 0;
}

/* ************************************************************ */
