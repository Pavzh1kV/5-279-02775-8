/* ******************************************************* */
/* РАБОТА С ХЕШ-ТАБЛИЦАМИ. Адрес входа в таблицу (индекс): */
/* двоичное значение первой буквы названия государства-128.*/
/* Конфликтные записи помещаются во внешнюю динамическую   */
/* цепочку. Записи по данному входу упорядочены.           */
/* \HTBL_GOS.CPP */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define KR struct el_type
#define  k  7
KR
{
    char Gos[20];
    char Stl[20];
    int Pl, Nas;
    KR *Ptr;
} Ved[32], EL;

int i, p = 1;
char *menu[k][40];
unsigned char q = 'А', r = 'Я';	/* А и Я - русский алфавит */
char key[81];
void Ini_Tbl(KR * T);		/* Инициализация таблицы - создание пустой */
void Crt_Tbl(KR * T);		/* Заполнение таблицы */
KR *Input_El(KR * T);		/* Ввод данных о государстве */
int Show_El(KR * T);		/* Вывод элемента  */
void Show_Tbl(KR * T);		/* Вывод таблицы */
int Del(KR * T);		/* Удаление элемента */
int Search(KR * T);			/* Поиск элемента в таблице */
void Wait_Entr(void);		/* Ожидание нажатия клавиши ввода */
int Main_Menu(void);		/* Вывод главного меню */
KR *T, *R, Table[32];
int In = 0;
int count = 0;
/* =============================================================== */
/* ГЛАВНАЯ ФУНКЦИЯ */
int main(void)
{
    setlocale(LC_ALL,"Russian");
    p = 1;
    T = Ved;
    *menu[0] = "1. Инициализация таблицы";
    *menu[1] = "2. Заполнение таблицы";
    *menu[2] = "3. Поиск государства";
    *menu[3] = "4. Удаление государства";
    *menu[4] = "5. Вывод таблицы на экран";
    *menu[5] = "6. Окончание работы";
    *menu[6] = "   Введите номер пункта меню";
    system("clear");
    printf(" Работа со таблицей государств\n");
    while (p)
    {
        Main_Menu();
        system("clear");
    }
    printf("Конец работы со таблицей \n");
    Wait_Entr();
    return 0;
}

/* ========================================================= */
int Main_Menu(void)
{
    int ns, i;
    KR *TEK;
    while (1)
    {
        fflush(NULL);
        for (i = 0; i < k; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns >= k)
        {
            system("clear");
            printf
            ("\n ОШИБКА в номере!! Будьте внимательны.");
            continue;
        }
        if (In == 0 && ns != 1 && ns != 6)
        {
            system("clear");
            printf
            ("\n Сначала инициализируйте таблицу ");
            continue;
        }
        break;
    }
    switch (ns)
    {
    case 1:
        Ini_Tbl(T);
        break;
    case 2:
        Crt_Tbl(T);
        break;
    case 3:
        Search(T);
        break;
    case 4:
        Del(T);
        break;
    case 5:
        Show_Tbl(T);
        break;
    case 6:
        p = 0;
    }
    return 0;
}

/* ====================================================== */
/* ИНИЦИАЛИЗАЦИЯ ТАБЛИЦЫ - СОЗДАНИЕ ПУСТОЙ ТАБЛИЦЫ */
void Ini_Tbl(KR * T)
{
    int i;
    for (i = 0; i < 33; i++)
    {
        strcpy(T[i].Gos, "f");
        strcpy(T[i].Stl, 0);
        T[i].Pl = T[i].Nas = 0;
        T[i].Ptr = NULL;
        In = 1;			/* признак инициализации таблицы */
    }
}

/* ======================================================== */
/* ВВОД ДАННЫХ О ГОСУДАРСТВЕ */
KR *Input_El(KR * T)
{
    while (1)
    {
        printf("\n Введите государство или ** =>");
        fflush(NULL);
        fgets(T->Gos,20,stdin);
        if (strcmp(T->Gos, "**") == 0)
            return NULL;
        /* Название государства с заглавной буквы русского алфавита? */
        if ((unsigned char) T->Gos[0] < q || (unsigned char) T->Gos[0] > r)
        {
            printf("\n ОШИБКА  ");
            continue;
        }
        break;
    }
    printf("\n Введите столицу государства=>");
    fflush(NULL);
    scanf("%s", &T->Stl);
    printf("\n Введите площадь государства=>");
    fflush(NULL);
    scanf("%d", &T->Pl);
    printf
    ("\n Введите численность населения=>");
    fflush(NULL);
    scanf("%d", &T->Nas);
    return T;
}

