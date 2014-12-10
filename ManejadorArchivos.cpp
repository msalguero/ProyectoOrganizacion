#include "ManejadorArchivos.h"

ManejadorArchivos::ManejadorArchivos()
{
    //ctor
}

ManejadorArchivos::~ManejadorArchivos()
{
    //dtor
}

void ManejadorArchivos::abrirArchivo(const char *archivo)
{
    FILE * pFile;
    pFile = fopen(archivo, "ab");
    fclose(pFile);

    pFile = fopen (archivo,"r+b");
    Archivo = pFile;
}

void ManejadorArchivos::escribirElementoIndice(int pos, char *elemento)
{
    int posElemento = pos*8;
    fseek(Archivo, posElemento, 0);
    fwrite(elemento, sizeof(char), 8, Archivo);
}

char* ManejadorArchivos::leerElementoIndice(int pos)
{
    int posElemento = pos*8;
    fseek(Archivo, posElemento, 0);

    char* elemento = (char*)malloc(8);

    fread(elemento, 1, 8, Archivo);

    return elemento;
}

void ManejadorArchivos::abrirArchivoLectura(char* archivo)
{
    FILE * pFile;
    pFile = fopen (archivo,"rb");
    Archivo = pFile;
}


void ManejadorArchivos::cerrarArchivo()
{
   fclose(Archivo);
}

char* ManejadorArchivos::leerBloque(int numBloque)
{
    int posBloque = numBloque*TAM_BLOQUE;

    fseek(Archivo, posBloque, 0);

    char* bloque = (char*)malloc(TAM_BLOQUE);

    fread(bloque, 1, TAM_BLOQUE, Archivo);

    return bloque;
}

void ManejadorArchivos::escribirBloque(int numBloque, char *bloque)
{
    int posBloque = numBloque*TAM_BLOQUE;

    fseek(Archivo, posBloque, 0);

    fwrite(bloque, sizeof(char), TAM_BLOQUE, Archivo);
}

int ManejadorArchivos::leerEncabezado(int numBloque)
{
    int posBloque = numBloque*TAM_BLOQUE;

    fseek(Archivo, posBloque, 0);

    char* bloque = (char*)malloc(4);

    fread(bloque, 1, 4, Archivo);

    int encabezado;

    memcpy(&encabezado, bloque, 4);

    return encabezado;
}

char* ManejadorArchivos::leerRegistro(int direccion, int tam)
{
    fseek(Archivo, direccion, 0);
    char* registro = (char*)malloc(tam);

    fread(registro, 1, tam, Archivo);

    return registro;
}

void ManejadorArchivos::leerArchivo(char* data, char* archivo)
{
    FILE * pFile;
    pFile = fopen (archivo,"rb");

    fseek(pFile, 0, SEEK_END);
    int tam = ftell(pFile);
    rewind(pFile);

    char buffer[tam];

    fread (buffer,1,tam,pFile);
    fclose (pFile);

    memcpy(data, buffer, tam);
}

void ManejadorArchivos::escribirArchivo(char* data,int cant_bytes, char* archivo)
{
    FILE * pFile;
    pFile = fopen (archivo,"w");

    fwrite(data, sizeof(char), cant_bytes,pFile);
    fclose (pFile);
}
