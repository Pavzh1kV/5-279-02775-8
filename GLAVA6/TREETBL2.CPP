/* РАБОТА С ДРЕВОВИДНОЙ ТАБЛИЦЕЙ ПОИСКА В ВЕКТОРНОЙ ПАМЯТИ,*/
/*   ЭЛЕМЕНТ - СТРУКТУРА, данные: только КЛЮЧ-ФАМИЛИЯ      */
/* Программа демонстрирует возможности функций \treetbl2.cpp */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <string.h>
#define m 15			/* Размер массива для таблицы */
#define KR struct el
KR
{
    int L;
    char key[20];
    int R;
} Table[m];

void IniTable(KR * T, int k);	/* инициализация таблицы */
int Insert(KR * T, char *key);	/* включение элемента */
int Search(KR * T, char *key);	/* поиск элемента */
int Del_El(KR * T, char *key);	/* удаление элемента */
int Save_Tbl(KR * T, int n);	/* сохранение таблицы в файле */
void Preorder(KR * T, int k);	/* нисходящий обход дерева */
void Postorder(KR * T, int k);	/* восходящий обход дерева */
void Inorder(KR * T, int k);	/* смешанный обход дерева */
KR *Rd_Tbl(void);		/* чтение таблицы из файла */
void Wait_Entr(void);		/* ждать до нажатия ввода */
FILE *fin, *fout;
/* ========================================================= */
/*  ГЛАВНАЯ ФУНКЦИЯ  */
main()
{
    setlocale(LC_ALL,"Russian");
    int i, k, n;
    char *key;
    KR *Rable;
    printf
    ("\n  Работа с древовидной таблицей в векторной памяти ");

    /* Инициализация таблицы */
    k = m;
    IniTable(Table, k);

    printf
    ("\n Создание таблицы:ввод ключей(фамилий), конец ввода - **");
    i = 1;
    while (1)
    {
        printf
        ("\nВведите %d-й ключ(фамилию или **) =>",
         i);
        fflush(NULL);
        fgets(key,20,stdin);
        if (strcmp(key, "**") == 0)	/* конец ввода? */
            break;		/* да, таблица создана */
        k = Insert(Table, key);	/* включение элемента */
        if (k == -1)		/* повторяющийся ключ? */
            printf("\n Kлюч %s уже есть", key);
        else if (k == -2)  	/* Таблица переполнена? */
        {
            printf
            ("\nТаблица переполнена, ключ %s отвергается",
             key);
            getchar();
            break;
        }

        else
        {
            printf("\nКлюч %s включен в таблицу", key);
            i++;
        }
    }

    printf
    ("\n Контрольная печать сформированной таблицы");
    n = i - 1;			/* число элементов в таблице */
    for (i = 0; i < n + 2; i++)
        printf("\n%d\t %d\t %s\t %d", i, Table[i].L, Table[i].key,
               Table[i].R);
    Wait_Entr();

    /* Показ результатов обходов дерева */
    printf("\n     Обходы дерева:");
    printf("\n Левый нисходящий обход");
    Preorder(Table, Table[0].L);
    Wait_Entr();
    printf("\n Левый восходящий обход");
    Postorder(Table, Table[0].L);
    Wait_Entr();
    printf("\n Левый смешанный обход");
    Inorder(Table, Table[0].L);
    Wait_Entr();

    /*  Сохранение таблицы в файле */
    Save_Tbl(Table, m - 2);

    /*  Чтение таблицы из файла. Если файл не открыт,
       то последующие операции не выполняются  */
    if ((Rable = Rd_Tbl()) != NULL)
    {
        printf
        ("\n Нисходящий обход считанного дерева");
        Preorder(Rable, Rable[0].L);

        /* Удаление элементов по заданным ключам */
        printf
        ("\n Удаление элементов, конец удаления - **");
        while (1)
        {
            printf("\nВведите  ключ или ** =>");
            fflush(NULL);
            fgets(key,20,stdin);
            if (strcmp(key, "**") == 0)
                break;
            k = Del_El(Rable, key);
            printf("\n k=%d", k);
            printf
            ("\n Таблица после удаления ключа");
            for (i = 0; i < n + 2; i++)
                printf("\n%d\t %d\t %s\t %d", i, Rable[i].L, Rable[i].key,
                       Rable[i].R);
            Wait_Entr();
        }

        /* Добавление элементов с заданными ключами */
        printf
        ("\n Добавление :ввод ключей, конец ввода - **");
        i = Rable[1].L + 1;
        while (1)
        {
            printf("\nВведите %d-й ключ или ** =>", i);
            fflush(NULL);
            fgets(key,20,stdin);
            if (strcmp(key, "**") == 0)
                break;
            k = Insert(Rable, key);
            if (k == -1)
                printf("\n Kлюч %s уже есть", key);
            else if (k == -2)
            {
                printf
                ("\nТаблица переполнена, ключ %s отвергается",
                 key);
                getchar();
                break;
            }
            else
            {
                printf("\nКлюч %s включен в таблицу",
                       key);
                i++;
            }
        }

        printf
        ("\n Вывод таблицы после добавления элементов");
        n = Rable[1].R;		/* число элементов в таблице */
        for (i = 0; i < n + 2; i++)
            printf("\n%d\t %d\t %s\t %d", i, Rable[i].L, Rable[i].key,
                   Rable[i].R);
        Wait_Entr();

        /* Поиск элементов по заданным ключам */
        printf
        ("\n Поиск элементов по ключу, конец поиска - **");
        while (1)
        {
            printf("\nВведите  ключ или ** =>");
            fflush(NULL);
            fgets(key,20,stdin);
            if (strcmp(key, "**") == 0)
                break;
            k = Search(Rable, key);
            if (k > 0)
                printf(" \nКлюч %s найден, k= %d", Rable[k].key,
                       k);
            else if (k == -2)
                printf("\n Таблица пустая");
            else
                printf("\nКлюч %s не найден", key);
            getchar();
            printf
            ("\n Отладочная печать таблицы после поиска");
            for (i = 0; i < n + 2; i++)
                printf("\n%d\t %d\t %s\t %d", i, Rable[i].L, Rable[i].key,
                       Rable[i].R);
            Wait_Entr();
        }
    }
    return 0;
}

