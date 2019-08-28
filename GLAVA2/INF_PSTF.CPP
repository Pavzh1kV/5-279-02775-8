/* РАБОТА СО СТЕКОМ В ВЕКТОРНОЙ ПАМЯТИ, преобразование
	арифметического выражения в обратную польскую запись.
	 \inf_pstf.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#include <math.h>
typedef struct
{
    char op;			/* знак операции */
    int pr;			/* приоритет операции */
} EL;
EL tabl[8] =
{
    {'(', 0}, {')', 1}, {'=', 2}, {'+', 3}, {'-', 3}, {'*', 4}, {'/', 4},
    {'^', 5}
};

#include "incl_stc.c"	/* файл включения */
int Scan(STC * s);
void Rez(char *s);
EL e;
char stropz[80];
/* ===================== ГЛАВНАЯ ФУНКЦИЯ ==================== */
int main()
{
    setlocale(LC_ALL,"Russian");
    int i;
    char isstr[100];
    printf
    ("\n Преобразование арифметического выражения в \
 обратную польскую запись\n");
    if (Crt_stc(&s1) == -1)
        return -1;
    if (Scan(&s1) == -1)
    {
        printf("\n Ошибка в выражении!!!\n");
        getchar();
        return -1;
    }
    return 0;
}

/* ============================================================== */
/* СКАНИРОВАНИЕ ИСХОДНОЙ СТРОКИ С АРИФМЕТИЧЕСКИМ ВЫРАЖЕНИЕМ */
int Scan(STC * s)
{
    char c;
    int i, j, k;
    char str[] = "+-*/^()=";	/* строка знаков операций */
    char *cp;
    (s->un)->pr = -1;
    (s->un)->op = ' ';
    s->uv = 0;
    fflush(NULL);
    printf
    ("\n Введите арифметическое выражение, завершающееся знаком '='\n=>");
    j = 0;
    while (1)
    {
        i = 0;
        while (1)  		/* удаляем  пробелы */
        {
            c = getchar();
            if (c == ' ')
                continue;
            else
                break;
        }
        while (1)
        {
            cp = strchr(str, c);	/* это знак операции */
            if (cp == 0)  	/* нет, формируем операнд в выходной строке */
            {
                stropz[j++] = c;
                c = getchar();
                if (c != ' ')
                    continue;
                else
                    stropz[j++] = ' ';	/* конец операнда определился пробелом */
                Rez(stropz);
                break;
            }
            else  		/* конец операнда определился знаком операции */
            {
                stropz[j++] = ' ';
                if (c == '=')  	/* конец выражения, выдаем результат */
                {
                    while (1)
                    {
                        k = Pop_el(s, &e);
                        if (k == 0)
                        {
                            stropz[j++] = e.op;
                            continue;
                        }
                        stropz[j++] = '=';
                        stropz[j] = '\0';
                        break;
                    }
                    Rez(stropz);
                    getchar();
                    return 0;
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
                    Peek_el(s, &e);
                    if (tabl[k].pr == 0 || tabl[k].pr > e.pr)
                    {
                        Push_el(s, tabl[k]);
                        if (tabl[k].pr == 1)  	/* закрыв. скобка ) */
                        {
                            Pop_el(s, &e);
                            Pop_el(s, &e);
                        }
                        break;
                    }
                    else
                    {
                        Pop_el(s, &e);
                        stropz[j++] = e.op;
                        continue;
                    }
                }
            }
            Rez(stropz);
            break;
        }
    }
    return 0;
}

/* ======================================================== */
/* ВЫВОД ВЫХОДНОЙ СТРОКИ */
void Rez(char *s)
{
    printf("\n Результат =%s", stropz);
}

/* ========================================================= */
/* ВЫВОД СОДЕРЖИМОГО СТЕКА  (для отладки) */
int Show_stc(STC * s)
{
    int i;
    if (s->un == NULL)
        return -1;
    printf("\n");
    for (i = 0; i < s->m; i++)
        printf("\n %c %d", s->un[i].op, s->un[i].pr);
    getchar();
    return 0;
}

/* ********************************************************* */
