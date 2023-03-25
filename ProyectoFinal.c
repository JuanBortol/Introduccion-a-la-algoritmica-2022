//Introducción a la Algoritmica 2022
//Alumnos:Juan Francisco Bortol, Andrés Venier

/*Proyecto final:
A través de este programa se busca modelar el registro de diferentes parametros climaticos relevados por una estación meteorológica,
valores se obtienen a diario. La estación analiza la información para obtener series de datos que le permitan 
alimentar modelos de predicción del tiempo. Nos solicitan que desarrollemos un programa para poder almacenar 
los registros diarios y procesar los valores almacenados para la elaboración de los pronósticos del tiempo.
*/
/*Consideración especial:
A la hora de definir el nombre del archivo a trabajar, el mismo debe incluir solamente el año en números, correspondiente al año en curso de los registros a cargar. 
Por ejemplo, en caso de que se quiera trabajar con un archivo que contenga los registros correspondientes al año 2022, el nombre del archivo debe ser "2022". 
La extensión sera asignada por el programa posteriormente. Desarrollado y compilado en g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0.
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef struct 
{
	long int ddmmyyyy;
	int tmax;
	int tmin;
	int HUM;
	int PNM;
	int DV;
	int FF;
	int PP;
	int borrado;
}Tregdiario;

typedef struct TElem{
	Tregdiario info;
	struct TElem *next;
}TNodo;
TNodo *q;


Tregdiario registro;

Tregdiario arregloActivo[256];

int cant;
int pos;
int opcion;


FILE * f;
FILE * b;

//Variables para la manipulación del nombre del archivo
char directorio[]="";
char nomArch[100];
char nombreFecha[100];
char ext[]=".dat";
char sn;
char nombreRespaldo[100];
long int anioArchivo;




//////MANIPULACION DE LA LISTA////////////////////////////////
TNodo *CrearLista(){ //Crea la lista vacia
	TNodo *cabeza = NULL;
	return cabeza;
}

TNodo *CrearNodo(Tregdiario num[], int indice){ //Crea un nodo en la lista
	TNodo *aux; 
	aux = malloc(sizeof(TNodo));
	aux->info = num[indice];
	aux->next = NULL;
	return aux;
}

void InsertarCabeza(TNodo **cabeza, Tregdiario num[], int indice){ //Inserta el nodo creado en la cabeza de la lista
	TNodo *aux;
	aux = CrearNodo(num, indice);
	aux->next = *cabeza;
	*cabeza = aux;
}
/////////////////////////////////////////////////////////////

//////APERTURA DEL ARCHIVO///////////////////////////////////       
void Apertura(char *nomArch, char *directorio){
  Tregdiario aux;
  char pausa[50];
	printf("\n\nLa carpeta de trabajo es:\n");  
	*directorio = system("pwd");	//Utilizamos la carpeta actual como carpeta de trabajo, la misma de donde se ejecuta el programa.
	printf("\nIngrese el nombre del archivo sin la extensión \n");
	scanf("%s",nombreFecha); //Almacena el nucleo del nombre del archivo(el año del que se van a cargar registros)
	strcat(nomArch,directorio); //Concatena el directorio a la cabeza del nombre final del archivo
  strcat(nomArch,nombreFecha); //Concatena el nucleo al nombre final del archivo
  strcat(nomArch,ext); //Concatena la extensión al final del nombre del archivo
		if ((f = fopen(nomArch, "rb"))  == NULL){
			printf ("No existe o no puede abrirse el archivo. ¿Desea crear un archivo con ese nombre?\n");
			scanf("%s", &sn);
			if (sn == 's'){
				f = fopen(nomArch,"wb+");
				printf ("El archivo ha sido creado exitosamente\n");
				printf("El archivo no tiene registros cargados, por favor ingrese el año asociado al archivo.\n");
			do{
				scanf("%li",&anioArchivo);
					if (anioArchivo>9999 || anioArchivo<1000){
						printf("Fecha invalida, ingrese un valor de cuatro digitos.\n");
					}
			}while(anioArchivo>9999 || anioArchivo<1000);
			fclose(f);
			} 
			else {
			printf("Se optó por no crear el archivo...\n");
			}
		} 
		else { //fread(&aux,sizeof(Tregdiario), 1, f) > 0) - variable anioArchivo = aux.ddmmyyyy
			if (fread(&aux,sizeof(Tregdiario), 1, f) > 0){
				printf("Archivo abierto exitosamente\n");
				anioArchivo = (aux.ddmmyyyy%10000);
			}
			else{
					printf("El archivo no tiene registros cargados, por favor ingrese el año asociado al archivo.\n");
					do{
						scanf("%li",&anioArchivo);
						if (anioArchivo>9999 || anioArchivo<1000){
							printf("Fecha invalida, ingrese un valor de cuatro digitos.\n");
						}
					}while(anioArchivo>9999 || anioArchivo<1000);
			}
		}
		printf("Archivo abierto exitosamente\n");
		fclose(f);
}
	

/////////////////////////////////////////////////////////////


////////CARGA FECHA//////////////////////////////////////////       
void CargarFecha(long int *fecha){ //Almacena el valor de la fecha considerando el año y el mes 
	int dia;
	int mes;
	int bisiesto;

	if (anioArchivo % 4 == 0 && (anioArchivo % 100 != 0 || anioArchivo % 400 == 0)){
		bisiesto = 1;
	} else {
		bisiesto = 0;
	}
	do {
		printf("Ingrese la fecha del nuevo registro correspondiente al año: %li.\n\n",anioArchivo);
		printf("Ingrese el mes:\n");
		scanf("%d", &mes);
		if (mes < 1 || mes > 12){
			printf ("El valor del mes debe ser entre 1 y 12\n");
			mes = 0;
		}
	} while (mes == 0);
	do {
		switch (mes){
			case 1: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 31){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 2: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (mes == 2 && bisiesto == 1 && (dia < 1 || dia > 29)){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 29\n");
						*fecha = 0;
					}else if (mes == 2 && bisiesto == 0 && (dia < 1 || dia > 28)){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 28\n");
						*fecha = 0;
					}else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 3: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 31){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 4: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 30){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 30\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 5: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 31){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 6: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 30){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 30\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 7: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 31){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 8: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 31){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 9: printf("Ingrese el día:\n");
					scanf("%d", &dia);
					if (dia < 1 || dia > 30){
						printf("El valor ingresado es erroneo, debe ser entre 1 y 30\n");
						*fecha = 0;
					} else {
						*fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					};break;
			case 10: printf("Ingrese el día:\n");
					 scanf("%d", &dia);
					 if (dia < 1 || dia > 31){
					 	 printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						 *fecha = 0;
					 } else {
						 *fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					 };break;
			case 11: printf("Ingrese el día:\n");
					 scanf("%d", &dia);
					 if (dia < 1 || dia > 31){
						 printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						 *fecha = 0;
					 } else {
						 *fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					 };break;
			case 12: printf("Ingrese el día:\n");
					 scanf("%d", &dia);
					 if (dia < 1 || dia > 31){
						 printf("El valor ingresado es erroneo, debe ser entre 1 y 31\n");
						 *fecha = 0;
					 } else {
						 *fecha = anioArchivo + (mes * 10000) + (dia * 1000000);
					 };break;
			default: printf("La fecha ingresada es erronea\n");
		}
	}while(*fecha == 0);
	printf("\nLa fecha ingresada es: %li \n\n", *fecha);
}
/////////////////////////////////////////////////////////////


////////CARGA DATOS//////////////////////////////////////////       ¡ 
void Cargaregistro(Tregdiario *reg){ //Almacena los valores de los campos del registro considerando sus limitaciones
  printf ("Ingrese el valor de temperatura máxima\n ");
	scanf ("%d", &reg->tmax);
	printf ("Ingrese el valor de temperatura mínima\n ");
	scanf ("%d", &reg->tmin);
	printf ("Ingrese el porcentaje de humedad (entre 0 y 100) \n ");
	do{
		scanf ("%d", &reg->HUM);
		if (reg->HUM < 0 || reg->HUM > 100){
			printf ("El valor ingresado se encuentra fuera de rango, intente nuevamente\n");
		} 
	} while (reg->HUM < 0 || reg->HUM > 100);
	printf ("Ingrese el valor de presión atmosférica (entre 900 y 3500)\n ");
	do{
		scanf ("%d", &reg->PNM);
		if (reg->PNM < 900 || reg->PNM > 3500){
			printf("El valor ingresado se encuentra fuera de rango, intente nuevamente\n");
		}
	} while (reg->PNM < 900 || reg->PNM > 3500);
	printf ("Ingrese la dirección del viento (entre 0 y 360)\n ");
	do {
		scanf ("%d", &reg->DV);
		if (reg->DV < 0 || reg->DV > 360){
			printf("El valor ingresado se encuentra fuera de rango, intente nuevamente\n");
		}
	} while (reg->DV < 0 || reg->DV > 360);
	printf ("Ingrese la velocidad del viento\n ");
	scanf ("%d", &reg->FF);
	printf ("Ingrese el valor total de precipitaciones\n ");
	scanf ("%d", &reg->PP);
	reg->borrado = 0;
 	}
///////////////////////////////////////////////////////////// 

//////////GRABAR REGISTRO ///////////////////////////////////
void GrabarRegistro(){
		Tregdiario reg;
		Tregdiario aux;
		long int fecha; // Fecha ingresada por el usuario en formato entero
		CargarFecha(&fecha); //Carga el valor de la variable fecha
		reg.ddmmyyyy = fecha;//Almacenamos la fecha en la variable que usaremos para escribir en el archivo
		fseek(f,0,SEEK_SET);// Nos posicionamos al principio del archivo y buscamos si ya existe un registro con esa fecha en el archivo (BUSQUEDA MARCA INICIAL)
			while ((fread(&aux,sizeof(Tregdiario), 1, f) != 0) ){ //Lectura secuencial del archivo hasta llegar al final o encontrar un registro con la fecha que se quiere agregar
				printf("\n %li \n",aux.ddmmyyyy);
				if ((aux.ddmmyyyy == reg.ddmmyyyy) && (!aux.borrado)) { //Se encontro un registro con el mismo valor de ddmmyyyy que la fecha que se quiere cargar 
					printf ("Ya existe un registro asociado a esa fecha\n");
					return;
				}
			} 
			 //Se alcanzó el final del archivo
			Cargaregistro(&reg); //Almacenar los valores de los campos restantes del registro a cargar
			fwrite(&reg, sizeof(Tregdiario), 1, f); //Escritura del registro al archivo									
}
///////////////////////////////////////////////////////////////

//////////ALTA ////////////////////////////////////////////////
void AltaRegistro (char *nombreArch){ //Crea un nuevo registro en el archivo
  FILE *f;
  f = fopen(nombreArch,"ab+"); //Apertura para añadir
	char respRecargar; // Almacena la respuesta a la pregunta de seguir cargando registros
	do{
		respRecargar = 'n';
		GrabarRegistro();
		printf("¿Desea seguir cargando registros al archivo?\n");
		scanf("%s",&respRecargar);									
	}while(respRecargar == 's' || respRecargar == 'S');
	printf("Cerrando el Archivo\n");
  fclose(f);
}
/////////////////////////////////////////////////////////////

///////MOSTRAR //////////////////////////////////////////////     
void MostrarRegistroClima(char *nomArch){
  Tregdiario aux;
	int j;// Variable con la que voy a controlar la cantidad de registros que voy a mostrar y pausar.
  FILE *f;
  f = fopen(nomArch,"rb");
  if (feof(f)){
    printf("El archivo no tiene registros cargados.\n");
    }
  else{  
	j = 1; // inicialización variable de control. 
  while(fread(&aux,sizeof(Tregdiario), 1, f) > 0){  //Lectura secuencial de los registros cargados en el archivo
    if (! aux.borrado){ //Comprueba los registros activos
			printf("\n----------------------------------------------------------------------------------------------\n");
      printf("Al dia %li/%li/%li, se registraron los siguientes parametros climaticos:\n\n",(aux.ddmmyyyy/1000000),((aux.ddmmyyyy/10000)%100),(aux.ddmmyyyy%10000));
      printf("Temperatura máxima:%d\n",aux.tmax);
      printf("Temperatura mínima:%d\n",aux.tmin);
      printf("Humedad promedio:%d \n",aux.HUM);
      printf("Presión atmosferica:%d hPa\n",aux.PNM);
      printf("Dirección del viento:%d  \n",aux.DV);
      printf("Velocidad del viento:%d km/h \n",aux.FF);
      printf("Precipitaciones:%d mm\n",aux.PP);
			printf("----------------------------------------------------------------------------------------------\n");
			if (j%3==0){
				printf("\nPRESIONE ENTER PARA CONTINUAR..................\n");
				getchar();
			}
			j++;
    }
  }
 }
 fclose(f);
}
/////////////////////////////////////////////////////////////


////////ELIMINAR/////////////////////////////////////////////    
void Eliminar(char *nombreArch){
	long int fecha;
	Tregdiario aux;
	char msj[50];
  FILE *f;
  f = fopen(nomArch,"rb+");
	
	printf("\nIngrese la fecha que desea eliminar:\n");
	CargarFecha(&fecha);
	while(fread(&aux,sizeof(Tregdiario),1,f) >0){ // confirmar antes de eliminar...
		if((fecha == aux.ddmmyyyy) && (!aux.borrado)){
			aux.borrado = 1;
			fseek(f,-1*sizeof(Tregdiario),SEEK_CUR);
			fwrite(&aux, sizeof(Tregdiario), 1, f);
			fclose(f);
			printf("\nEliminación exitosa!\n");
			return;
		}
	}
	fclose(f);
	printf("No hay registros cargados para el dia %li. \n\n",fecha);		
}
/////////////////////////////////////////////////////////////


///////MODIFICAR ////////////////////////////////////////////    
void Modificar(char *nombreArch){
	long int fecha;
	Tregdiario aux;
	char msj[50];
  FILE *f;
  f = fopen(nomArch,"rb+");
	printf("\nIngrese la fecha del registro que desea modificar.\n");
	CargarFecha(&fecha);
	while(fread(&aux,sizeof(Tregdiario),1,f) >0){
		if((fecha == aux.ddmmyyyy) && (!aux.borrado)){
			fseek(f,-1*sizeof(Tregdiario),SEEK_CUR);
			Cargaregistro(&aux);
			fwrite(&aux, sizeof(Tregdiario), 1, f);
			fclose(f);
			printf("La edición se realizó con exito.\n");
			return;
		}
	}
	fclose(f);
	printf("No hay registros cargados para el dia %li. \n\n",fecha);
}
/////////////////////////////////////////////////////////////


//////ARCHIVO A ARREGLO//////////////////////////////////////     
void PasaAlArreglo (char *nomArch, Tregdiario arreglo[], int *cantElem){ //Copia los valores de los registros activos del archivo a un arreglo para su manipulacion
	Tregdiario aux;
	int i = 0;
	*cantElem = 0; //almacena la cantidad de elementos del arreglo
	FILE *f;
	f = fopen(nomArch,"rb");  //Abrir el archivo para lectura
	while (fread(&aux,sizeof(Tregdiario),1,f) > 0){ //Lectura secuencial del archivo
		if (!aux.borrado){ //Comprobación de registros activos
			arreglo[i] = aux;
			i = i + 1;
			*cantElem = *cantElem + 1;
		}
	}
	fclose(f);
}
/////////////////////////////////////////////////////////////


//////BUSQUEDA RECURSIVA DE REGISTRO/////////////////////////     
int BusquedaRecursiva (Tregdiario arreglo[], int cantElem, long int fechaBuscar){
	cantElem = cantElem -1;
	if (cantElem < 0){ //Si no hay elementos en el arreglo o se lo recorre por completo sin encontrar el elemento buscado
		printf ("No se encontro el registro.\n");
		return -1;
	}	
	if (fechaBuscar == arreglo[cantElem].ddmmyyyy){ //Si se encuentra el elemento buscado
		return cantElem;
	}
	return BusquedaRecursiva (arreglo, cantElem, fechaBuscar); //LLamada recursiva para buscar en el siguiente elemento
}
//////////////////////////////////////////////////////////////

//////BUSQUEDA ///////////////////////////////////////////////     
void Buscar(Tregdiario arreglo[]){ //Define los paramentros necesarios para la busqueda recursiva del elemento
	int dia;
	long int fechaBuscar;
	CargarFecha (&fechaBuscar);
	dia = BusquedaRecursiva(arregloActivo, cant, fechaBuscar);
	if (dia != -1){
		printf ("El registro se encuentra en la posición n°: %d \n", dia + 1);
		printf("\n----------------------------------------------------------------------------------------------\n");
  		printf("Al dia %li/%li/%li, se registraron los siguientes parametros climaticos:\n\n",(arreglo[dia].ddmmyyyy/1000000),((arreglo[dia].ddmmyyyy/10000)%100),(arreglo[dia].ddmmyyyy%10000));
  		printf("Temperatura máxima:%d\n",arreglo[dia].tmax);
  		printf("Temperatura mínima:%d\n",arreglo[dia].tmin);
  		printf("Humedad promedio:%d \n",arreglo[dia].HUM);
  		printf("Presión atmosferica:%d hPa\n",arreglo[dia].PNM);
  		printf("Dirección del viento:%d  \n",arreglo[dia].DV);
 		 printf("Velocidad del viento:%d km/h \n",arreglo[dia].FF);
  		printf("Precipitaciones:%d mm\n",arreglo[dia].PP);
		printf("----------------------------------------------------------------------------------------------\n");
	}
}

//////////////////////////////////////////////////////////////

//////PASAR A LISTA Y ORDENAR TEMPERATURA MAXIMA/////////////     
void OrdenarMayorTemp (Tregdiario arreglo[], int cantElem){
	int max;
	int i = 0;
	q = CrearLista();
	max = arreglo[i].tmax; //Tratamiento del primer elemento
	while (i < cantElem){ //Armado de la lista y recorrido del arreglo con tratamiento del primer elemento para determinar el mayor valor de tmax
		InsertarCabeza(&q, arreglo, i);
		if (arreglo[i].tmax > max){ 
			max = arreglo[i].tmax;
		}
		i = i + 1; 
	}
	printf ("La máxima temperatura alcanzada es de %d °, registrada los siguientes días: \n", max);
	while (q !=NULL){
		if (q->info.tmax == max){ //Recorrido secuencial de la lista buscando nodos con el valor maximo de temperatura registrado
			printf (" %li/%li/%li\n",(q->info.ddmmyyyy/1000000),((q->info.ddmmyyyy/10000)%100),(q->info.ddmmyyyy%10000));
		}
		q = q->next;
	}
}
/////////////////////////////////////////////////////////////


//////ORDENAR PRECIPITACIONES MAXIMAS////////////////////////      
void OrdPrecipitMax (Tregdiario arreglo[], int cantElem){ //Bubble sort con condición de comparación invertida
	Tregdiario aux;
	int i = cantElem; //Indice inicializado con el tamaño final del arreglo
	int j;
	while (i > 0){
		j = 0;
		while (j < i){
			if (arreglo[j].PP < arreglo[j+1].PP){ //El lugar de mover el mayor elemento al final mueve el menor
				aux = arreglo[j];
				arreglo[j] = arreglo[j+1];
				arreglo[j+1] = aux;
			}
			j = j + 1;
		}
		i = i - 1;
	}
	i = 0;
	printf("\n----------------------------------------------------------------------------------------------\n");
	while ((i <= 9) && (i < cantElem)){
		printf ("El día %li/%li/%li, el registro de precipitaciones fue de: %d mm\n",(arreglo[i].ddmmyyyy/1000000),((arreglo[i].ddmmyyyy/10000)%100),(arreglo[i].ddmmyyyy%10000), arreglo[i].PP);
		i = i + 1;
	}
	printf("\n----------------------------------------------------------------------------------------------\n");
}
/////////////////////////////////////////////////////////////


//////ORDENAR MAYOR VIENTO///////////////////////////////////     
void OrdenarMayorViento (Tregdiario arreglo[], int cantElem){ //Insertion sort con condición de comparación invertida
	int i;
	int j;
	Tregdiario aux;
	i = 1;
	while (i <= cantElem){
		aux = arreglo[i];
		j = i - 1;
		while (j > -1 && arreglo[j].FF < aux.FF){
			arreglo[j+1] = arreglo[j];
			j = j - 1;
		}
		arreglo[j+1] = aux;
		i = i + 1;
	}
	i = 0;
	printf("\n----------------------------------------------------------------------------------------------\n");
	while ((i <= 9) && (i < cantElem)){
		printf ("El día %li/%li/%li, el registro de mayor velocidad del viento fue de: %d km/h\n",(arreglo[i].ddmmyyyy/1000000),((arreglo[i].ddmmyyyy/10000)%100),(arreglo[i].ddmmyyyy%10000), arreglo[i].FF);
		i = i + 1;
	}
	printf("\n----------------------------------------------------------------------------------------------\n");
}
/////////////////////////////////////////////////////////////

//////CREAR COPIA DE RESPALDO////////////////////////////////     
void CrearRespaldo(char *nombResp){
	time_t t = time(NULL); //Establece un puntero al valor de tiempo actual
	struct tm tiempoLocal = *localtime(&t); // Define una variable del tipo tm con la estructura de presentación del tiempo local
	char fecha[50];
	char *formato = "(%d-%m-%Y|%H:%M)"; //Forma de presentación de las variables de tiempo (dia, mes, año, hora, minutos)
	strftime(fecha, sizeof(fecha), formato, &tiempoLocal);//Guarda en una variable la información del tiempo en el formato previamente establecido
	strcat(nombResp,directorio);
	strcat(nombResp, nombreFecha);
  strcat(nombResp,fecha);
  strcat(nombResp, ext); // Las 4 lineas construyen el nombre final del archivo de respaldo
  printf("Nombre del respaldo: %s\n", nombResp);
		if ((f = fopen(nombResp, "rb"))  == NULL){ // Verifica si existe un archivo con ese nombre
			printf ("No existe o no puede abrirse el archivo. ¿Desea crear un archivo con ese nombre?(s/n)\n");
			scanf("%s", &sn);
			if (sn == 's')
		{
			f = fopen(nombResp,"wb+");//Crea el archivo de respaldo
			printf ("El archivo ha sido creado exitosamente\n");
			fclose(f);
		} else {
			printf("Se optó por no crear el archivo...\n");
		}
	} else {
		printf("Ya existe un archivo con ese nombre.\n");
		fclose(f);
	}
}
/////////////////////////////////////////////////////////////


//////COPIA DE SEGURIDAD////////////////////////////////////     
void CopiaBackup (char *original, char *copia){ //Toma el nombre de ambos archivos y copia los parametros de uno al otro
	Tregdiario aux;
	int i = 1;
	f = fopen(original,"rb"); // Abre el archivo original para lectura
	b = fopen(copia, "wb"); // Abre el archivo de respaldo para escritura
	while ((fread(&aux,sizeof(Tregdiario), 1, f) > 0)){ //Mientras haya información en el archivo...
		if (!aux.borrado){ 
			fwrite(&aux, sizeof(Tregdiario), 1, b); //Escribe el registro en el archivo de respaldo
			printf ("Registro n° %d copiado con exito!!!\n", i);
			i = i + 1;
		}
	}
	fclose(f);
	fclose(b);
}
/////////////////////////////////////////////////////////////



int main() {
	 printf("//////////////////////////////////////////////////////////////////\n");
   system("date");
   printf("||        ------SERVICIO METEOROLOGICO LOCAL-------             ||\n");
   printf("||                                                              ||\n");
   printf("||     Bienvenid@ al sistema de registro climatico!             ||\n");
   printf("||                                                              ||\n");
   printf("|| Antes de comenzar a operar, debera crear un archivo de       ||\n");
   printf("|| registro anual, o bien abrir uno existente...                ||\n");
   printf("||                                                              ||\n");
   printf("//////////////////////////////////////////////////////////////////\n");
   Apertura(nomArch,directorio);
   PasaAlArreglo(nomArch, arregloActivo, &cant);	
	system("clear");
	do{
   printf("/////////////////////////////////////////////////////////////////\n");
   system("date");
   printf("||        ------SERVICIO METEOROLOGICO LOCAL-------             ||\n");
   printf("||                                                              ||\n");
   printf("|| Ingrese el número correspondiente a la opción solicitada:    ||\n");
   printf("||                                                              ||\n");
   printf("|| 1) Cargar un registro diario                                 ||\n");
   printf("|| 2) Eliminar un registro diario                               ||\n");
   printf("|| 3) Buscar un registro por fecha                              ||\n");
   printf("|| 4) Modificar un registro diario                              ||\n");
   printf("|| 5) Lista de registros cargados                               ||\n");
   printf("|| 6) Mostrar registros superiores de precipitaciones maximas   ||\n");
   printf("|| 7) Mostrar registros superiores de velocidades del viento    ||\n");
   printf("|| 8) Mostrar registros superiores de temperatura máxima        ||\n");
   printf("|| 9) Crear copia de respaldo                                   ||\n");
   printf("|| 0) Salir del programa                                        ||\n");
   printf("||                                                              ||\n");
   printf("//////////////////////////////////////////////////////////////////\n");
   scanf ("%d", &opcion);
        switch (opcion){
            case 1: system("clear");
                    AltaRegistro(nomArch);
                    PasaAlArreglo (nomArch,arregloActivo,&cant);break;
            case 2: system("clear");
                    Eliminar(nomArch);
                    PasaAlArreglo (nomArch,arregloActivo,&cant);break;
            case 3: system("clear");
                    Buscar(arregloActivo);break;
            case 4: system("clear");
                    Modificar(nomArch);
										PasaAlArreglo (nomArch,arregloActivo,&cant);break;
            case 5: system("clear");
                    MostrarRegistroClima(nomArch);break;
            case 6: system("clear");
            				OrdPrecipitMax(arregloActivo, cant);break;
            case 7: system("clear");
            				OrdenarMayorViento(arregloActivo, cant);break;
            case 8: system("clear");
            				OrdenarMayorTemp (arregloActivo, cant);break;
            case 9: system("clear");
            				CrearRespaldo(nombreRespaldo);
            				CopiaBackup(nomArch, nombreRespaldo);break;
            case 0: printf("Cerrando el programa...\n");break;           				           				            				
            default : system("clear");
            					printf ("El numero ingresado es incorrecto, intente nuevamente.\n");
        }
    }while (opcion != 0);
    return 0;
}

