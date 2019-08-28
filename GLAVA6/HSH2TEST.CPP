/* РАБОТА С ХЕШ-ТАБЛИЦАМИ. Разрешение коллизий методом */
/*  открытой адресации c двойным хешированием          */
/*  Hsh2test.cpp Программа тестирования и анализа */
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>
#include <math.h>
#define N 47
/*char F[50][12]={"Артюхов","Бабичев","Белоусов","Боярков","Бузоверя","Бучнев",
	  "Гайдаров","Голобоков","Григорьев","Дурнев","Жданов","Иванюк","Колосов",
	  "Конорев","Кудявцев","Лобанов","Макаров","МакаровД","Макоклюев",
	  "Маллер","Никоненко","Одерков","Париков","Перчаткин","Роенок",
	  "Сандракула","Севрюков","Семенов","Степанов","Степура","Тремсин",
	  "Туровский","Урубков","Шевеленко","Власко"};*/
char F[50][40] =
{
    "Артюхов", "Антонов", "Адов", "Громов",
    "Аров", "Адамов", "Аглаков", "Абрамов", "Абрамович",
    "Абасов", "Абрам", "Абрамин", "Баринов",
    "Вовов", "Азов", "Дядя", "Елин",
    "Ёлин", "Жлин", "Зоин", "Иванов",
    "Йошкар", "Котов", "Лотов", "Мотов",
    "Нотов", "Отов", "Попов", "Ротов", "Сотов",
    "Титов", "Фёдоров", "Хусаинов", "Цальп",
    "Чугунов", "Шадрина", "Щукин", "Эмма",
    "Ютов", "Яковлев", "Аб", "Ав",
    "Аг", "Ад", "Ае", "Ап",
    "Ац", "Ам", "Ан", "Ал"
};

struct TCadet
{
    char Name[20];
    int Mark[6];
} Table[N];			/* N=47 */
char *menu[9] =
{
    "Добавление элементa",
    "Чтение таблицы из файла",
    "Сохранение таблицы в файле",
    "Поиск записи в таблице",
    "Удаление записи",
    "Отладочная печать таблицы",
    "Заполнение таблицы",
    "Анализ поиска",
    "Конец работы"
};

int Exit = 0;
FILE *fin, *fout;
char *Discipline[6] =
{
    "Социология", "Метрология", "История",
    "Арх-ра ВС", "Психология", "Физ.кул."
};

char Empty[] = "*****";		/* пустая запись */
int MainMenu(void);
void AddRecord(void);
void ClearTable(void);
void ClearRecord(int u);
void DestroyRecord(int u);
int FindRecord(const char *key, int *);
void PrintTable(void);
int Hash(const char *key, int u);
void FullTable(void);
void AnlzFind(void);
/* ====================================================== */
/* ГЛАВНАЯ ФУНКЦИЯ */
main()
{
    setlocale(LC_ALL,"Russian");
    float z;
    system("clear");			/* scanf("\n %f",&z); */
    ClearTable();
    while (!MainMenu());
    return 0;
}

/* ======================================================= */
/* ОБНУЛЕНИЕ ЗАПИСИ */
void ClearRecord(int u)
{
    strcpy(Table[u].Name, Empty);
    for (int j = 0; j <= 5; j++)
        Table[u].Mark[j] = 0;
}

/* ======================================================= */
/* УДАЛЕНИЕ ЗАПИСИ */
void DestroyRecord(int u)
{
    strcpy(Table[u].Name, "ffff");
    for (int j = 0; j <= 5; j++)
        Table[u].Mark[j] = 0;
}

/* ======================================================= */
/* ОБНУЛЕНИЕ ТАБЛИЦЫ */
void ClearTable(void)
{
    for (int i = 0; i < N; i++)
        ClearRecord(i);
}

/* ======================================================= */
/* ДВОЙНОЕ ХЕШИРОВАНИЕ */
int Hash(const char *key, int u)
{
    return ((unsigned int) key[0] % N +
            u * ((unsigned int) key[1] % (N - 1) + 1)) % N;
}

