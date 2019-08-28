/* ****************************************************** */
/* СОРТИРОВКА  МАССИВА СТРОК. Метод пузырька.\sortstr.cpp */
/* ====================================================== */
//#include <iostream.h>
//#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
const int m = 64;
/* ====================================== */
/* СОРТИРОВКА МЕТОДОМ ПУЗЫРЬКА            */
int sort(char a[][m], int n)
{
    int ch, i, j;
    char temp[40];
    for (i = 0; i < n - 1; i++)
    {
        ch = 0;
        for (j = n - 1; j > i; j--)
            if (strcmp((a[j]), (a[j - 1])) < 0)
            {
                strcpy(temp, a[j]);
                strcpy(a[j], a[j - 1]);
                strcpy(a[j - 1], temp);
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
    const int n = 5;
    char list[n][m];		/* = {"555zzzzzz","4444ssssssssssss","111aaaaaa",
				   "333ddd","222cccccccccc"}; */
    /* Можно по-другому:*/
    strcpy(list[0], "555арбуз");
    strcpy(list[1], "4444sssssssssssss");
    strcpy(list[2], "111aaaaaaaaaaaaaaaa");
    strcpy(list[3], "555арб");
    strcpy(list[4], "222ccccccccc");
    printf("\n\n ДО СОРТИРОВКИ");
    for (i = 0; i < n; i++)
        printf("\n%s", list[i]);
    getchar();
    sort(list, n);
    printf("\n\n ПОСЛЕ СОРТИРОВКИ");
    for (i = 0; i < n; i++)
        printf("\n%s", list[i]);
    getchar();
    return 0;
}

/* ******************************************* */
