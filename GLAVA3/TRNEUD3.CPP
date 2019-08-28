/* **************************************************************** */
/* РАБОТА С БИНАРНЫМИ ДЕРЕВЬЯМИ: удаление студентов с тремя двойками */
/* trneud3.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define kol 6
#define Rec struct r_e
Rec
{
    char fam[12];
    int mark1, mark2, mark3, mark4;
    Rec *LPTR, *RPTR;
} El;

Rec *T, *RAB;
char *menu[kol][60];
int i, pp, ts = 1, sum;
char key[12];
int ndwo = 0;
char *dwo[20][12];
void Find_dwo(Rec * T);
void Del_dwo(void);
void Crt_Tr_Srch1(void);
int Srch_Insrt1(Rec E, Rec ** T);
void Lpreorder(Rec * T);
void p(Rec * T);
int Del_Node(char *key, Rec ** T);
void Del1(Rec ** R, Rec ** K);
int Main_Menu(void);
void Wait_Entr(void);
int In_Data(void);
int Show_El(void);
/* ===================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ */
int main()
{
    setlocale(LC_ALL,"Russian");
    pp = 1;
    T = 0;
    *menu[0] =
        "1. Создание бинарного дерева поиска";
    *menu[1] = "2. Oбход дерева";
    *menu[2] =
        "3. Вывод данных о заданном студенте на экран";
    *menu[3] =
        "4. Удаление студентов с двумя и более двойками";
    *menu[4] = "5. Конец работы";
    *menu[5] = "         Введите номер строки";
    system("clear");
    printf("    Работа с бинарными деревьями \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    return 0;
}

/* ================================================== */
/*   ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    int ns, m;
    while (1)
    {
        for (i = 0; i < kol; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns > kol)
        {
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
        Crt_Tr_Srch1();
        break;
    case 2:
        Lpreorder(T);
        Wait_Entr();
        break;
    case 3:
        Show_El();
        break;
    case 4:
        ndwo = 0;
        Find_dwo(T);
        Del_dwo();
        break;
    case 5:
        pp = 0;
    }
    return 0;
}

/* =================================================== */
/* ПОСТРОЕНИЕ ДЕРЕВА ПОИСКА */
void Crt_Tr_Srch1(void)
{
    printf
    ("\n Cоздание справочной системы о курсантах.\n");
    while (1)
    {
        if (In_Data() != 0)
        {
            printf("\n Ввод завершен");
            break;
        }
        else
            Srch_Insrt1(El, &T);
    }
}

/* ====================================================== */
/* ВВОД ДАННЫХ ДЛЯ УЗЛА ДЕРЕВА, данные вводятся в диалоге */
int In_Data(void)
{
    printf
    ("\n Введите данные о курсанте или ** для прекращения ввода:");
    printf("\n Фамилия=>");
    scanf("%s", El.fam);
    if (strcmp(El.fam, "**") == 0)
        return -1;
    else
    {
        while (1)
        {
            printf(" Mark1=>");
            fflush(NULL);
            if (!scanf("%d", &El.mark1) || El.mark1 < 2 || El.mark1 > 5)
            {
                printf
                ("\nОШИБКА ВВОДА: оценка может быть только\
		  в интервале [2,5]\nВведите другое значение ");
                continue;
            }
            break;
        }
        while (1)
        {
            printf(" Mark2=>");
            fflush(NULL);
            if (!scanf("%d", &El.mark2) || El.mark2 < 2 || El.mark2 > 5)
            {
                printf
                ("\nОШИБКА ВВОДА: оценка может быть только\
		  в интервале [2,5]\nВведите другое значение ");
                continue;
            }
            break;
        }
        while (1)
        {
            printf(" Mark3=>");
            fflush(NULL);
            if (!scanf("%d", &El.mark3) || El.mark3 < 2 || El.mark3 > 5)
            {
                printf
                ("\nОШИБКА ВВОДА: оценка может быть только\
		  в интервале [2,5]\nВведите другое значение ");
                continue;
            }
            break;
        }
        while (1)
        {
            printf(" Mark4=>");
            fflush(NULL);
            if (!scanf("%d", &El.mark4) || El.mark4 < 2 || El.mark4 > 5)
            {
                printf
                ("\nОШИБКА ВВОДА: оценка может быть только\
		  в интервале [2,5]\nВведите другое значение ");
                continue;
            }
            break;
        }
        return 0;
    }
}

/* ================================================= */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ДЕРЕВО ПОИСКА */
/* E -переменная типа Rec с данными включаемого узла */
/* TT - указатель корня дерева */
int Srch_Insrt1(Rec E, Rec ** TT)
{
    Rec *newnode, *t;
    t = *TT;
    if (*TT == 0)
    {
        newnode = (Rec *) calloc(1, sizeof(Rec));
        *newnode = E;
        newnode->LPTR = 0;
        newnode->RPTR = 0;
        *TT = newnode;
    }
    else if (strcmp(E.fam, t->fam) < 0)
        Srch_Insrt1(E, &t->LPTR);
    else if (strcmp(E.fam, t->fam) > 0)
        Srch_Insrt1(E, &t->RPTR);
    else
    {
        p(*TT);
        printf("\n Элемент уже есть в дереве");
        Wait_Entr();
        return 1;
    }
    return 0;
}

/* ========================================================== */
/* ПОИСК ЭЛЕМЕНТА ПО ЗАДАННОМУ КЛЮЧУ В ДЕРЕВЕ ПОИСКА */
/* в EL возвращается указатель найденного элемента   */
/* код возврата = 0, если элемент найден, =1, если не найден  */
int Loc_Node(char *key, Rec * T, Rec ** EL)
{
    while (1)
    {
        if (T == 0)
            return 1;
        else if (strcmp(key, T->fam) < 0)
            T = T->LPTR;
        else if (strcmp(key, T->fam) > 0)
            T = T->RPTR;
        else
        {
            *EL = T;
            return 0;
        }
    }
}

/* ================================================ */
/* ОЖИДАНИЕ НАЖАТИЯ КЛАВИШИ ВВОДА */
void Wait_Entr(void)
{
    printf("\n Нажмите ввод ");
    fflush(NULL);
    getchar();
}

/* ================================================ */
/* ПЕЧАТЬ ДАННЫХ УЗЛА ДЕРЕВА О КУРСАНТАХ */
void p(Rec * T)
{
    printf("\n %s %d %d %d %d", T->fam, T->mark1, T->mark2, T->mark3,
           T->mark4);
}

/* ================================================= */
void In_fam(void)
{
    printf("\n Введите фамилию курсанта=>");
    scanf("%s", &key);
}

/* ================================================= */
/* ПОКАЗ ДАННЫХ УЗЛА НА ЭКРАНЕ */
void Scrn_El(Rec * E)
{
    printf("\n Фамилия => %s", E->fam);
    printf("\n Mark1 => %d", E->mark1);
    printf("\n Mark2 => %d", E->mark2);
    printf("\n Mark3 => %d", E->mark3);
    printf("\n Mark4 => %d", E->mark4);
    Wait_Entr();
}

/* =============================================== */
/* ВЫВОД ДАННЫХ УЗЛА НА ЭКРАН */
int Show_El(void)
{
    In_fam();			/* Ввод фамилии студента */
    if (Loc_Node(key, T, &RAB) == 0)
        Scrn_El(RAB);
    else
    {
        printf("\n Студент %s не найден", key);
        Wait_Entr();
        return 1;
    }
    return 0;
}

/* ================================================== */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void Lpreorder(Rec * T)
{
    if (T != 0)
    {
        p(T);
        Lpreorder(T->LPTR);
        Lpreorder(T->RPTR);
    }
}

/* =================================================== */
/* СОЗДАНИЕ СПИСКА СТУДЕНТОВ С ТРЕМЯ И БОЛЕЕ ДВОЙКАМИ */
void Find_dwo(Rec * T)
{
    if (T != 0)
    {
        sum = 0;
        if (T->mark1 == 2)
            sum++;
        if (T->mark2 == 2)
            sum++;
        if (T->mark3 == 2)
            sum++;
        if (T->mark4 == 2)
            sum++;
        if (sum > 2)
        {
            ndwo++;
            *dwo[ndwo - 1] = T->fam;
        }
        Find_dwo(T->LPTR);
        Find_dwo(T->RPTR);
    }
}

/* ============================================= */
/* УДАЛЕНИЕ ДВОИЧНИКОВ */
void Del_dwo(void)
{
    char fam[12];
    for (i = 0; i < ndwo; i++)
    {
        printf("\n Исключается %s ", *dwo[i]);
        Del_Node(*dwo[i], &T);
    }
    printf("\n После исключения остались:");
    Lpreorder(T);
    getchar();
}

/* ================================================ */
/* УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА ПОИСКА -  рекурсия   */
int Del_Node(char *key, Rec ** T)
{
    Rec *K, *t;
    t = *T;
    if (*T == 0)
    {
        printf("   Ключ %s не найден", key);
        Wait_Entr();
        return 1;
    }
    if (strcmp(key, t->fam) < 0)	/* Ищем заданный узел */
        Del_Node(key, &t->LPTR);
    else if (strcmp(key, t->fam) > 0)
        Del_Node(key, &t->RPTR);
    else
    {
        K = *T;			/* Узел найден  */
        if (K->RPTR == 0)  	/* Имеет только левую ветвь */
        {
            t = *T;
            *T = K->LPTR;
            free(t);
        }
        else if (K->LPTR == 0)  	/* Имеет только правую ветвь */
        {
            t = *T;
            *T = K->RPTR;
            free(t);
        }
        else			/* Имеет обе ветви  */
            Del1(&K->LPTR, &K);	/* Идем по левой ветви */
    }
    return 0;
}

/* ========================================================== */
/* ВСПОМОГАТЕЛЬНАЯ ДЛЯ УДАЛЕНИЯ ИЗ ДЕРЕВА ПОИСКА - рекурсия   */
void Del1(Rec ** R, Rec ** K)
{
    Rec *r, *kl, *Lp, *Rp;
    r = *R;
    kl = *K;
    if (r->RPTR != 0)		/* Теперь спускаемся по правым ветвям до конца */
        Del1(&r->RPTR, &kl);
    else  			/* Удаляемый узел заменяем на самый нижний правый */
    {

        Lp = kl->LPTR;
        Rp = kl->RPTR;
        *kl = *r;
        kl->LPTR = Lp;
        kl->RPTR = Rp;
        *K = *R;
        *R = r->LPTR;
        free(r);
    }
}

/* *************************************************************** */
