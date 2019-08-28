/* ********************************************************* */
/* РАБОТА С БИНАРНЫМИ ДЕРЕВЬЯМИ - диалоговая программа */
/* \dtree28.c  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define k 21
#define Rec struct r_e
Rec
{
    char Gos[20];
    char Stl[20];
    int Pl, Nas;
    Rec *LPTR, *RPTR;
} El;

Rec *ROOT, *R, *L, *Q, *T, *TA, *TB, *TC, *RAB, *TEK, *PRED, *TT;
char *menu[k][60];
int i, pp, ts = 1;
char key[20];
void Crt_Tr_Srch1(void);
int Srch_Insrt1(Rec E, Rec ** T);
void Lpreorder(Rec * T);
void Lpostorder(Rec * T);
void Linorder(Rec * T);
void Rpreorder(Rec * T);
void Rpostorder(Rec * T);
void Rinorder(Rec * T);
void p(Rec * T);
int Loc(char *key, Rec * T, Rec ** EL);
int Delete(char *key, Rec ** T);
void Del(Rec ** T);
int Del_Node(char *key, Rec ** T);
void Del1(Rec ** R, Rec ** K);
int Uni_Trees(Rec * A, Rec * B, Rec ** C);
int Cross_Trees(Rec * A, Rec * B, Rec ** C);
int Dif_Trees(Rec * A, Rec * B, Rec ** C);
int Move_Node(Rec * A, Rec ** B, char *key);
void Select_Tree(void);
Rec *Del_Tree(Rec ** T);
int Main_Menu(void);
void Wait_Entr(void);
void Prnt(void);
void In_Gos(void);
int In_Data(void);
int Show_El(void);
void Scrn_El(Rec * El);
/* ========================================================= */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    pp = 1;
    T = 0;
    RAB = 0;
    TEK = 0;
    PRED = 0;
    TA = T;
    TB = 0;
    TC = 0;
    TT = 0;
    *menu[0] =
        "1. Выбор бинарного дерева поиска";
    *menu[1] =
        "2. Создание бинарного сбалансированного дерева";
    *menu[2] =
        "3. Создание бинарного дерева поиска";
    *menu[3] =
        "4. Левый нисходящий обход дерева";
    *menu[4] =
        "5. Левый восходящий обход дерева";
    *menu[5] = "6. Левый смешанный обход дерева";
    *menu[6] =
        "7. Правый нисходящий обход дерева";
    *menu[7] =
        "8. Правый восходящий обход дерева";
    *menu[8] =
        "9. Правый смешанный обход дерева";
    *menu[9] =
        "10.Включение элемента в дерево поиска";
    *menu[10] =
        "11.Удаление элемента из дерева поиска";
    *menu[11] =
        "12.Вывод данных элемента на экран";
    *menu[12] =
        "13.Перенос элемента из одного дерева в другое";
    *menu[13] = "14.Сохранение дерева в файле";
    *menu[14] =
        "15.Восстановление дерева из файла";
    *menu[15] =
        "16.Объединение двух деревьев поиска как множеств";
    *menu[16] =
        "17.Пересечение двух деревьев поиска как множеств";
    *menu[17] =
        "18.Разность двух деревьв поиска как множеств";
    *menu[18] = "19.Уничтожение дерева";
    *menu[19] = "20.Конец работы";
    *menu[20] = "         Введите номер строки";
    system("clear");
    printf("    Работа с бинарными деревьями \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с деревом\n");
    Wait_Entr();
    return 0;
}

/* ======================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    int ns, m;
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
    switch (ts)
    {
    case 1:
        TA = T;
        break;
    case 2:
        TB = T;
        break;
    case 3:
        TC = T;
    }
    switch (ns)
    {
    case 1:
        Select_Tree();
        break;
    case 2:			/*T = Create_Tree(n,a); */
        Prnt();
        break;
    case 3:
        Crt_Tr_Srch1();
        break;
    case 4:
        Lpreorder(T);
        Wait_Entr();
        break;
    case 5:
        Lpostorder(T);
        Wait_Entr();
        break;
    case 6:
        Linorder(T);
        Wait_Entr();
        break;
    case 7:			/* Rpreorder(T); */
        Prnt();
        break;
    case 8:			/* Rpostorder(T); */
        Prnt();
        break;
    case 9:			/* Rinorder(T);     */
        Prnt();
        break;
    case 10:
        In_Data();
        Srch_Insrt1(El, &T);
        break;
    case 11:
        In_Gos();
        Del_Node(key, &T);
        break;
    case 12:
        Show_El();
        break;
    case 13:			/*Move_Node(TA,&TB,key); */
        Prnt();
        break;
    case 14:			/*Out_File(T); */
        Prnt();
        break;
    case 15:			/*In_File(&T);   */
        Prnt();
        break;
    case 16:			/*Uni_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 17:			/*Cross_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 18:			/*Dif_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 19:
        Del_Tree(&T);
        getchar();
        break;
    case 20:
        pp = 0;
    }
    return 0;
}

/* ========================================================== */
/* ВЫБОР ДЕРЕВА ПОИСКА */
void Select_Tree(void)
{
    char ns;
    while (1)
    {
        fflush(NULL);
        printf("  Введите номер дерева (1,2,3)=>");
        ns = getchar();
        if (ns < '1' || ns > '3')
        {
            printf("Ошибка в номере, повторно \n");
            continue;
        }
        break;
    }
    switch (ts)
    {
    case 1:
        TA = T;
        break;
    case 2:
        TB = T;
        break;
    case 3:
        TC = T;
        break;
    }
    switch (ns)
    {
    case '1':
        ts = 1;
        T = TA;
        break;
    case '2':
        ts = 2;
        T = TB;
        break;
    case '3':
        ts = 3;
        T = TC;
    }
}

