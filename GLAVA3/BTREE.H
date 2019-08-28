/* *************************************************** */
/* РАБОТА С В-ДЕРЕВЬЯМИ, файл включения содержит       */
/*  необходимые функции и данные                       */
/*	 btree.h 16.01.04 Хусаинов Б.С.                     */
/* =================================================== */
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
//#include <alloc.h>
//#include <conio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define nn 2*N // nn - макс. число элементов в узле (странице)
					// N задается в клиентской программе
#define Item struct II  // структура элемента в узле
#define Page struct PP  // структура узла (страницы)
 Item     // структура элемента
	 { DT DATA;   // ключ+данные элемента
		Page *p;   // указатель на узел-потомок
		int count; // счетчик, возможно для дубль-ключей
	 };
 Page  // структура узла (страницы)
	 { int m;     // Число реальных элементов в узле
		Item e[nn+1];
	 };
 Page *q; int h,d=0;
int compr(int a,int b);     //сравнение целочисленных данных
int compr(char *a,char *b); //сравнение символьных строк
int compr(float a,float b);
void preorder(Page *T,int level);  //нисходящий обход
void postorder(Page *T,int level); //восходящий обход
void inorder(Page *T);             //смешанный обход
void preordrx(Page *T,void(*g)(DT));//нисходящий обход
									 //с обработкой элементов
void PrBtree(Page *T,void(*f)(DT)); //печать дерева
void AddEl1(DT x,Page **T);  //начальная функция включения
	  // элемента, используется в клиентской программе
int  AddEl(DT x,Page *a,Item *v); // вспомогательная функция
	  // включения элемента
void Delete1(DT x,Page **root); //начальная функция удаления
	 // элемента, используется в клиентской программе
int delet(DT x,Page *a); // вспомогательная для удаления
int del(Page *p,Page *a,int k); //вспомогательная для удаления
int underflow(Page *c,Page *a,int s); //вспомогательная для
	 // удаления
void Del_Btree(Page **T); //удаление дерева - освобождение узлов
/* ====================================================== */
/* ПЕРЕГРУЖЕННАЯ ФУНКЦИЯ СРАВНЕНИЯ ЦЕЛОЧИСЛЕННЫХ ДАННЫХ   */
 int compr(int a,int b)
  { return a-b;
  }
/* ====================================================== */
/* ПЕРЕГРУЖЕННАЯ ФУНКЦИЯ СРАВНЕНИЯ СИМВОЛЬНЫХ СТРОК       */
 int compr(char *a,char *b)
  { return strcmp(a,b);
  }
/* ====================================================== */
/* ПЕРЕГРУЖЕННАЯ ФУНКЦИЯ СРАВНЕНИЯ ЧИСЕЛ типа float       */
 int compr(float a,float b)
  { return a-b;
  }
/* ===================================================== */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА - рекурсивная функция
	Т - корень дерева, level - уровень поддерева  */
  void preorder(Page *T,int level)
 {  int i; 	/* i - счетчик цикла */
	 if(T==NULL && d==0)
		 { printf("\n Дерево пустое");
			return;
		 }
	 d++;
	 if(T==NULL) return;
	 printf("\n Уровень %d T=%p ",level,T);
//	 printf(" p[0]=%p",T->e[0].p); //адрес страницы - любознательным
	 for(i=1;i<=T->m;i++)    /* цикл печати содержимого */
		{                      /* узла 'T' B-дерева */
//  printf(" p[%d]=%p ",i,T->e[i].p); //адрес страницы
		  cout<<" ключ="<<T->e[i].DATA.Skey;
		  //printf(" сч=%d",T->e[i].count);      getchar();
		}
	 for(i=0;i<=T->m;i++)             /* цикл обхода потомков */
		preorder(T->e[i].p,level+1);
 }
