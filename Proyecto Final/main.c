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

int New_Client();//Lista y probada                                 (Debo editar para que obtenga los codigo de los juegos.)
int Ten_Game();//Lista y probada                               (Debo editar y anadir que pueda coger los datos desde fuera.)
int Old_Client();//Lista y probada                                      (Devuelve el # del archivo del cliente.)
int veri_Existe(int cont);//Lista y probada                      (Devuelve 0 si existe y el 1er # que encuentra y no existe.)
int creador();//Lista y probada
void menu(int val);

int main(){
    int seguro,val,elige,opcion=0;
    printf("Bienvenido al Casino.\n");
    do{
        if(opcion!=0){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
        printf("Es usted: \n \t 1 - Administrador. \n \t 2 - Cliente. \n");
        scanf("%d",&opcion);
    }while(opcion!=1 && opcion!=2);
    do{
        fflush( stdin );
        switch(opcion){
            case 1:
                opcion=Ten_Game();
                break;
            case 2:
                printf("Saludos espero que su estadia sea placentera.\n");
                printf("Es usted un Nuevo Cliente:\n \t 1 - Si.\n \t 2 - No.\n");
                scanf("%d",&elige);
                switch(elige){
                    case 1:
                        val=New_Client();//Devuelve el numero del archivo del cliente.
                        break;
                    case 2:
                        val=Old_Client();//Devuelve el numero del archivo del cliente.
                        break;
                }
                break;
        }
    }while(opcion==1);
    return 0;
}

int Ten_Game(){
    FILE* Ten = fopen("D_Juegos.txt","wb");
    Game juegos[10];
    int admin;
    printf("Usted debera Ingresar la Informacion de los 10 Juegos: \n");
    for(admin=0;admin<10;admin++){
        fflush(stdin);
        printf("Ingrese la Informacion del Juego #%d: \n",admin+1);
        printf("Ingrese el Nombre: \n");
        scanf("%s",juegos[admin].nombre);
        juegos[admin].codigo=admin;
        printf("Ingrese el la cantidad de puntos que vale el euro en este Juego:\n");
        scanf("%d",&juegos[admin].euro);
        fprintf(Ten,"%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    return 2;
}

int New_Client(){
    int acum=creador();
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1,num=acum,admin=0;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", acum, nombre, extension);
    FILE* User;
    FILE* Ten;
    Cliente Usuario;
    printf("Ingrese su nombre:\n");
    scanf("%s",Usuario.nombre);
    printf("Ingrese la Cedula:\n");
    scanf("%d",&Usuario.cedula);
    printf("Ingrese su # telefonico sin guiones:\n");
    scanf("%d",&Usuario.telefono);
    printf("Ingrese su Sexo: \n \t 1 - Hombre \n \t 2 - Mujer \n \t 3 - Otro \n");
    scanf("%d",&Usuario.sexo);
    Ten = fopen("D_Juegos.txt","rb");
    while(feof(Ten)==0){
        fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
        printf("%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
        admin++;
    }
    fclose(Ten);
    User = fopen(fileSpec,"wb");
    fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    for(admin=0;admin<10;admin++){
            printf(".");
            fprintf(User,"%d %d \n",juegos[admin].codigo,Usuario.puntos[admin].cant=0);
    }
    fclose(User);
    return acum;
}

int Old_Client(){
    //Esta funcion deberia buscar dentro de un archivo informacion exacta.
    int opcion,ced;
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1,acum=0,num;
    FILE* datos;
    Cliente usuario;
    printf("Ingrese la cedula del Cliente:\n");
    scanf("%d",&ced);
    do{
        acum++;
        num=acum;
        while(num/10>0){
            num=num/10;
            digitos++;
        }
        char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
        snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", acum, nombre, extension);
        datos = fopen(fileSpec,"rb");
        fscanf(datos,"%d",&usuario.cedula);
        if(veri_Existe(acum)!=0){
            printf("Error,no se ha encontrado el archivo del Cliente, por favor verifique: #Cedula: %d \n\t 1 - La Cedula fue introducida de manera incorrectamente. \n\t 2 - Es un Nuevo Cliente.\n",ced);
            scanf("%d",&opcion);
            switch(opcion){
                case 1:
                    printf("El buscador se reiniciara, Espere un momento...\n");
                    fclose(datos);
                    acum=Old_Client();
                    return acum;
                    break;
                case 2:
                    fclose(datos);
                    acum=New_Client();
                    return acum;
                default:
                    printf("Error, no ha escogido una opcion valida...\n");
                    printf("El buscador se reiniciara, Espere un momento...\n");
                    fclose(datos);
                    acum=Old_Client();
                    return acum;
            }
        }
    }while(usuario.cedula!=ced);
    fclose(datos);
    return acum;
}

int creador(){
    int val,i=0;
    char buffer[21]={0};//Maximo de clientes a almacenar <1M,debido a que coge 14 espacios el comentario + 1 por el vacio y deja 4 libres para numeros.
    do{
        i++;
        val=veri_Existe(i);
    }while(val==0);
    sprintf(buffer, "%d - Cliente.txt", val);
    int acum=val;
    do{
        fopen(buffer, "wb");
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
    FILE* datos;
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", cont, nombre, extension );
    datos = fopen( fileSpec, "rb" );
    if(datos==NULL){
        //printf("El Cliente #%d no existe.\n",cont);
        fclose(datos);
        return cont;
    }
    else{
        //printf("El Cliente #%d existe.\n",cont);
        fclose(datos);
        return 0;
    }
}

void menu(int val){
    /*
1 Introducir puntos de un jugador.
2. Conocer los puntos que un jugador lleva conseguidos en un juego.
3. Mostrar para un jugador los puntos conseguidos en cada juego que ha participado.
4. Calcular los euros ganados por un jugador.
5. Terminar.
*/
}
