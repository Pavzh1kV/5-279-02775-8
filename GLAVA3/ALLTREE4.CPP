/* РАБОТА С ПРОСТЫМ И  БИНАРНЫМ ДЕРЕВЬЯМИ ПОИСКА */
/* 14.01.2003. Хусаинов Б.С.  c:\bc\xbs\tree\alltree4.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define n 21
typedef struct RECORD  		/* структура узла дерева */
{
    int DATA;			/* ключ+даные, здесь только ключ */
    RECORD *LPTR, *RPTR;	/* левый и правый указатели */
    int N;			/* счетчик узлов дерева (поддерева) */
    int bal;			/* признак сбалансированности дерева */
} OO;
typedef RECORD *EL;
#include "INCL_QUE.CPP"
#include "incl_stc.c"
OO *I, *S, *AV, *R, *T, *E;
int ndi = 0;
int i;
int a[n] =
{
    11, 9, 7, 8, 15, 19, 20, 21, 2, 3, 1, 6, 4, 5, 13, 14, 10, 12, 17,
    16,
    18
};

/*int a[n]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};*/
/*int a[n]={21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};*/
/*int a[n]={6,17,20,16,12,21,9,3,22,4,19,14,13,1,5,2,8,18,7,10,15}; */
RECORD *tree(int k, int d[]);	/* идеально сбалансир. */
void preorder(RECORD *);	/* нисходящий обход */
void preorder_nr(RECORD *);	/* то же, нерекурсивн. */
void postorder(RECORD *);	/* восходящий обход */
void inorder(RECORD *);		/* смешанный обход */
void lvlorder(RECORD *);	/* обход по уровням */
void p(RECORD *);		/* обработка узла */
void insertS(int key, RECORD ** T);	/* в дерево поиска */
int insertAV(int key, RECORD ** T, int *h);	/* в АВЛ-дерево */
int loc(int key, RECORD * T, RECORD ** EL);	/* поиск эл-та */
void del_el_AV(int key, RECORD ** t, int *h);	/* из АВЛ */
void balanceL(RECORD ** t, int *h);	/* АВЛ */
void balanceR(RECORD ** t, int *h);	/* АВЛ */
void delbal(RECORD ** t, RECORD ** q, int *h);	/* АВЛ */
int Rdel_elS(int key, RECORD ** T);	/* из дерева поиска */
void Rdel(RECORD ** T, RECORD ** q);	/* из дерева поиска */
void rotR(RECORD **);		/* ротация вправо */
void rotL(RECORD **);		/* ротация влево */
void insertT(RECORD **, int);	/* вставка в корень */
void insertR(RECORD **, int);	/* вставка в рандомиз. */
int count(RECORD *);		/* счетчик в узел */
void preordC(RECORD *);		/* счетчики в дерево */
void preordN(RECORD *);		/* обход с печатью счетчиков */
/* ==================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
int main()
{
    setlocale(LC_ALL,"Russian");
    int h = 0;
    int ii, r;
    printf
    ("\n\n\n Работа с бинарными деревьями, ");
    printf("\n    содержащими %d элементов", n);
    /* Массив значений данных можно вводить по запросу: */
    /*  int j;
       for (j=0; j<n; j++)
       {printf("Введите %d -й элемент дерева",j);
       scanf("%d",a[j]); */
    printf("\n Исходный массив ключей \n");
    for (i = 0; i < n; i++)
        printf(" %4d", a[i]);
    getchar();
    printf
    ("\n\n Идеально сбалансированное дерево");
    I = tree(n, a);		/* Создание дерева */
    printf("\n  Нисходящий обход дерева\n");
    preorder(I);
    printf("\n Восходящий обход дерева\n");
    postorder(I);
    printf("\n Смешанный обход дерева\n");
    inorder(I);
    getchar();

    printf
    ("\n\nСоздадим бинарные  деревья поиска ");
    for (i = 0; i < n; i++)
    {
        insertS(a[i], &S);
        insertAV(a[i], &AV, &h);
        /*         printf("\n"); *//* процесс формирования АВЛ-дерева */
        /*	 preorder(AV);*/
        insertR(&R, a[i]);
        preordC(R);		/* включение счетчиков в рандом. дерево */
        printf("\n");		/* процесс форм-ния рандомиз. дерева */
        preordN(R);
        getchar();
    }
    printf
    ("\n Нисходящий обход дерева поиска\n");
    preorder(S);
    printf
    ("\nНисходящий обход дерева поиска - нерекурс. функция\n");
    preorder_nr(S);
    printf
    ("\nНисходящий обход (АВЛ) - нерекурсивная функция\n");
    preorder_nr(AV);
    printf
    ("\nНисходящий обход (ранд.) - нерекурсивная функция\n");
    preorder_nr(R);
    printf("\n Обход по уровням:");
    lvlorder(S);
    printf("\n Нисходящий обход АВЛ-дерева:\n");
    preorder(AV);
    printf
    ("\n Нисходящий обход дерева с вставкой в корень:\n");
    preorder(T);
    printf
    ("\n Нисходящий обход рандомизированного дерева:\n");
    preordN(R);
    getchar();
    printf
    ("\n Вставим в корень дерева поиска элемент 11");
    insertT(&S, 11);
    printf
    ("\n Нисходящий обход дерева после вставки\n");
    preorder(S);
    printf
    ("\n Вставим в корень рандом.дерева  элемент 11");
    insertT(&R, 11);
    printf
    ("\n Нисходящий обход дерева после вставки\n");
    preorder(R);
    preordC(S);			/* вставка счетчиков в дерево поиска */
    printf
    ("\n Нисход. обход после вставки счетчиков\n");
    preordN(S);
    printf
    ("\n В АВЛ-дерево включим элементы 45,21,39");
    insertAV(45, &AV, &h);
    insertAV(21, &AV, &h);
    insertAV(39, &AV, &h);
    printf("\n Нисходящий обход дерева \n");
    preorder(AV);
    printf
    ("\n Удалим из АВЛ-дерева элементы с 12 по 24");
    for (ii = 12; ii < 25; ii++)
    {
        h = 0;
        del_el_AV(ii, &AV, &h);
        printf("\nОбход после  удаления key=%d\n", ii);
        preorder(AV);
        getchar();
    }
    printf
    ("\n Поиск и удаление элементов в дереве ");
    printf
    ("\n поиска с случайным выбором ключей\n");
    for (i = 1; i < 11; i++)
    {
        ii = rand() % 25;
        r = loc(ii, S, &E);
        if (r == 0)
            printf("\n Ключ %d найден", E->DATA);
        else
            printf("\n Ключ %d не найден", ii);
        r = Rdel_elS(ii, &S);
        if (r == 0)
            printf("\n Элемент %d удален", ii);
        else
            printf("\n Элемент %d  не найден", ii);
        printf("\n");
        preorder(S);
        getchar();
    }
    getchar();
    return 0;
}

