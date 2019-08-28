/* ******************************************** */
/* ВЫДЕЛЕНИЕ СЛОВ ИЗ СТРОКИ И РАЗМЕЩЕНИЕ ИХ     */
/*	В СТРОКАХ ДВУХМЕРНОГО СВОБОДНОГО МАССИВА     */
/* \freearr.cpp                                 */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <cstdio>
//#include <conio.h>
#include <string.h>
//#include <alloc.h>
/* ============================================ */
/* Выделение слов из строки и размещение их     */
/* в строках свободного массива                 */
int obrstr(char *c, char **FA)
{
    int ln, n = 0, i = 0;	/* n - число выделенных слов */
    char *wr;			/* указатель на выделенное слово */
    char *tempstr;		/* чтобы не испортить исходную
				   строку, ее копируем во временную         */
    ln = strlen(c);
    tempstr = (char *) calloc(ln + 1, sizeof(char));
    strcpy(tempstr, c);
    wr = strtok(tempstr, " ");
    ln = strlen(wr);
    FA[i] = (char *) calloc(ln + 1, sizeof(char));
    strcpy(FA[i++], wr);
    n++;
    while (wr = strtok(NULL, " "))
    {
        ln = strlen(wr);
        FA[i] = (char *) calloc(ln + 1, sizeof(char));
        strcpy(FA[i++], wr);
        n++;
    }
    free(tempstr);
    return n;
}

/* ============================================= */
/* ГЛАВНАЯ ФУНКЦИЯ */
int main()
{
    setlocale(LC_ALL,"Russian");
    char *SM[40];		/* массив указателей строк
				   свободного массива */
    int i, n;			/* n - число занятых строк в нем */
    char str[120];		/* для ввода исходной строки */
    system("clear");
    printf
    ("Выделение слов из строки и размещение\
 их в строках свободного массива");
    printf("\n Введите строку \n=>");
    fgets(str,120,stdin);
    printf("\n    Исходная строка:\n");
    puts(str);
    n = obrstr(str, SM);
    printf("\n    Свободный массив:");
    for (i = 0; i < n; i++)
        printf("\n%s", SM[i]);
    /* Если массив больше не нужен, то освободим
       память, занятую его строками */
    for (i = 0; i < n; i++)
    {
        free(SM[i]);
        SM[i] = NULL;
    }
    printf("\n\n  Конец работы");
    getchar();
}

/* ************************************************* */
