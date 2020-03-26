#include <stdio.h>
#include <stdlib.h>

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
    int cédula;
    int teléfono;
    int sexo;
    point puntos[10];
}Cliente;

void ad_cl(); //Esta funcion es para la recopilacion de datos, tengo en plan separarla en 3 pero para ir manteniendo orden es mejor ir creando y editando

void menu();

void fin(); //Dentro es cual sera su funcion.

int main(){
    //En las 3 sgtes lineas podremos ver la creacion de datos pero realmente hace falta variables de archivos pero no se bn usarlar, estas para guardar la informacion de los clientes.
    int opcion,Inicio,admin,c_opcion,cant_cliente=0;
    Game juegos[10];
    Cliente usuario[10];
    printf("Bienvenido al Casino.\n");
    ad_cl();//Todavia estoy ideando una manera de sacar todos los datos pero debo tener el medio externo.
    return 0;
}

void ad_cl(){
    printf("Es Usted administrador o Cliente: \n \t 1 - administrador \n \t 2 - Cliente \n");
    scanf("%d",&opcion);
    switch(opcion){ //Dentro de ambos casos se necesita guardar en un archivo externo
        case 1:
            printf("Usted debera Ingresar la Informacion de 10 Juegos: \n");
            for(admin=0;admin<10;admin++){
                    printf("Ingrese la Informacion del Juego #%d:",admin+1);
                    printf("Ingrese el Nombre:\n");
                    getc(juegos[admin].nombre);
                    printf("Ingrese el Codigo del Juego:\n");
                    scanf("%d",&juegos[admin].codigo);
                    printf("Ingrese el la cantidad de puntos que vale el euro en este Juego:\n");
                    scanf("%d",&juegos[admin].euro);
            }
            opcion=2;
            break;
        case 2:
            printf("Es usted un Nuevo Cliente: \n \t 1 - Si \n \t 2 - No \n");
            scanf("%d",&c_opcion);
            switch (c_opcion){
                case 1: //Aqui se necesita guardar en un archivo externo la informacion.
                    printf("Ingrese su nombre:\n");
                    getc(usuario[cant_cliente].nombre);
                    printf("Ingrese la Cedula:\n");
                    scanf("%d",usuario[cant_cliente].cédula);
                    printf("Ingrese su # telefonico sin guiones:");
                    scanf("",usuario[cant_cliente].teléfono);
                    printf("Ingrese su Sexo: \n \t 1 - Hombre \n \t 2 - Mujer \n \t 3 - Otro \n");
                    scanf("",usuario[cant_cliente].sexo);
                    cant_cliente++;
                    break;
                case 2://Aqui crear un modo de busqueda y recopilacion de archivos externo
                    break;
                default:
                    printf("Error, A ingresado un numero no valido \n Reinicio. \n");
            }

        default:
            printf("Error, A ingresado un numero no valido \n Reinicio. \n");
            ad_cl();
        }
}

void menu(){
    printf("Que desea realizar? \n \t 1. Desea Introducir puntos de un jugador. \n \t 2. Mostrar puntos conseguidos de un jugador. \n \t 3. Desea calcular los euros ganados por un jugador. \n \t  4. Desea Terminar.  \n");
    usuario sustituible; //esta variable es para poder sustituir la informacion del cliente con la externa y poder mostrarla.
    switch (c_opcion){
        case 1:

            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            fin();
            break;
        default:
            printf("Error, A ingresado un numero no valido \n Reinicio. \n");
            menu();
        }
}

void fin(){
    /* Al finalizar el día, el usuario elegirá esta opción, que le permitirá terminar la ejecución del programa y, además,
    el programa le deberá indicar la cantidad total de euros que la Sala de Juegos ha entregado ese día y
     número del juego que más euros ha entregado ese día.*/
}