/* ======================================================= */
/*  ПОСТРОЕНИЕ БИНАРНОГО ИДЕАЛЬНО СБАЛАНСИРОВАННОГО ДЕРЕВА */
RECORD *tree(int k, int *d)
{
    RECORD *newnode;
    int nl, nr;
    if (k == 0)
        newnode = 0;
    else
    {
        nl = k / 2;
        nr = k - nl - 1;
        newnode = (RECORD *) malloc(sizeof(RECORD));
        newnode->DATA = d[ndi++];
        newnode->LPTR = tree(nl, d);
        newnode->RPTR = tree(nr, d);
    }
    return newnode;
}

/* ================================================== */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void preorder(RECORD * T)
{
    if (T != 0)
    {
        p(T);			/* обработка данных в узле */
        preorder(T->LPTR);
        preorder(T->RPTR);
    }
}

/* =================================================== */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА  С ПЕЧАТЬЮ ЧИСЛА УЗЛОВ
	 В ПОДДЕРЕВЬЯХ*/
void preordN(RECORD * T)
{
    if (T != 0)
    {
        printf(" k=%d N=%d", T->DATA, T->N);
        preordN(T->LPTR);
        preordN(T->RPTR);
    }
}

/* ==================================================== */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА С ВКЛЮЧЕНИЕМ ЧИСЛА УЗЛОВ
	 В ПОДДЕРЕВЕ*/
