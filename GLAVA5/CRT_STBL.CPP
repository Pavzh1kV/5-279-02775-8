/* **************************************************** */
/* Создание упорядоченной таблицы о государствах.
	Упорядочение осуществляется в процессе ввода записей */
/* Crt_stbl.cpp  */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define Rec struct r_e
Rec
{
    char Gos[25];
    char Stl[25];
    int Pl, Nas;
} El;

Rec *Crt_tbl(int m);
int In_Data(void);
void Show_Tbl(Rec * T, int m);
/* ======================================================= */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    int m;
    Rec *T;
    printf
    ("\n Создание упорядоченной таблицы о государствах");
    while (1)
    {
        printf
        ("\n Введите число элементов таблицы\n=>");
        fflush(NULL);
        if ((scanf("%d", &m) == 0) || (m < 1))
        {
            printf("\n ОШИБКА !!!");
            continue;
        }
        else
            break;
    }
    T = Crt_tbl(m);
    printf("\n Упорядоченная таблица");
    Show_Tbl(T, m);
    free(T);
    T = NULL;
    printf("\n  Конец pаботы \n");
    getchar();
    return 0;
}

/* =============================================== */
/* СОЗДАНИЕ УПОРЯДОЧЕННОЙ ТАБЛИЦЫ О ГОСУДАРСТВАХ,
   данные вводятся в диалоге */
Rec *Crt_tbl(int m)
{
    int j, i;
    Rec R, *A;
    /* Получение памяти под таблицу */
    if ((A = (Rec *) calloc(m + 1, sizeof(Rec))) == NULL)
    {
        printf("\n Память не выделена");
        getchar();
        return NULL;
    }
    for (i = 0; i < m; i++)
    {
        if (In_Data() != 0)
            break;
        else
        {
            A[i] = R = El;
            j = i - 1;
            while (j >= 0 && (strcmp(R.Gos, A[j].Gos) < 0))
            {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = R;
        }
        getchar();
    }
    printf("\n Таблица создана ");
    return A;
}

/* ===================================================== */
/* ВВОД ДАННЫХ О ГОСУДАРСТВЕ, данные вводятся в диалоге */
int In_Data(void)
{
    fflush(NULL);
    printf
    ("\n Введите данные о государстве или ** для прекращения ввода:");
    printf("\n Государство=>");
    fflush(NULL);
    fgets(El.Gos,25,stdin);
    if (strcmp(El.Gos, "**") == 0)
        return 1;
    else
    {
        printf(" Столица=>");
        fgets(El.Stl,25,stdin);
        printf(" Площадь государства=>");
        scanf("%d", &El.Pl);
        printf(" Численность населения=>");
        scanf("%d", &El.Nas);
        return 0;
    }
}

/* ====================================================== */
/* ПОКАЗ ТАБЛИЦЫ  */
void Show_Tbl(Rec * T, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        printf("\n %s %s %d %d", T[i].Gos, T[i].Stl, T[i].Pl, T[i].Nas);
        getchar();
    }
    getchar();
}

/* ********************************************************** */
