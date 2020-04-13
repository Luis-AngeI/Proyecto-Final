int creador(){
    system("cls");
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
    return acum;
}

int veri_Existe(int cont){
    char* nombre = " - Cliente";
    char* extension = ".txt";
    int digitos=1;
    int num=cont;
    while(num/10>0){
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
