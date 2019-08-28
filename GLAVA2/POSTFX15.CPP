/* РАБОТА СО СТЕКОМ В ВЕКТОРНОЙ ПАМЯТИ, МОДЕЛИРОВАНИЕ */
/* ПОСТФИКСНОГО КАЛЬКУЛЯТОРА. \postfx15.cpp           */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#include <math.h>
typedef double EL;
#include "incl_stc.c"	/*файл с дескрип-
					   тором стека и функциями для работы со стеком */
int Scan(STC * s, char *isx);
int Compute(STC * s, char c);
void Rez(STC * s);
int Show_stc(STC * s);
EL op;

/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    char isxstr[120];		/* строка для обратной польской записи */
    printf(" Постфиксный калькулятор \n");
    if (Crt_stc(&s1) == -1)
    {
        printf("\n Не выделена память для стека");
        getchar();
        return -1;
    }
    printf
    ("\n Введите арифметическое выражение в постфиксной форме\n=>");
    fflush(NULL);
    fgets(isxstr,120,stdin);
    if (Scan(&s1, isxstr) != 0)
    {
        printf("\n Ошибка в выражении!!!\n");
        getchar();
        return -1;
    }
    else
        Rez(&s1);
    return 0;
}

/* ============================================================== */
int Scan(STC * s, char *isx)
{
    char c;
    int i;
    char str1[10];		/* для формирования операнда */
    char str[] = "+-*/^=";	/* строка знаков операций */
    char *cp;
    int j = 0;
    if (isx[0] == '=' || strlen(isx) == 0)
    {
        printf("\n Пустое выражение");
        getchar();
        return -1;
    }
    if (strchr(isx, '=') == NULL)
    {
        printf
        ("\n Выражение должно завершаться знаком '='");
        getchar();
        return -3;
    }
    while (1)  			/* до конца выражения */
    {
        i = 0;
        while (1)  		/*удаляем пробелы */
        {
            c = isx[j++];
            if (c == ' ')
                continue;
            else
                break;
        }
        while (1)  		/* обработка очередного элемента выражения */
        {
            cp = strchr(str, c);	/* это знак операции? */
            if (cp == 0)  	/* нет */
            {
                str1[i] = c;
                i++;		/* формируем строку операнда */
                c = isx[j++];
                if (c != ' ')
                    continue;
                else
                {
                    str1[i] = '\0';	/* конец операнда определился пробелом */
                    if (sscanf(str1, "%lf", &op) != 0)
                    {
                        Push_el(s, op);
                        Show_stc(s);	/* отладка */
                        getchar();
                    }
                    break;
                }
            }
            else
            {
                if (i != 0)  	/* конец операнда определился знаком операции */
                {
                    str1[i] = '\0';
                    if (sscanf(str1, "%lf", &op) != 0)
                    {
                        Push_el(s, op);
                        Show_stc(s);	/* отладка */
                        getchar();
                    }
                }
                if (c == '=')  	/* конец выражения */
                {
                    if (s->uv > 0)  	/* остались лишние операнды */
                    {
                        printf
                        ("\n Не хватает оператора");
                        getchar();
                        return -1;
                    }
                    else
                        return 0;
                }
                switch (c)  	/* выполним текущую операцию */
                {
                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                    if (Compute(&s1, c) == -1)
                        return -1;
                }
            }
            break;
        }
    }
}

/* ========================================================== */
/* ВЫДАЧА РЕЗУЛЬТАТА ВЫЧИСЛЕНИЙ */
void Rez(STC * s)
{
    Peek_el(s, &op);
    printf("\n Результат =%lf", op);
    getchar();
}

/* ============================================================== */
/* ВЫПОЛНЕНИЕ ОПЕРАЦИИ НАД ДВУМЯ ОПЕРАНДАМИ */
int Compute(STC * s, char c)
{
    EL op1, op2;
    int r1, r2;
    if (Pop_el(s, &op2) != 0)
    {
        printf
        ("\n Для операции '%c' нет операндов!!!",
         c);
        return -1;
    }
    if (Pop_el(s, &op1) != 0)
    {
        printf
        ("\nДля операции '%c' нет левого операнда!!!",
         c);
        return -1;
    }
    switch (c)
    {
    case '+':
        op = op1 + op2;
        Push_el(s, op);
        break;
    case '-':
        op = op1 - op2;
        Push_el(s, op);
        break;
    case '*':
        op = op1 * op2;
        Push_el(s, op);
        break;
    case '/':
        if (op2 == 0.0)
        {
            printf("\n Деление на ноль \n");
            return -1;
        }
        else
            op = op1 / op2;
        Push_el(s, op);
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
        Push_el(s, op);
        break;
    }
}

/* ============================================================ */
/* ВЫВОД СОДЕРЖИМОГО СТЕКА */
int Show_stc(STC * s)
{
    int i;
    if (s->un == NULL)
        return -1;
    printf("\n");
    for (i = 0; i < s->uv; i++)
        printf("\n %lf", s->un[i]);
    getchar();
    return 0;
}

/* ********************************************************* */