/* ================================================ */
/* ПОСТРОЕНИЕ ДЕРЕВА ПОИСКА О ГОСУДАРСТВАХ */
void Crt_Tr_Srch1(void)
{
    fflush(NULL);
    printf
    ("\n Cоздание дерева с данными о государствах\n");
    while (1)
    {
        if (In_Data() != 0)
        {
            printf("\n Ввод завершен");
            Wait_Entr();
            break;
        }
        else
            Srch_Insrt1(El, &T);
    }
}

/* ======================================================= */
/* ВВОД ДАННЫХ ДЛЯ УЗЛА ДЕРЕВА, данные вводятся в диалоге */
int In_Data(void)
{
    fflush(NULL);
    printf
    ("\n Введите данные о государстве или ** для прекращения ввода:");
    printf("\n Государство=>");
    scanf("%s", El.Gos);
    if (strcmp(El.Gos, "**") == 0)
        return -1;
    else
    {
        printf(" Столица=>");
        scanf("%s", &El.Stl);
        printf(" Площадь государства=>");
        scanf("%d", &El.Pl);
        printf(" Численность населения=>");
        scanf("%d", &El.Nas);
        return 0;
    }
}

/* ========================================================== */
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

/* =========================================================== */
/* ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void Lpostorder(Rec * T)
{
    if (T != 0)
    {
        Lpostorder(T->LPTR);
        Lpostorder(T->RPTR);
        p(T);
    }
}

/* ============================================================ */
/* СМЕШАННЫЙ ОБХОД ДЕРЕВА */
void Linorder(Rec * T)
{
    if (T != 0)
    {
        Linorder(T->LPTR);
        p(T);
        Linorder(T->RPTR);
    }
}

/* ============================================================ */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ДЕРЕВО ПОИСКА */
/* E -переменная типа Rec с данными включаемого узла.
	TT - указатель корня дерева */
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
    else if (strcmp(E.Gos, t->Gos) < 0)
        Srch_Insrt1(E, &t->LPTR);
    else if (strcmp(E.Gos, t->Gos) > 0)
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

/* ====================================================== */
/*  ПОИСК ЭЛЕМЕНТА ПО ЗАДАННОМУ КЛЮЧУ В ДЕРЕВЕ ПОИСКА */
/* в EL возвращается указатель найденного элемента */
/* код возврата = 0, если элемент найден, =1, если не найден */
int Loc_Node(char *key, Rec * T, Rec ** EL)
{
    while (1)
    {
        if (T == 0)
            return 1;
        else if (strcmp(key, T->Gos) < 0)
            T = T->LPTR;
        else if (strcmp(key, T->Gos) > 0)
            T = T->RPTR;
        else
        {
            *EL = T;
            return 0;
        }
    }
}

