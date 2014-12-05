#include "DataBaseManager.h"
#include <QDebug>
DataBaseManager::DataBaseManager(const char* nombreArchivo)
{
    //ctor
    bloqueDisponible = 1;
    cantTablas = 0;
    tablas = new Lista<Table*>();
    archivo = new ManejadorArchivos();
    archivo->abrirArchivo(nombreArchivo);
}

DataBaseManager::~DataBaseManager()
{
    //dtor
    archivo->cerrarArchivo();
}

Table* DataBaseManager::crearNuevaTabla(char* nombre)
{
    Table* tablaNueva = new Table(nombre);
    tablas->Agregar(tablaNueva);
    MetaDataReg* meta = tablaNueva->metaData;

    bloqueDisponible = (cantTablas*2)+1;

    meta->idTabla = cantTablas;
    meta->blqMeta = bloqueDisponible++;
    meta->blqDataI = bloqueDisponible++;
    meta->blqDataF = bloqueDisponible;

    cantTablas++;

    return tablaNueva;
}

void DataBaseManager::guardarMetaDataTablas()
{
    char *bloqueMetaData = (char*)malloc(SIZE_BLOQUE);
    int pos = 4;

    memcpy(bloqueMetaData, &cantTablas, 4);


    for(int i = 0; i<cantTablas; i++)
    {
        Table* tabla = tablas->Recupera(i);
        memcpy(&(bloqueMetaData[pos]), tabla->mandarMetaDataTabla(), MetaDataReg::SIZE);
        pos += MetaDataReg::SIZE;
        guardarMetaDataCampos(tabla);
    }
    archivo->escribirBloque(0, bloqueMetaData);

}

void DataBaseManager::leerMetaDataTablas()
{
    char *bloqueMetaData = archivo->leerBloque(0);
    int pos = 4;

    memcpy(&cantTablas, bloqueMetaData, 4);


    for(int i = 0; i<cantTablas; i++)
    {
        Table* tabla = new Table("");
        tabla->recibirMetaDataTabla(&(bloqueMetaData[pos]));
        //memcpy(&(bloqueMetaData[pos]), tabla->mandarMetaDataTabla(), MetaDataReg::SIZE);
        pos += MetaDataReg::SIZE;
        leerMetaDataCampos(tabla);
        tablas->Agregar(tabla);
    }

}

void DataBaseManager::guardarMetaDataCampos(Table* tabla)
{
    char* bloque = (char*)malloc(1024);
    memcpy(bloque, tabla->mandarMetaDataCampos(), MetaDataField::SIZE*tabla->metaData->cantitdadCampos());
    archivo->escribirBloque(tabla->metaData->blqMeta, bloque);
}

void DataBaseManager::leerMetaDataCampos(Table* tabla)
{
    char* bloque = (char*)malloc(1024);
    bloque = archivo->leerBloque(tabla->metaData->blqMeta);
    tabla->recibirMetaDataCampos(bloque);
}

Table* DataBaseManager::buscarTabla(int idTabla)
{
    for(int i = 0; i < cantTablas; i++)
    {
        Table* tabla = tablas->Recupera(i);
        if(tabla->metaData->idTabla == idTabla)
            return tabla;
    }
    return NULL;
}

Table* DataBaseManager::buscarTabla(const char *nombre)
{
    for(int i = 0; i < cantTablas; i++)
    {
        Table* tabla = tablas->Recupera(i);
        if(strcmp(tabla->metaData->nombre, nombre) == 0)
            return tabla;
    }
    return NULL;
}

void DataBaseManager::guardarRegistrosTabla(int idTabla)
{
    Table* tabla = buscarTabla(idTabla);
    if(tabla == NULL)
        return ;

    int bloqueRegistros = tabla->metaData->blqDataI;
    int tamDatos = tabla->metaData->getSizeRegistro()*tabla->registros->size;


    for(int cont = 0; cont<tamDatos; cont+= 1024)
    {
        char* bloque = (char*)malloc(1024);

        memcpy(bloque, &(tabla->mandarRegistros()[cont]), tamDatos);

        archivo->escribirBloque(bloqueRegistros, bloque);
    }

    /*
    char* bloque = (char*)malloc(1024);

    memcpy(bloque, tabla->mandarRegistros(), tamDatos);

    archivo->escribirBloque(bloqueRegistros, bloque);
    */
}

void DataBaseManager::leerRegistrosTabla(int idTabla)
{
    Table* tabla = buscarTabla(idTabla);
    if(tabla == NULL)
        return ;

    int bloqueRegistros = tabla->metaData->blqDataI;

    char* bloque = archivo->leerBloque(bloqueRegistros);

    tabla->recibirBloqueRegistros(bloque);
}
