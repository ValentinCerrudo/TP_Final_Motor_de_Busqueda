#ifndef TERMINO_H_INCLUDED
#define TERMINO_H_INCLUDED

typedef struct {
    char palabra[20];
    int idDOC;
    int pos; //incrementa palabra por palabra, y no letra por letra
} Termino;

///Estructura realizada para guardarla en el archivo nombresTextos
typedef struct {
    char nomTexto [20];
    int idDOC;
} infoTexto;

void pedirNomTexto (char archTexto[]);
int contarCantIdDoc (char archivo[]);
void guardarNomTextArchivo (char archTexto [], char archivo[]);
void recorrerArch (char archivo[]);
int dimensionArchivo (char archivoTexto[]);
char *generarStringTxt(char archivoTexto[], int tamanio);
int validaChar(char letra);
int contarCantidadPalabras(char texto[], int validos);
void textoToArregloTermino(char texto[], int validosT, Termino textoT[], int validos, int idDoc);
void mostrarTermino(Termino palabra);
void guardarTextoEnArchivoDic(char archivo[], Termino palabras[], int validos);
void mostrarDiccionario (char archivo[]);

#endif // TERMINO_H_INCLUDED