void preordC(RECORD * T)
{
    if (T != 0)
    {
        T->N = count(T);	/* включение счетчика в узел */
        preordC(T->LPTR);
        preordC(T->RPTR);
    }
}

/* ======================================================== */
/* СМЕШАННЫЙ ОБХОД ДЕРЕВА */
void inorder(RECORD * T)
{
    if (T != 0)
    {
        inorder(T->LPTR);
        p(T);
        inorder(T->RPTR);
    }
}

/* ======================================================== */
/* ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void postorder(RECORD * T)
{
    if (T != 0)
    {
        inorder(T->LPTR);
        inorder(T->RPTR);
        p(T);
    }
}

/* ======================================================== */
/* ОБРАБОТКА КОРНЯ ДЕРЕВА */
void p(RECORD * T)
{
    printf(" %d ", T->DATA);
}

/* ************************************* */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ДЕРЕВО ПОИСКА */
/* С ВКЛЮЧЕНИЕМ СЧЕТЧИКОВ В УЗЛЫ      */
void insertS(int key, RECORD ** T)
{
    RECORD *newnode, *t;
    t = *T;
    static int s;
    if (*T == 0)
    {
        newnode = (RECORD *) malloc(sizeof(RECORD));
        newnode->DATA = key;
        newnode->LPTR = 0;
        newnode->RPTR = 0;
        newnode->N = 1;		/* счетчик */
        *T = newnode;
    }
    else if (key < (*T)->DATA)
    {
        s = 1;
        insertS(key, &t->LPTR);
        if (s)			/* элемент включен  */
            (*T)->N++;		/* увеличим счетчик */
    }
    else if (key > t->DATA)
    {
        s = 1;
        insertS(key, &t->RPTR);
        if (s)
            (*T)->N++;
    }
    else
    {
        p(t);
        s = 0;
    }				/* повторяющийся ключ */
}

/* ==================================================== */
/*  ПОИСК ЭЛЕМЕНТА ПО ЗАДАННОМУ КЛЮЧУ В ДЕРЕВЕ ПОИСКА */
/* в EL возвращается указатель найденного элемента */
/* код возврата=0, если найден, =1, если не найден */
int loc(int key, RECORD * T, RECORD ** EL)
{
    while (1)
    {
        if (T == 0)
            return 1;
        else if (key < T->DATA)
            T = T->LPTR;
        else if (key > T->DATA)
            T = T->RPTR;
        else
        {
            *EL = T;
            return 0;
        }
    }
}

