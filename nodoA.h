#ifndef NODOA_H_INCLUDED
#define NODOA_H_INCLUDED
#include "nodoT.h"
#include "Termino.h"

typedef struct nodoA {
    char palabra[20];
    int frecuencia; //representa la cantidad de nodos de la lista
    nodoT *ocurrencias; //ordenada por idDOC, luego por pos
    struct nodoA *der;
    struct nodoA *izq;
} nodoA;

nodoA *crearNodoA(char palabra[]);
void insertarNodoA(nodoA** arbol, Termino nuevo);
void crearArbolDiccionario(nodoA** arbol, char diccionario[]);
void mostrarNodoA(nodoA* arbol);
void mostrarArbolPreOrder(nodoA* arbol);
nodoA *existeNodo(nodoA* arbol, char palabra[]);
void buscarPalabra(nodoA* arbol, char palabra[]);

#endif // NODOA_H_INCLUDED
