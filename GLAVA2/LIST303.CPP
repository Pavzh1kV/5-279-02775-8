/* РАБОТА С ТРЕМЯ ПОСЛЕДОВАТЕЛЬНЫМИ СПИСКАМИ */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#define EL struct el_type
#define k 13
EL
{
    char FIO[24];
    int OC1;
    int OC2;
    int OC3;
    char prim[45];
    EL *next;
};

typedef char *KEY;
EL *SP, *RAB, *TEK, *PRED, *SPA, *SPB, *SPC, *TEKA, *TEKB, *TEKC;
char *menu[k][40];
int i;
int p = 1, ts = 1;
KEY key;
void main_menu(void);
EL *Create_el(char *key);
EL *Insert(EL ** L);
int Change(EL ** L);
int Show_el(EL el);		/*показ содержимого элемента */
int Show_elkey(EL * L);		/* показ элемента по ключу */
void Show_sp(EL * L);
int Del_el(EL ** L);
void Destroy(EL ** L);
void Wait_entr(void);
void Get_str(char *ln, int n);
void Select_sp(void);
void Out_f_t(EL * T);
int In_f_t(EL ** L);
void Out_f_b(EL * T);
int In_f_b(EL ** L);
int Cross_Ls(EL * A, EL * B, EL ** C);
int Uni_Ls(EL * A, EL * B, EL ** C);
KEY In_key();
EL *Search_el(EL * L, KEY key);
EL el;
/* ==================================================== */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    key = (KEY) calloc(80, sizeof(char));
    SP = RAB = TEK = PRED = SPA = SPB = SPC = NULL;
    *menu[0] = "1. Выбор списка";
    *menu[1] = "2. Включение элемента в список";
    *menu[2] = "3. Изменение данных в элементе";
    *menu[3] = "4. Вывод данных элемента";
    *menu[4] = "5. Удаление элемента из списка";
    *menu[5] = "6. Вывод списка на экран";
    *menu[6] = "7. Уничтожение списка";
    *menu[7] = "8. Сохранение списка в файле";
    *menu[8] =
        "9. Восстановление списка из файла";
    *menu[9] =
        "10.Объединение списков как множеств";
    *menu[10] =
        "11.Пересечение cписков как множеств";
    *menu[11] = "12.Конец работы";
    *menu[12] = "         Введите номер строки";
    system("clear");
    printf("    Работа со списком \n");
    while (p)
    {
        main_menu();
        system("clear");
    }
    printf("    Конец pаботы со списком\n");
    return 0;
}

/* ======================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void main_menu(void)
{
    int ns;
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
        else
            break;
    }
    switch (ts)
    {
    case 1:
        SPA = SP;
        break;
    case 2:
        SPB = SP;
        break;
    case 3:
        SPC = SP;
    }
    switch (ns)
    {
    case 1:
        Select_sp();
        break;
    case 2:
        Insert(&SP);
        break;
    case 3:
        Change(&SP);
        break;
    case 4:
        Show_elkey(SP);
        break;
    case 5:
        Del_el(&SP);
        break;
    case 6:
        Show_sp(SP);
        break;
    case 7:
        Destroy(&SP);
        break;
    case 8:
        Out_f_t(SP);
        break;
    case 9:
        In_f_t(&SP);
        break;
    case 10:
        Uni_Ls(SPA, SPB, &SPC);
        break;
    case 11:
        Cross_Ls(SPA, SPB, &SPC);
        break;
    case 12:
        p = 0;
    }
}

/* ===================================================== */
/* ВЫВОД СПИСКА НА ЭКРАН */
void Show_sp(EL * L)
{
    TEK = L;
    while (TEK != 0)
    {
        Show_el(*TEK);
        TEK = TEK->next;
    }
    printf("\n КОНЕЦ СПИСКА");
    Wait_entr();
}

/* ===================================================== */
/* ПОИСК ЭЛЕМЕНТА СПИСКА */
EL *Search_el(EL * L, KEY key)
{
    PRED = 0;
    TEK = L;
    while (TEK != 0 && strcmp(TEK->FIO, key) < 0)
    {
        PRED = TEK;
        TEK = TEK->next;
    }
    if (strcmp(TEK->FIO, key) == 0)
        return TEK;
    else
        return NULL;
}

/* ===================================================== */
/*  ВЫВОД ДАННЫХ ЭЛЕМЕНТА */
int Show_elkey(EL * L)
{
    KEY key;
    EL *el;
    /* Ввод ключа поиска */
    key = In_key();
    /*Поиск элемента в списке */
    if (el = Search_el(L, key))
        Show_el(*el);
    else
        printf(" Элемент %s не найден", key);
    getchar();
    return 0;
}