/* ================================================== */
/* ВКЛЮЧЕНИЕ В СБАЛАНСИРОВАННОЕ ДЕРЕВО ПОИСКА */
int insertAV(int key, RECORD ** t, int *h)
{
    RECORD *t1, *t2, *T;
    int ret = 0;
    T = *t;
    if (T == NULL)  		/* ключа нет в дереве */
    {
        T = (RECORD *) calloc(1, sizeof(RECORD));
        T->DATA = key;
        T->bal = 0;
        *h = 1;
        T->LPTR = T->RPTR = NULL;
    }
    else /* поиск ключа в дереве */ if (key < T->DATA)
    {
        insertAV(key, &T->LPTR, h);
        if (*h)
        {
            switch (T->bal)
            {
            case 1:
                T->bal = 0;
                *h = 0;
                break;
            case 0:
                T->bal = -1;
                break;
            case -1:		/* балансировка */
            {
                t1 = T->LPTR;
                if (t1->bal == -1)  	/* однократный LL-поворот */
                {
                    T->LPTR = t1->RPTR;
                    t1->RPTR = T;
                    T->bal = 0;
                    T = t1;
                }
                else  	/* двукратный LR-поворот */
                {

                    t2 = t1->RPTR;
                    t1->RPTR = t2->LPTR;
                    t2->LPTR = t1;
                    T->LPTR = t2->RPTR;
                    t2->RPTR = T;
                    if (t2->bal == -1)
                        T->bal = 1;
                    else
                        T->bal = 0;
                    if (t2->bal == 1)
                        t1->bal = -1;
                    else
                        t1->bal = 0;
                    T = t2;
                }
                T->bal = 0;
                *h = 0;
            }
            }
        }
    }
    else if (key > T->DATA)
    {
        insertAV(key, &T->RPTR, h);
        if (*h == 1)
            switch (T->bal)
            {
            case -1:
                T->bal = 0;
                *h = 0;
                break;
            case 0:
                T->bal = 1;
                break;
            case 1:		/* балансировка */
            {
                t1 = T->RPTR;
                if (t1->bal == 1)  	/* однократный RR-поворот */
                {
                    T->RPTR = t1->LPTR;
                    t1->LPTR = T;
                    T->bal = 0;
                    T = t1;
                }
                else  	/* двукратный RL-поворот */
                {

                    t2 = t1->LPTR;
                    t1->LPTR = t2->RPTR;
                    t2->RPTR = t1;
                    T->RPTR = t2->LPTR;
                    t2->LPTR = T;
                    if (t2->bal == 1)
                        T->bal = -1;
                    else
                        T->bal = 0;
                    if (t2->bal == -1)
                        t1->bal = 1;
                    else
                        t1->bal = 0;
                    T = t2;
                }
                T->bal = 0;
                *h = 0;
            }
            }
    }
    else
    {
        printf("\n В АВЛ: %d - повторяющийся ключ",
               key);
        ret = -1;
        getchar();
    }

    *t = T;
    return ret;
}

/* =================================================== */
/* УДАЛЕНИЕ ЭЛЕМЕТА ИЗ СБАЛАНСИРОВАННОГО ДЕРЕВА ПОИСКА */
void del_el_AV(int key, RECORD ** T, int *h)
{
    RECORD *t, *K;
    t = *T;
    if (*T == NULL)
    {
        printf("\n Ключ %d не найден", key);
        *h = 0;
    }
    else if (key < t->DATA)
    {
        del_el_AV(key, &t->LPTR, h);
        if (*h)
            balanceL(&t, h);
    }
    else if (key > t->DATA)
    {
        del_el_AV(key, &t->RPTR, h);
        if (*h)
            balanceR(&t, h);
    }
    else  			/* удаление */
    {

        K = t;			/* узел найден */
        if (K->RPTR == NULL)  	/* имеет только левую ветвь */
        {
            t = K->LPTR;
            free(K);
            *h = 1;
        }
        else if (K->LPTR == NULL)  	/* имеет только правую ветвь */
        {
            t = K->RPTR;
            free(K);
            *h = 1;
        }
        else
        {
            delbal(&K->LPTR, &K, h);
            if (*h)
                balanceL(&t, h);
        }
    }
    *T = t;
}

/* =============================================== */
void delbal(RECORD ** R, RECORD ** K, int *h)
{
    RECORD *r, *k;
    r = *R;
    k = *K;
    if (r->RPTR != NULL)  	/* спускаемся по правым ветвям до конца */
    {
        delbal(&r->RPTR, &k, h);
        if (*h)
            balanceR(R, h);
    }
    else
    {
        k->DATA = r->DATA;
        *R = r->LPTR;
        free(r);
        *h = 1;
    }
}

