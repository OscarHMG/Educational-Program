#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
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
void saveInfo(Header *info);
void quitEnter(char *string);
void inputScores();
void saveScores(char *name,int n1_1P,int n2_1P,int n3_1P,int ex_1P,int n1_2P,int n2_2P,int n3_2P,int ex_2P);
int  inputNumOfStudents();
void printStadistics();
void getFinalScore(char line[], int cont);
void prinGraph(int score);
void printWelcomeMessage();
void headerInput();
Pila* loadHeaders();
Pila * inicializacion ();
void imprimir_pila (Pila * tas);
//Main Function
struct Header *headers[MAX];
int main(){
	int num,i;
	Pila *pila= loadHeaders();
	printWelcomeMessage();
	headerInput();
	num = inputNumOfStudents();
	for(i =0; i<num;i++){
		inputScores();
	}
	printf("\n\n");
	system("cls");
	printStadistics();
	system("PAUSE");
	return 0;
}

void headerInput(){
	Header *info = createHeader();
	inputHeaderInfo(info);
	saveInfo(info);
}
void printWelcomeMessage(){
	printf("\n\t\t\tSISTEMA DE CONTROL DE CALIFICACIONES\n");
	printf("\t\t\tSeccion de Ingreso de Datos\n\n");
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
	int ln ;
	career = (char *)malloc(50 * sizeof(char));
	professor = (char *)malloc(50 * sizeof(char));
	subject = (char *)malloc(50 * sizeof(char));
	printf("Career: ");
	fgets(career, 50, stdin);
	strcpy(info->career, career);
	quitEnter(info->career);
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
	strcpy(info->professor, professor);
	quitEnter(info->professor);
	fflush(stdin);
	printf("Subject: ");
	fgets(subject, 50, stdin);
	strcpy(info->subject, subject);
	quitEnter(info->subject);
	fflush(stdin);
}
 
void quitEnter(char *string){
	int ln = strlen(string) - 1;
	if (string[ln] == '\n')
		string[ln] = '\0';
}

void saveInfo(Header *info){
	FILE *f = fopen("headers_info.txt", "a");
	if (f == NULL){
		printf("Error opening file!\n");
		exit(1);
	}
	fflush(f);
	//Save the info of the header
	fprintf(f, "%s,""%d,""%d,""%s,""%s\n", info->career,info->semester, info->course,info->professor, info->subject);
	fclose(f);
}

void inputScores(){
	char *name;
	int n1_1P,n2_1P,n3_1P, ex_1P;
	int n1_2P,n2_2P,n3_2P, ex_2P;
	int final_prom;
	name = (char *)malloc(50 * sizeof(char));
	printf("Name: ");
	fgets(name, 50, stdin);
	quitEnter(name);
	fflush(stdin);
	printf("Nota #1 1er Parcial: ");
	scanf("%d",&n1_1P);
	printf("Nota #2 1er Parcial: ");
	scanf("%d",&n2_1P);
	printf("Nota #3 1er Parcial: ");
	scanf("%d",&n3_1P);
	printf("Examen 1er Parcial: ");
	scanf("%d",&ex_1P);
	printf("Nota #1 2do Parcial: ");
	scanf("%d",&n1_2P);
	printf("Nota #2 2do Parcial: ");
	scanf("%d",&n2_2P);
	printf("Nota #3 2do Parcial: ");
	scanf("%d",&n3_2P);
	printf("Examen 2do Parcial: ");
	scanf("%d",&ex_2P);
	fflush(stdin);
	saveScores(name,n1_1P,n2_1P,n3_1P,ex_1P,n1_2P,n2_2P,n3_2P,ex_2P);
	printf("\t\t\t\nIngreso de estudiante ha sido exitoso...\n\n");
}

void saveScores(char *name,int n1_1P,int n2_1P,int n3_1P,int ex_1P,int n1_2P,int n2_2P,int n3_2P,int ex_2P){
	int promedio_1P, promedio_2P, promedio_Final;
	FILE *f = fopen("scores.txt", "a");
	if (f == NULL){
		printf("Error opening file!\n");
		exit(1);
	}
	promedio_1P = (n1_1P + n2_1P + n3_1P + ex_1P)/4;
	promedio_2P = (n1_2P + n2_2P+ n3_2P + ex_2P)/4;
	promedio_Final = (promedio_1P + promedio_2P)/2;
	//Save the info of the Students and his notes
	fprintf(f, "%s,""%d,""%d,""%d,""%d,""%d,""%d,""%d,""%d,""%d,""%d,""%d\n", name,n1_1P,n2_1P,n3_1P,ex_1P,promedio_1P,n1_2P,n2_2P,n3_2P,ex_2P,promedio_2P,promedio_Final);
	fclose(f);
}

int  inputNumOfStudents(){
	int num;
	printf("\n\nCuantos estudiantes desea ingresar:");
	scanf("%d", &num);
	fflush(stdin);
	return num;
}


void printStadistics(){
	FILE *file;
	int i = 0, cont=0;
	char line[300];
	file = fopen("scores.txt","r");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
	}else{
		system("cls");
		printf("\t\t\t STADISTICS\n");
		while (feof(file) == 0){
			fgets(line,300,file);
			cont++;
			getFinalScore(line, cont);
			//printf("%s", line);
	    }
	}
	fclose(file);
}


