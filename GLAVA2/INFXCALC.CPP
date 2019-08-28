/* ************************************************ */
/* РАБОТА СО СТЕКОМ В ВЕКТОРНОЙ ПАМЯТИ,
   МОДЕЛИРОВАНИЕ ИНФИКСНОГО КАЛЬКУЛЯТОРА.
   c:\bc\xbs\stack\infxcalc.c  - головной файл */
/* Хусаинов Б.С.   27.01.2002 */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#include <math.h>
/*  Стек для работы с операндами =============== */
typedef double ELop;
#define STCop struct st
STCop				/* дескриптор стека */
{
    ELop *un;			/* Указатель начала стека */
    int uk;			/* Указатель конца стека */
    int uv;			/* Указатель вершины стека */
    int m;			/* число элементов в стеке */
} sop;				/* sop -переменная типа STCop */

ELop eop;
int Show_stcop(STCop * s);
int compute(STCop * s, char c);
/* ========================================== */
/*      ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СТЕК   */
int Push_elop(STCop * s, ELop el)
{
    if (s->un == NULL)		/*стек не создан */
        return -2;
    if (s->uv == s->uk)
        return -1;		/* стек полон */
    *(s->un + s->uv + 1) = el;
    ++s->uv;
    return 0;
}

/* ========================================== */
/*       ВЫБОРКА ЭЛЕМЕНТА ИЗ СТЕКА     */
int Pop_elop(STCop * s, ELop * el)
{
    if (s->un == NULL)
        return -2;		/* стек не создан */
    if (s->uv < 0)
        return -1;		/* стек пуст */
    else
    {
        *el = *(s->un + s->uv);
        *(s->un + s->uv) = 0;
        --s->uv;
        return 0;
    }
}

/* ========================================== */
/* ИЗВЛЕЧЕНИЕ ЗНАЧЕНИЯ ЭЛЕМЕНТА ИЗ СТЕКА БЕЗ УДАЛЕНИЯ ЭЛЕМЕНТА  */
int Peek_elop(STCop * s, ELop * el)
{
    if (s->un == NULL)
        return -2;		/* стек не создан */
    if (s->uv < 0)
        return -1;		/* стек пуст */
    else
    {
        *el = *(s->un + s->uv);
        return 0;
    }
}

/* ========================================== */
/*       ОСВОБОЖДЕНИЕ СТЕКА       */
int Destroyop(STCop * s)
{
    free(s->un);
    s->un = NULL;
    return 0;
}

/* ========================================== */
/*      СОЗДАНИЕ СТЕКА           */
int Crt_stcop(STCop * s)
{
    int n;
    if (s->un != NULL)
    {
        printf("\n Старый стек уничтожить? (y/n) ");
        fflush(NULL);
        if (getchar() != 'y')
        {
            printf("\n Работаем со старым стеком");
            return -2;
        }
    }
    printf
    ("\n Введите число элементов стека операндов =>");
    scanf("%d", &n);
    s->un = (ELop *) calloc(n, sizeof(ELop));
    if (s->un == NULL)
        return -1;		/* память не выделена */
    else
    {
        s->uv = -1;
        s->uk = n - 1;
        s->m = n;
        return 0;
    }
}

/* ================================================= */
/*   Стек для работы со знаками операций =========== */
typedef struct
{
    char op;			/* знак операции */
    int pr;			/* приоритет операции */
} ELcl;
#define STCcl struct stcl
STCcl				/* дескриптор стека */
{
    ELcl *un;			/* Указатель начала стека */
    int uk;			/* Указатель конца стека */
    int uv;			/* Указатель вершины стека */
    int m;			/* число элементов в стеке */
} scl;				/* scl -переменная типа STC */

ELcl ecl;
/* Таблица приоритетов операций и разделителей */
ELcl tabl[8] = { {'(', 0},
    {')', 1},
    {'=', 2},
    {'+', 3},
    {'-', 3},
    {'*', 4},
    {'/', 4},
    {'^', 5}
};

/* ========================================== */
/*      ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СТЕК   */
int Push_elcl(STCcl * s, ELcl el)
{
    if (s->un == NULL)		/*стек не создан */
        return -2;
    if (s->uv == s->uk)
        return -1;		/* стек полон */
    *(s->un + s->uv + 1) = el;
    ++s->uv;
    return 0;
}

