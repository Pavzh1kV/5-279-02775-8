/* ************************************************** */
/* СОРТИРОВКА ДИНАМИЧЕСКОГО СВОБОДНОГО МАССИВА СТРОК  */
/* Метод пузырька. Вариант 2. \sortdin.cpp            */
/* ================================================== */
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
int sort(String * a, int n)
{
    int ch, i, j;
    String temp;
    do
    {
        ch = 0;
        for (j = 0; j < n - 1; j++)
            if (strcmp(a[j + 1], a[j]) < 0)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                ch = 1;
            }
    }
    while (ch);
    return 0;
}

/* ====================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i;
    for (i = 0; i < max; i++)
        list[i] = new char[40];
    list[0] = "zzzzzz";
    list[1] = "sssssssssssss";
    list[2] = "aaaaaaaaaaaaaaaa";
    list[3] = "ddd";
    list[4] = "ccccccccc";
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