/* ========================================================= */
/* ИНИЦИАЛИЗАЦИЯ ТАБЛИЦЫ */
void IniTable(KR * T, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        T[i].L = 0;
        strcpy(T[i].key, "f");
        T[i].R = i + 1;
    }
    T[0].R = 2;
    T[1].R = n - 2;
}

/* ================================================= */
/* ВКЛЮЧЕНИЕ ЗАПИСИ В ТАБЛИЦУ */
int Insert(KR * T, char *key)
{
    int i, j;
    /*  *****  Таблица полная   ***** */
    if (T[1].L == T[1].R)	/* если таблица полная */
        return -2;
    /*  *****  Таблица пустая  *****  */
    if (T[1].L == 0)
    {
        j = T[0].R;		/* первая строка в списке пустых */
        T[0].L = j;		/* она станет корнем дерева - началом списка занятых */
    }
    else  			/*  *****  Таблица заполнена частично  *****  */
    {
        i = T[0].L;		/* Вершина дерева */
        /* Ищем ключ или место включения нового элемента */
        while (1)
        {
            int p = strcmp(key, T[i].key);
            if (p == 0)		/* Такой ключ уже есть */
                return -1;
            if (p < 0)
                if (T[i].L == 0)  	/* ключа нет, новый элемент - левый потомок */
                {
                    j = T[0].R;	/* первая свободная строка для нового эл-та */
                    T[i].L = j;	/* указатель на новый эл-т в левой ветви */
                    break;
                }
                else
                    i = T[i].L;
            else if (T[i].R == 0)  	/* ключа нет, новый элемент - правый потомок */
            {
                j = T[0].R;	/* свободная строка для нового элемента */
                T[i].R = j;	/* указатель на новый эл-т в правой ветви */
                break;
            }
            else
                i = T[i].R;
        }
    }
    T[0].R = T[j].R;		/* корректировка списка свободных элементов */
    /* В свободной строке формируем  элемент с заданным ключом */
    strcpy(T[j].key, key);	/* данные элемента */
    T[j].L = 0;
    T[j].R = 0;			/* обнуление указателей */
    T[1].L++;			/* счетчик занятых элементов */
    return j;			/* возвращаем номер строки нового элемента */
}

/* =========================================================== */
/*  ПОИСК ЭЛЕМЕНТА ПО КЛЮЧУ */
int Search(KR T[], char *key)
{
    int j, p;
    if (T[1].L == 0)		/* если таблица пустая */
        return -2;
    j = T[0].L;			/* вершина дерева */
    while (1)
    {
        p = strcmp(key, T[j].key);
        if (p == 0)		/*  ключ найден  */
            return j;
        if (p < 0)
        {
            if (T[j].L != 0)
            {
                j = T[j].L;
                continue;
            }
            else
                return -1;	/* ключ не найден */
        }
        if (p > 0)
        {
            if (T[j].R != 0)
            {
                j = T[j].R;
                continue;
            }
            else
                return -1;
        }
    }
}