/* =========================================================== */
/*       ВОСХОДЯЩИЙ ОБХОД ДЕРЕВА     */
 void postorder(Page *T,int level)
 { int i;      /* счетчик цикла*/
	 if(T==NULL && d==0)
		 { printf("\n Дерево пустое");
			return;
		 }
	 d++;
	if(T==NULL) return;
	for(i=0;i<=T->m;i++)   /* цикл обхода потомков */
	  postorder(T->e[i].p,level+1);
	printf("\n Уровень %d >",level);
	for(i=1;i<(T->m+1);i++)  /* цикл печати содержимого узла 'T' */
	  cout<<" "<<T->e[i].DATA.Skey;
 }
/* ============================================================= */
/*    СМЕШАННЫЙ ОБХОД ДЕРЕВА     */
 void inorder(Page *T)
 { int i;                         /* счетчик цикла*/
	 if(T==NULL && d==0)
		 { printf("\n Дерево пустое");
			return;
		 }
	 d++;
	if(T==NULL) return;
	inorder(T->e[0].p);
	for(i=1;i<T->m+1;i++)  /* цикл обхода потомков */
	  { cout<<"  "<< T->e[i].DATA.Skey;
		 inorder(T->e[i].p);
	  }
 }
/* ===================================================== */
/* ФУНКЦИЯ ПЕЧАТИ ДЕРЕВА - используется для демонстрации
	динамики изменения дерева при добавлении и удалении
	элементов. р - корень дерева */
 void PrBtree(Page *p,void (*f)(DT))
  {int i;
	if(p==NULL && d==0)
	  { printf("\n Дерево пустое");
		 return;
	  }
	d++;
	if (p!=NULL)
	  { printf("   ");
		 for (i=1; i<=p->m; i++)
			f(p->e[i].DATA);
		 printf("\n");
		 for(i=0; i<=p->m; i++)
			PrBtree(p->e[i].p,f);
	  }
  }
/* ===================================================== */
/* НИСХОДЯЩИЙ ОБХОД ДЕРЕВА С ОБРАБОТКОЙ ЭЛЕМЕНТОВ */
 void preordrx(Page *p,void (*f)(DT))
  {int i;
	if(p==NULL && d==0)
	  { printf("\n Дерево пустое");
		 return;
	  }
	d++;
	if (p!=NULL)
	  { printf("   ");
		 for (i=1; i<=p->m; i++)
			f(p->e[i].DATA);
		 printf("\n");
		 for(i=0; i<=p->m; i++)
			preordrx(p->e[i].p,f);
	  }
  }
/* ========================================================= */
 /* НАЧАЛЬНАЯ ФУНКЦИЯ ДОБАВЛЕНИЯ ЭЛЕМЕНТА х в В-дерево */
	void AddEl1(DT x,Page **root)
  { int h; Item u;Page *temp; temp=*root;
	 h=AddEl(x,*root,&u);
	 if (h)
		{ *root=temp; q=*root;
		  *root=(Page*)calloc(1,sizeof(Page));
//		  printf(" root=%p",*root);getchar(); /* новый корень */
		  temp=*root; temp->m=1; temp->e[0].p=q;
		  temp->e[1]=u; *root=temp;
		}
  }
  /* ======================================================== */
