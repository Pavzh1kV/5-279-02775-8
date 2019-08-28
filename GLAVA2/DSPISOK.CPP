/* РАБОТА С ПОСЛЕДОВАТЕЛЬНЫМ СПИСКОМ   c:\bc\xbs\spisok\dspisok.cpp */
/* Пример управления списком с использованием дескриптора */
/* В файл <stdio.h> введена строка: int _Cdecl flushall(void); */
#include <stdio.h>
#include <locale.h>
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

#define DS struct ds
DS
{
    KT *SP;			/* указатель на начало списка */
    KT *TEK;			/* указатель на текущий элемент */
    KT *PRED;			/* указатель на предыдущий элемент */
    KT *RAB;			/* указатель на рабочий элемент */
    int c;			/* счетчик элементов в списке */
} *d1;

typedef KT KURSANT;
char *menu[10][40];
int i;
static int p = 1;
char key[81];
void main_menu(void);
void create_el(DS * L, char *key);
void create_sp(DS * l);
void insert(DS * l);
void change(DS * l);
void show_el(DS * l);
void show_sp(DS * l);
void del_el(DS * l);
void destroy(DS * l);
void wait_entr(void);
void get_str(char *ln, int n);
void out_file(DS * l);
int in_file(DS * L);
void out_filef(DS * T);
int in_filef(DS * L);

/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
main()
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    /* Инициализация дескриптора */
    d1->SP = d1->RAB = d1->TEK = d1->PRED = NULL;	/*указатели */
    d1->c = 0;			/* счетчик элементов */
    *menu[0] = "1.Сохранение списка в файле";
    *menu[1] =
        "2.Восстановление списка из файла";
    *menu[2] = "3.Включение курсанта в список";
    *menu[3] = "4.Изменение данных о курсанте,";
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
            fflush(NULL);
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        else
            pp = 0;
        switch (ns)
        {
        case '1':
            out_filef(d1);
            break;
        case '2':
            in_filef(d1);
            break;
        case '3':
            insert(d1);
            break;
        case '4':
            change(d1);
            break;
        case '5':
            show_el(d1);
            break;
        case '6':
            del_el(d1);
            break;
        case '7':
            show_sp(d1);
            break;
        case '8':
            destroy(d1);
            break;
        case '9':
            p = 0;
        }
    }
}

/* ================================================== */

/*  СОЗДАНИЕ НОВОГО СПИСКА */
void create_sp(DS * L)
{
    printf
    ("\n Старый список уничтожается! Вы согласны? (y/n)\n");
    scanf("%s", &key);
    if (strcmp(key, "y"))
        return;
    else
    {
        destroy(L);
        L->SP = L->PRED = L->TEK = L->RAB = 0;
    }
}

/* =========================================================*/
/* ВЫВОД СПИСКА НА ЭКРАН */
void show_sp(DS * L)
{
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != NULL)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
        printf("\n%s %d %d  %d %s",
               L->PRED->FIO, L->PRED->OC1, L->PRED->OC2, L->PRED->OC3,
               L->PRED->prim);
    }
    printf("\n\n КОНЕЦ СПИСКА");
    wait_entr();
}

/* ====================================================== */

/*  ВЫВОД ДАННЫХ О КУРСАНТЕ */
void show_el(DS * L)
{
    printf("\n Введите Ф.И.О.\n");
    get_str(key, 23);
    /*Поиск курсанта в списке */
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != 0 && strcmp(L->TEK->FIO, key) < 0)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
    }
    if (strcmp(L->TEK->FIO, key) == 0)  	/*Курсант найден */
    {
        printf("\n %s", L->TEK->FIO);
        printf("\n Первая оценка - %d", L->TEK->OC1);
        printf("\n Вторая оценка - %d", L->TEK->OC2);
        printf("\n Третья оценка - %d", L->TEK->OC3);
        printf("\n %s", L->TEK->prim);
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
void change(DS * L)
{
    int p = 1;
    printf("\n введите ФИО \n");
    get_str(key, 23);
    /* поиск курсанта в списке */
    L->PRED = NULL;
    L->TEK = L->SP;
    while ((L->TEK != 0) && (strcmp(L->TEK->FIO, key) < 0))
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
    }
    /* курсанта нет в списке */
    if (strcmp(L->TEK->FIO, key) != 0)
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
             L->TEK->OC1);
            scanf("%d", &L->TEK->OC1);
            /* проверка 2<=OC1<=5 */
            if ((L->TEK->OC1) > 5 || (L->TEK->OC1) < 2)
                printf("\n ОШИБКА !! ");
            else
                p = 0;
        }
    }
    /*  .....  ввод второй оценки, ....  */
}

