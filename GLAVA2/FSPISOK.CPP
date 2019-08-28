/* **************************************************** */
/* РАБОТА С ПОСЛЕДОВАТЕЛЬНЫМ СПИСКОМ   \fspisok.cpp     */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#define KT struct el_type
KT
{
    char FIO[24];
    int OC1;
    int OC2;
    int OC3;
    char prim[45];
    KT *next;
};

typedef KT KURSANT;
KURSANT *SP, *RAB, *TEK, *PRED;
char *menu[10][40];
int i;
static int p = 1;
char key[81];
void main_menu(void);		/* вывод главного меню */
void create_el(char *key);	/* создание элемента */
void create_sp(KURSANT ** l);	/* создание нового списка */
void insert(KURSANT ** l);	/* включение эл-та в список */
void change(KURSANT ** l);	/* изменение  данных в элементе */
void show_el(KURSANT * l);	/* показ элемента */
void show_sp(KURSANT * l);	/* показ списка */
void del_el(KURSANT ** l);	/* удаление элемента */
void destroy(KURSANT ** l);	/* уничтожение списка */
void wait_entr(void);		/* "подождите" */
void get_str(char *ln, int n);	/* ввод строки */
void out_file(KURSANT * T);	/* сохранение списка в файле */
int in_file(KURSANT ** L);	/* восстановление списка из файла */
void out_filef(KURSANT * T);	/* сохранение списка в файле */
int in_filef(KURSANT ** L);	/* восстановление списка из файла */

/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
main()
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    SP = 0;
    RAB = 0;
    TEK = 0;
    PRED = 0;
    *menu[0] = "1.Сохранение списка в файле";
    *menu[1] =
        "2.Восстановление списка из файла";
    *menu[2] = "3.Включение курсанта в список";
    *menu[3] = "4.Изменение данных о курсанте";
    *menu[4] = "5.Вывод данных о курсанте";
    *menu[5] = "6.Удаление курсанта из списка";
    *menu[6] = "7.Вывод списка на экран";
    *menu[7] = "8.Уничтожение списка";
    *menu[8] = "9.Конец работы";
    *menu[9] = "         Введите номер строки";
    system("clear");
    printf("    Работа со списком курсантов\n");
    while (p)
    {
        main_menu();
        system("clear");
    }
    printf("    Конец pаботы со списком\n");
    return 0;
}