/* ======================================================== */
/*  ВЫВОД ДАННЫХ НА ЭКРАН */
int Show_el(EL el)
{
    printf("\n%s %d %d %d %s", el.FIO, el.OC1, el.OC2, el.OC3, el.prim);
    return 0;
}

/* ========================================================= */
/* ИЗМЕНЕНИЕ ДАННЫХ ЭЛЕМЕНТА */
int Change(EL ** l)
{
    EL *el;
    key = In_key();		/* ключ поиска */
    /* поиск элемента в списке */
    el = Search_el(*l, key);
    /* элемента нет в списке */
    if (!el)
    {
        printf("\n %s не найден в списке \n", key);
        Wait_entr();
        return -1;
    }
    else  			/* элемент найден, обновим первую оценку */
    {
        while (1)
        {
            printf
            ("\n Первая оценка- %d,введите новое значение ",
             TEK->OC1);
            scanf("%d", &TEK->OC1);
            /* проверка 2<=OC1<=5 */
            if ((TEK->OC1) > 5 || (TEK->OC1) < 2)
            {
                printf("\n ОШИБКА !! ");
                continue;
            }
            else
                break;
        }
        /*  ..Обновление второй оценки, ....  */
    }
    return 0;
}

/* ================================================== */
/*СОЗДАНИЕ И ЗАПОЛНЕНИЕ ЭЛЕМЕНТА*/
EL *Create_el(char *key)
{
    RAB = (EL *) calloc(1, sizeof(EL));
    strcpy(RAB->FIO, key);
    while (1)
    {
        printf("Введите 1-ю оценку\n");
        scanf("%d", &RAB->OC1);
        if ((RAB->OC1) < 2 || (RAB->OC1) > 5)
        {
            printf("\nОШИБКА!!!\n");
            fflush(NULL);
            continue;
        }
        else
            break;
    }
    while (1)
    {
        printf("Введите 2-ю оценку\n");
        scanf("%d", &RAB->OC2);
        if ((RAB->OC2) < 2 || (RAB->OC2) > 5)
        {
            printf("\nОШИБКА!!!\n");
            fflush(NULL);
            continue;
        }
        else
            break;
    }
    while (1)
    {
        printf("Введите 3-ю оценку\n");
        scanf("%d", &RAB->OC3);
        if ((RAB->OC3) < 2 || (RAB->OC3) > 5)
        {
            printf("\nОШИБКА!!!\n");
            fflush(NULL);
            continue;
        }
        else
            break;
    }
    printf("Введите примечание\n");
    Get_str(RAB->prim, 44);
    return RAB;
}

/* ===================================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В УПОРЯДОЧЕННЫЙ СПИСОК */
/* Элемент не подготовлен */
EL *Insert(EL ** L)
{
    key = In_key();
    if (Search_el(*L, key))
    {
        printf("\n %s  уже находится в списке\n", key);
        Wait_entr();
        return NULL;
    }
    /* Создание элемента */
    Create_el(key);
    /*Список пустой, включаем в начало */
    if (*L == 0)
    {
        RAB->next = *L;
        *L = RAB;
        return RAB;
    };
    RAB->next = TEK;
    if (PRED == 0)		/*Включение в начало списка */
        *L = RAB;
    else
        PRED->next = RAB;
    return 0;
}

/*  ============================================== */
/* ИСКЛЮЧЕНИЕ ЭЛЕМЕНТА ИЗ СПИСКА */
int Del_el(EL ** l)
{
    EL *e;
    key = In_key();
    TEK = *l;
    /*Поиск элемента в списке */
    e = Search_el(*l, key);
    /*Элемента нет в списке */
    if (!e)
    {
        printf("\n %s нет в списке\n", key);
        Wait_entr();
        return -1;
    }
    /* Элемент найден */
    if (PRED == 0 && (TEK->next) == 0)	/* единственный элемент */
        *l = 0;
    else if (*l == TEK)
        *l = TEK->next;
    else
        PRED->next = TEK->next;
    free(TEK);
    return 0;
}

/* ========================================================== */
/* УНИЧТОЖЕНИЕ СПИСКА */
void Destroy(EL ** l)
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

/* ============================================================ */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА   */
void Wait_entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ============================================================= */
/* ВВОД СТРОКИ СИМВОЛОВ ЗАДАННОЙ ДЛИНЫ */
void Get_str(char *ln, int n)
{
    fflush(NULL);			/* чистка буферов ввода-вывода */
    for (i = 0; ((ln[i] = getchar()) != '\n' && (i < n)); i++);
    ln[i] = '\0';
    fflush(NULL);
}