/* ===================================================== */
/*СОЗДАНИЕ И ЗАПОЛНЕНИЕ ЭЛЕМЕНТА*/
void create_el(DS * L, char *key)
{
    int p = 1;
    L->RAB = (KT *) calloc(1, sizeof(KT));
    strcpy(L->RAB->FIO, key);
    p = 1;
    while (p)
    {
        printf("Введите 1-ю оценку\n");
        fflush(NULL);
        scanf("%d", &L->RAB->OC1);
        if ((L->RAB->OC1) < 2 || (L->RAB->OC1) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 2-ю оценку\n");
        fflush(NULL);
        scanf("%d", &L->RAB->OC2);
        if ((L->RAB->OC2) < 2 || ((L->RAB->OC2) > 5))
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 3-ю оценку\n");
        fflush(NULL);
        scanf("%d", &L->RAB->OC3);
        if ((L->RAB->OC3) < 2 || (L->RAB->OC3) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    printf("Введите примечание\n");
    get_str(L->RAB->prim, 44);
    printf("%s %d %d", L->RAB->FIO, L->RAB->OC1, L->RAB->OC2);
    getchar();
}

/* ============================================ */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В УПОРЯДОЧЕННЫЙ СПИСОК */
void insert(DS * l)
{
    printf("\n Введите ФИО курсанта\n ");
    get_str(key, 23);
    /*Список пустой, включаем в начало */
    if (l->c == 0)
    {
        create_el(l, key);
        l->RAB->next = NULL;
        l->SP = l->RAB;
        l->c = l->c + 1;
        return;
    };
    /*Поиск курсанта в списке */
    l->PRED = NULL;
    l->TEK = l->SP;
    while ((l->TEK != 0) && strcmp(l->TEK->FIO, key) < 0)
    {
        l->PRED = l->TEK;
        l->TEK = l->TEK->next;
    };
    /*Курсант найден в списке */
    if (strcmp(l->TEK->FIO, key) == 0)
    {
        printf("\n %s  уже находится в списке\n", key);
        wait_entr();
        return;
    };
    /*Курсант не найден в списке, включаем в список */
    l->c = l->c + 1;
    create_el(l, key);
    l->RAB->next = l->TEK;
    if (l->PRED == NULL)	/*Включение в начало списка */
        l->SP = l->RAB;
    else
        l->PRED->next = l->RAB;
}

/* ================================================== */
/* ИСКЛЮЧЕНИЕ КУРСАНТА ИЗ СПИСКА */
void del_el(DS * L)
{
    printf("\n Введите Ф.И.О.\n");
    get_str(key, 23);
    /*Поиск курсанта в списке */
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != 0 && strcmp(L->TEK->FIO, key) < 0)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
    }
    /*Курсанта нет в списке */
    if (strcmp(L->TEK->FIO, key) != 0)
    {
        printf("\n %s нет в списке\n", key);
        wait_entr();
        return;
    }
    /*Курсант найден */
    if (L->PRED == NULL && (L->TEK->next) == NULL)
        L->SP = NULL;
    else if (L->SP == L->TEK)
        L->SP = L->TEK->next;
    else
        L->PRED->next = L->TEK->next;
    free(L->TEK);
    L->c = L->c - 1;
}

/* =============================================== */
/* УНИЧТОЖЕНИЕ СПИСКА */
void destroy(DS * L)
{
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != NULL)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
        free(L->PRED);
    }
    L->SP = L->PRED = L->TEK = L->RAB = NULL;
    L->c = 0;
}

