/* ********************************************** */
/* СОРТИРОВКА  ДИНАМИЧЕСКОГО МАССИВА СТРУКТУР.    */
/* Метод пузырька.\srtdnstr.cpp                   */
/* ============================================== */
//#include <iostream.h>
//#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
//#include <alloc.h>
const int m = 40;
struct strct
{
    char line[m];		/* ключ сортировки */
    int k;
};
/* ============================================ */
/* СОРТИРОВКА МАССИВА СТРУКТУР МЕТОДОМ ПУЗЫРЬКА */
int sort(strct * a, int n)
{
    int ch, i, j;
    strct temp;
    for (i = 0; i < n - 1; i++)
    {
        ch = 0;
        for (j = n - 1; j > i; j--)
            if (strcmp((a[j].line), (a[j - 1].line)) < 0)
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                ch = 1;
            }
        if (!ch)
            return 0;
        /* можно посмотреть процесс сортировки */
        printf("\n Шаг %d", i + 1);
        for (j = 0; j < n; j++)
            printf("\n    %s %d", a[j].line, a[j].k);
        getchar();
    }
    return 0;
}

/* ====================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, n;
    strct *list;
    printf
    ("\n СОРТИРОВКА ДИНАМИЧЕСКОГО МАССИВА СТРОК \n");
    printf("\n Введите число строк массива =>");
    scanf("\ %d", &n);
    list = (strct *) calloc(n, sizeof(strct));
    /* Можно так присвоить значения элементам массива структур:*/
    /*		strcpy(list[0].line,"Яковлев"); list[0].k=1;
    		strcpy(list[1].line,"Конев");   list[1].k=2;
    		strcpy(list[2].line,"Тарасов"); list[2].k=3;
    		strcpy(list[3].line,"Абрамович"); list[3].k=4;
    		strcpy(list[4].line,"Абрамов");   list[4].k=5; */
    /* Но лучше вводить данные*/
    for (i = 0; i < n; i++)
    {
        printf("\n Введите данные %d-й строки \n=>",
               i + 1);
        scanf("%s %d", list[i].line, &list[i].k);
    }
    printf("\n\n ДО СОРТИРОВКИ");
    for (i = 0; i < n; i++)
        printf("\n%s %d", list[i].line, list[i].k);
    getchar();
    sort(list, n);
    printf("\n\n ПОСЛЕ СОРТИРОВКИ");
    for (i = 0; i < n; i++)
        printf("\n%s %d", list[i].line, list[i].k);
    getchar();
    return 0;
}

/* ******************************************************** */
