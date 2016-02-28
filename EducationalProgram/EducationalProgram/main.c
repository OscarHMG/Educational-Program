#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Elemento {
    struct Header *contenido;
    struct ElementoLista *siguiente;
}Elemento;
 
typedef struct Pila{
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
Header * inputHeaderInfo();
void saveInfo(Header *info);
void quitEnter(char *string);
void inputScores();
void saveScores(char *name,int n1_1P,int n2_1P,int n3_1P,int ex_1P,int n1_2P,int n2_2P,int n3_2P,int ex_2P);
int  inputNumOfStudents();
void printStadistics();
void getFinalScore(char line[], int cont);
void prinGraph(int score);
void printWelcomeMessage();
void headerInput(Pila *p);
Pila* loadHeaders();
Pila * inicializacion ();
int printOptionMenu();
void searchHeader(Pila *p);
void imprimir_pila (Pila * tas);
int quitar_pila (Pila * tas);
void eliminateHeader();
//Main Function
struct Header *headers[MAX];
int main(){
    int opt=0;
	int num,i,option;
	Pila *pila= loadHeaders();
	while(opt==0){
	//imprimir_pila(pila);
	printWelcomeMessage();
	headerInput(pila);
	num = inputNumOfStudents();
	for(i =0; i<num;i++){
		inputScores();
	}
	printf("\n\n");
	system("cls");
	printStadistics();
		
	option = printOptionMenu();
	
	switch(option){
       case 1:
            searchHeader(pila);
            break;
       case 2:
            printf("\n\nHeaders: \n\n");
            imprimir_pila(pila);
            system("PAUSE");
            break;
       case 3:
            eliminateHeader(pila);
            break;
             
             }
       }
	system("PAUSE");
	return 0;
}

void headerInput(Pila *p){
	Header *info = inputHeaderInfo();
	saveInfo(info);
	insertar_pila(p, info);
}
void printWelcomeMessage(){
	system("cls");
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
Header * inputHeaderInfo(){
    Header *info = createHeader();
	char *career, *professor, *subject;
	int course, semester;
	int ln ;
	career = (char *)malloc(50 * sizeof(char));
	professor = (char *)malloc(50 * sizeof(char));
	subject = (char *)malloc(50 * sizeof(char));
	fflush(stdin);
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
	return info;
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
		printf("\n\n");
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
			quitEnter(h->subject);
			cont =0;
			insertar_pila(pila,h);
	    }
	}
	fclose(file);
	return pila;
}



 
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
         Header *h = actual->contenido;
         printf("Carrera: %s\nSemestre:%d\nCurso:%d\nProfesor:%s\nMateria:%s\n\n",h->career,h->semester,h->course,h->professor,h->subject);
         actual = actual->siguiente;
  }
}
 
int buscar_Pila(Pila *pila, Header *h){
	Elemento *actual;
	int i;
	actual = pila->inicio;
	
	for(i=0;i<pila->tamanio;++i){
		Header *actual_h = actual->contenido;
		if(strcmp(actual_h->career,h->career)==0 && strcmp(actual_h->professor,h->professor)==0 && strcmp(actual_h->subject,h->subject)==0 && actual_h->course==h->course && actual_h->semester==h->semester){
			return 1; //Existe en la pila
		}
		actual = actual->siguiente;
  }
	return 0; //No existe en la pila

}


int printOptionMenu(){
    int op;
     printf("\t\tLa informacion ha sido cargada exitosamente en memoria.\n");
     printf("\tQue desea hacer?\n");
     printf("1. Buscar una Cabecera\n");
     printf("2. Imprimir  todas las cabeceras\n");
     printf("3. Eliminar la ultima cabecera ingresada\n");
     printf("Ingrese Opcion: ");
     scanf("%d", &op);
     return op;
}


void searchHeader(Pila *p){
	int value;
	 Header *h;
     printf("\nIngrese informacion del header que desee buscar\n\n\n");
     h = inputHeaderInfo();
     value= buscar_Pila(p, h);
     if(value == 1){
         printf("El header que ud busca, se encontro!\n");
     }else{
         printf("El header qe ud busca, no existe!\n");
     }
     system("PAUSE");
}

void eliminateHeader(Pila *pila){
     int value = quitar_pila(pila);
     if(value == 0)
         printf("Se elimino correctamente el header\n\n");
     else 
         printf("ERROR, no se pudo eliminar el ultimo header\n\n");
     system("PAUSE");
     }
     
void printInfo(Header *h){
	 printf("\n\nCarrera: %s\nSemestre:%d\nCurso:%d\nProfesor:%s\nMateria:%s\n\n",h->career,h->semester,h->course,h->professor,h->subject);

}
     

