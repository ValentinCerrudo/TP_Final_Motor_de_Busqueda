#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodoA.h"

/// Funciones de nodoA y del arbol.
nodoA *crearNodoA(char palabra[]) {
    nodoA *nuevo = (nodoA*)malloc(sizeof(nodoA));
    strcpy(nuevo->palabra, palabra);
    nuevo->frecuencia = 1;
    nuevo->ocurrencias = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

/// Inserción del ABB
void insertarNodoA(nodoA** arbol, Termino nuevo) {
    if(*arbol) {
        switch(strcmp((*arbol)->palabra, nuevo.palabra)) {
        case 1:
            insertarNodoA(&((*arbol)->izq), nuevo);
            break;
        case -1:
            insertarNodoA(&((*arbol)->der), nuevo);
            break;
        case 0:
            (*arbol)->frecuencia++;
            insertarNodoT(&((*arbol)->ocurrencias), crearNodoT(nuevo.idDOC, nuevo.pos));
            break;
        }
    } else {
        *arbol = crearNodoA(nuevo.palabra);
        (*arbol)->ocurrencias = crearNodoT(nuevo.idDOC, nuevo.pos);
    }
}

///Creación del arbol a partir del archivo diccionario
void crearArbolDiccionario(nodoA** arbol, char diccionario[]) {
    FILE *arch = fopen(diccionario, "rb");

    if(arch) {
        Termino leido;

        while(fread(&leido, sizeof(Termino), 1, arch)>0) {
            insertarNodoA(arbol, leido);
        }
        fclose(arch);
    }

}

///Aux de prints de nodoA
void mostrarNodoA(nodoA* arbol) {
    printf("\nPalabra: %s", arbol->palabra);
    printf("\nFrecuencia: %i", arbol->frecuencia);
    printf("\nOcurrencias: ");
    mostrarListaNodoT(arbol->ocurrencias);
}

///Funcion para recorrer y mostrar un arbol en preOrder
void mostrarArbolPreOrder(nodoA *arbol) {
    if(arbol) {
        mostrarNodoA(arbol);
        mostrarArbolPreOrder(arbol->izq);
        mostrarArbolPreOrder(arbol->der);
    }
}

///Funcion utilizada para verificar si una palabra se encuentra en el arbol
nodoA *existeNodo(nodoA *arbol, char palabra[]) {
    nodoA *encontrado = NULL;
    if(arbol) {
        switch(strcmp(arbol->palabra, palabra)) {
        case 1:
            encontrado = existeNodo(arbol->izq, palabra);
            break;
        case -1:
            encontrado = existeNodo(arbol->der, palabra);
            break;
        case 0:
            encontrado = arbol;
            break;
        }
    }
    return encontrado;
}