/* ========================================================= */
/* УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА ПОИСКА, нерекурсивный вариант */
/* Работающий вариант, но здесь не используется */
int Delete(char *key, Rec ** t)
{
    int f = 0;
    int s = 0;
    Rec *P, *Q, *Lp, *Rp, *T;
    T = *t;
    if (T == 0)
    {
        printf("Дерево пустое");
        return 1;
    }
    while (T != 0 && f == 0)
    {
        if (strcmp(key, T->Gos) < 0)
        {
            s = 1;
            P = T;
            T = T->LPTR;
        }
        else if (strcmp(key, T->Gos) > 0)
        {
            s = -1;
            P = T;
            T = T->RPTR;
        }
        else
            f = 1;
    }
    /* ключ не найден */
    if (T == 0)
    {
        printf("\n ключ %d не найден", key);
        return 1;
    }
    /* удаляется элемент без потомков - лист */
    if (T->LPTR == 0 && T->RPTR == 0)
    {
        if (T == *t)  		/* в дереве только один элемент - корень дерева */
        {
            free(T);
            *t = NULL;
            return 1;
        }
        else
        {
            if (s == 1)
                P->LPTR = 0;
            else
                P->RPTR = 0;
        }
        free(T);
        return 0;
    }
    /* удаляется элемент с двумя потомками */
    if (T->LPTR != 0 && T->RPTR != 0)
    {
        Q = T->LPTR;		/* по левой ветви на уровень ниже */
        if (Q->RPTR == 0)  	/* если у него нет правого поддерева */
        {
            Rp = T->RPTR;	/* то он заменяет удаляемый узел */
            *T = *Q;
            T->RPTR = Rp;
        }
        else  		/* правое поддерево есть, идем */
        {

            while (Q->RPTR != 0)  	/* по нему до конца правой ветви */
            {
                P = Q;
                Q = Q->RPTR;
            }
            Lp = T->LPTR;
            Rp = T->RPTR;	/* удаляемый элемент заменяем */
            *T = *Q;
            T->RPTR = Rp;
            T->LPTR = Lp;	/* на конечный правый, */
            P->RPTR = Q->LPTR;	/* сохраняя указатели удаляемого */
        }
        free(Q);
        Q = 0;
        return 0;
    }
    /* удаляется элемент с одним потомком */
    if (T->LPTR != 0)
    {
        if (s == 1)
            P->LPTR = T->LPTR;
        else if (s == -1)
            P->RPTR = T->LPTR;
        else
        {
            Q = T->LPTR;
            *T = *Q;
            free(Q);
            return 0;
        }
    }
    else
    {
        if (s == 1)
            P->LPTR = T->RPTR;
        else if (s == -1)
            P->RPTR = T->RPTR;
        else
        {
            Q = T->RPTR;
            *T = *Q;
            free(Q);
            return 0;
        }
    }
    free(T);
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

/* ====================================================== */
/* УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА ПОИСКА - рекурсивный вариант */
int Del_Node(char *key, Rec ** T)
{
    Rec *K, *t;
    t = *T;
    /* printf("\n Введите название удаляемого государства=>");
     scanf("%s",&key);   printf("\n %s",t->Gos); Wait_Entr();*/
    if (*T == 0)
    {
        printf("   Ключ %s не найден", key);
        Wait_Entr();
        return 1;
    }
    if (strcmp(key, t->Gos) < 0)	/* Ищем заданный узел */
        Del_Node(key, &t->LPTR);
    else if (strcmp(key, t->Gos) > 0)
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

/* ======================================================== */
/* ВСПОМОГАТЕЛЬНАЯ ДЛЯ УДАЛЕНИЯ ИЗ ДЕРЕВА ПОИСКА - рекурсия */
void Del1(Rec ** R, Rec ** K)
{
    Rec *r, *kl, *Lp, *Rp;
    r = *R;
    kl = *K;
    if (r->RPTR != 0)		/* спускаемся по правым ветвям до конца */
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

/* ======================================================== */
/* НА ПЕРИОД РАЗРАБОТКИ ФУНКЦИЙ */
void Prnt(void)
{
    printf("\nНа стадии разработки");
    Wait_Entr();
}

/* ======================================================== */
/* УНИЧТОЖЕНИЕ БИНАРНОГО ДЕРЕВА  */
Rec *Del_Tree(Rec ** t)
{
    Rec *T;
    T = *t;
    if (T != 0)
    {
        Del_Tree(&(T->LPTR));
        Del_Tree(&(T->RPTR));
        printf(" T1=%p", *t);
        free(*t);
        printf(" T2=%p", *t);
        *t = NULL;
        getchar();
    }
    return T;
}

/* ========================================================= */
/* ОБРАБОТКА ДАННЫХ УЗЛА - здесь просто печать */
void p(Rec * T)
{
    printf("\n %s %s %d %d", T->Gos, T->Stl, T->Pl, T->Nas);
}

/* ========================================================= */
void In_Gos(void)
{
    printf("\n Введите название государства=>");
    scanf("%s", &key);
}

/* ========================================================= */
/* ПОКАЗ ДАННЫХ УЗЛА НА ЭКРАНЕ */
void Scrn_El(Rec * E)
{
    printf("\n Государство => %s", E->Gos);
    printf("\n Столица     => %s", E->Stl);
    printf("\n Площадь     => %d", E->Pl);
    printf("\n Численность населения => %d", E->Nas);
    Wait_Entr();
}

/* ========================================================= */
/* ВЫВОД ДАННЫХ ЗАДАННОГО УЗЛА НА ЭКРАН */
int Show_El(void)
{
    In_Gos();			/* Ввод названия государства */
    if (Loc_Node(key, T, &RAB) == 0)
        Scrn_El(RAB);
    else
    {
        printf("\n Государство %s не найдено", key);
        Wait_Entr();
        return 1;
    }
    return 0;
}

/* ********************************************************* */
