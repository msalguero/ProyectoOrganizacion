#include "MetaDataReg.h"

MetaDataReg::MetaDataReg(char* nombre)
{
    //ctor
    idTabla = 1;
    this->nombre = nombre;
    cantCampos = 0;
    metaDataFields = new Lista<MetaDataField*>();

    blqMeta = 1;
    blqDataI = 2;
    blqDataF = 3;
    cantRegistros = 0;
}

MetaDataReg::~MetaDataReg()
{
    //dtor
}

void MetaDataReg::setName(char* nombre)
{
    cout<<nombre;
    //memcpy(this->nombre, nombre, strlen(nombre));
    this->nombre = nombre;
}

int MetaDataReg::getSizeRegistro()
{
    int cantFields = metaDataFields->size;

    int size = 0;
    for(int i = 0; i<cantFields; i++)
    {
        size += metaDataFields->Recupera(i)->tamanioCampo;
    }
    return size;
}

int MetaDataReg::cantitdadCampos()
{
    return cantCampos;
}

char* MetaDataReg::toBytes()
{
    char* bytes = (char*) malloc (SIZE);

    memcpy(bytes, &idTabla, 4);
    memcpy(&(bytes[4]), nombre, 20);
    memcpy(&(bytes[24]), &blqMeta, 4);
    memcpy(&(bytes[28]), &blqDataI, 4);
    memcpy(&(bytes[32]), &blqDataF, 4);
    memcpy(&(bytes[36]), &cantCampos, 4);
    memcpy(&(bytes[40]), &cantRegistros, 4);

    return bytes;
}

void MetaDataReg::fromBytes(char* bytes)
{
    memcpy(&idTabla, bytes, 4);
    nombre = (char*)malloc(20);
    memcpy(nombre, &(bytes[4]), 20);
    memcpy(&blqMeta, &(bytes[24]), 4);
    memcpy(&blqDataI, &(bytes[28]), 4);
    memcpy(&blqDataF, &(bytes[32]), 4);
    memcpy(&cantCampos, &(bytes[36]), 4);
    memcpy(&cantRegistros, &(bytes[40]), 4);

}

void MetaDataReg::newField(int tipoDato, char *nombreCampo, int tamanio)
{
    metaDataFields->Agregar(new MetaDataField( tipoDato, nombreCampo, tamanio));
    cantCampos++;
}


char* MetaDataReg::getMetaDataBytes()
{
    char* bytes = (char*)malloc((MetaDataField::SIZE*cantCampos));

    int pos = 0;

    for(int i = 0; i<cantCampos; i++)
    {
        MetaDataField* field = metaDataFields->Recupera(i);
        memcpy(&(bytes[pos]), field->toBytes(), MetaDataField::SIZE);
        pos += MetaDataField::SIZE;
        //memcpy(bytes, &(field->tipoDato), 4);
        //memcpy(&(bytes[4]), field->nombreCampo, 20);
        //memcpy(&(bytes[24]), &(field->tamanioCampo), 4);
    }
    return bytes;
}

void MetaDataReg::setMetaDataBytes(char* bytes)
{
    int pos = 0;

    for(int i = 0; i<cantCampos; i++)
    {
        MetaDataField* field = new MetaDataField();
        field->fromBytes(&(bytes[pos]));
        pos += MetaDataField::SIZE;
        //memcpy(&(field->tipoDato), bytes, 4);
        //memcpy(field->nombreCampo, &(bytes[4]), 20);
        //memcpy(&(field->tamanioCampo), &(bytes[24]), 4);
        metaDataFields->Agregar(field);
    }
}