/* ========================================================= */
/*  УДАЛЕНИЕ ЭЛЕМЕНТА ПО КЛЮЧУ */
int Del_El(KR * T, char *key)
{
    int j, i, r, *p;
    if (T[1].L == 0)		/* если таблица пустая */
        return -2;
    j = T[0].L;
    p = &T[0].L;		/* адрес предыдущего указателя */
    while (1)
    {
        if (strcmp(key, T[j].key) == 0)  	/*  ключ найден  */
        {
            r = j;
            break;
        }
        if (strcmp(key, T[j].key) < 0)
        {
            if (T[j].L != 0)
            {
                p = &T[j].L;
                j = T[j].L;
                continue;
            }
            else
            {
                r = -1;
                break;
            }			/* ключ не найден */
        }
        if (strcmp(key, T[j].key) > 0)
        {
            if (T[j].R != 0)
            {
                p = &T[j].R;
                j = T[j].R;
                continue;
            }
            else
            {
                r = -1;
                break;
            }
        }
    }
    if (r == -1)		/* ключ не найден */
        return (r);
    /* Элемент найден в строке j, удалим его */
    if ((T[j].L == 0) && (T[j].R == 0))	/* элемент - лист дерева */
        if (j == T[0].L)	/* элемент - корень дерева */
            T[0].L = 0;
        else
            *p = 0;		/* элемент - лист дерева */
    else if ((T[j].L != 0) && (T[j].R != 0))  	/* Элемент в узле с двумя ветвями */
    {
        /* 1) Шаг влево вниз на один уровень.
           2) Затем вправо вниз до конца.
           3) Данные из конечного элемента пересылаем в удаляемый элемент.
           4) Левый указатель конечного элемента пересылаем в указатель
           предыдущего элемента (в левый или правый, откуда пришли). */
        p = &T[j].L;
        i = T[j].L;		/* шаг влево вниз */
        while (1)		/* Вправо вниз до конца */
            if (T[i].R != 0)
            {
                p = &T[i].R;
                i = T[i].R;
            }
            else
                break;
        strcpy(T[j].key, T[i].key);	/* переслали данные */
        *p = T[i].L;
        j = i;			/* для очистки строки */
    }
    else   /* элемент в узле с одной ветвью */
        if (j ==
                T[0].L)
            T[0].L = (T[j].L == 0) ? T[j].R : T[j].L;
        else
            *p = (T[j].L == 0) ? T[j].R : T[j].L;
    /* Освободим строку и скорректируем счетчик и указатели */
    T[1].L--;			/* счетчик занятых элементов таблицы */
    T[j].R = T[0].R;		/* корректировка списка свободных    */
    T[0].R = j;			/* элементов */
    T[j].L = 0;
    strcpy(T[j].key, "f");	/* чистка освобождаемой строки */
    return r;
}

/* =============================================================== */
void Wait_Entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* =============================================================== */
/* СОХРАНЕНИЕ  ДРЕВОВИДНОЙ ТАБЛИЦЫ ПОИСКА В ФАЙЛЕ */
int Save_Tbl(KR * T, int n)
{
    int i;
    char name[40];
    printf
    ("\n Сохранение таблицы в файле.\n Введите имя файла =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fout = fopen(name, "w")) == 0)
    {
        printf("\n Файл %s не открывается", name);
        Wait_Entr();
        return -1;
    }
    for (i = 0; i < n + 2; i++)
        fprintf(fout, "%d %s %d\n", T[i].L, T[i].key, T[i].R);
    fclose(fout);
    return 0;
}

/* =============================================================== */
/* ЧТЕНИЕ ТАБЛИЦЫ ИЗ ФАЙЛА */
KR *Rd_Tbl(void)
{
    int i, n;
    KR EL0, EL1, *Tbl;
    char name[40];
    printf
    ("\n Чтение таблицы из файла.\n Введите имя файла =>");
    fflush(NULL);
    fgets(name,40,stdin);
    if ((fin = fopen(name, "r")) == 0)
    {
        printf("\n Файл %s не открывается", name);
        Wait_Entr();
        return NULL;
    }
    fscanf(fin, "%d%s%d", &EL0.L, &EL0.key, &EL0.R);
    fscanf(fin, "%d%s%d", &EL1.L, &EL1.key, &EL1.R);
    n = EL1.R;
    n += 2;
    Tbl = (KR *) calloc(n, sizeof(KR));
    Tbl[0] = EL0;
    Tbl[1] = EL1;
    for (i = 2; i < n; i++)
    {
        fscanf(fin, "%d %s %d", &Tbl[i].L, &Tbl[i].key, &Tbl[i].R);
        printf("\n%d %s %d", Tbl[i].L, Tbl[i].key, Tbl[i].R);
    }
    Wait_Entr();
    return Tbl;
}

/* ========================================================== */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА В ТАБЛИЦЕ */
void Preorder(KR * T, int k)
{
    if (k != 0)
    {
        printf("\n key = %s", T[k].key);
        Preorder(T, T[k].L);
        Preorder(T, T[k].R);
    }
}

/* =========================================================== */
/* ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА */
void Postorder(KR * T, int k)
{
    if (k != 0)
    {
        Postorder(T, T[k].L);
        Postorder(T, T[k].R);
        printf("\n key = %s", T[k].key);
    }
}

/* ============================================================ */
/* СМЕШАННЫЙ ОБХОД ДЕРЕВА */
void Inorder(KR * T, int k)
{
    if (k != 0)
    {
        Inorder(T, T[k].L);
        printf("\n key = %s", T[k].key);
        Inorder(T, T[k].R);
    }
}

/* ************************************************************* */