/* ================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void main_menu(void)
{
    char ns;
    int pp = 1;
    fflush(NULL);			/* чистка буферов */
    while (pp)
    {
        for (i = 0; i < 10; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        ns = getchar();
        if (ns < '1' || ns > '9')
        {
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        else
            pp = 0;
        switch (ns)
        {
        case '1':
            out_filef(SP);
            break;
        case '2':
            in_filef(&SP);
            break;
        case '3':
            insert(&SP);
            break;
        case '4':
            change(&SP);
            break;
        case '5':
            show_el(SP);
            break;
        case '6':
            del_el(&SP);
            break;
        case '7':
            show_sp(SP);
            break;
        case '8':
            destroy(&SP);
            break;
        case '9':
            p = 0;
        }
    }
}

/* ================================================== */
/*  СОЗДАНИЕ НОВОГО СПИСКА */
void create_sp(KURSANT ** l)
{
    printf
    ("\n Старый список уничтожается! Вы согласны? (y/n)\n");
    scanf("%s", &key);
    if (strcmp(key, "y"))
        return;
    else
    {
        destroy(&SP);
        *l = 0;
        PRED = 0;
        TEK = 0;
        RAB = 0;
    }
}

/* =========================================================*/
/* ВЫВОД СПИСКА НА ЭКРАН */
void show_sp(KURSANT * L)
{
    PRED = 0;
    TEK = L;
    while (TEK != 0)
    {
        PRED = TEK;
        TEK = TEK->next;
        printf("\n%s %d %d  %d %s",
               PRED->FIO, PRED->OC1, PRED->OC2, PRED->OC3, PRED->prim);
    }
    printf("\n\n КОНЕЦ СПИСКА");
    wait_entr();
}

/* ====================================================== */
/*  ВЫВОД ДАННЫХ О КУРСАНТЕ */
void show_el(KURSANT * l)
{
    printf("\n Введите Ф.И.О.\n");
    get_str(key, 23);
    /*Поиск курсанта в списке */
    PRED = 0;
    TEK = l;
    while (TEK != 0 && strcmp(TEK->FIO, key) < 0)
    {
        PRED = TEK;
        TEK = TEK->next;
    }
    if (strcmp(TEK->FIO, key) == 0)  	/*Курсант найден */
    {
        printf("\n %s", TEK->FIO);
        printf("\n Первая оценка - %d", TEK->OC1);
        printf("\n Вторая оценка - %d", TEK->OC2);
        printf("\n Третья оценка - %d", TEK->OC3);
        printf("\n %s", TEK->prim);
        wait_entr();
        return;
    }
    else
    {
        printf("\n %s нет в списке\n", key);
        wait_entr();
    }
}

/*  ================================================= */
/* ИЗМЕНЕНИЕ ДАННЫХ О КУРСАНТЕ */
void change(KURSANT ** l)
{
    int p = 1;
    printf("\n введите ФИО \n");
    get_str(key, 23);
    /* поиск курсанта в списке */
    PRED = 0;
    TEK = *l;
    while ((TEK != 0) && (strcmp(TEK->FIO, key) < 0))
    {
        PRED = TEK;
        TEK = TEK->next;
    }
    /* курсанта нет в списке */
    if (strcmp(TEK->FIO, key) != 0)
    {
        printf("\n %s не найден в списке \n", key);
        wait_entr();
        return;
    }
    else  			/* курсант найден */
    {
        p = 1;
        while (p)
        {
            printf
            ("\n Первая оценка- %d, введите новое значение ",
             TEK->OC1);
            scanf("%d", &TEK->OC1);
            /* проверка 2<=OC1<=5 */
            if ((TEK->OC1) > 5 || (TEK->OC1) < 2)
                printf("\n ОШИБКА !! ");
            else
                p = 0;
        }
    }
    /*  .....  ввод второй оценки, ....  */
}

/* ===================================================== */
/*СОЗДАНИЕ И ЗАПОЛНЕНИЕ ЭЛЕМЕНТА*/
void create_el(char *key)
{
    int p = 1;
    RAB = (KURSANT *) calloc(1, sizeof(KURSANT));
    strcpy(RAB->FIO, key);
    p = 1;
    while (p)
    {
        printf("Введите 1-ю оценку\n");
        fflush(NULL);
        scanf("%d", &RAB->OC1);
        if ((RAB->OC1) < 2 || (RAB->OC1) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 2-ю оценку\n");
        fflush(NULL);
        scanf("%d", &RAB->OC2);
        if ((RAB->OC2) < 2 || ((RAB->OC2) > 5))
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 3-ю оценку\n");
        fflush(NULL);
        scanf("%d", &RAB->OC3);
        if ((RAB->OC3) < 2 || (RAB->OC3) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    printf("Введите примечание\n");
    get_str(RAB->prim, 44);
}

/* =================================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В УПОРЯДОЧЕННЫЙ СПИСОК */
void insert(KURSANT ** l)
{
    printf("\n Введите ФИО курсанта\n ");
    get_str(key, 23);
    /*Список пустой, включаем в начало*/
    if (*l == 0)
    {
        create_el(key);
        RAB->next = *l;
        *l = RAB;
        return;
    };
    /*Поиск курсанта в списке*/
    PRED = 0;
    TEK = *l;
    while ((TEK != 0) && strcmp(TEK->FIO, key) < 0)
    {
        PRED = TEK;
        TEK = TEK->next;
    };
    /*Курсант найден в списке*/
    if (strcmp(TEK->FIO, key) == 0)
    {
        printf("\n %s  уже находится в списке\n", key);
        wait_entr();
        return;
    };
    /*Курсант не найден в списке, включаем в список*/
    create_el(key);
    RAB->next = TEK;
    if (PRED == 0)		/*Включение в начало списка */
        *l = RAB;
    else
        PRED->next = RAB;
}

/* ================================================= */

/* ИСКЛЮЧЕНИЕ КУРСАНТА ИЗ СПИСКА */
void del_el(KURSANT ** l)
{
    printf("\n Введите Ф.И.О.\n");
    get_str(key, 23);
    /*Поиск курсанта в списке */
    PRED = 0;
    TEK = *l;
    while (TEK != 0 && strcmp(TEK->FIO, key) < 0)
    {
        PRED = TEK;
        TEK = TEK->next;
    }
    /*Курсанта нет в списке */
    if (strcmp(TEK->FIO, key) != 0)
    {
        printf("\n %s нет в списке\n", key);
        wait_entr();
        return;
    }
    /*курсант найден */
    if (PRED == 0 && (TEK->next) == 0)
        *l = 0;
    else if (*l == TEK)
        *l = TEK->next;
    else
        PRED->next = TEK->next;
    free(TEK);
}

/* ======================================================== */
/* УНИЧТОЖЕНИЕ СПИСКА */
void destroy(KURSANT ** l)
{
    PRED = 0;
    TEK = *l;
    while (TEK != 0)
    {
        PRED = TEK;
        TEK = TEK->next;
        free(PRED);
    }
    *l = 0;
}

/* ================================================== */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА   */
void wait_entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ================================================== */
/* ВВОД СТРОКИ СИМВОЛОВ */
void get_str(char *ln, int n)
{
    fflush(NULL);			/* чистка буферов ввода-вывода */
    for (i = 0; ((ln[i] = getchar()) != '\n' && (i < n)); i++);
    ln[i] = '\0';
    fflush(NULL);
}

/* ========================================================== */
/* ЗАПИСЬ СПИСКА В ФАЙЛ, неформатитрованный (байтовый) вывод  */
void out_file(KURSANT * T)
{
    FILE *fout;
    char name[80];
    char *e;
    int sk = sizeof(KURSANT);
    printf(" Введите полное имя файла => ");
    fflush(NULL);
    fgets(name,80,stdin);
    fout = fopen(name, "wb");
    PRED = 0;
    TEK = T;
    while (TEK != 0)
    {
        PRED = TEK;
        TEK = TEK->next;
        e = (char *) PRED;
        for (i = 0; i < sk; i++)
            fputc(e[i], fout);
    }
    fclose(fout);
    printf("Список записан в файл %s", name);
    wait_entr();
}

/* ====================================================== */
/* ВОССТАНОВЛЕНИЕ СПИСКА ИЗ ФАЙЛА, побайтовый ввод данных */
int in_file(KURSANT ** L)
{
    FILE *fin;
    KURSANT rt, *R;
    int j, i = 0;
    char name[80];
    char *e[sizeof(KURSANT)];
    int sk = sizeof(KURSANT);
    printf(" Введите полное имя файла =>");
    fflush(NULL);
    fgets(name,80,stdin);
    if ((fin = fopen(name, "rb")) != 0)
        printf("okey");
    else
    {
        printf("\n Файла %s нет", name);
        getchar();
        return 1;
    }
    while (1)
    {
        for (j = 0; j < sk; j++)
        {
            e[j] = (char *) getc(fin);
            if (feof(fin) != 0)
            {
                printf("\n Конец файла");
                fflush(NULL);
                getchar();
                return 0;
            }
        }
        R = (KURSANT *) e;
        R->next = 0;
        printf("\n%s %d %d %d %s %ld", R->FIO,
               R->OC1, R->OC2, R->OC3, R->prim, R->next);
        if (i++ == 0)
        {
            *L = R;
            PRED = R;
        }
        else
        {
            PRED->next = R;
            PRED = PRED->next;
        }
    }
    wait_entr();
    return 0;
}

/* ======================================================= */
/* ЗАПИСЬ СПИСКА В ФАЙЛ, текстовый режим - форматный вывод */
void out_filef(KURSANT * T)
{
    FILE *fout;
    char name[80];
    printf(" Введите полное имя файла=>");
    fflush(NULL);
    fgets(name,80,stdin);
    fout = fopen(name, "w");
    PRED = 0;
    TEK = T;
    while (TEK != 0)
    {
        PRED = TEK;
        TEK = TEK->next;
        fprintf(fout, "%s %d %d %d %s \n",
                PRED->FIO, PRED->OC1, PRED->OC2, PRED->OC3, PRED->prim);
    }
    fclose(fout);
    printf("Список записан в файл %s", name);
    wait_entr();
}

/* ======================================================== */
/* ЧТЕНИЕ СПИСКА ИЗ ФАЙЛА, текстовый режим - форматный ввод */
int in_filef(KURSANT ** L)
{
    FILE *fin;
    KURSANT rt, *R;
    int i = 0;
    char name[80];
    printf(" Введите полное имя файла=>");
    fflush(NULL);
    fgets(name,80,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n Файла %s нет", name);
        return -1;
    }
    while (feof(fin) == 0)
    {
        R = (KURSANT *) calloc(1, sizeof(KURSANT));
        rt = *R;
        fscanf(fin, "%s %d %d %d %s", &rt.FIO, &rt.OC1, &rt.OC2, &rt.OC3,
               &rt.prim);
        rt.next = 0;
        if (feof(fin) != 0)
            break;
        *R = rt;
        if (i++ == 0)
        {
            *L = R;
            PRED = R;
        }
        else
        {
            PRED->next = R;
            PRED = PRED->next;
        }
        printf(" \n %s %d %d %d %s \n",
               rt.FIO, rt.OC1, rt.OC2, rt.OC3, rt.prim);
        wait_entr();
    }
    return 0;
}

/* ********************************************************* */
