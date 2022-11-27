#include <stdio.h>
#include <stdlib.h>
#include "nodoT.h"

nodoT *crearNodoT(int idDoc, int pos)
{
    nodoT *nuevo = (nodoT*)malloc(sizeof(nodoT));
    nuevo->idDOC = idDoc;
    nuevo->pos = pos;
    nuevo->sig = NULL;

    return nuevo;
}

void insertarNodoT(nodoT** lista, nodoT* nuevo)
{
    if(*lista==NULL)
    {
        *lista=nuevo;
    }
    else
    {
        if((*lista)->idDOC < nuevo->idDOC)
        {
            insertarNodoT(&(*lista)->sig,nuevo);
        }
        else if((*lista)->pos < nuevo->pos)
        {
            insertarNodoT(&((*lista)->sig), nuevo);
        }
        else
        {
            nuevo->sig = *lista;
            *lista = nuevo;
        }

    }
}

///Aux de prints del nodoT
void mostrarNodoT(nodoT* dato)
{
    printf("\n");
    printf("\t    [Id Documento: %i", dato->idDOC);
    printf(" Posicion: %i]", dato->pos);
}

///Función recursiva de muestra de una lista de nodoT
void mostrarListaNodoT(nodoT *lista)
{
    if(lista)
    {
        mostrarNodoT(lista);
        mostrarListaNodoT(lista->sig);
    }
}