/* ========================================== */
/*       ВЫБОРКА ЭЛЕМЕНТА ИЗ СТЕКА     */
int Pop_elcl(STCcl * s, ELcl * el)
{
    if (s->un == NULL)
        return -2;		/* стек не создан */
    if (s->uv <= 0)
        return -1;		/* стек пуст */
    else
    {
        *el = *(s->un + s->uv);
        --s->uv;
        return 0;
    }
}

/* ========================================== */
/* ИЗВЛЕЧЕНИЕ ЗНАЧЕНИЯ ЭЛЕМЕНТА ИЗ СТЕКА БЕЗ УДАЛЕНИЯ ЭЛЕМЕНТА  */
int Peek_elcl(STCcl * s, ELcl * el)
{
    if (s->un == NULL)
        return -2;		/* стек не создан */
    if (s->uv < 0)
        return -1;		/* стек пуст */
    else
    {
        *el = *(s->un + s->uv);
        return 0;
    }
}

/* ========================================== */
/*       ОСВОБОЖДЕНИЕ СТЕКА       */
int Destroycl(STCcl * s)
{
    free(s->un);
    s->un = NULL;
    return 0;
}

/* ========================================== */
/*      СОЗДАНИЕ СТЕКА           */
int Crt_stccl(STCcl * s)
{
    int n;
    if (s->un != NULL)
    {
        printf("\n Старый стек уничтожить? (y/n) ");
        fflush(NULL);
        if (getchar() != 'y')
        {
            printf("\n Работаем со старым стеком");
            return -2;
        }
    }
    /* В начале стека вспомогательный элемент */
    printf
    ("\n Введите число элементов стека операций =>");
    scanf("%d", &n);
    s->un = (ELcl *) calloc(n + 1, sizeof(ELcl));
    if (s->un == NULL)
        return -1;		/* память не выделена */
    else
    {
        (s->un)->pr = -1;
        (s->un)->op = ' ';
        s->uv = 0;
        s->uk = n;
        s->m = n + 1;
        return 0;
    }
}

/* *************************************************** */

int Scan(STCcl * scl, STCop * sop, char *isx);
int Compute(STCop * s, char c);
void Rez(STCop * s);

/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    char isxstr[120];
    printf(" Инфиксный калькулятор \n");
    if (Crt_stcop(&sop) == -1)
        return -1;
    if (Crt_stccl(&scl) == -1)
        return -1;
    printf
    ("\n Введите арифм-кое выражение, заканчивающееся знаком '='\n=>");
    fflush(NULL);
    fgets(isxstr,120,stdin);
    if (Scan(&scl, &sop, isxstr) == -1)
    {
        printf("\n Ошибка в выражении!!!\n");
        getchar();
        return -1;
    }
    return 0;
}