/* ================================================== */
/* БАЛАНСИРОВКА, h=1, левая ветвь короче */
void balanceL(RECORD ** t, int *h)
{
    RECORD *t1, *t2, *T;
    int b1, b2;
    T = *t;
    switch (T->bal)
    {
    case -1:
        T->bal = 0;
        break;
    case 0:
        T->bal = 1;
        *h = 0;
        break;
    case 1:			/* балансировка */
    {
        t1 = T->RPTR;
        b1 = t1->bal;
        if (b1 >= 0)  	/* однократный RR-поворот */
        {
            T->RPTR = t1->LPTR;
            t1->LPTR = T;
            if (b1 == 0)
            {
                T->bal = 1;
                t1->bal = -1;
                *h = 0;
            }
            else
            {
                T->bal = 0;
                t1->bal = 0;
            }
            T = t1;
        }
        else  		/* двукратный RL-поворот */
        {

            t2 = t1->LPTR;
            b2 = t2->bal;
            t1->LPTR = t2->RPTR;
            t2->RPTR = t1;
            T->RPTR = t2->LPTR;
            t2->LPTR = T;
            if (b2 == 1)
                T->bal = -1;
            else
                T->bal = 0;
            if (b2 == -1)
                t1->bal = 1;
            else
                t1->bal = 0;
            T = t2;
            t2->bal = 0;
        }
    }
    }
    *t = T;
}

/* ================================================== */
/* БАЛАНСИРОВКА, h=1, правая ветвь короче */
void balanceR(RECORD ** t, int *h)
{
    RECORD *t1, *t2, *T;
    int b1, b2;
    T = *t;
    switch (T->bal)
    {
    case 1:
        T->bal = 0;
        break;
    case 0:
        T->bal = -1;
        *h = 0;
        break;
    case -1:			/* балансировка */
    {
        t1 = T->LPTR;
        b1 = t1->bal;
        if (b1 <= 0)  	/* однократный LL-поворот */
        {
            T->LPTR = t1->RPTR;
            t1->RPTR = T;
            if (b1 == 0)
            {
                T->bal = -1;
                t1->bal = 1;
                *h = 0;
            }
            else
            {
                T->bal = 0;
                t1->bal = 0;
            }
            T = t1;
        }
        else  		/* двукратный LR-поворот */
        {

            t2 = t1->RPTR;
            b2 = t2->bal;
            t1->RPTR = t2->LPTR;
            t2->LPTR = t1;
            T->LPTR = t2->RPTR;
            t2->RPTR = T;
            if (b2 == -1)
                T->bal = 1;
            else
                T->bal = 0;
            if (b2 == 1)
                t1->bal = -1;
            else
                t1->bal = 0;
            T = t2;
            t2->bal = 0;
        }
    }
    }
    *t = T;
}

/* ================================================= */
/* УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА ПОИСКА - рекурсия */
int Rdel_elS(int key, RECORD ** T)
{
    RECORD *K, *t;
    t = *T;
    static int s;
    if (*T == 0)  		/*printf("\n Ключ %d не найден",key); */
    {
        s = 0;
        return 1;
    }
    if (key < t->DATA)  	/* Ищем заданный узел */
    {
        s = 1;
        Rdel_elS(key, &t->LPTR);
    }
    else if (key > t->DATA)
    {
        s = 1;
        Rdel_elS(key, &t->RPTR);
    }
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
            Rdel(&K->LPTR, &K);	/* Идем по левой ветви */
    }
    preordC(*T);		/* Восстановление счетчиков */
    return !s;
}

/* ========================================================== */
/* ВСПОМОГАТЕЛЬНАЯ ДЛЯ УДАЛЕНИЯ ИЗ ДЕРЕВА ПОИСКА - рекурсия   */
void Rdel(RECORD ** R, RECORD ** K)
{
    RECORD *r, *k;
    r = *R;
    k = *K;
    if (r->RPTR != 0)		/* спуск по правым ветвям до конца */
        Rdel(&r->RPTR, &k);
    else  			/* Удаляемый узел заменяем на самый нижний правый */
    {

        k->DATA = r->DATA;
        *K = *R;
        *R = r->LPTR;
        free(r);
    }
}

