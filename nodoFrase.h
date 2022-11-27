#ifndef NODOFRASE_H_INCLUDED
#define NODOFRASE_H_INCLUDED
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"
#include <conio.h>

///nodoFrase se utiliza para los punts 3 y 4

typedef struct nodoFrase
{
    char palabra[20];
    int idDOC;
    int pos;
    struct nodoFrase* sig;
}nodoFrase;

nodoFrase *crearNodoFrase(char palabra[]);
void insertarNodoFrase(nodoFrase** lista, char palabra[]);
void mostrarNodoFrase(nodoFrase* nodo);
void mostrarListaFrase(nodoFrase *lista);
void mostrarFraseEncontrada(nodoFrase* lista);
char* validarPalabra(char palabra[], int dim);
int leerPalabra(char palabra[]);
void ingresarFrase(nodoFrase** lista);
nodoT* buscarListaOcurrenciasPalabra(nodoA *arbol, char palabra[]);
void liberarFrase(nodoFrase** lista);



#endif // NODOFRASE_H_INCLUDED