/* ============================================================== */
/* СКАНИРОВАНИЕ И ОБРАБОТКА ИСХОДНОЙ СТРОКИ С АРИФМЕТИЧЕСКИМ ВЫРАЖЕНИЕМ */
int Scan(STCcl * scl, STCop * sop, char *isx)
{
    char c;
    int i, j, k, r;
    char strop[20];
    char str[] = "+-*/^()=";	/* строка знаков операций */
    char *cp;
    i = 0;			/* индекс для сканирования исходной строки */
    while (1)
    {
        j = 0;			/* индекс для формирования операнда */
        while (1)  		/* удаляем  пробелы */
        {
            c = isx[i++];
            printf(" c=%c ", c);
            getchar();
            if (c == ' ')
                continue;
            else
                break;
        }
        while (1)  		/* здесь символ с - не пробел */
        {
            cp = strchr(str, c);	/* это знак операции */
            if (cp == 0)  	/* нет, формируем операнд в выходной строке */
            {
                strop[j++] = c;
                c = isx[i++];
                printf(" c=%c ", c);
                getchar();
                if (c != ' ')
                    continue;
                else
                {
                    strop[j++] = '\0';	/* конец операнда определился пробелом */
                    if (sscanf(strop, "%lf", &eop) != 0)
                    {
                        Push_elop(sop, eop);
                        printf("\n конец-пробел op=%lf ", eop);
                        Show_stcop(sop);	/* отладка */
                        getchar();
                    }
                    else
                    {
                        printf("\n Ошибка 1 в операнде");
                        getchar();
                        return -3;
                    }
                    break;
                }
            }
            else
            {
                if (j != 0)  	/* конец операнда определился знаком операции */
                {
                    strop[j++] = '\0';
                    if (sscanf(strop, "%lf", &eop) != 0)
                    {
                        Push_elop(sop, eop);
                        printf("\n конец-операция op=%lf ",
                               eop);
                        Show_stcop(sop);	/* отладка */
                        getchar();
                    }
                    else
                    {
                        printf("\n Ошибка 2 в операнде");
                        getchar();
                        return -3;
                    }
                }
                if (c == '=')  	/* конец выражения, выдаем результат */
                {
                    while (1)
                    {
                        k = Pop_elcl(scl, &ecl);
                        printf("\n ecl=%c", ecl.op);
                        getchar();
                        if (k == 0)
                        {
                            if (compute(sop, ecl.op) != 0)
                                return -1;
                            continue;
                        }
                        else
                        {
                            Rez(sop);
                            getchar();
                            return 0;
                        }
                    }
                }
                switch (c)  	/* выполним текущую операцию */
                {
                case '+':
                    k = 3;
                    break;
                case '-':
                    k = 4;
                    break;
                case '*':
                    k = 5;
                    break;
                case '/':
                    k = 6;
                    break;
                case '^':
                    k = 7;
                    break;
                case '(':
                    k = 0;
                    break;
                case ')':
                    k = 1;
                    break;
                }
                while (1)
                {
                    Peek_elcl(scl, &ecl);
                    if (tabl[k].pr == 0 || tabl[k].pr > ecl.pr)
                    {
                        Push_elcl(scl, tabl[k]);
                        if (tabl[k].op == ')')  	/* закрыв. скобка ) */
                        {
                            Pop_elcl(scl, &ecl);
                            printf("\n Убрали %c ", ecl.op);
                            getchar();
                            Pop_elcl(scl, &ecl);
                            break;
                        }
                        printf("\n добавили %c ", tabl[k].op);
                        getchar();
                        break;
                    }
                    else
                    {
                        r = Peek_elcl(scl, &ecl);
                        printf("\nEEEcl=%c", ecl.op);
                        getchar();
                        if (r != 0)
                            break;
                        Pop_elcl(scl, &ecl);
                        r = compute(sop, ecl.op);
                        printf(" r=%d", r);
                        Show_stcop(sop);
                        if (r == -1)
                            return -1;
                    }
                }
            }
            break;
        }
    }
    return 0;
}

/* ========================================================== */
/* ВЫДАЧА РЕЗУЛЬТАТА ВЫЧИСЛЕНИЙ */
void Rez(STCop * s)
{
    Peek_elop(s, &eop);
    printf("\n Результат =%lf", eop);
    getchar();
}

/* ============================================================== */
/* ВЫПОЛНЕНИЕ ОПЕРАЦИИ НАД ДВУМЯ ОПЕРАНДАМИ */
int compute(STCop * s, char c)
{
    ELop op1, op2, op;
    if (Pop_elop(s, &op2) != 0)
    {
        printf("\n Нет 2-го операнда!!!");
        return -1;
    }
    if (Pop_elop(s, &op1) != 0)
    {
        printf("\n Нет 1-го операнда!!!");
        return -1;
    }
    switch (c)
    {
    case '+':
        op = op1 + op2;
        Push_elop(s, op);
        break;
    case '-':
        op = op1 - op2;
        Push_elop(s, op);
        break;
    case '*':
        op = op1 * op2;
        Push_elop(s, op);
        break;
    case '/':
        if (op2 == 0.0)
        {
            printf("\n Деление на ноль \n");
            return -1;
        }
        else
            op = op1 / op2;
        Push_elop(s, op);
        break;
    case '^':
        if (op1 < 0)
        {
            printf
            ("\n Cтепень отрицательного числа!!! ");
            return -1;
        }
        else
            op = pow(op1, (float) op2);
        Push_elop(s, op);
        break;
    }
    return 0;
}

/* ============================================================ */
/* ВЫВОД СОДЕРЖИМОГО СТЕКА, выводим только занятые элементы */
int Show_stcop(STCop * s)
{
    int i;
    if (s->un == NULL)
        return -1;
    printf("\n");
    for (i = 0; i <= s->uv; i++)
        printf("\n %lf", s->un[i]);
    getchar();
    return 0;
}

/* ********************************************************* */
