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
    int ganancia;
}Cliente;

int New_Client();//Lista y probada                                 (Debo editar para que obtenga los codigo de los juegos.)
int Ten_Game();//Lista y probada                               (Debo editar y anadir que pueda coger los datos desde fuera.)
int Old_Client();//Lista y probada                                      (Devuelve el # del archivo del cliente.)
int veri_Existe(int cont);//Lista y probada                      (Devuelve 0 si existe y el 1er # que encuentra y no existe.)
int creador();//Lista y probada
int calculadora(int val);//Lista y probada
void Anadir(int val);
void Mostrar(int val);
void Mostrar_especifico(int val);
void menu(int val);

int main(){
    int val,elige,opcion;
    printf("Bienvenido al Casino.\n");
    do{
        printf("Es usted: \n \t 1 - Administrador. \n \t 2 - Cliente. \n");
        scanf("%d",&opcion);
        if(opcion<1 && opcion>2){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 && opcion>2);
    do{
        fflush( stdin );
        if(opcion==-1){
            opcion=2;
        }
        switch(opcion){
            case 1:
                opcion=Ten_Game();
                break;
            case 2:
                do{
                    printf("Saludos espero que su estadia sea placentera.\n");
                    printf("Es usted un Nuevo Cliente:\n \t 1 - Si.\n \t 2 - No.\n");
                    scanf("%d",&elige);
                    if(opcion<1 && opcion>2){
                        printf("Error, numero invalido, seleccione nuevamente.\n");
                    }
                }while(opcion<1 && opcion>2);
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
                    printf("%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
            }
            break;
        default:
            fclose(Ten);
            printf("Error,numero no valido,Se reiniciara. \n");
            return Ten_Game();
        }
    fclose(Ten);
    return -1;
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

void Anadir(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1,cod,acum=11,cant=0,repetidor,opcion;
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
        printf("%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    for(admin=0;admin<10;admin++){
            fscanf(User,"%d %d ",&juegos[admin].codigo,&Usuario.puntos[admin].cant);
    }
    fclose(User);
    do{
        repetidor=0;
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
        do{
            printf("Desea añadir mas puntos?\n\t 1 - Si. \n\t 2 - No.\n");
            scanf("%d",&opcion);
        }while(opcion<=0 || opcion >=3);
    }while(repetidor==1);
    fclose(User);
}

void Mostrar(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1;
    Cliente Usuario;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    char fileSpec[strlen(nombre)+strlen(extension)+digitos+1];
    snprintf( fileSpec, sizeof( fileSpec ), "%d%s%s", val, nombre, extension);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    printf("La Informacion del Usuario es:\n \t \t Cedula: %d \n \t Nombre: %s \n \t Telefono: %d \n \t Sexo: %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    printf("Su puntuacion es:");
    for(admin=0;admin<10;admin++){
        fscanf(User,"%d %d ",&juegos[admin].codigo,&Usuario.puntos[admin].cant);
        printf("%d %d ",juegos[admin].codigo,Usuario.puntos[admin].cant);
    }
    fclose(User);
}

void Mostrar_especifico(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,admin,digitos=1,acum=11,cod;
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
        printf("%d %s %d \n",juegos[admin].codigo,juegos[admin].nombre,juegos[admin].euro);
    }
    fclose(Ten);
    FILE* User= fopen(fileSpec,"rb");
    fscanf(User,"%d %s %d %d ",&Usuario.cedula,Usuario.nombre,&Usuario.telefono,&Usuario.sexo);
    printf("La Informacion del Usuario es:\n \t \t Cedula: %d \n \t Nombre: %s \n \t Telefono: %d \n \t Sexo: %d \n",Usuario.cedula,Usuario.nombre,Usuario.telefono,Usuario.sexo);
    //printf("Su puntuacion es:");
    for(admin=0;admin<10;admin++){
        fscanf(User,"%d %d ",&juegos[admin].codigo,&Usuario.puntos[admin].cant);
        //printf("%d %d ",juegos[admin].codigo,Usuario.puntos[admin].cant);
    }
    do{
        printf("Ingrese el codigo del juego que desea ver puntos:\n");
        scanf("%d",&cod);
        for(admin=0;admin<10;admin++){
                if(cod==juegos[admin].codigo){
                    acum=admin;
                }
        }
        if(acum==11){
            printf("Error,el codigo del juego no existe, por favor \n:\n");
        }
    }while(acum==11);
    fclose(User);
}

int calculadora(int val){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int num=val,digitos=1,admin,cont,opcion;
    Cliente Usuario;
    Game juegos[10];
    while(num/10>0){
        num=num/10;
        digitos++;
    }
    printf(".");
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
        if(opcion > 2 || opcion < 1){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion > 2 || opcion < 1);
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
    return Usuario.ganancia;
}

void menu(int val){
    int opcion,cant;
    do{
        printf("Seleccione la accion que desea realizar:\n \t 1 - Introducir puntos de un jugador.\n \t 2 - Conocer los puntos que un jugador lleva conseguidos en un juego.\n \t 3 - Mostrar para un jugador los puntos conseguidos en cada juego que ha participado.\n \t 4 - Calcular los euros ganados por un jugador.\n \t 5 - Terminar.\n");
        scanf("%d",&opcion);
        if(opcion<1 && opcion>5){
            printf("Error, numero invalido, seleccione nuevamente.\n");
        }
    }while(opcion<1 && opcion>5);
    switch(opcion){
        case 1:
            //1 Introducir puntos de un jugador.
            Anadir(val);
            menu(val);
            break;
        case 2:
            //2. Conocer los puntos que un jugador lleva conseguidos en un juego.
            Mostrar_especifico(val);
            menu(val);
            break;
        case 3:
            //3. Mostrar para un jugador los puntos conseguidos en cada juego que ha participado.
            Mostrar(val);
            menu(val);
            break;
        case 4:
            //4. Calcular los euros ganados por un jugador.
            cant=calculadora(val);
            menu(val);
            break;
        case 5:
            //5. Terminar.
            printf("Gracias por preferirnos.\n");
            break;
        default:
            printf("Error,El menu se reiniciara.\n");
            menu(val);
        }
}
