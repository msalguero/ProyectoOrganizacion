#include "MetaDataField.h"

MetaDataField::MetaDataField(int tipoDato, char *nombreCampo, int tamanio)
{
    this->tipoDato=tipoDato;
    this->nombreCampo=nombreCampo;
    this->tamanioCampo=tamanio;
}

MetaDataField::MetaDataField()
{
    tipoDato = 0;
    nombreCampo = (char*)malloc(20);
    tamanioCampo = 0;
}


MetaDataField::~MetaDataField()
{
    //dtor
}

void MetaDataField::fromBytes(char *bytes)
{
    memcpy(&tipoDato, bytes, 4);
    memcpy(nombreCampo, &(bytes[4]), 20);
    memcpy(&tamanioCampo, &(bytes[24]), 4);
}

char* MetaDataField::toBytes()
{
    char* bytes = (char*) malloc (SIZE);

    memcpy(bytes, &tipoDato, 4);
    memcpy(&(bytes[4]), nombreCampo, 20);
    memcpy(&(bytes[24]), &tamanioCampo, 4);

    return bytes;
}