/* ========================================================= */
/* РОТАЦИЯ ВПРАВО                                            */
void rotR(RECORD ** h)
{
    RECORD *x;
    x = (*h)->LPTR;
    (*h)->LPTR = x->RPTR;
    x->RPTR = *h;
    *h = x;
}

/* ======================================== */
/* РОТАЦИЯ ВЛЕВО                            */
void rotL(RECORD ** h)
{
    RECORD *x;
    x = (*h)->RPTR;
    (*h)->RPTR = x->LPTR;
    x->LPTR = *h;
    *h = x;
}

/* ======================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В КОРЕНЬ ДЕРЕВА       */
void insertT(RECORD ** T, int x)
{
    if (*T == NULL)
    {
        *T = (RECORD *) calloc(1, sizeof(RECORD));
        (*T)->DATA = x;
        (*T)->LPTR = (*T)->RPTR = NULL;
        (*T)->N = 0;
        return;
    }
    if (x < (*T)->DATA)
    {
        insertT(&(*T)->LPTR, x);
        rotR(T);
    }
    else
    {
        insertT(&(*T)->RPTR, x);
        rotL(T);
    }
    /*	preordC(*T);*/
}

/* =============================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В РАНДОМИЗИРОВАННОЕ ДЕРЕВО   */
/* С ВКЛЮЧЕНИЕМ СЧЕТЧИКОВ В УЗЛЫ ДЕРЕВА            */
void insertR(RECORD ** T, int x)
{
    int r, R;
    if (*T == NULL)
    {
        *T = (RECORD *) calloc(1, sizeof(RECORD));
        (*T)->DATA = x;
        (*T)->LPTR = (*T)->RPTR = NULL;
        /*(*T)->N++; */ return;
    }
    r = rand();
    R = RAND_MAX / ((*T)->N);
    if (r < R)
    {
        insertT(T, x);
        return;
    }
    if (x < (*T)->DATA)
    {
        insertR(&(*T)->LPTR, x);	/* (*T)->N++; */
    }
    else
    {
        insertR(&(*T)->RPTR, x);	/* (*T)->N++; */
    }
}

/* =============================================== */
/* ПОДСЧЕТ ЧИСЛА УЗЛОВ В ДЕРЕВЕ                    */
int count(RECORD * T)
{
    if (T == NULL)
        return NULL;
    return (count(T->LPTR) + count(T->RPTR) + 1);
}

/* ============================================== */
/* ОБХОД БИНАРНОГО ДЕРЕВА ПО УРОВНЯМ */
void lvlorder(RECORD * T)
{
    static QUE q;
    EL el;
    if (T == NULL)
        return;			/* дерево пустое */
    Crt_que(&q);
    Add_el(&q, T);
    while (Empty_que(&q))  	/* пока очередь не пуста */
    {
        Extr_el(&q, &el);
        p(el);
        if (el->LPTR)
            Add_el(&q, el->LPTR);
        if (el->RPTR)
            Add_el(&q, el->RPTR);
    }
    Destroy_que(&q);
}

/* =============================================== */
/* ЛЕВЫЙ НИСХОДЯЩИЙ ОБХОД - нерекурсивная функция  */
void preorder_nr(RECORD * T)
{
    static STC s;
    EL el;
    if (T == NULL)
        return;			/* дерево пустое */
    Crt_stc(&s);
    Push_el(&s, T);
    while (!(s.uv < 0))
    {
        Pop_el(&s, &el);
        p(el);
        if (el->RPTR)
            Push_el(&s, el->RPTR);
        if (el->LPTR)
            Push_el(&s, el->LPTR);
    }
    Destroy_stc(&s);
}

/* *********************************************** */
