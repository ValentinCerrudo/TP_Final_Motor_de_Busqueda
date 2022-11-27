#ifndef FUNCIONESUSUARIO_H_INCLUDED
#define FUNCIONESUSUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "nodoA.h"
#include "nodoFrase.h"
#define DICCIONARIO "diccionario.bin"
#define nombreTextos "infoTexto.bin"

int verificarPalabra (nodoA* arbol, char palabra[]);
void buscarPalabra(nodoA *arbol, char palabra[]);
int verificarIdIngresado (int idBusqueda);
void buscarPalabraPorAnd (nodoA* arbol, char palabra[], int idDoc1, int idDoc2);
int buscarIdOcurrencias (nodoT* ocurrencias, int idDoc);
void mostrarNodoAAND(nodoA* arbol, int id1, int id2);
void mostrarListaNodoTAND(nodoT *lista, int id1, int id2);
int buscaPalabrasMismoDoc(nodoA* arbol, nodoFrase* listaP);
int buscaPalabras(int idDOC, nodoFrase* listaP, nodoA* arbol);
int buscarFraseEnDiccionario(nodoA* arbol, nodoFrase* lista);
int buscarFrase(int idDOC, int pos, nodoFrase* lista, nodoA* arbol);
void buscarMayorFrecuenciaDoc(nodoA* arbol, nodoA** mayorFrec, int idDoc, int* maxFrec);
nodoA* mayorFrecuenciaDoc(nodoA* arbol, int idDoc);
int cuentaFrecuenciaOcurrencias (nodoT* ocurrencias, int idDoc);
void mostrarNodoAFREC(nodoA* arbol, int id);
void mostrarListaNodoTFREC(nodoT *lista, int id);
int Minimo (int a, int b, int c);
int Levenshtein(char *s1,char *s2);
void sugierePalabrasSimilares (nodoA* arbol, char* palabra);

#endif // FUNCIONESUSUARIO_H_INCLUDED
