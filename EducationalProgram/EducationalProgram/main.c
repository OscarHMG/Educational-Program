#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elementoLista {
    char *dato;
    struct ElementoLista *siguiente;
}Elemento;
 
typedef struct ListaUbicacion{
  Elemento *inicio;
  int tamanio;
} Pila;
 


//Struct Header
typedef struct Header{
	char *career,*professor,*subject;
	int course, semester;
}Header;

typedef struct Student{
	char *name;
	int score1_P1, score2_P1, score3_P1, exam_scoreP1;
	int score1_P2, score2_P2, score3_P3, exam_scoreP2;
	int final_score;
}Student;

//Prototypes of Functions
Header * createHeader();
void inputHeaderInfo(Header *info);


//Main Function

int main(){
	Header *info = createHeader();
	inputHeaderInfo(info);
	system("PAUSE");
	return 0;
}




Header * createHeader(){
	Header *tmp = (Header*)malloc(sizeof(Header));
	tmp->career = (char *)malloc(50 * sizeof(char));
	tmp->professor = (char *)malloc(50 * sizeof(char));
	tmp->subject = (char *)malloc(50 * sizeof(char));
	tmp->course = -1;
	tmp->semester = -1;
	return tmp;
}

//This Function ask for the info of the Header
void inputHeaderInfo(Header *info){
	char *career, *professor, *subject;
	int course, semester;
	career = (char *)malloc(50 * sizeof(char));
	professor = (char *)malloc(50 * sizeof(char));
	subject = (char *)malloc(50 * sizeof(char));
	printf("Career: ");
	fgets(career, 50, stdin);
	strcpy(info->career,career);
	fflush(stdin);
	printf("Semester: ");
	scanf("%d",&semester);
	info->semester = semester;
	fflush(stdin);
	printf("Course: ");
	scanf("%d",&course);
	info->course = course;
	fflush(stdin);
	printf("Professor: ");
	fgets(professor, 50, stdin);
	strcpy(info->professor,professor);
	fflush(stdin);
	printf("Subject: ");
	fgets(subject, 50, stdin);
	strcpy(info->subject,subject);
	fflush(stdin);
}
 

void inicializacion (Pila * tas){
  tas->inicio = NULL;
  tas->tamanio = 0;
}
 
/* apilar (a�adir) un elemento en la pila */
int insertar_pila (Pila * tas, char *dato){
  Elemento *nuevo_elemento;
 
  if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;
  if ((nuevo_elemento->dato = (char *) malloc (50 * sizeof (char)))== NULL)
    return -1;
 
  strcpy (nuevo_elemento->dato, dato);
  nuevo_elemento->siguiente = tas->inicio;
  tas->inicio = nuevo_elemento;
  tas->tamanio++;
  return 0;
}
 
 
int quitar_pila (Pila * tas){
 
  Elemento *sup_elemento;
 
  if (tas->tamanio == 0)
    return -1;
 
  sup_elemento = tas->inicio;
  tas->inicio = tas->inicio->siguiente;
 
  free (sup_elemento->dato);
  free (sup_elemento);
  tas->tamanio--;
 
  return 0;
}
 
/* visualizaci�n de la pila */
void imprimir_pila (Pila * tas){
  Elemento *actual;
  int i;
  actual = tas->inicio;
 
  for(i=0;i<tas->tamanio;++i){
    printf("\t%p - %s\n",actual, actual->dato);
    actual = actual->siguiente;
  }
}