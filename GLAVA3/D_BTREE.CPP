/* ************************************************* */
/* РАБОТА С В_ДЕРЕВЬЯМИ. Элемент - структура, ключ - */
/* символьная строка.    Используется файл включения */
/* Диалоговая программа, пример использования функций*/
/*  \tree\d_btree.cpp        */
/* ================================================= */
#define N 2			// N - порядок В-дерева
typedef struct EL		// структура данных в элементе
{
    char fam[20];		// ключ - фамилия, символьная строка
    char nmb[15];		// номер телефона
    int code;			// числовой код владельца
};
typedef EL DT;			// тип структуры данных, для связи
// с файлом включения
#define Skey fam		// идентификатор поля ключа, для
// связи с файлом включения
void prnt(EL);			// обработчик элементов (печать)
void handler(EL);		// обработчик элементов
#include "BTREE.H"	// файл включения
Page *T, *A, *B, *C;		//указатели деревьев
EL x;
int In_Data(EL *);		//ввод данных элемента
int Main_Menu(void);		//управление меню
void Wait_Entr(void);		//ожидание нажатия ввода
void Select_Tree(void);		//выбор активного дерева
void Crt_Btree(void);		//создание выбранного дерева
void Prnt(void);		//вывод сообщения "на стадии разработки"
void In_Key();			//ввод ключа элемента
int i, pp, ts = 1;
const int k = 21;			//число строк меню
char *menu[k][60];		//строки меню
/* ========================================================== */
/* ГЛАВНАЯ ФУНКЦИЯ */
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL,"Russian");
    pp = 1;
    cout <<
         "\n РАБОТА С В-ДЕРЕВЬЯМИ. ДАННЫЕ О ТЕЛЕФОНАХ \n\n";
    *menu[0] = "1. Выбор дерева (1 - А, 2 - В или 3 - С)";
    *menu[1] =
        "2. Создание выбранного дерева (включение элементов)";
    *menu[2] = "3. ***     Свободная строка";
    *menu[3] = "4. Нисходящий обход дерева";
    *menu[4] = "5. Восходящий обход дерева";
    *menu[5] = "6. Смешанный обход дерева";
    *menu[6] =
        "7. Нисходящий обход дерева с обработкой элементов";
    *menu[7] =
        "8. Нисходящий обход дерева с другой обработкой";
    *menu[8] = "9. ***     Свободная строка";
    *menu[9] =
        "10.Включение элемента в дерево поиска";
    *menu[10] =
        "11.Удаление элемента из дерева поиска";
    *menu[11] =
        "12.Вывод данных элемента на экран";
    *menu[12] =
        "13.Перенос элемента из одного дерева в другое";
    *menu[13] = "14.Сохранение дерева в файле";
    *menu[14] =
        "15.Восстановление дерева из файла";
    *menu[15] =
        "16.Объединение двух деревьев А и В как множеств";
    *menu[16] =
        "17.Пересечение двух деревьев А и В как множеств";
    *menu[17] =
        "18.Разность двух деревьв А и В как множеств";
    *menu[18] = "19.Уничтожение дерева";
    *menu[19] = "20.Конец работы";
    *menu[20] = "         Введите номер строки";
    system("clear");
    printf("    Работа с бинарными деревьями \n");
    while (pp)
    {
        Main_Menu();
        system("clear");
    }
    printf("    Конец pаботы с деревом\n");
    Wait_Entr();
    return 0;
}				//end main

/* ======================================================== */
/*  ВЫВОД ГЛАВНОГО МЕНЮ */
int Main_Menu(void)
{
    int ns;
    fflush(NULL);			/* чистка буферов */
    while (1)
    {
        for (i = 0; i < k; i++)
            printf("\n %s", *menu[i]);
        printf("\n");
        if ((scanf("%d", &ns) < 1) || ns < 1 || ns > k)
        {
            fflush(NULL);
            system("clear");
            printf
            ("\nОшибка в номере!!Будьте внимательны.");
            continue;
        }
        break;
    }
    switch (ns)
    {
    case 1:
        Select_Tree();
        break;
    case 2:
        Crt_Btree();
        break;
    case 3:
        Prnt();
        break;
    case 4:
        preorder(T, 0);
        Wait_Entr();
        break;
    case 5:
        d = 0;
        postorder(T, 0);
        Wait_Entr();
        break;
    case 6:
        d = 0;
        inorder(T);
        Wait_Entr();
        break;
    case 7:
        d = 0;
        preordrx(T, handler);
        Wait_Entr();
        break;
    case 8:
        d = 0;
        preordrx(T, prnt);
        Wait_Entr();
        break;
    case 9:			/* Rinorder(T);     */
        Prnt();
        break;
    case 10:
        if (!In_Data(&x))
            AddEl1(x, &T);
        break;
    case 11:
        In_Key();
        Delete1(x, &T);
        break;
    case 12:			/*Show_El(); */
        Prnt();
        break;
    case 13:			/*Move_Node(TA,&TB,key); */
        Prnt();
        break;
    case 14:			/*Out_File(T); */
        Prnt();
        break;
    case 15:			/*In_File(&T);   */
        Prnt();
        break;
    case 16:			/*Uni_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 17:			/*Cross_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 18:			/*Dif_Trees(TA,TB,&TC); */
        Prnt();
        break;
    case 19:
        Del_Btree(&T);
        getchar();
        break;
    case 20:
        pp = 0;
    }
    return 0;
}				//end Main_menu

