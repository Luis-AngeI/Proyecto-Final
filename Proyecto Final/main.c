#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "milib.h"

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
    int ganancia;
}Cliente;

int New_Client();
int Ten_Game();
int Old_Client();
void calculadora(int val);
void calculadora_especifica(int val);
void Mostrar(int val);
void Mostrar_especifico(int val);
void menu(int val);

int main(){
    int val,elige,opcion;
    printf("Bienvenido al Casino.\n");
    do{
        printf("Es usted: \n \t 1 - Administrador. \n \t 2 - Cliente. \n");
        scanf("%d",&opcion);
        if(opcion<1 || opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    do{
        fflush( stdin );
        if(opcion==-1){
            opcion=2;
        }
        switch(opcion){
            case 1:
                system("cls");
                opcion=Ten_Game();
                break;
            case 2:
                do{
                    printf("Saludos espero que su estadia sea placentera.\n");
                    printf("Es usted un Nuevo Cliente:\n \t 1 - Si.\n \t 2 - No.\n");
                    scanf("%d",&elige);
                    if(opcion<1 || opcion>2){
                        printf("Error, numero invalido, seleccione nuevamente.\n");
                    }
                }while(opcion<1 || opcion>2);
                system("cls");
                switch(elige){
                    case 1:
                        val=New_Client();//Devuelve el numero del archivo del cliente.
                        menu(val);
                        break;
                    case 2:
                        val=Old_Client();//Devuelve el numero del archivo del cliente.
                        menu(val);
                        break;
                }
                break;
        }
    }while(opcion==-1);
    return 0;
}

int Ten_Game(){
    FILE* Ten;
    Game juegos[10];
    int admin;
    printf("Usted debera Ingresar la Informacion de los 10 Juegos: \n \t 1 - Introducirlos Directamente. \n \t 2 - Importar de almacenamiento Externo. \n");
    scanf("%d",&admin);
    switch(admin){
        case 1:
            Ten = fopen("D_Juegos.txt","wb");
            for(admin=0;admin<10;admin++){
                fflush(stdin);
                printf("Ingrese la Informacion del Juego #%d: \n",admin+1);
                printf("Ingrese el Nombre: \n");
                scanf("%s",juegos[admin].nombre);
                juegos[admin].codigo=admin;
                printf("Ingrese el la cantidad de puntos que vale el euro en este Juego:\n");
                scanf("%d",&juegos[admin].euro);
                fprintf(Ten,"%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
                system("cls");
            }
            break;
        case 2:
            Ten = fopen("D_Juegos.txt","rb");
            if(Ten==NULL){
                    fclose(Ten);
                    printf("El archivo no existe.\nEsta Seccion se reiniciara.\n");
                    return Ten_Game();
            }
            else
                for(admin=0;admin<10;admin++){
                    fscanf(Ten,"%d %s %d \n",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
                    printf(" Codigo: %d \t Nombre: %s \t Cant.Puntos*Euro: %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
            }
            break;
        default:
            printf("Error,numero no valido,Esta Seccion se reiniciara. \n");
            return Ten_Game();
        }
    fclose(Ten);
    return -1;
}

int New_Client(){
    int digitos=1,admin=0,acum=0,num=acum,ced;
    char* nombre = " - Cliente";
    char* extension = ".txt";
    FILE* User;
    FILE* Ten;
    Cliente Usuario;
    printf("Ingrese su Cedula:\n");
    scanf("%d",&Usuario.cedula);
    do{
        fclose(User);
        acum++;
        num=acum;
        while(num/10>0){
            num=num/10;
            digitos++;
        }
        char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
        snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", acum, nombre, extension);
        User = fopen(fileSpec,"rb");
        fscanf(User,"%d",&ced);
        if(veri_Existe(acum)!=0){
            break;
        }
    }while(Usuario.cedula!=ced);
    fclose(User);
    if(Usuario.cedula==ced){
        printf("Esta cedula, ya esta registrada,sera redirigido a su cuenta. \nCon propositos de confirmacion por favor, nuevamente ");
        return Old_Client();
    }
    else{
        acum=creador();
        digitos=1;
        num=acum;
        Game juegos[10];
        while(num/10>0){
            num=num/10;
            digitos++;
        }
        char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
        snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", acum, nombre, extension);
        printf("Ingrese su Cedula:\n%d\n",Usuario.cedula);
        printf("Ingrese su nombre:\n");
        scanf("%s",Usuario.nombre);
        printf("Ingrese su # telefonico sin guiones:\n");
        scanf("%d",&Usuario.telefono);
        do{
            printf("Ingrese su Sexo: \n \t 1 - Hombre \n \t 2 - Mujer \n \t 3 - Otro \n");
            scanf("%d",&Usuario.sexo);
            if(Usuario.sexo<1 || Usuario.sexo>3){
                system("cls");
                printf("Error,Numero invalido,por favor seleccione nuevamente.\n");
            }
        }while(Usuario.sexo<1 || Usuario.sexo>3);
        Ten = fopen("D_Juegos.txt","rb");
        while(feof(Ten)==0){
            fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
            admin++;
        }
        fclose(Ten);
        User = fopen(fileSpec,"wb");
        fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
        for(admin=0;admin<10;admin++){
            fprintf(User,"%d %d \n",juegos[admin].codigo,Usuario.puntos[admin].cant=0);
        }
        fclose(User);
        return acum;
    }
}

int Old_Client(){
    //Esta funcion deberia buscar dentro de un archivo informacion exacta.
    int opcion,ced;
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1,acum=0,num;
    FILE* datos;
    Cliente Usuario;
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
        fscanf(datos,"%d",&Usuario.cedula);
        if(veri_Existe(acum)!=0){
            printf("Error,no se ha encontrado el archivo del Cliente, por favor verifique: #Cedula: %d \n\t 1 - La Cedula fue introducida de manera incorrectamente. \n\t 2 - Es un Nuevo Cliente.\n",ced);
            scanf("%d",&opcion);
            system("cls");
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
    }while(Usuario.cedula!=ced);
    fclose(datos);
    num=acum;
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char file[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( file, sizeof( file ), "%d%s%s", acum, nombre, extension);
    datos = fopen(file,"rb");
    fscanf(datos,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    printf("La Informacion del Usuario es:\n \t Archivo #%d \n \t Cedula: %d \n \t Nombre: %s \n \t Telefono: %d \n \t Sexo: ",acum,Usuario.cedula,Usuario.nombre,Usuario.telefono);
    switch(Usuario.sexo){
        case 1:
            printf("Hombre. \n");
            break;
        case 2:
            printf("Mujer. \n");
            break;
        case 3:
            printf("Otro. \n");
        break;
    }
    fclose(datos);
    return acum;
}

void Anadir(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1,cod,acum=11,cant=0,opcion;
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    Cliente Usuario;
    Game juegos[10];
    FILE* Ten = fopen("D_Juegos.txt","rb");;
    for(admin=0;admin<10;admin++){
        fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
        printf(" Codigo: %d \t Nombre: %s \t Cant.Puntos*Euro: %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fscanf(User,"%d %d ",&juegos[admin].codigo,&Usuario.puntos[admin].cant);
    }
    fclose(User);
    printf("Ingrese el codigo del juego al que desea añadir puntos:\n");
    scanf("%d",&cod);
    for(admin=0;admin<10;admin++){
            if(cod==juegos[admin].codigo){
                acum=admin;
            }
    }
    if(acum==11){
        printf("Error,el codigo ingresado no coincide con ningun juego, Por favor asegurese de escribirlo correctamente.\n Reiniciando ingreso de puntos.\n");
        Anadir(val);
    }
    else{
        printf("Ingrese la cantidad de puntos que ha obtenido:\n");
        scanf("%d",&cant);
        Usuario.puntos[acum].cant+=cant;
        User= fopen(fileSpec,"wb");
        fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
        for(admin=0;admin<10;admin++){
            fprintf(User,"%d %d \n",juegos[admin].codigo,Usuario.puntos[admin].cant);
        }
    }
    fclose(User);
    do{
        printf("Desea ver todos sus puntos: \n \t 1 - Si. \n \t 2 - No. \n");
        scanf("%d",&opcion);
        if(opcion<1 && opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    if(opcion==1){
        system("cls");
        Mostrar(val);
    }
    do{
        printf("Desea añadir mas puntos: \n \t 1 - Si. \n \t 2 - No. \n");
        scanf("%d",&opcion);
        if(opcion<1 && opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    if(opcion==1){
        system("cls");
        Anadir(val);
    }
}

void Mostrar(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1;
    Cliente Usuario;
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    printf("Su puntuacion es: \n");
    for(admin=0;admin<10;admin++){
        fscanf(User,"%d %d ",&Usuario.puntos[admin].code_game,&Usuario.puntos[admin].cant);
        printf(" Codigo: %d \t Puntos: %d \n",Usuario.puntos[admin].code_game,Usuario.puntos[admin].cant);
    }
    fclose(User);
}

void Mostrar_especifico(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1,acum=11,cod,opcion;
    Cliente Usuario;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    FILE* Ten = fopen("D_Juegos.txt","rb");
    printf("Los Juegos Son:\n");
    for(admin=0;admin<10;admin++){
        fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
        printf("Codigo: %d \t Nombre: %s \t Cant.Puntos*Euro: %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    printf("La Informacion del Usuario es:\n \t Cedula: %d \n \t Nombre: %s \n \t Telefono: %d \n \t Sexo: %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    for(admin=0;admin<10;admin++){
        fscanf(User,"%d %d ",&Usuario.puntos[admin].code_game,&Usuario.puntos[admin].cant);
    }
    do{
        printf("Ingrese el codigo del juego que desea ver puntos:\n");
        scanf("%d",&cod);
        for(admin=0;admin<10;admin++){
                if(cod==Usuario.puntos[admin].code_game){
                    acum=admin;
                }
        }
        if(acum==11){
            printf("Error,el codigo del juego no existe, por favor \n:\n");
        }
    }while(acum==11);
    for(admin=0;admin<10;admin++){
        if(Usuario.puntos[acum].code_game==juegos[admin].codigo){
                printf("Usted Tiene %d puntos en el juego %s.\n",Usuario.puntos[acum].cant,juegos[admin].nombre);
        }
    }
    fclose(User);
    do{
        printf("Desea revisar otra puntuacion: \n \t 1 - Si. \n \t 2 - No. \n");
        scanf("%d",&opcion);
        if(opcion<1 || opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    if(opcion==1){
        system("cls");
        Mostrar_especifico(val);
    }
}

void calculadora(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,digitos=1,admin,cont,opcion;
    Cliente Usuario;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    FILE* Ten;
    Ten = fopen("D_Juegos.txt","rb");
    for(admin=0;admin<10;admin++){
        fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User;
    User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fscanf(User,"%d %d ",&Usuario.puntos[admin].code_game,&Usuario.puntos[admin].cant);
    }
    fclose(User);
    Usuario.ganancia=0;
    for(admin=0;admin<10;admin++){
            for(cont=0;cont<10;cont++){
                    if(Usuario.puntos[admin].code_game==juegos[cont].codigo){
                            Usuario.ganancia=Usuario.ganancia+(juegos[cont].euro*Usuario.puntos[admin].cant);
                    }
            }
    }
    printf("Usted tiene hasta ahora %d euros ganados.\n",Usuario.ganancia);
    do{
        printf("Desea retirar sus ganancias?\n\n\t 1 - Si.\n\t 2- No.\n");
        scanf("%d",&opcion);
        if(opcion<1 || opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    if(opcion==1){
        printf("Usted a retirado un monto de %d Euros",Usuario.ganancia);
        for(admin=0;admin<10;admin++){
                Usuario.puntos[admin].cant=0;
        }
    }
    User= fopen(fileSpec,"wb");
    fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fprintf(User,"%d %d \n",Usuario.puntos[admin].code_game,Usuario.puntos[admin].cant);
    }
    fclose(User);
}

void calculadora_especifica(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,digitos=1,admin,opcion,cod,acum=11;
    Cliente Usuario;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    FILE* Ten;
    Ten = fopen("D_Juegos.txt","rb");
    printf("La Informacion de los Juegos es:\n");
    for(admin=0;admin<10;admin++){
        fscanf(Ten,"%d %s %d ",&juegos[admin].codigo,juegos[admin].nombre,&juegos[admin].euro);
        printf(" Codigo: %d \t Nombre: %s \t Cant.Punto*Euro: %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User;
    User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fscanf(User,"%d %d ",&Usuario.puntos[admin].code_game,&Usuario.puntos[admin].cant);
    }
    fclose(User);
    do{
        printf("Ingrese el codigo del juego que desea calcular euros ganados:\n");
        scanf("%d",&cod);
        for(admin=0;admin<10;admin++){
                if(cod==Usuario.puntos[admin].code_game){
                    acum=admin;
                }
        }
        if(acum==11){
            printf("Error,el codigo del juego no existe, por favor \n:\n");
        }
    }while(acum==11);
    for(admin=0;admin<10;admin++){
        if(Usuario.puntos[acum].code_game==juegos[admin].codigo){
            Usuario.ganancia=juegos[admin].euro*Usuario.puntos[acum].cant;
            printf("Usted tiene hasta ahora %d euros ganados en el juego de %s.\n",Usuario.ganancia,juegos[admin].nombre);
            do{
                printf("Desea retirar sus ganancias?\n\t 1 - Si.\n\t 2- No.\n");
                scanf("%d",&opcion);
                if(opcion<1 || opcion>2){
                    printf("Error, numero invalido, seleccione nuevamente.\n");
                }
            }while(opcion<1 || opcion>2);
            if(opcion==1){
                printf("Usted a retirado un monto de %d Euros, del Juego de %s.\n",Usuario.ganancia,juegos[admin].nombre);
                Usuario.puntos[acum].cant=0;
            }
        }
    }
    User= fopen(fileSpec,"wb");
    fprintf(User,"%d %s %d %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fprintf(User,"%d %d \n",Usuario.puntos[admin].code_game,Usuario.puntos[admin].cant);
    }
    fclose(User);
    do{
        printf("Desea Calcular los euros de otra puntuacion: \n \t 1 - Si. \n \t 2 - No. \n");
        scanf("%d",&opcion);
        if(opcion<1 || opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>2);
    if(opcion==1){
        system("cls");
        calculadora_especifica(val);
    }
}

void menu(int val){
    int opcion;
    do{
        printf("Seleccione la accion que desea realizar:\n \t 1 - Introducir puntos de un jugador.\n \t 2 - Conocer los puntos que un jugador lleva conseguidos en un juego.\n \t 3 - Mostrar para un jugador los puntos conseguidos en cada juego que ha participado.\n \t 4 - Calcular los euros ganados por un juego.\n \t 5 - Calcular el total de euros ganados por un jugador.\n \t 6 - Terminar.\n");
        scanf("%d",&opcion);
        if(opcion<1 || opcion>6){
            system("cls");
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 || opcion>6);
    switch(opcion){
        case 1:
            //1 Introducir puntos de un jugador.
            system("cls");
            Anadir(val);
            system("cls");
            menu(val);
            break;
        case 2:
            //2. Conocer los puntos que un jugador lleva conseguidos en un juego.
            system("cls");
            Mostrar_especifico(val);
            system("cls");
            menu(val);
            break;
        case 3:
            //3. Mostrar para un jugador los puntos conseguidos en cada juego que ha participado.
            system("cls");
            Mostrar(val);
            menu(val);
            break;
        case 4:
            //4 - Calcular los euros ganados en un juego por un jugador.
            system("cls");
            calculadora_especifica(val);
            system("cls");
            menu(val);
            break;
        case 5:
            //5. Calcular el total de euros ganados por un jugador.
            system("cls");
            calculadora(val);
            system("cls");
            menu(val);
            break;
        case 6:
            //6. Terminar.
            system("cls");
            printf("Gracias por preferirnos.\n");
            break;
        default:
            system("cls");
            printf("Error,El menu se reiniciara.\n");
            menu(val);
        }
}