/* Рекурсивная функция включения  элемента  х
	в В-дерево с корнем *а. Осуществляется поиск элемента.
	Если элемент  уже есть, то счетчик элемента
	count увеличивается на 1, иначе в дерево включается
	элемент х со счетчиком 1. Если элемент должен
	передаваться на низший уровень, то он присваивается v,
	и дерево станет выше, признак роста дерева присаивается
	h1 и возвращается через имя функции вызывающей функции. */

	int AddEl(DT x, Page *a, Item *v)
	{ int i,L,R,k,h1; Page *b; Item u;
	  /* Поиск элемента х на странице *а */
	 h1=0;
	 if (a==NULL)  /* дерево пустое или дошли до листа */
		{ h1=1;
		 v->DATA=x; v->count=1;
		  v->p=NULL;
		}
	 else  /* двоичный поиск элемента на странице */
		{ L=1; R=a->m;
		  do
			{ k=(L+R)/2;
			  if (compr(x.Skey,a->e[k].DATA.Skey)<=0)
				 R=k-1;
			  if (compr(x.Skey,a->e[k].DATA.Skey)>=0)
				 L=k+1;
			}
		  while (R>=L);
		  if ((L-R)>1) /* дубль-ключ */
			 { a->e[k].count++; h1=0;
				printf("\n дубль-ключ");
			 }
		  else   /* на этой странице элемента нет */
			{ if (R==0)
				 q=a->e[0].p;
			  else
				 q=a->e[R].p;
			  h1=AddEl(x,q,&u);
			  if (h1)  /* дошли до листа, ключ - не дубль */
				if (a->m < nn) /* есть место на странице */
				 { h1=0; a->m=a->m+1;
					for (i=a->m; i>=R+2; i--)
					  a->e[i] = a->e[i-1];
					a->e[R+1] = u;
				 }
				else   /* страница полна, расщепляем ее */
				 {
					b=(Page*) calloc(1,sizeof(Page)); //printf(" b=%p",b);
					if (R<=N)
					  { if (R==N)
						  *v=u;
						 else
							{ *v=a->e[N];
							  for (i=N; i>=R+2; i--)
								 a->e[i]=a->e[i-1];
							  a->e[R+1]=u;
							}
						 for (i=1; i<=N; i++)
							b->e[i]=a->e[i+N];
					  }
					else  /*включение в правую страницу */
					  { R=R-N; *v=a->e[N+1];
						 for (i=1; i<=R-1; i++)
							b->e[i]=a->e[i+N+1];
						 b->e[R]=u;
						 for (i=R+1; i<=N; i++)
							b->e[i]=a->e[i+N];
					  }
					a->m=N; b->m=N;
					b->e[0].p=v->p; v->p=b;  h1=1;
				 }
			  }
		  } return h1;
  }
/* ===================================================== */
  /* НАЧАЛЬНАЯ ФУНКЦИЯ УДАЛЕНИЯ ЭЛЕМЕНТА х из В-дерева */
	void Delete1(DT x, Page **root)
  { int h; Page *temp,*t; temp=*root;
		  h=delet(x,*root); t=*root;
		  if (h)  /* уменьшен размер корневой страницы */
				if (t->m == 0)
				  { *root=temp;q=*root; temp=q->e[0].p;
					  free(q); *root=temp; /* высота дерева уменьшилась*/
					 // printf(" del q=%p root=%p",q,*root); getchar();/*удаленный узел-корень */
					  q=NULL;
				  }
  }
 /* =================================================== */
 /* РЕКУРСИВНАЯ ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
	 ЭЛЕМЕНТА ИЗ ДЕРЕВА. Вызывается из начальной функции Delete1 */
 int delet(DT x,Page *a)
 /* поиск и удаление элемента х в В-дереве а. Если
 при удалении на странице останется мало элементов,
 то балансировка с соседней страницей либо слияние.
 h1=true при нехватке элементов на странице */
  {int i,k,L,R; Page *q; int h1;
	 if (a==NULL)
		{ cout<<"\n ключ "<<x.Skey<<" не найден"; h1=0; }
	 else
	 { L=1; R=a->m; /*двоичный поиск в массиве*/
		do
		  { k=(L+R)/2;
			 if (compr(x.Skey,a->e[k].DATA.Skey)<=0)
				R=k-1;
			 if (compr(x.Skey,a->e[k].DATA.Skey)>=0)
				L=k+1;
		  }
		while ( R>=L);
		if (R==0) q=a->e[0].p; else q=a->e[R].p;
		if ((L-R)>1) /*найден, теперь удаление e[k]*/
		  { if (q==NULL)
				{ /*a -терминальная страница*/
				  a->m--; h1=(a->m<N);
				  for ( i=k; i<=a->m; i++) a->e[i]=a->e[i+1];
				}
			 else
				{ h1=del(q,a,k);
				  if (h1) h1=underflow(a,q,R);
				}
			}
		 else
			{ h1=delet(x,q);
			  if (h1) h1=underflow(a,q,R);
			}
		}  return h1;
  }