/* ========================================================== */
/* ВЫБОР ДЕРЕВА ПОИСКА */
void Select_Tree(void)
{
    char ns;
    while (1)
    {
        fflush(NULL);
        printf
        ("  Введите номер дерева: 1(А), 2(В) или 3(С)=>");
        ns = getchar();
        if (ns < '1' || ns > '3')
        {
            printf("Ошибка в номере, повторно \n");
            continue;
        }
        break;
    }
    switch (ts)
    {
    case 1:
        A = T;
        break;
    case 2:
        B = T;
        break;
    case 3:
        C = T;
        break;
    }
    switch (ns)
    {
    case '1':
        ts = 1;
        T = A;
        break;
    case '2':
        ts = 2;
        T = B;
        break;
    case '3':
        ts = 3;
        T = C;
    }
}				//end Select_Tree

/* ================================================ */
/* ПОСТРОЕНИЕ ДЕРЕВА ПОИСКА О ГОСУДАРСТВАХ */
void Crt_Btree(void)
{
    printf
    ("\n Cоздание B-дерева с данными о телефонах\n");
    while (1)
    {
        if (In_Data(&x) != 0)
        {
            printf("\n Ввод завершен");
            Wait_Entr();
            break;
        }
        else
            AddEl1(x, &T);
    }
}				//end Crt_Btree

/* ======================================================= */
/* НА ПЕРИОД РАЗРАБОТКИ ФУНКЦИЙ */
void Prnt(void)
{
    printf("\nНа стадии разработки");
    Wait_Entr();
}				//end Prnt

/* ======================================================== */
void In_Key()
{
    printf("\n Введите фамилию =>");
    cin >> x.fam;
}				//end In_Key

/* ========================================================= */
/* ВЫВОД ДАННЫХ ЗАДАННОГО УЗЛА НА ЭКРАН */
/* int Show_El(void)
  { In_Key();
	 if ( Loc_Node(key,T,&RAB) == 0)
			Scrn_El(RAB);
	 else
		 { printf("\n Элемент %s не найден",key);
			Wait_Entr();
			return 1;
		 }
	 return 0;
  }*/
/* ========================================================== */
/* ВВОД ДАННЫХ ЭЛЕМЕНТА */
int In_Data(EL * z)
{
    cout <<
         "\n Введите фамилию или ** - конец ввода\n =>";
    fflush(NULL);
    cin >> z->fam;
    if (!strcmp(z->fam, "**"))
        return -1;
    cout << "\n Введите номер телефона =>";
    cin >> z->nmb;
    while (1)
    {
        cout <<
             "\n Введите числовой код клиента=>";
        fflush(NULL);
        if (scanf("%d", &z->code))
            break;
        else
            cout << " ОШИБКА !!!";
    }
    return 0;
}				//end In_Data

/* =============================================== */
/* ВЫВОД ДАННЫХ ЭЛЕМЕНТА НА ЭКРАН */
void prnt(EL e)
{
    cout << "\n " << e.fam << " " << e.nmb << " " << e.code;
}				// end prnt

/* =============================================== */
/* ОБРАБОТЧИК ЭЛЕМЕНТОВ В УЗЛАХ */
void handler(EL e)
{
    cout << " Обработай меня, " << e.fam;
}				//end handler

/* =============================================== */
/* ОЖИДАНИЕ НАЖАТИЯ ВВОДА */
void Wait_Entr(void)
{
    cout << "\n Нажмите ввод";
    getchar();
}				//end Wait

/* *********************************************** */