/* ============================================================== */
/* ВЫБОР СПИСКА */
void Select_sp(void)
{
    char ns;
    while (1)
    {
        fflush(NULL);
        printf("  Введите номер списка (1,2,3)=>");
        ns = getchar();
        if (ns < '1' || ns > '3')
        {
            printf("Ошибка в номере, повторно \n");
            continue;
        }
        else
            break;
    }
    switch (ns)
    {
    case '1':
        ts = 1;
        SP = SPA;
        break;
    case '2':
        ts = 2;
        SP = SPB;
        break;
    case '3':
        ts = 3;
        SP = SPC;
    }
}

/* ===================================================== */
/* ОБЪЕДИНЕНИЕ ДВУХ СПИСКОВ КАК МНОЖЕСТВ */
int Uni_Ls(EL * A, EL * B, EL ** C)
{
    int s;
    switch (ts)
    {
    case 1:
        SPA = SP;
        break;
    case 2:
        SPB = SP;
        break;
    case 3:
        SPC = SP;
        ts = 1;
        SP = SPA;
    }
    printf("\n Объединение списков ");
    if (SPC != NULL)
        Destroy(&SPC);
    if ((SPA == NULL) && (SPB == NULL))
    {
        SPC = NULL;
        printf("\n Исходные списки пустые \n");
        Wait_entr();
        return -1;
    }
    TEKA = SPA;
    TEKB = SPB;
    SPC = (EL *) calloc(1, sizeof(EL));
    TEKC = SPC;
    PRED = SPC;
    while ((TEKA != NULL) || (TEKB != NULL))
        if (TEKA == NULL)
            while (TEKB != NULL)
            {
                *TEKC = *TEKB;
                TEKC->next = (EL *) calloc(1, sizeof(EL));
                PRED = TEKC;
                TEKC = TEKC->next;
                TEKB = TEKB->next;
            }
        else if (TEKB == NULL)
            while (TEKA != NULL)
            {
                *TEKC = *TEKA;
                TEKC->next = (EL *) calloc(1, sizeof(EL));
                PRED = TEKC;
                TEKC = TEKC->next;
                TEKA = TEKA->next;
            }
        else
        {
            s = strcmp(TEKA->FIO, TEKB->FIO);
            if (s == 0)
            {
                *TEKC = *TEKA;
                TEKA = TEKA->next;
                TEKB = TEKB->next;
                TEKC->next = (EL *) calloc(1, sizeof(EL));
                PRED = TEKC;
                TEKC = TEKC->next;
            }
            else if (s < 0)
            {
                *TEKC = *TEKA;
                TEKA = TEKA->next;
                TEKC->next = (EL *) calloc(1, sizeof(EL));
                PRED = TEKC;
                TEKC = TEKC->next;
            }
            else
            {
                *TEKC = *TEKB;
                TEKB = TEKB->next;
                TEKC->next = (EL *) calloc(1, sizeof(EL));
                PRED = TEKC;
                TEKC = TEKC->next;
            }
        }
    PRED->next = NULL;
    /* Отладочный режим: выведем списки */
    printf("\n Список А:");
    Show_sp(SPA);
    printf("\n Список В:");
    Show_sp(SPB);
    printf("\n Список С:");
    Show_sp(SPC);
    free(TEKC);
    ts = 3;
    SP = SPC;
    Wait_entr();
    return 0;
}

/* ===================================================== */
/*ПЕРЕСЕЧЕНИЕ ДВУХ УПОРЯДОЧЕННЫХ СПИСКОВ КАК МНОЖЕСТВ*/
int Cross_Ls(EL * A, EL * B, EL ** C)
{
    int s, r, i = 0;
    switch (ts)
    {
    case 1:
        SPA = SP;
        break;
    case 2:
        SPB = SP;
        break;
    case 3:
        SPC = SP;
        ts = 1;
        SP = SPA;
        r = 1;
    }
    printf("\n Операция пересечения списков");
    if (SPC != NULL)
        Destroy(&SPC);		/*Уничтожить список С */
    if ((SPA == NULL) || (SPB == NULL))  	/* А или В-пустой */
    {
        SPC = NULL;
        printf("\n Исходный список пустой \n");
        Wait_entr();
        return -1;
    }
    TEKA = SPA;
    TEKB = SPB;
    SPC = (EL *) calloc(1, sizeof(EL));
    TEKC = SPC;
    PRED = SPC;
    while ((TEKA != NULL) && (TEKB != NULL))
    {
        s = strcmp(TEKA->FIO, TEKB->FIO);	/*Сравнение ключей */
        if (s == 0)
        {
            *TEKC = *TEKA;
            TEKA = TEKA->next;
            TEKB = TEKB->next;
            TEKC->next = (EL *) calloc(1, sizeof(EL));
            PRED = TEKC;
            TEKC = TEKC->next;
            i = i + 1;
        }
        else if (s < 0)
        {
            TEKA = TEKA->next;
        } /* к следующ.эл-ту списка А */
        else
        {
            TEKB = TEKB->next;
        }			/* к следующ.эл-ту списка В */
    }
    PRED->next = NULL;
    if (i == 0)
    {
        SPC = NULL;
        r = 0;
        printf
        ("\n Общих элементов нет - список С пуст");
        Wait_entr();
    }
    /* Отладочный режим: выведем списки */
    printf("\n Список А:");
    Show_sp(SPA);
    printf("\n Список В:");
    Show_sp(SPB);
    printf("\n Список С:");
    Show_sp(SPC);
    free(TEKC);
    if (r == 1)
    {
        ts = 3;
        SP = SPC;
    }
    Wait_entr();
    return 0;
}

