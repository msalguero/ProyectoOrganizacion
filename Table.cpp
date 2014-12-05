#include "Table.h"
#include <QDebug>
Table::Table(char* nombre="")
{
    //ctor
    metaData = new MetaDataReg(nombre);
   // metaData->setName(nombre);
    registros = new Lista<Register*>();
}

Table::~Table()
{
    //dtor
}

void Table::agregarRegistro(char* data)
{
    Register* registro = new Register(metaData);

    registro->fromBytes(data);

    registros->Agregar(registro);
    metaData->cantRegistros++;
}

void Table::agregarRegistro(Register* registro)
{
    qDebug()<<"Se agrego un registro";
    registros->Agregar(registro);
    metaData->cantRegistros++;
}


void Table::agregarCampo(int tipoDato, char* nombreCampo, int tamanio)
{
    metaData->newField(tipoDato, nombreCampo, tamanio);
}


void Table::recibirBloqueRegistros(char* bloque)
{
    int cantRegistros = metaData->cantRegistros;
    qDebug()<<cantRegistros;
    int tamRegistro = metaData->getSizeRegistro();
    char* bytesRegistro = (char*) malloc(tamRegistro);

    int pos = 0;
    for(int i = 0; i<cantRegistros; i++)
    {
        Register* reg = new Register(metaData);
        memcpy(bytesRegistro, &(bloque[pos]), tamRegistro);
        pos+=tamRegistro;
        reg->fromBytes(bytesRegistro);
        registros->Agregar(reg);
    }
}

void Table::recibirMetaDataTabla(char* data)
{
    metaData->fromBytes(data);
}

void Table::recibirMetaDataCampos(char* data)
{
    metaData->setMetaDataBytes(data);
}

char* Table::mandarRegistros()
{
    int tamRegistro = metaData->getSizeRegistro();
    char* data = (char*)malloc(metaData->cantRegistros*tamRegistro);
    int pos = 0;

    for(int i = 0; i<metaData->cantRegistros; i++)
    {
        Register* registro = registros->Recupera(i);
        char* bytesRegistro = (char*)malloc(tamRegistro);
        registro->toBytes(bytesRegistro);
        memcpy(&(data[pos]), bytesRegistro, tamRegistro);
        pos+=tamRegistro;
    }
    return data;
}

char* Table::mandarMetaDataTabla()
{
    return metaData->toBytes();
}

char* Table::mandarMetaDataCampos()
{
    return metaData->getMetaDataBytes();
}