/* ===================================================== */
/* ЗАПОЛНЕНИЕ ТАБЛИЦЫ */
void Crt_Tbl(KR * T)
{
    KR *t, RAB, *TEK, *PRED, *NEW;
    int a;
    while (1)
    {
        printf("\n Ввод данных о %d-м государстве",
               count + 1);
        t = Input_El(&EL);
        if (t == NULL)
            break;
        a = (unsigned char) t->Gos[0] - q;	/* а - индекс входа в таблицу */
        /* Если строка свободна, включаем туда */
        if (T[a].Gos[0] == 'f')
        {
            T[a] = *t;
            T[a].Ptr = NULL;
            count++;
            continue;
        }
        /* Если элемент с меньшим ключом, то его включаем в строку,
           а  элемент из строки включим в список */
        if (strcmp(t->Gos, T[a].Gos) < 0)
        {
            RAB = T[a];
            T[a] = *t;
            T[a].Ptr = RAB.Ptr;
            *t = RAB;
            t->Ptr = NULL;
        }
        /* Найдем место включения в списке и включим туда */
        TEK = T[a].Ptr;
        PRED = &T[a];
        while ((TEK != NULL) && (strcmp(TEK->Gos, t->Gos) < 0))
        {
            PRED = TEK;
            TEK = TEK->Ptr;
        }
        NEW = (KR *) calloc(1, sizeof(KR));
        *NEW = *t;
        NEW->Ptr = TEK;
        PRED->Ptr = NEW;
        count++;
        continue;
    }
    printf("\n Таблица заполнена\n");
    Wait_Entr();
}

/* ============================================================= */
/* ВЫВОД ТАБЛИЦЫ НА ЭКРАН */
void Show_Tbl(KR * T)
{
    KR *TEK, *Ptr;
    printf("\n Таблица государств");
    for (i = 0; i < 32; i++)
    {
        if (T[i].Gos[0] != 'f')
            printf("\n Gos=%s Stl=%s Pl=%d Nas=%d",
                   T[i].Gos, T[i].Stl, T[i].Pl, T[i].Nas);
        TEK = &T[i];
        while (TEK->Ptr != NULL)
        {
            TEK = TEK->Ptr;
            printf("\n Gos=%s Stl=%s Pl=%d Nas=%d",
                   TEK->Gos, TEK->Stl, TEK->Pl, TEK->Nas);
        }
    }
    getchar();
}

/* ======================================================= */
/* ПОИСК ЭЛЕМЕНТА В ТАБЛИЦЕ ПО ЗАДАННОМУ КЛЮЧУ */
int Search(KR * T)
{
    char name[20];
    int a;
    KR *TEK;
    while (1)
    {
        printf
        ("\n Введите государство для поиска =>");
        fflush(NULL);
        fgets(name,40,stdin);
        if ((unsigned char) name[0] < q || (unsigned char) name[0] > r)
        {
            printf("\n ОШИБКА !! ");
            continue;
        }
        break;
    }
    a = (unsigned char) name[0] - q;
    if (T[a].Gos[0] == 'f')
    {
        printf("\n Государство %s не найдено", name);
        getchar();
        return -1;
    }
    TEK = &T[a];
    while ((TEK != NULL) && (strcmp(TEK->Gos, name) != 0))
        TEK = TEK->Ptr;
    if (TEK == 0)
    {
        printf("\n Государство %s не найдено", name);
        getchar();
        return -1;
    }
    else
        Show_El(TEK);
    return 0;
}

/* ======================================================= */
int Show_El(KR * R)
{
    if (R == NULL)
    {
        printf("\n Нет его ");
        Wait_Entr();
        return -1;
    }
    printf("\n Gos=%s Stl=%s Pl=%d Nas=%d", R->Gos, R->Stl, R->Pl, R->Nas);
    Wait_Entr();
    return 0;
}

/* ======================================================== */
/* Ожидание нажатия клавиши ввода */
void Wait_Entr(void)
{
    printf("\n Нажмите ввод");
    fflush(NULL);
    getchar();
}

/* ======================================================== */
/* УДАЛЕНИЕ ГОСУДАРСТВА */
int Del(KR * T)
{
    char name[20];
    int a;
    KR *TEK, *PRED, *R;
    while (1)
    {
        printf
        ("\n Введите государство для удаления =>");
        fflush(NULL);
        fgets(name,40,stdin);
        if ((unsigned char) name[0] < q || (unsigned char) name[0] > r)
        {
            printf("\n ОШИБКА !! ");
            continue;
        }
        break;
    }
    a = (unsigned char) name[0] - q;	/* индекс входа в таблицу */
    TEK = &T[a];
    PRED = NULL;
    /* Поиск государства по данному входу */
    while ((TEK != NULL) && (strcmp(TEK->Gos, name) != 0))
    {
        PRED = TEK;
        TEK = TEK->Ptr;
    }
    /* Государство не найдено */
    if (TEK == NULL)
    {
        printf("\n Государство  %s не найдено", name);
        getchar();
        return -1;
    }

    /* Государство найдено, уточняем, где  */
    if (PRED == NULL)  		/* государство в строке таблицы */
    {
        if (TEK->Ptr == 0)  	/* цепочки нет */
        {
            T[a].Gos[0] = 'f';
            count--;
            T[a].Ptr = NULL;
        }
        else  		/* цепочка есть */
        {

            R = TEK->Ptr;
            T[a] = *TEK->Ptr;
            free(R);
            count--;
        }
    }
    else  			/* государство в цепочке */
    {

        PRED->Ptr = TEK->Ptr;
        free(TEK);
        count--;
    }
    Show_Tbl(T);
    return 0;
}

/* ********************************************************** */
