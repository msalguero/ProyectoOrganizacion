#include "Register.h"

Register::Register(MetaDataReg *metaDatareg)
{
    this->metaDatareg=metaDatareg;
    this->campos = new Lista<Field*>();
}

Register::~Register()
{
    //dtor
}

void Register::fromBytes(char* bytes)
{
    int cantFields = metaDatareg->metaDataFields->size;
    int pos = 0;
    for(int i = 0; i<cantFields; i++)
    {
        MetaDataField* campo = metaDatareg->metaDataFields->Recupera(i);
        int tamCampo = campo->tamanioCampo;
        char *valor = new char[tamCampo];
        memcpy(valor, &(bytes[pos]), tamCampo);
        pos += tamCampo;
        campos->Agregar(new Field(campo, valor));
    }

}

int Register::toBytes(char* bytes)
{
    int cantFields = metaDatareg->metaDataFields->size;
    int tamRegistro = metaDatareg->getSizeRegistro();
    int pos = 0;
    for(int i = 0; i<cantFields; i++)
    {
        Field *campo = campos->Recupera(i);
        int tamCampo = campo->metaData->tamanioCampo;
        char *dataCampo = (char*) malloc (tamCampo);
        campo->toBytes(dataCampo);
        memcpy(&(bytes[pos]), dataCampo, tamCampo);
        pos+= tamCampo;
    }

    return tamRegistro;
}
