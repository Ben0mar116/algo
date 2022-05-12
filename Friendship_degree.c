#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

typedef struct cellule{
	char name[20];
	int id ;
	bool visited;
}vertex;


typedef struct {
	vertex *tableau;
	int utilisee;
	int taille;
}people;

void initialisation(people* a, int tailleinitial){
	(*a).tableau = malloc(tailleinitial * sizeof(vertex));
	a->utilisee = 0;
	a->taille = tailleinitial;
}

void insert(people *a, vertex *x){
	if(a->utilisee == a->taille){
		a->taille +=1;
		a->tableau = (vertex* )realloc(a->tableau,a->taille * sizeof(vertex));
	}
	x->id = a->utilisee;
	a->tableau[a->utilisee++] = *x;
}


typedef struct edge{
	int from;
	int to;
	struct edge* next;
}edge;

typedef struct lista {
	edge *head;
	edge *tail;
}list;

list adjlist;
people p;

void establish_cxn(list *l, int idfrom, int idto){
	list tmp = adjlist;
	while(tmp.head != NULL){
		if(tmp.head->to == idfrom && tmp.head->from == idto)return;
		tmp.head = tmp.head->next;
	}
	edge *newelement = malloc(sizeof(edge));
	if (newelement == NULL ){
		return;
	}
	newelement->from = idfrom;
	newelement->to = idto;
	newelement->next = NULL;
	if(l->tail != NULL){
		l->tail->next= newelement;
	}
	l->tail=newelement;
	if(l->head == NULL){
		l->head = newelement;
	}
	/** second entry **/
	edge *newelementx = malloc(sizeof(edge));
	newelementx->from = idto;
	newelementx->to = idfrom;
	newelementx->next = NULL;
	if(l->tail != NULL){
		l->tail->next= newelementx;
	}
	l->tail=newelementx;
}
int q1[50];
int q2[50];
int lastq2=0;
int firstq1=0,lastq1=0;
int search(int id,int dest){
        int lvl = 1;
		q1[lastq1]=id;
		while(1){
            if (p.tableau[id].visited == false)	{
			p.tableau[id].visited=true;
			list emp =  adjlist;
			while (emp.head != NULL){
				if(emp.head->from == id){ // found the id from adjlist
					if(emp.head->to == dest)return lvl;  // check if there is connection
					 if(p.tableau[emp.head->to].visited == false)
                {
                    q2[lastq2]=emp.head->to;
                    lastq2++;
                }
   				}
				emp.head=emp.head->next;
			}}//q2 is full
			firstq1++;
if ( lastq2==0 && firstq1 > lastq1)return 0;
			if (firstq1 > lastq1 ){// switch
             lvl++;
             firstq1=lastq1=0;
                for (int i=0;i<lastq2;i++)
                {
                    q1[i]=q2[i];
                    lastq1++;
                }
            lastq2=0;

			}

            id = q1[firstq1];


		}
	}


void printinfo(vertex a){
    printf("%d - %s \n (", a.id,a.name);
    list ptr = adjlist;
    while(ptr.head != NULL)
    {
        if(ptr.head->from == a.id)
        {
            printf(" - %s ",p.tableau[ptr.head->to].name);
        }
        ptr.head=ptr.head->next;
    }



printf( " ) \n");

}
void showpeople(people p){
	for (int i = 0 ; i < p.taille ; i++ ){
		printinfo(p.tableau[i]);
	}
	printf("\n");
}
int main(){
	vertex x;
	x.visited = false;
	initialisation(&p,1);
	adjlist.head = NULL;
	adjlist.tail = NULL;
 	for(;;){
		pp:
		system("cls");
		printf("                           Friendship Problem\n");
		printf("1.  Add a person                           ");
		printf("2.  Establish a friendship\n");
		printf("3.  Calculate the degree of friendship     ");
		printf("4.  exit\n");
		vertex x;
		int a,b;
		switch(getch()){
			case 49:
				printf("Insert the person's name : ");
				scanf("\n%[^\n]",&(x.name));
				insert(&p,&x);
				goto pp;
			case 50:
				ss:
				    if (p.utilisee > 1 ){
				printf("\nEstablishing connections\n\n");
				showpeople(p);
				printf("\n");
				printf("Person : ");
				scanf("%d",&a);
				printf("Will befriend : ");
				scanf("%d",&b);
				printf("\n");
				if(a == b || a> p.utilisee-1 || b > p.utilisee -1)goto ss;
				establish_cxn(&adjlist,a,b);
				system("pause");
				goto pp;
				}
			case 51:
				firstq1 =lastq1=lastq2= 0;
				for(int k = 0 ; k < p.taille ; k++){
					p.tableau[k].visited = false;
				}
				if (p.utilisee > 1 ){
				printf("\n");
				showpeople(p);
				printf("\n");
				printf("Initial Person : ");
				scanf("%d",&a);
				printf("Target: ");
				scanf("%d",&b);
				if (b>a)printf("The degree of friendship between %s and %s is : %d\n",p.tableau[a].name,p.tableau[b].name,search(a,b));
				else {printf("The degree of friendship between %s and %s is : %d\n",p.tableau[a].name,p.tableau[b].name,search(b,a));}
				system("pause");}
				goto pp;
			case 52:
				exit(1);
			default:;
		}
	}
	return 0;
}