/* ========================================================= */
/* ЗАПИСЬ СПИСКА В ФАЙЛ, двоичный режим */
void Out_f_b(EL * T)
{
    FILE *fout;
    char name[80];
    char *e;
    int sk = sizeof(EL);
    printf(" Введите полное имя файла =>");
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
    Wait_entr();
}

/* ===================================================== */
/* ЧТЕНИЕ СПИСКА ИЗ ФАЙЛА, двоичный режим */
int In_f_b(EL ** L)
{
    FILE *fin;
    EL *R;
    int j, i = 0;
    char name[80];
    char *e;
    int sk = sizeof(EL);
    printf
    (" Введите полное имя файла хранения списка \n => ");
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
        e = (char *) calloc(1, sizeof(EL));
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
        R = (EL *) e;
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
    Wait_entr();
    return 0;
}

/* ======================================================= */
/* ЗАПИСЬ СПИСКА В ФАЙЛ , текстовый режим, форматный вывод */
void Out_f_t(EL * T)
{
    FILE *fout;
    char name[80];
    printf(" Введите полное имя файла => ");
    fflush(NULL);
    fgets(name,80,stdin);
    fout = fopen(name, "w");
    PRED = 0;
    TEK = T;
    while (TEK != 0)
    {
        PRED = TEK;
        TEK = TEK->next;
        fputs(PRED->FIO, fout);
        fputc('\n', fout);
        fprintf(fout, " %d %d %d ", PRED->OC1, PRED->OC2, PRED->OC3,
                PRED->prim);
        fputs(PRED->prim, fout);
        fputc('\n', fout);
    }
    fclose(fout);
    printf("Список записан в файл %s", name);
    Wait_entr();
}

/* ============================================================== */
/* ЧТЕНИЕ СПИСКА ИЗ ФАЙЛА, текстовый режим, форматный ввод */
int In_f_t(EL ** L)
{
    FILE *fin;
    EL rt, *R;
    int i = 0;
    char name[80];
    printf
    (" Введите полное имя файла хранения списка \n =>");
    fflush(NULL);
    fgets(name,80,stdin);
    if ((fin = fopen(name, "r")) != 0)
        printf("okey");
    else
    {
        printf("\n Файла %s нет", name);
        getchar();
        return 1;
    }
    fflush(NULL);
    getchar();
    while (feof(fin) == 0)
    {
        R = (EL *) calloc(1, sizeof(EL));
        rt = *R;
        fgets(rt.FIO, 40, fin);
        *strchr(rt.FIO, '\n') = '\0';
        fscanf(fin, " %d %d %d ", &rt.OC1, &rt.OC2, &rt.OC3);
        fgets(rt.prim, 80, fin);
        *strchr(rt.prim, '\n') = '\0';
        rt.next = 0;
        if (feof(fin) != 0)
            break;
        *R = rt;
        if (i++ == 0)
        {
            *L = R;
            PRED = R;
            Wait_entr();
        }
        else
        {
            PRED->next = R;
            PRED = PRED->next;
        }
        printf(" \n %s %d %d %d %s \n", rt.FIO, rt.OC1, rt.OC2, rt.OC3,
               rt.prim);
    }
    Wait_entr();
    return 0;
}

/* ================================================================= */
/* ВВОД КЛЮЧА ЭЛЕМЕНТА */
KEY In_key()
{
    char key[80];
    printf("\nВведите ключ элемента =>");
    scanf("%s", &key);
    return key;
}

/* ****************************************************************** */
