#include "Field.h"

Field::Field(MetaDataField *metaData, char *valor)
{
    this->metaData=metaData;
    this->valor=valor;
}

Field::~Field()
{
    //dtor
}

int Field::toBytes(char* bytes)
{
    int tam = metaData->tamanioCampo;
    memcpy(bytes, valor, tam);
    return tam;
}
