/* ******************************************************* */
/* РАБОТА С БИНАРНЫМИ ДЕРЕВЬЯМИ ПОИСКА:                    */
/* - простое бинарное дерево поиска;                       */
/* - сбалансированное АВЛ-дерево поиска;                   */
/* - сбалансированное рандомизированное дерево поиска.     */
/* - Ключ элемента - целое число.                          */
/* - Можно проследить за ходом роста дерева при включении  */
/*   элементов и разрушения дерева при удалении элементов. */
/* - Для работы с бинарными деревьями поиска исполььзуется */
/*   файл включения c:\bc\xbs\tree\poiskper.h              */
/* 11.01.2004.  c:\bc\xbs\tree\poiskper.cpp  */
/* ======================================================= */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#define n 21			/*количество узлов дерева для примера */
typedef struct DataNode  	/* структура данных в узле   */
{
    char Dkey[40];		/* поле ключа в данных       */
};
DataNode ai;
typedef DataNode DT;		/* тип данных для связи с файлом включения */
#define Skey Dkey		/* имя ключа для связи с файлом включения  */
void visit(DT * dt);		/* расширение в обработке данных узла */
#include "POISKPER.H"	/* для деревьев поиска */
REC *S, *AV, *R, *T, *E, *A, *C;
char a[n][10] = { "h11", "d9", "s7", "a8", "n15", "b19", "c20", "e21",
                  "x2", "z3", "k1", "d6", "w4", "q5", "h13", "m14", "f10", "y12", "o17",
                  "r16", "e18"
                };

//int a[n]={11,9,7,8,15,19,2,21,2,3,1,6,4,5,13,14,10,12,17,16,18};
/* ================================================================ */
void visit1(DT * dt)
{
    insertS(*dt, &A);
    cout << " ins: " << dt->Dkey;
}

/* ================================================================ */
void visit2(DT * dt)
{
    cout << " Обработка2: " << dt->Dkey;
}

/* ==================================================== */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
int main()
{
    setlocale(LC_ALL,"Russian");
    int h = 0;
    int i, ii, r;
    printf
    ("\n\n\n Работа с бинарными деревьями, ");
    printf("\n    содержащими %d элементов", n);
    /* Массив значений данных можно вводить по запросу: */
    /*  int j;
       for (j=0; j<n; j++)
       {printf("Введите %d -й элемент дерева",j);
       ....a[j]); */
    printf("\n Исходный массив ключей \n");
    for (i = 0; i < n; i++)
        cout << " " << a[i];
    getchar();
    printf
    ("\n\nСоздадим бинарные  деревья поиска ");
    for (i = 0; i < n; i++)
    {
        strcpy(ai.Dkey, a[i]);	//символьные ключи
        insertS(ai, &S);
        insertAV(ai, &AV, &h);
        //      printf("\n Процесс формирования АВЛ-дерева:");
        //      preorder(AV); getchar();
        insertR(&R, ai);
        preordC(R);		/* включение счетчиков в рандом. дерево */
        //      printf("\n  Процесс форм-ния рандомиз. дерева:");
        //      preordN(R);getchar();
    }
    printf
    ("\n Нисходящий обход дерева поиска\n");
    preordrx(S, visit1);
    getchar();
    printf("\n Нисходящий обход дерева А:\n");
    preorder(A);
    getchar();
    printf
    ("\nНисходящий обход дерева поиска - нерекурс. функция\n");
    preorder_nr(S);
    getchar();
    printf
    ("\n Восходящий обход дерева поиска\n");
    postorder(S);
    getchar();
    printf("\n Смешанный обход дерева поиска\n");
    inorder(S);
    getchar();
    printf
    ("\n Нисходящий обход дерева с вставкой в корень:\n");
    preorder(S);
    printf
    ("\nНисходящий обход (АВЛ) - нерекурсивная функция\n");
    preorder_nr(AV);
    printf
    ("\nНисходящий обход (ранд.) - нерекурсивная функция\n");
    preorder_nr(R);
    printf("\n Обход по уровням:");
    lvlorder(S);
    printf("\n Нисходящий обход АВЛ-дерева:\n");
    preordrx(AV, visit2);
    getchar();
    printf
    ("\n Нисходящий обход рандомизированного дерева:\n");
    preorder(R);
    getchar();
    printf
    ("\n Вставим в корень дерева поиска элемент p11");
    strcpy(ai.Dkey, "p11");
    insertT(&S, ai);
    printf
    ("\n Нисходящий обход дерева после вставки\n");
    preorder(S);
    printf
    ("\n Вставим в корень рандом.дерева  элемент p11");
    insertT(&R, ai);
    printf
    ("\n Нисходящий обход дерева после вставки\n");
    preorder(R);
    preordC(S);			/* вставка счетчиков в дерево поиска */
    printf
    ("\n Нисход. обход после вставки счетчиков\n");
    preordN(S);
    printf
    ("\n В АВЛ-дерево включим элементы e45,c21,v39");
    strcpy(ai.Dkey, "e45");
    insertAV(ai, &AV, &h);
    strcpy(ai.Dkey, "c21");
    insertAV(ai, &AV, &h);
    strcpy(ai.Dkey, "v39");
    insertAV(ai, &AV, &h);
    printf("\n Нисходящий обход дерева \n");
    preorder(AV);
    printf
    ("\n Удалим из АВЛ-дерева элементы с 12 по 24");
    /* for (ii=12;ii<25;ii++)
    	{ h=0; del_el_AV(ii,&AV,&h);
    	  printf("\nОбход после  удаления key=%d\n",ii);
    	  preorder(AV); getchar();
    	}*/
    printf
    ("\n Поиск и удаление элементов в дереве ");
    printf
    ("\n поиска с случайным выбором ключей\n");
    /*for(i=1; i<11; i++)
       {ii=rand()%25;
       r=loc(ii,S,&E);
       if (r==0)
       printf("\n Ключ %d найден",E->DATA);
       else
       printf("\n Ключ %d не найден",ii);
       r=Rdel_elS(ii,&S);
       if (r==0)
       printf("\n Элемент %d удален",ii);
       else
       printf("\n Элемент %d  не найден",ii);
       printf("\n");
       preorder(S);
       getchar();
       } */
    getchar();
    return 0;
}

/* *********************************************** */
