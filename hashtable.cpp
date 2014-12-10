#include "hashtable.h"
#include <string.h>
#include <QDebug>
#include "Register.h"

struct ElementoIndice{
    int llave;
    int direccionRegistro;
};

HashTable::HashTable(ManejadorArchivos *archivo, MetaDataReg *metaData)
{
    bloqueTablaHash = archivo;
    this->metaData = metaData;
    tam=100;
}

int HashTable::hash(char *llave)
{
    int suma = 0;

    for(int i =0; i<(int)strlen(llave); i++)
    {
        suma += llave[i];
    }
    return suma%tam;
}

int HashTable::Agregar(char *llave, int valor)
{
    int pos=hash(llave);
    qDebug()<<"Posicion en indice: "<<pos;
    qDebug()<<"llave: "<<llave;
    //Escribir en archivo
    ManejadorArchivos* archivoTemporal = new ManejadorArchivos();
    archivoTemporal->abrirArchivo("indice");
    ElementoIndice structElemento;
    structElemento.llave = atoi(llave);
    structElemento.direccionRegistro = valor;
    char* bytesElemento = (char*)malloc(8);
    memcpy(bytesElemento, &structElemento, 8);
    archivoTemporal->escribirElementoIndice(pos,bytesElemento);
    archivoTemporal->cerrarArchivo();
    //valores[pos]=valor;
    return pos;
}

Register* HashTable::Buscar(char *llave)
{
    int pos=hash(llave);
    qDebug()<<"Posicion en indice: "<<pos;
    qDebug()<<"llave: "<<llave;
    //leer valores[pos]
    ManejadorArchivos* archivoTemporal = new ManejadorArchivos();
    archivoTemporal->abrirArchivo("indice");
    ElementoIndice structElemento;
    char* bytesElemento = archivoTemporal->leerElementoIndice(pos);
    memcpy(&structElemento, bytesElemento, 8);
    //char buffer [33];
    //itoa(structElemento.llave, buffer, 10);
    archivoTemporal->cerrarArchivo();

    char* bytes = bloqueTablaHash->leerRegistro(structElemento.direccionRegistro, metaData->getSizeRegistro());

    Register* registro = new Register(metaData);
    registro->fromBytes(bytes);
    return registro;
}

void HashTable::Eliminar(char *llave)
{
    int pos=hash(llave);
     //valores[pos]=-1;
}
