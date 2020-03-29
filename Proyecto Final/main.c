#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nombre[30];
    int codigo;
    int euro;
}Game;

typedef struct{
    int cant;
    int code_game;
}Point; // Esta es para poder introducir los puntos por juego relacionandola a la de clientes

typedef struct{
    char nombre[30];
    int cedula;
    int telefono;
    int sexo;
    Point puntos[10];
}Cliente;

void New_Client();
void Ten_Game();
void Old_Client();
int veri_Existe(int cont);//Lista y probada
int creador();

int main(){
    New_Client();
    return 0;
}

void Ten_Game(){
    FILE* Ten = fopen("D_Juegos.txt","w");
    Game juegos[10];
    printf("Usted debera Ingresar la Informacion de los 10 Juegos: \n");
    for(int admin=0;admin<10;admin++){
        printf("Ingrese la Informacion del Juego #%d: \n",admin+1);
        printf("Ingrese el Nombre: \n");
        scanf("%s",juegos[admin].nombre);
        printf("Ingrese el Codigo del Juego:\n");
        scanf("%d",&juegos[admin].codigo);
        printf("Ingrese el la cantidad de puntos que vale el euro en este Juego:\n");
        scanf("%d",&juegos[admin].euro);
        fprintf(Ten,"%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
}

void New_Client(){
    int acum=creador();
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1,num=acum;
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", acum, nombre, extension);
    FILE *User;
    do{
        User = fopen(fileSpec,"wb");
    }while(User==NULL);
    Cliente Usuario;
    printf("Ingrese su nombre:\n");
    scanf("%s",Usuario.nombre);
    printf("Ingrese la Cedula:\n");
    scanf("%d",Usuario.cedula);
    printf("Ingrese su # telefonico sin guiones:\n");
    scanf("%d",Usuario.telefono);
    printf("Ingrese su Sexo: \n \t 1 - Hombre \n \t 2 - Mujer \n \t 3 - Otro \n");
    scanf("%d",Usuario.sexo);
    fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    fclose(User);
}

void Old_Client(){
    //Esta funcion deberia buscar dentro de un archivo informacion exacta.
}

int creador(){
    int val,i=0;
    char buffer[80]={0};
    do{
        i++;
        val=veri_Existe(i);
    }while(val==0);
    sprintf(buffer, "%d - Cliente.txt", val);
    int acum=val;
    do{
        fopen(buffer, "w");
        val=veri_Existe(val);
    }while(acum==val);
    printf("Ya se ha creado correctamente el archivo del Cliente #%d,Puede proceder a Ingresar.\n",acum);
    return acum;
}

int veri_Existe(int cont){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1;
    int num=cont;
    while(num/10>0)
    {
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    FILE *datos;
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", cont, nombre, extension );
    datos = fopen( fileSpec, "rb" );
   if(datos==NULL){
       printf("El Cliente #%d no existe.\n",cont);
       return cont;
   }
   else{
       return 0;
   }
}