/* ========================================================= */
  /* РЕКУРСИВНАЯ ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
	  ЭЛЕМЕНТА ИЗ ДЕРЕВА */
  int del(Page *p,Page *a,int k)
	{ Page *q;int h1;
		q=p->e[p->m].p;
		if (q!=NULL)
		  { h1=del(q,a,k);
			 if(h1)  h1=underflow(p,q,p->m);
		  }
		else
		  { p->e[p->m].p=a->e[k].p; a->e[k]=p->e[p->m];
			 p->m=p->m-1;h1=(p->m<N);
		  } return h1;
	 }
  /* ======================================================= */
 /* ФУНКЦИЯ, РЕАЛИЗУЮЩАЯ ЧАСТЬ АЛГОРИТМА УДАЛЕНИЯ
	 ЭЛЕМЕНТА ИЗ ДЕРЕВА */
  int underflow(Page *c,Page *a,int s)
	/* а - страница с нехваткой, с - страница-предок */
 { Page *b;int i,k,mb,mc,h1;
	mc=c->m;  h1=1;
	 if (s<mc)
		{ /* b:=страница справа от а*/
		  s=s+1;
		  b=c->e[s].p; mb=b->m; k=(mb-N+1)/2;
		  /* k - число элементов на соседней странице b */
		  a->e[N]=c->e[s]; a->e[N].p=b->e[0].p;
		  if (k>0)
			 { /* пересылка k элементов с b на а */
				for (i=1; i<=k-1;i++)
				  a->e[i+N]=b->e[i];
				c->e[s]=b->e[k]; c->e[s].p=b;
				b->e[0].p=b->e[k].p; mb=mb-k;
				for (i=1; i<=mb; i++)
				  b->e[i]=b->e[i+k];
				b->m=mb; a->m=N-1+k; h1=0;
			 }
		  else
			 { /*слияние страниц а и b */
				for (i=1; i<=N; i++)
				  a->e[i+N]=b->e[i];
				for (i=s; i<=mc-1; i++)
				  c->e[i]=c->e[i+1];
				a->m=nn; c->m=mc-1; free(b); //printf("\n under=%p",b);
				h1=c->m<N;
			 }
		  }
		else

		  { /* b := страница слева от а */
			 if (s==1) b=c->e[0].p; else b=c->e[s-1].p;
			 mb=b->m+1; k=(mb-N)/2;
			 if (k>0)
				{ /* пересылка k элементов со страницы b на a */
				  for (i=N-1; i>=1; i--)
					 a->e[i+k]=a->e[i];
				  a->e[k]= c->e[s]; a->e[k].p=a->e[0].p; mb=mb-k;
				  for (i=k-1; i>=1; i--)
					 a->e[i]=b->e[i+mb];
				  a->e[0].p=b->e[mb].p;
				  c->e[s]=b->e[mb]; c->e[s].p=a;
				  b->m=mb-1; a->m=N-1+k; h1=0;
				}
			 else
				{ /* слияние страниц а и b */
				  b->e[mb]=c->e[s]; b->e[mb].p=a->e[0].p;
				  for (i=1; i<=N-1; i++)
					 b->e[i+mb]=a->e[i];
				  b->m=nn; c->m=mc-1;  free(a);
				  //printf(" del a=%p",a); getchar();/* отладка*/
				  a=NULL;
				  h1=(c->m<N);
				}
		  }  return h1;
	 }
  /* ========================================================= */
  /*ФУНКЦИЯ ОСВОБОЖДЕНИЯ ПАМЯТИ,ЗАНЯТОЙ УЗЛАМИ ДЕРЕВА*/
 void Del_Btree(Page **t)
 {int i;Page *T; static s=1;T=*t;
	printf(" s=%d T=%p",s++,T); getchar();
	if(T==NULL)
	return;
  if(T->e[0].p==0)
  { free(T);
	 T=NULL;*t=T;return;}
  else
	 for(i=0;i<T->m+1;i++)
	  Del_Btree(&(T->e[i].p));
	  free(T);T=NULL;*t=T; getchar();
  }
/* ******************************************************* */


