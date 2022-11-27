#ifndef NODOT_H_INCLUDED
#define NODOT_H_INCLUDED

typedef struct nodoT {
    int idDOC;
    int pos;
    struct nodoT* sig;
} nodoT;

nodoT *crearNodoT(int idDoc, int pos);
void insertarNodoT(nodoT** lista, nodoT* nuevo);
void mostrarNodoT(nodoT* dato);
void mostrarListaNodoT(nodoT *lista);

#endif // NODOT_H_INCLUDED
