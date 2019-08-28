/* РАБОТА СО СТЕКОМ В ВЕКТОРНОЙ ПАМЯТИ
   d:\tc\xbs\massiv\dstackg2.c -  головной файл */
/* Хусаинов Б.С.   3.01.2002 */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
//#include <process.h> // Не известноя деректива
typedef struct  		/*Структура элемента стека с именем EL */
{
    char Name[80];
} EL;
EL e;
#include "INCL_QUE.CPP"	/*файл включения */
char *menu[7][40];
static int p = 1;
int In_el(EL *);
int Show_stc(STC);
void main_menu(void);
/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    *menu[0] = "1.Создание пустого стека";
    *menu[1] = "2.Включение элемента в стек";
    *menu[2] = "3.Выборка элемента из стека";
    *menu[3] = "4.Освобождение стека";
    *menu[4] =
        "5.Вывод содержимого стека на экран";
    *menu[5] = "6.Конец работы";
    *menu[6] = "         Введите номер строки";
    system("clear");
    printf
    ("    Работа со стеком в векторной памяти\n");
    while (p)
    {
        main_menu();
        system("clear");
    }
    printf("    Конец pаботы со стеком\n");
    return 0;
}

/* ================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void main_menu(void)
{
    char ns;
    int pp = 1, r = 0, i;
    fflush(NULL);			/* чистка буферов */
    while (pp)
    {
        for (i = 0; i < 7; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        ns = getchar();
        if (ns < '1' || ns > '6')
        {
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        else
            pp = 0;
        switch (ns)
        {
        case '1':
            if (Crt_stc(&s1) == -1)
            {
                printf
                ("\n Память под стек не выделена");
                getchar();
            }
            break;
        case '2':
            if (In_el(&e) == 0)
            {
                r = Push_el(&s1, e);
                if (r == -2)
                {
                    printf("\nСтек не создан!!!");
                    getchar();
                }
                else if (r == -1)
                {
                    printf("\n Стек полон!!!");
                    getchar();
                }
            }
            break;
        case '3':
            r = Pop_el(&s1, &e);
            if (r == -1)
                printf("\n Стек пуст");
            else if (r == -2)
                printf("\n Стек не создан!!");
            else
            {
                printf("\n Элемент выбран\n");
                /* Обработка элемента */
                system(e.Name);
            }
            getchar();
            break;
        case '4':
            Destroy_stc(&s1);
            break;
        case '5':
            if (Show_stc(s1) == -1)
            {
                printf("\n Стек не создан");
                getchar();
            }
            break;
        case '6':
            p = 0;
        }
    }
}

/* ===================================================== */
int In_el(EL * el)
{
    printf
    ("\n Ввод элемента стека или ** для отказа от ввода");
    printf
    ("\n Введите команду DOS или имя исполняемого файла\n=>");
    fflush(NULL);
    fgets(el->Name,80,stdin);
    return 0;
}

/* ========================================================= */
int Show_stc(STC s)
{
    int i;
    if (s.un == NULL)
        return -1;
    for (i = 0; i <= s.uv; i++)
        printf("\n %s", s.un[i].Name);
    getchar();
    return 0;
}

/* ********************************************************* */
