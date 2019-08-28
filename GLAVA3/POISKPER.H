/* ******************************************************* */
/* РАБОТА С БИНАРНЫМИ ДЕРЕВЬЯМИ ПОИСКА:                    */
/* - простое бинарное дерево поиска;                       */
/* - сбалансированное АВЛ-дерево поиска;                   */
/* - сбалансированное рандомизированное дерево поиска.     */
/* - Ключ элемента - целое число.                          */
/* - Можно проследить за ходом роста дерева при включении  */
/*   элементов и разрушения дерева при удалении элементов. */
/* - В нерекурсивных функциях используются стеки и очереди,*/
/*   для манипулирования ими подключаются файлы включения  */
/*  incl_stc.c и incl_que.cpp                              */
/*  11.01.04. Хусаинов Б.С.  c:\bc\xbs\tree\poiskper.h    */
/* ======================================================= */
typedef struct  REC   /* структура узла бинарного дерева   */
{
    REC  *LPTR,*RPTR;  /* левый и правый указатели */
    DT DATA ;          /* ключ+данные -тип DT определяется */
    int N;             /* счетчик узлов дерева (поддерева)*/
    int bal;           /* признак балансированности АВЛ-дерева*/
};
typedef REC* EL;
#include "INCL_QUE.CPP" /* очереди */
#include "incl_stc.c"   /* стеки   */

void preorder(REC *);     /* нисходящий обход */
void preorder_nr(REC *);  /* то же, нерекурсивн. */
void postorder(REC *);    /* восходящий обход */
void inorder(REC *);      /* смешанный обход */
void lvlorder(REC *);     /* обход по уровням */
void p(REC* T);        	/* обработка узла */
void px(REC* T,void(*f)(DT)); /* расширенная обработка*/
int  loc(DT key,REC *T,REC **EL);     /* поиск эл-та*/
void insertS(DT key,REC **T);   /* в дерево поиска */
int  Rdel_elS(DT key,REC **T);  /* из дерева поиска */
void Rdel(REC **T,REC **q);      /* из дерева поиска */
int  insertAV(DT key,REC **T,int *h);  /* в АВЛ-дерево*/
void del_el_AV(DT key,REC **t,int *h); /* из АВЛ */
void balanceL(REC**t,int *h);           /* АВЛ */
void balanceR(REC **t,int *h);          /* АВЛ */
void delbal(REC **t,REC **q,int *h);    /* АВЛ */
void rotR(REC**);                /* ротация вправо */
void rotL(REC**);                /* ротация влево */
void insertT(REC**,int);         /* вставка в корень */
void insertR(REC**,int);         /* вставка в рандомиз.*/
int  count(REC*);                /* счетчик в узел */
void preordC(REC*);              /* счетчики в дерево */
void preordN(REC*);    /* обход с печатью счетчиков */
int  compr(int a,int b);
int  compr(char*,char*);
int  compr(float a,float b);
/* ======================================================== */
/* ОБРАБОТКА УЗЛА ДЕРЕВА */
void p(REC* T)
{
    cout<<" k= "<<T->DATA.Skey;
}
/* ======================================================== */
/* РАСШИРЕННАЯ ОБРАБОТКА УЗЛА */
void px(REC *T,void(*f)(DT t))
{
    f(T->DATA);
}
/* ======================================================== */
/* НИСХОДЯЩИЙ ОБХОД С РАСШИРЕННОЙ ОБРАБОТКОЙ УЗЛА */
void preordrx(REC *T,void(*f)(DT *d))
{
    if (T!=NULL)
    {
        f(&T->DATA);
        preordrx(T->LPTR,f);
        preordrx(T->RPTR,f);
    }
}
/* ======================================================= */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void  preorder(REC *T)
{
    if (T!=0)
    {
        p(T); /* обработка данных в узле */
        preorder(T->LPTR);
        preorder(T->RPTR);
    }
}
/* =================================================== */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА  С ПЕЧАТЬЮ КЛЮЧЕЙ И ЧИСЛА  */
/* УЗЛОВ В ПОДДЕРЕВЬЯХ*/
void preordN(REC *T)
{
    if (T!=0)
    {
        cout<<" k= " <<T->DATA.Skey <<" N= "<<T->N;
        preordN(T->LPTR);
        preordN(T->RPTR);
    }
}
/* ==================================================== */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА С ВКЛЮЧЕНИЕМ ЧИСЛА УЗЛОВ
	 В КАЖДОМ ПОДДЕРЕВЕ*/