/* ==================================== */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА   */
void wait_entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ==================================== */
/* ВВОД СТРОКИ СИМВОЛОВ */
void get_str(char *ln, int n)
{
    fflush(NULL);			/* чистка буферов ввода-вывода */
    for (i = 0; ((ln[i] = getchar()) != '\n' && (i < n)); i++);
    ln[i] = '\0';
    fflush(NULL);
}

/* ======================================== */
/* ЗАПИСЬ СПИСКА В ФАЙЛ, неформатитрованный (байтовый) вывод  */
void out_file(DS * L)
{
    FILE *fout;
    char name[80];
    char *e;
    int sk = sizeof(KURSANT);
    printf
    (" Введите полное имя файла, например, d:\\tc\\531-1\\sp531-5.str ");
    fflush(NULL);
    fgets(name,80,stdin);
    fout = fopen(name, "wb");
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != NULL)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
        e = (char *) L->PRED;
        for (i = 0; i < sk; i++)
            fputc(e[i], fout);
    }
    fclose(fout);
    printf("Список записан в файл %s", name);
    wait_entr();
}

/* ====================================================== */
/* ВОССТАНОВЛЕНИЕ СПИСКА ИЗ ФАЙЛА, побайтовый ввод данных */
int in_file(DS * L)
{
    FILE *fin;
    KURSANT *R;
    int j, i = 0;
    char name[80];
    char *e;
    int sk = sizeof(KURSANT);
    printf
    (" Введите полное имя файла, например, d:\\tc\\531-1\\sp531-5.str ");
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
        e = (char *) calloc(1, sizeof(KURSANT));
        for (j = 0; j < sk; j++)
        {
            e[j] = getc(fin);
            if (feof(fin) != 0)
            {
                printf("\n Конец файла");
                fflush(NULL);
                getchar();
                free(e);
                return 0;
            }
        }
        R = (KURSANT *) e;
        R->next = NULL;
        printf("\n%s %d %d %d %s %ld", R->FIO,
               R->OC1, R->OC2, R->OC3, R->prim, R->next);
        if (i++ == 0)
        {
            L->SP = R;
            L->PRED = R;
        }
        else
        {
            L->PRED->next = R;
            L->PRED = L->PRED->next;
        }
    }
    wait_entr();
    return 0;
}

/* ================================================== */
/* ЗАПИСЬ СПИСКА В ФАЙЛ, текстовый режим - форматный вывод */
void out_filef(DS * L)
{
    FILE *fout;
    char name[80];
    printf
    (" Введите полное имя файла, например, d:\\tc\\531-1\\sp531-5.str ");
    fflush(NULL);
    fgets(name,80,stdin);
    fout = fopen(name, "w");
    L->PRED = NULL;
    L->TEK = L->SP;
    while (L->TEK != 0)
    {
        L->PRED = L->TEK;
        L->TEK = L->TEK->next;
        fprintf(fout, "%s %d %d %d %s \n",
                L->PRED->FIO, L->PRED->OC1, L->PRED->OC2, L->PRED->OC3,
                L->PRED->prim);
    }
    fclose(fout);
    printf("Список записан в файл %s", name);
    wait_entr();
}

/* ======================================================== */
/* ЧТЕНИЕ СПИСКА ИЗ ФАЙЛА, текстовый режим - форматный ввод */
int in_filef(DS * L)
{
    FILE *fin;
    KURSANT rt, *R;
    int i = 0;
    char name[80];
    printf
    (" Введите полное имя файла, например, d:\\tc\\531-1\\sp531-5.str ");
    fflush(NULL);
    fgets(name,80,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n Файла %s нет", name);
        return 0;
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
            L->SP = R;
            L->PRED = R;
        }
        else
        {
            L->PRED->next = R;
            L->PRED = L->PRED->next;
        }
        printf(" \n %s %d %d %d %s \n", rt.FIO, rt.OC1, rt.OC2, rt.OC3,
               rt.prim);
        wait_entr();
    }
    return 0;
}

/* *************************************************************** */
