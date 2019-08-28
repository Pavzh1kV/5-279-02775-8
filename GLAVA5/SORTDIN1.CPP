/* ************************************* */
/* СОРТИРОВКА ДИНАМИЧЕСКОГО СВОБОДНОГО МАССИВА СТРОК.*/
/* Метод пузырька, вариант 1.          \sortdin1.cpp */
/* ================================================= */
//#include <iostream.h>
//#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
typedef char *String;
const int max = 10;
String list[max];
/* ====================================== */
/* СОРТИРОВКА МЕТОДОМ ПУЗЫРЬКА            */
int sort(String * a, int n)
{
    int ch, i, j;
    String temp;
    for (i = 0; i < n - 1; i++)
    {
        ch = 0;
        for (j = n - 1; j > i; j--)
            if (strcmp(a[j], a[j - 1]) < 0)
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                ch = 1;
            }
        if (!ch)
            return 0;
        /* можно посмотреть процесс сортировки */
        /*	 for(j=0; j<n; j++)
        	  printf("\n    %s",a[j]);  getchar(); */
    }
    return 0;
}

/* ====================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i;
    for (i = 0; i < max; i++)
        list[i] = new char[40];
    list[0] = "555zzzzzz";
    list[1] = "4444sssssssssssss";
    list[2] = "111aaaaaaaaaaaaaaaa";
    list[3] = "333ddd";
    list[4] = "222ccccccccc";
    printf("\n\n ДО СОРТИРОВКИ");
    for (i = 0; i < 5; i++)
        printf("\n%s", list[i]);
    sort(list, 5);
    printf("\n\n ПОСЛЕ СОРТИРОВКИ");
    for (i = 0; i < 5; i++)
        printf("\n%s", list[i]);
    getchar();
    return 0;
}

/* ******************************************* */