/* ======================================================= */
/* СЧИТЫВАНИЕ ИЗ ФАЙЛА */
int ReadFromFile()
{
    char name[50];
    ClearTable();
    printf("\n Введите имя файла : ");
    scanf("%s", name);
    if (!(fin = fopen(name, "r+")))
    {
        printf(" Файл %s не открыт", name);
        getchar();
        return -1;
    }
    for (int i = 0; i < N; i++)
    {
        fscanf(fin, "%s %d %d %d %d %d %d\n", &Table[i].Name,
               &Table[i].Mark[0], &Table[i].Mark[1], &Table[i].Mark[2],
               &Table[i].Mark[3], &Table[i].Mark[4], &Table[i].Mark[5]);
    }
    fclose(fin);
    return 0;
}

/* ========================================================= */
/* ЗАПИСЬ ТАБЛИЦЫ В ФАЙЛ */
int WriteToFile()
{
    char name[50];
    printf("\nВведите имя файла : ");
    scanf("%s", name);
    if (!(fout = fopen(name, "w+")))
    {
        printf(" Файл %s не открыт", name);
        return -1;
    }
    for (int i = 0; i < N; i++)
    {
        fprintf(fout, "%s %d %d %d %d %d %d\n", Table[i].Name,
                Table[i].Mark[0], Table[i].Mark[1], Table[i].Mark[2],
                Table[i].Mark[3], Table[i].Mark[4], Table[i].Mark[5]);
    }
    fclose(fout);
    return 0;
}

/* ====================================================== */
/* ВЫВОД ОДНОЙ ЗАПИСИ */
void PrintRecord(int u)
{
    system("clear");
    printf("\nФамилия: %s", Table[u].Name);
    for (int i = 0; i <= 5; i++)
        printf("\nОценка по дисц. \"%s\": %d", Discipline[i],
               Table[u].Mark[i]);
}

/* ======================================================== */
/* ОТЛАДОЧНАЯ ПЕЧАТЬ ТАБЛИЦЫ */
void PrintTable(void)
{
    system("clear");
    printf("№п/п    Фамилия %s %s %s %s %s %s\n",
           Discipline[0],
           Discipline[1],
           Discipline[2], Discipline[3], Discipline[4], Discipline[5]);
    for (int i = 0; i < N; i++)
    {
        printf(" %2d. %10s %8d %8d %8d %8d %8d %8d\n",
               i + 1, Table[i].Name, Table[i].Mark[0], Table[i].Mark[1],
               Table[i].Mark[2], Table[i].Mark[3], Table[i].Mark[4],
               Table[i].Mark[5]);
        if (!((i + 1) % 24))
        {
            getchar();
            system("clear");
            printf("№п/п    Фамилия %s %s %s %s %s %s\n",
                   Discipline[0],
                   Discipline[1],
                   Discipline[2], Discipline[3], Discipline[4],
                   Discipline[5]);
        }
    }
    getchar();
}

/* ================================================= */
/* ПОИСК ЗАПИСИ ПО КЛЮЧУ */
int FindRecord(const char *key, int *rep)
{
    int i, a;
    for (i = 0; i <= N; i++)
    {
        a = Hash(key, i);
        *rep = i;
        if (!strcmp(Table[a].Name, key))
            return a;
        if (!strcmp(Table[a].Name, Empty))
            return -1;
    }
    return -1;
}

/* ==================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int MainMenu(void)
{
    char name[50];
    int i, r;
    for (i = 0; i < 9; i++)
        printf("\n%d. %s", i + 1, menu[i]);
    printf("\nВведите номер строки");
    switch (getchar())
    {
    case '1':
        AddRecord();
        break;
    case '2':
        if (!ReadFromFile())
            printf("Таблица считана.");
        getchar();
        break;
    case '3':
        WriteToFile();
        printf("Таблица сохранена.\n");
        getchar();
        break;
    case '4':
        printf("\nВведите фамилию для поиска:");
        scanf("%s", name);
        i = FindRecord(name, &r);
        printf("\nft=%d", r + 1);
        getchar();
        if (i != -1)
            PrintRecord(i);
        else
            printf("\n %s не найден в таблице\n", name);
        getchar();
        break;
    case '5':
        printf("\nВведите фамилию для удаления:");
        scanf("%s", name);
        i = FindRecord(name, &r);
        if (i != -1)
        {
            DestroyRecord(i);
            printf
            ("\n %s успешно удалён из таблицы\n",
             name);
        }
        else
            printf("\n %s не найден в таблице\n", name);
        getchar();
        break;
    case '6':
        PrintTable();
        break;
    case '7':
        FullTable();
        break;
    case '8':
        AnlzFind();
        break;
    case '9':
        return 1;
    default:
        printf
        ("\nОшибка в номере! Повторите ввод.");
        getchar();
    }
    system("clear");
    return 0;
}

/* ======================================================= */
/* ФУНКЦИЯ ЗАПОЛНЕНИЯ ОДНОЙ ЗАПИСИ В ТАБЛИЦЕ */
TCadet Input(void)
{
    TCadet tmp;
    system("clear");
    printf("\n Введите данные о студенте:\n");
    printf("Фамилия:");
    scanf("%s", tmp.Name);
    for (int i = 0; i <= 5; i++)
    {
        printf("Оценка по дисц.\"%s\":", Discipline[i]);
        scanf("%d", &tmp.Mark[i]);
        if ((tmp.Mark[i] < 2) || (tmp.Mark[i] > 5))
        {
            printf
            ("Оценка - целое число от 2 до 5!\n");
            i--;
        }
    }
    return tmp;
}