void preordC(REC *T)
{
    if (T!=0)
    {
        T->N=count(T); /* включение счетчика в узел */
        preordC(T->LPTR);
        preordC(T->RPTR);
    }
}
/* ======================================================== */
/* СМЕШАННЫЙ ОБХОД ДЕРЕВА */
void inorder(REC *T)
{
    if (T!=0)
    {
        inorder(T->LPTR);
        p(T);
        inorder(T->RPTR);
    }
}
/* ======================================================== */
/* ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void postorder(REC *T)
{
    if (T!=0)
    {
        postorder(T->LPTR);
        postorder(T->RPTR);
        p(T);
    }
}
/* ======================================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В ДЕРЕВО ПОИСКА */
/* С ВКЛЮЧЕНИЕМ СЧЕТЧИКОВ В УЗЛЫ      */
void insertS(DT e,REC **T)
{
    REC  *newnode,*t;
    static int s;
    t=*T;
//  cout<<"e= "<<e.Skey; getchar();
    if (*T == 0)
    {
        newnode=(REC *) malloc(sizeof(REC));
        newnode->DATA=e;
        newnode->LPTR=0;
        newnode->RPTR=0;
        newnode->N=1;   /* счетчик */
        *T = newnode;
    }
    else if (compr(e.Skey,(*T)->DATA.Skey)<0)
    {
        s=1;
        insertS(e,&t->LPTR);
        if(s)        /* элемент включен  */
            (*T)->N++; /* увеличим счетчик */
    }
    else if (compr(e.Skey,t->DATA.Skey)>0)
    {
        s=1;
        insertS(e,&t->RPTR);
        if(s)
            (*T)->N++;
    }
    else
    {
        p(t);    /* повторяющийся ключ */
        s=0;
    }
}
/* ==================================================== */
/*  ПОИСК ЭЛЕМЕНТА ПО ЗАДАННОМУ КЛЮЧУ В ДЕРЕВЕ ПОИСКА */
/* в EL возвращается указатель найденного элемента */
/* код возврата=0, если найден, =1, если не найден */
int loc(DT e,REC *T,REC **EL)
{
    while (1)
    {
        if (T == 0)
            return 1;
        else if (compr(e.Skey,T->DATA.Skey)<0)
            T=T->LPTR;
        else if (compr(e.Skey,T->DATA.Skey)>0)
            T=T->RPTR;
        else
        {
            *EL=T;
            return 0;
        }
    }
}
/* ================================================== */
/* ВКЛЮЧЕНИЕ В СБАЛАНСИРОВАННОЕ АВЛ-ДЕРЕВО ПОИСКА */
int insertAV(DT e,REC**t,int *h)
{
    REC *t1,*t2,*T;
    int ret=0;
    T=*t;
    if ( T == NULL)   /* ключа нет в дереве */
    {
        T=(REC*) calloc(1,sizeof(REC));
        T->DATA = e;
        T->bal = 0;
        *h=1;
        T->LPTR = T->RPTR = NULL;
    }
    else   /* поиск ключа в дереве */
        if (compr(e.Skey,T->DATA.Skey)<0)
        {
            insertAV(e,&T->LPTR,h);
            if (*h)
            {
                switch (T->bal)
                {
                case 1:
                    T->bal=0;
                    *h=0;
                    break;
                case 0:
                    T->bal=-1;
                    break;
                case -1:  /* балансировка */
                {
                    t1=T->LPTR;
                    if (t1->bal == -1) /* однократный LL-поворот*/
                    {
                        T->LPTR = t1->RPTR;
                        t1->RPTR = T;
                        T->bal = 0;
                        T = t1;
                    }
                    else  /* двукратный LR-поворот */
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
                    *h =0;
                }
                }
            }
        }
        else if (compr(e.Skey,T->DATA.Skey)>0)
        {
            insertAV(e,&T->RPTR,h);
            if (*h==1)
                switch (T->bal)
                {
                case -1:
                    T->bal=0;
                    *h=0;
                    break;
                case 0:
                    T->bal=1;
                    break;
                case 1:  /* балансировка */
                {
                    t1=T->RPTR;
                    if (t1->bal == 1) /* однократный RR-поворот*/
                    {
                        T->RPTR = t1->LPTR;
                        t1->LPTR = T;
                        T->bal = 0;
                        T = t1;
                    }
                    else  /* двукратный RL-поворот */
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
                    *h =0;
                }
                }
        }
        else
        {
            printf("\n В АВЛ: %d - повторяющийся ключ",e.Skey);
            ret=-1;
            getchar();
        }
    *t = T;
    return ret;
}
/* =================================================== */
/* УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ СБАЛАНСИР-ГО АВЛ-ДЕРЕВА ПОИСКА */
void del_el_AV(DT e,REC **T,int *h)
{
    REC *t,*K;
    t=*T;
    if (*T == NULL)
    {
        printf("\n Ключ %d не найден",e.Skey);
        *h = 0;
    }
    else if (compr(e.Skey,t->DATA.Skey)<0)
    {
        del_el_AV(e,&t->LPTR,h);
        if (*h)
            balanceL(&t,h);
    }
    else if (compr(e.Skey,t->DATA.Skey)>0)
    {
        del_el_AV(e,&t->RPTR,h);
        if (*h)
            balanceR(&t,h);
    }
    else                      /* удаление */
    {
        K = t;                /* узел найден */
        if (K->RPTR == NULL)  /* имеет только левую ветвь */
        {
            t=K->LPTR;
            free(K);
            *h = 1;
        }
        else if (K->LPTR == NULL) /* имеет только правую ветвь */
        {
            t = K->RPTR;
            free(K);
            *h = 1;
        }
        else
        {
            delbal(&K->LPTR,&K,h);
            if (*h)
                balanceL(&t,h);
        }
    }
    *T=t;
}
/* =============================================== */
void delbal(REC **R,REC **K,int *h)
{
    REC *r,*k;
    r = *R;
    k = *K;
    if (r->RPTR != NULL) /* спускаемся по правым ветвям до конца */
    {
        delbal(&r->RPTR,&k,h);
        if (*h)
            balanceR(R,h);
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
void balanceL(REC **t,int *h)
{
    REC *t1,*t2,*T;
    int b1,b2;
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
    case 1:          /* балансировка */
    {
        t1 = T->RPTR;
        b1 = t1->bal;
        if (b1 >= 0)  /* однократный RR-поворот */
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
        else    /* двукратный RL-поворот */
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
void balanceR(REC **t,int *h)
{
    REC *t1,*t2,*T;
    int b1,b2;
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
    case -1:         /* балансировка */
    {
        t1 = T->LPTR;
        b1 = t1->bal;
        if (b1 <= 0)  /* однократный LL-поворот */
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
        else    /* двукратный LR-поворот */
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
int Rdel_elS(DT e,REC **T)
{
    REC *K,*t;
    static int s;
    t=*T;
    if (*T == 0)
    {
        /*printf("\n Ключ %d не найден",key);*/
        s=0;
        return 1;
    }
    if (compr(e.Skey,t->DATA.Skey)<0)             /* Ищем заданный узел */
    {
        s=1;
        Rdel_elS(e,&t->LPTR);
    }
    else if (compr(e.Skey,t->DATA.Skey)>0)
    {
        s=1;
        Rdel_elS(e,&t->RPTR);
    }
    else
    {
        K = *T;                  /* Узел найден  */
        if (K->RPTR == 0)        /* Имеет только левую ветвь */
        {
            t = *T;
            *T = K->LPTR;
            free(t);
        }
        else if (K->LPTR == 0)      /* Имеет только правую ветвь */
        {
            t = *T;
            *T = K->RPTR;
            free(t);
        }
        else                    /* Имеет обе ветви  */
            Rdel(&K->LPTR,&K);    /* Идем по левой ветви */
    }
    preordC(*T);    /* Восстановление счетчиков */
    return !s;
}
/* ========================================================== */
/* ВСПОМОГАТЕЛЬНАЯ ДЛЯ УДАЛЕНИЯ ИЗ ДЕРЕВА ПОИСКА - рекурсия   */
void Rdel(REC **RR,REC **K)
{
    REC *r,*k;
    r=*RR;
    k = *K;
    if (r->RPTR != 0)    /* спуск по правым ветвям до конца */
        Rdel(&r->RPTR,&k);
    else  /* Удаляемый узел заменяем на самый нижний правый */
    {
        k->DATA =r->DATA;
        *K = *RR;
        *RR = r->LPTR;
        free(r);
    }
}
/* ========================================================= */
/* РОТАЦИЯ ВПРАВО                                            */
void rotR(REC **h)
{
    REC *x;
    x=(*h)->LPTR;
    (*h)->LPTR=x->RPTR;
    x->RPTR=*h;
    *h=x;
}
/* ======================================== */
/* РОТАЦИЯ ВЛЕВО                            */
void rotL(REC **h)
{
    REC *x;
    x=(*h)->RPTR;
    (*h)->RPTR=x->LPTR;
    x->LPTR=*h;
    *h=x;
}
/* ======================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В КОРЕНЬ ДЕРЕВА       */
void insertT(REC **T,DT e)
{
    if(*T==NULL)
    {
        *T=(REC*)calloc(1,sizeof(REC));
        (*T)->DATA=e;
        (*T)->LPTR=(*T)->RPTR=NULL;
        (*T)->N=0;
        return;
    }
    if (compr(e.Skey,(*T)->DATA.Skey)<0)
    {
        insertT(&(*T)->LPTR,e);
        rotR(T);
    }
    else
    {
        insertT(&(*T)->RPTR,e);
        rotL(T);
    }
    /*	preordC(*T);*/
}
/* =============================================== */
/* ВКЛЮЧЕНИЕ ЭЛЕМЕНТА В РАНДОМИЗИРОВАННОЕ ДЕРЕВО   */
void insertR(REC**T,DT e)
{
    int r,R;
    REC *t;
    t=*T;
    if(*T==NULL)
    {
        *T=(REC*)calloc(1,sizeof(REC));
        (*T)->DATA=e;
        (*T)->LPTR=(*T)->RPTR=NULL;
        preordC(t);
        return;
    }
    r=rand();
    R=RAND_MAX/((*T)->N);
    if(r<R)
    {
        insertT(T,e);
        return;
    }
    if(compr(e.Skey,(*T)->DATA.Skey)<0)
    {
        insertR(&(*T)->LPTR,e);
    }
    else
    {
        insertR(&(*T)->RPTR,e);
    }
}
/* =============================================== */
/* ПОДСЧЕТ ЧИСЛА УЗЛОВ В ПОДДЕРЕВЕ                    */
int count(REC* T)
{
    if (T==NULL)
        return NULL;
    return  (count(T->LPTR) + count(T->RPTR)+1);
}
/* ====================================================== */
/* ОБХОД БИНАРНОГО ДЕРЕВА ПО УРОВНЯМ - используем очередь */
void lvlorder(REC *T)
{
    static QUE q;
    REC* el;   //int cnt=0;
    if (T==NULL)
        return; /* дерево пустое */
    Crt_que(&q);
    Add_el(&q,T);
    while(Empty_que(&q))     /* пока очередь не пуста */
    {
        Extr_el(&q,&el);
        p(el);               // cnt++;
        if (el->LPTR)
            Add_el(&q,el->LPTR);
        if (el->RPTR)
            Add_el(&q,el->RPTR);
    }                     // cout<<"Cnt="<<cnt; getchar();
    Destroy_que(&q);
}
/* =============================================== */
/* ЛЕВЫЙ НИСХОДЯЩИЙ ОБХОД - нерекурсивная функция  */
/* Используем стек */
void preorder_nr(REC *T)
{
    static STC s;
    REC* el;
    if (T==NULL)
        return; /* дерево пустое */
    Crt_stc(&s);
    Push_el(&s,T);
    while(!(s.uv<0))
    {
        Pop_el(&s,&el);
        p(el);
        if(el->RPTR)
            Push_el(&s,el->RPTR);
        if(el->LPTR)
            Push_el(&s,el->LPTR);
    }
    Destroy_stc(&s);
}
/* ==================================================== */
int compr(int a,int b)
{
    return a-b;
}
/* ==================================================== */
int compr(float a,float b)
{
    return a-b;
}
/* ==================================================== */
int compr(char *a,char *b)
{
    return strcmp(a,b);
}
/* **************************************************** */
