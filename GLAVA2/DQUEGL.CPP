/* РАБОТА С КОЛЬЦЕВОЙ ОЧЕРЕДЬЮ В ВЕКТОРНОЙ ПАМЯТИ
   c:\bc\xbs\stack\dquegl.c */
/* Хусаинов Б.С.   4.01.2002 */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
typedef struct  		/*Структура элемента очереди с именем EL */
{
    char FIO[24];
    int OC1;
    int OC2;
    int OC3;
} EL;
#include "INCL_QUE.CPP" /*файл с дескриптором очереди и
					   функциями для работы с очередью */
char *menu[7][40];
static int p = 1;
void main_menu(void);
int In_el(EL * el);
int Show_que(QUE s);
int Show_el(EL el);
/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    *menu[0] = "1.Создание пустой очереди";
    *menu[1] = "2.Включение элемента в очередь";
    *menu[2] = "3.Выборка элемента из очереди";
    *menu[3] = "4.Освобождение очереди";
    *menu[4] =
        "5.Вывод содержимого очереди на экран";
    *menu[5] = "6.Конец работы";
    *menu[6] = "         Введите номер строки";
    system("clear");
    printf("    Работа с кольцевой очередью\n");
    while (p)
    {
        main_menu();
        system("clear");
    }
    printf("    Конец pаботы с очередью \n");
    return 0;
}

/* ================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
void main_menu(void)
{
    char ns;
    int pp = 1, r = 0, i;
    EL el;
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
            if (Crt_que(&q1) == -1)
                printf
                ("\n Память под очередь не выделена");
            getchar();
            break;
        case '2':
            if (Empty_que(&q1) < 0)
            {
                printf("\n Очередь не создана");
                getchar();
                break;
            }
            if (In_el(&el))
                break;		/* отказ от ввода элемента */
            r = Add_el(&q1, el);
            if (r == -1)
                printf("\n Очередь полна!!!");
            break;
        case '3':
            if (Extr_el(&q1, &e) < 0)
                getchar();
            else
            {
                printf("\n Элемент выбран:");
                Show_el(e);
                getchar();
            }
            break;
        case '4':
            Destroy_que(&q1);
            break;
        case '5':
            if (Show_que(q1) == -1)
                printf("\n Очередь не создана");
            getchar();
            break;
        case '6':
            p = 0;
        }
    }
}

/* ===================================================== */
/* ФОРМИРОВАНИЕ ЭЛЕМЕНТА  ДЛЯ ВКЛЮЧЕНИЯ В ОЧЕРЕДЬ */
int In_el(EL * el)
{
    int p = 1;
    printf
    ("\n Ввод элемента очереди или * для отказа от ввода");
    printf("\n Введите фамилию =>");
    fflush(NULL);
    fgets(&el->FIO[0],24,stdin);
    if (el->FIO[0] == '*')
        return 1;
    p = 1;
    while (p)
    {
        printf("Введите 1-ю оценку\n");
        fflush(NULL);
        scanf("%d", &el->OC1);
        if ((el->OC1) < 2 || (el->OC1) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 2-ю оценку\n");
        fflush(NULL);
        scanf("%d", &el->OC2);
        if ((el->OC2) < 2 || ((el->OC2) > 5))
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    p = 1;
    while (p)
    {
        printf("Введите 3-ю оценку\n");
        fflush(NULL);
        scanf("%d", &el->OC3);
        if ((el->OC3) < 2 || (el->OC3) > 5)
            printf("\nОШИБКА!!!\n");
        else
            p = 0;
    }
    return 0;
}

/* ========================================================= */
/* ВЫВОД СОДЕРЖИМОГО ОЧЕРЕДИ (ВЕКТОРА) НА ЭКРАН */
int Show_que(QUE s)
{
    int i;
    if (s.un == NULL)
        return -1;
    for (i = 0; i < s.m; i++)
    {
        printf("\n Фамилия - %s", s.un[i].FIO);
        printf("\n Первая оценка - %d", s.un[i].OC1);
        printf("\n Вторая оценка - %d", s.un[i].OC2);
        printf("\n Третья оценка - %d", s.un[i].OC3);
    }
    return 0;
}

/* =============================================== */
/* ВЫВОД СОДЕРЖИМОГО ЭЛЕМЕНТА НА ЭКРАН             */
int Show_el(EL e)
{
    printf("\n Фамилия - %s", e.FIO);
    printf("\n Первая оценка - %d", e.OC1);
    printf("\n Вторая оценка - %d", e.OC2);
    printf("\n Третья оценка - %d", e.OC3);
    return 0;
}

/* ********************************************************* */
