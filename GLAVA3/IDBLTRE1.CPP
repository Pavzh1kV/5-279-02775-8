/* ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ  БИНАРНОЕ ДЕРЕВО */
/* 11.11.02 Хусаинов Б.С.  c:\bc\xbs\idbltre1.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#define RECORD struct el_root
RECORD				/* Структура узла дерева */
{
    int DATA;			/* данные узла - только ключ */
    RECORD *LPTR, *RPTR;	/* левый и правый указатели на поддеревья */
};

RECORD *ROOT;			/* Указатель корня дерева */
static int ndi = 0;		/* последовательный номер включаемого элемента,
				   для удобства работы пользователя и контроля наличия дерева.
				   Перед каждым обращением к функциям tree, preorder, postorder,
				   inorder в вызывающей функции переменную ndi нужно обнулять. */
RECORD *tree(int k);		/* функция cоздания дерева, k - число узлов */
int preorder(RECORD *);		/* функция нисходящего обхода дерева */
int postorder(RECORD *);	/* Восходящий обход */
int inorder(RECORD *);		/* Смешанный обход */
void p(RECORD *);		/* Печать данных в узле */
void InData(RECORD *);
/* =============================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
main()
{
    setlocale(LC_ALL,"Russian");
    int i, n;
    printf
    ("\n\n РАБОТА С ИДЕАЛЬНО СБАЛАНСИРОВАННЫМ БИНАРНЫМ ДЕРЕВОМ");
    printf("\n Создание дерева");
    printf("\n Введите число узлов дерева =>");
    scanf("%d", &n);
    /* Создание идеально сбалансированного бинарного дерева */
    ndi = 0;
    if ((ROOT = tree(n)) == NULL)
    {
        printf("\n Дерево не создано");
        getchar();		/* return -1; */
    }
    printf
    ("\n Обходы дерева с печатью данных в узлах");
    printf("\n  Нисходящий обход дерева:\n");
    ndi = 0;
    preorder(ROOT);
    getchar();
    printf("\n Восходящий обход дерева:\n");
    ndi = 0;
    postorder(ROOT);
    getchar();
    printf("\n Смешанный обход дерева:\n");
    ndi = 0;
    inorder(ROOT);
    getchar();
    printf("\n Конец\n");
    getchar();
    return 0;
}

/* ======================================================= */
/*  ПОСТРОЕНИЕ БИНАРНОГО ИДЕАЛЬНО СБАЛАНСИРОВАННОГО ДЕРЕВА */
RECORD *tree(int k)
{
    RECORD *newnode;
    int nl, nr;
    if (k <= 0)			/* k<0 при ошибочном задании параметра */
        newnode = 0;
    else
    {
        nl = k / 2;
        nr = k - nl - 1;
        newnode = (RECORD *) calloc(1, sizeof(RECORD));
        InData(newnode);
        newnode->LPTR = tree(nl);
        newnode->RPTR = tree(nr);
    }
    return newnode;
}

/* ========================================================= */
/*  НИСХОДЯЩИЙ ОБХОД ДЕРЕВА */
int preorder(RECORD * T)
{
    if (T == NULL && ndi == 0)
    {
        printf("\n Дерево пустое");
        getchar();
        return -1;
    }
    if (T != 0)
    {
        ndi++;
        p(T);			/* обработка данных в узле */
        preorder(T->LPTR);
        preorder(T->RPTR);
    }
    return 0;
}

/* ======================================================= */
/* ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА */
int postorder(RECORD * T)
{
    if (T == NULL && ndi == 0)
    {
        printf("\n Дерево пустое");
        getchar();
        return -1;
    }
    if (T != 0)
    {
        ndi++;
        postorder(T->LPTR);
        postorder(T->RPTR);
        p(T);
    }
    return 0;
}

/* ======================================================= */
/* СМЕШАННЫЙ ОБХОД ДЕРЕВА */
int inorder(RECORD * T)
{
    if (T == NULL && ndi == 0)
    {
        printf("\n Дерево пустое");
        getchar();
        return -1;
    }
    if (T != 0)
    {
        ndi++;
        inorder(T->LPTR);
        p(T);
        inorder(T->RPTR);
    }
    return 0;
}

/* ======================================================= */
/* ОБРАБОТКА ДАННЫХ УЗЛА ДЕРЕВА */
void p(RECORD * B)
{
    printf(" %d ", B->DATA);
}

/* ======================================================= */
/* ВВОД ДАННЫХ УЗЛА ДЕРЕВА */
void InData(RECORD * d)
{
    printf(" Введите %d-й ключ =>", ++ndi);
    scanf("%d", &d->DATA);
}

/* ****************************************************** */