/* ===================================================== */
/* ДОБАВЛЕНИЕ ЭЛЕМЕНТА В ТАБЛИЦУ */
void AddRecord(void)
{
    int j, a, r;
    static TCadet tmp;
    printf("\n Добавление элемента в таблицу\n");
    tmp = Input();
    if (FindRecord(tmp.Name, &r) >= 0)
    {
        printf("\n Добавление записи в таблицу невозможно -\
  запись %s уже есть!\n",
               tmp.Name);
        getchar();
        return;
    }
    for (j = 0; j <= N; j++)
    {
        a = Hash(tmp.Name, j);
        if (!strcmp(Table[a].Name, Empty)
                || !strcmp(Table[a].Name, "ffff"))
        {
            Table[a] = tmp;
            printf
            ("\n %s успешно включен в таблицу a=%d\n",
             tmp.Name, a);
            getchar();
            return;
        }
    }
    printf
    ("\n Включить %s не удалось. Нет свободных ячеек.\n",
     tmp.Name);
    getchar();
}

/* ========================================================= */
/* ЗАПОЛНЕНИЕ ТАБЛИЦЫ ЗАПИСЯМИ ИЗ МАССИВА. Задавая различные */
/* значения n - число включаемых элементов, и N - число эле- */
/* ментов в таблице, т.е. изменяя коэффициент заполнения таб-*/
/* лицы n/N, можно проследить за изменением суммарного числа */
/* шагов: kk - для определения того, не является ли включаемый*/
/* элемент дублирующим, sum - для включения новых элементов. */
/* mk и ms - среднее число попыток на один включаемый элемент*/
void FullTable(void)
{
    int i, j, pk, pe, a, r, n, sum = 0;
    static TCadet tmp;
    static int kk = 0;
    printf("\n Добавление элементов в таблицу");
    n = 47;			/* число включаемых элементов в таблицу размером N */
    for (i = 0; i < n; i++)
    {
        pk = FindRecord(F[i], &r);
        kk = kk + r + 1;
        if (pk >= 0)
        {
            printf("\n Добавление записи в таблицу невозможно -\
 запись %s уже есть!\n",
                   F[i]);
            getchar();
            continue;
        }
        pe = 1;
        strcpy(tmp.Name, F[i]);
        for (j = 0; j <= N; j++)
        {
            a = Hash(F[i], j);
            if (!strcmp(Table[a].Name, "ffff")
                    || !strcmp(Table[a].Name, Empty))
            {
                tmp.Mark[0] = j + 1;
                Table[a] = tmp;
                sum = sum + j + 1;
                printf("\n %s  включен в таблицу a=%d",
                       tmp.Name, a);
                pe = 0;
                getchar();
                break;
            }
        }
        if (pe)
        {
            printf
            ("\n Включить %s не удалось. Нет свободных ячеек.\n",
             tmp.Name);
            getchar();
        }
    }
    printf("\n kk=%d mk=%f sum=%d ms=%f", kk, (float) kk / n, sum,
           (float) sum / n);
    kk = 0;
    getchar();
}

/* ================================================================== */
/* Анализ операции поиска записей */
void AnlzFind(void)
{
    int i, r, p, sumtimep = 0, sumtimem = 0;
    for (i = 0; i < 47; i++)
    {
        p = FindRecord(F[i], &r);
        if (p >= 0)
            sumtimep += r + 1;
        else
            sumtimem += r + 1;
    }
    printf("\n sumtimep=%d sumtimem=%d", sumtimep, sumtimem);
    getchar();
}

/* ****************************************************************** */