void getFinalScore(char line[], int cont){
	int i, cont_comma=0,j=0;
	int sum;
	char prom[4];
	int lenght= strlen(line)-1;
	for(i=0;i<lenght;i++){
		if(line[i]==','){
			cont_comma++;
		}else if(cont_comma == 11){
			prom[j]= line[i];
			j++;
		}
	}
	prom[j]='\0';
	sum = atoi( prom );

	printf("%d |", cont);
	prinGraph(sum);
}

void prinGraph(int score){
	int i=0;
	int value = score/5;
	for(i=0;i<value;i++){
		printf("*");
	}
	printf(" %d \n",score);
}

Pila* loadHeaders(){
	FILE *file;
	int i = 0;
	char line[400];
	Header *h ;
	int cont=0;
	char career[50], subject[50], professor[50],n[50];
	int course=0, semester=0;
	char *p;
	Pila *pila= inicializacion();
	file = fopen("headers_info.txt","r");
	if (file == NULL){
		printf("\nError de apertura del archivo. \n\n");
	}else{
		while (feof(file) == 0){
			h = createHeader();
			fgets(line,400,file);
			p = strtok(line,",");
			while(p!=NULL){
				strcpy(n,p);
				p = strtok(NULL,",");
				if(cont==0)
					strcpy(h->career,n);
				else if(cont==1)
					h->semester=atoi(n);
				else if(cont ==2)
					h->course= atoi(n);
				else if(cont ==3)
					strcpy(h->professor,n);
				else if(cont ==4)
					strcpy(h->subject, n);
				cont++;
			}
			cont =0;
			headers[cont] = h; //Lleno una estructura de Headers
			insertar_pila(pila,h->professor);
	    }
	}
	fclose(file);
	//imprimir_pila(pila);
	return pila;
}














//Stack Functions
//------------------------------//
Pila * inicializacion (){
	Pila *tas = (Pila*)malloc(sizeof(Pila));
	tas->inicio = NULL;
	tas->tamanio = 0;
	return tas;
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
    printf("%s\n", actual->dato);
    actual = actual->siguiente;
  }
}
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Elemento {
    struct Header *contenido;
    struct ElementoLista *siguiente;
}Elemento;
 

typedef struct Header{
	char *career,*professor,*subject;
	int course, semester;
}Header;

typedef struct Pila{
  Elemento *inicio;
  int tamanio;
} Pila;
 
Pila * inicializacion (){
	Pila *tas = (Pila*)malloc(sizeof(Pila));
	tas->inicio = NULL;
	tas->tamanio = 0;
	return tas;
}
 
int insertar_pila (Pila * tas, Header *h){
  Elemento *nuevo_elemento;
 
  if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;
  if ((nuevo_elemento->contenido = (Header *) malloc (sizeof (Header)))== NULL)
    return -1;
  nuevo_elemento->contenido = h;
  //strcpy (nuevo_elemento->dato, dato);
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
 
  free (sup_elemento->contenido);
  free (sup_elemento);
  tas->tamanio--;
  return 0;
}
 
void imprimir_pila (Pila * tas){
  Elemento *actual;
  int i;
  actual = tas->inicio;
  
  for(i=0;i<tas->tamanio;++i){
    //printf("\t%p - %s\n",actual, actual->dato);
	  Header *h = actual->contenido;
	  printf("Carrera: %s\nSemestre:%d\nCurso:%d\nProfesor:%s\nMateria:%s\n\n",h->career,h->semester,h->course,h->professor,h->subject);
	  actual = actual->siguiente;
  }
}
 
int searchHeader(Pila *pila, Header *h){
	Elemento *actual;
	int i;
	actual = pila->inicio;
	
	for(i=0;i<pila->tamanio;++i){
		Header *actual_h = actual->contenido;
		if(strcmp(actual_h->career,h->career) && strcmp(actual_h->professor,h->professor) && strcmp(actual_h->subject,h->subject) && actual_h->course==h->course && actual_h->semester==h->semester){
			return 1; //Existe en la pila
		}
		actual = actual->siguiente;
  }
	return 0; //No existe en la pila

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
 
int main(int argc, char *argv[]){
	Pila *pila = inicializacion();
	Header *h1= createHeader();
	Header *h2=  createHeader();
	Header *h3= createHeader();
	Header *h4= createHeader();
	Header *h5= createHeader();
	h1->career ="Ingieneria";
	h1->course=5;
	h1->professor="Caelos moreno";
	h1->semester=8;
	h1->subject="Programacion";
	
	h2->career ="Biologo";
	h2->course=5;
	h2->professor="Manuel Perez";
	h2->semester=8;
	h2->subject="Fisica";
	
	h3->career ="Economista";
	h3->course=5;
	h3->professor="Martha Lorenzo";
	h3->semester=8;
	h3->subject="Eocnoimia";
	
	h4->career ="Doctorado";
	h4->course=5;
	h4->professor="Marcos Tulio";
	h4->semester=8;
	h4->subject="Matematica";


	h5->career ="Masterado";
	h5->course=1;
	h5->professor="Carlos Jordan";
	h5->semester=8;
	h5->subject="Matematica";
	insertar_pila(pila,h1);
	insertar_pila(pila,h2);
	insertar_pila(pila,h3);
	insertar_pila(pila, h4);
	imprimir_pila(pila);
	printf("Existe? : %d",searchHeader(pila,h5));
	system("PAUSE");
		return 0;
}
*/