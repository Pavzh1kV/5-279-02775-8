/* ************************************ */
/* СЖАТИЕ ДАННЫХ ПО АЛГОРИТМУ ХАФФМАНА  */
/* c:\bc\xbs\algoritm\huffman/cpp       */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "INCL_HFM.CPP"
/* ======================================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i, length;
    char istr[300];		/* исходная строка */
    unsigned int cstr[150];	/* закодированная строка */
    char dstr[300];		/* декодированная строка */
    printf("\n Введите строку для сжатия \n =>");
    fgets(istr,300,stdin);
    printf("\n Длина строки = %d", strlen(istr));
    length = Code_Hfm(istr, cstr);
    printf
    ("\n Закодированная строка длиной %d :\n",
     length);
    i = 0;
    while (cstr[i])
        printf(" %x", cstr[i++]);
    Dcde_Hfm(cstr, dstr);
    printf("\n Декодированная строка:\n");
    puts(dstr);
    getchar();
}

/* ***************************************************** */
