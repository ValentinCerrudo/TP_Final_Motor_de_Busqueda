#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "Termino.h"
#include "nodoT.h"
#include "nodoA.h"
#include "nodoFrase.h"
#include "funcionesUsuario.h"

#define DICCIONARIO "diccionario.bin"
#define nombreTextos "infoTexto.bin"

///Se pide por consola el nombre del texto para que se guarde en el archivo de nombres de textos que posee el nombre junto con su idDoc
void cargaTextoDiccionario() {
    char nomTexto [100];
    int validos, cant, idDoc;

    pedirNomTexto(nomTexto);
    guardarNomTextArchivo(nomTexto, nombreTextos);
    strcat(nomTexto, ".bin");

    validos=dimensionArchivo(nomTexto);

    char* texto = (char*)malloc(sizeof(char)*validos);

    strcpy(texto, generarStringTxt(nomTexto, validos));

    printf("Contenido de el texto: \n");
    printf("%s", texto);
    printf("\n");
    system("pause");
    system("cls");

    cant = contarCantidadPalabras(texto, validos);
    Termino* palabrasTexto1 = (Termino*)malloc(sizeof(Termino)*cant);
    idDoc = contarCantIdDoc(nombreTextos);
    textoToArregloTermino(texto, validos, palabrasTexto1, cant, idDoc);
    guardarTextoEnArchivoDic(DICCIONARIO, palabrasTexto1, cant);
}

///Se invoca a la funcion de carga de los diferentes textos y su correspondiente carga en el diccionario hasta que por consola se diga que no.
void menuTextoDiccionario() {
    char control = 's';

    recorrerArch(nombreTextos);

    printf("Quiere cargar textos? (s-n)\n");
    fflush(stdin);
    scanf("%c", &control);

    while(control == 's') {
        cargaTextoDiccionario();
        system("cls");
        printf("Quiere cargar otro texto? (s-n)\n");
        fflush(stdin);
        scanf("%c", &control);
    }

    system("cls");
    printf("Lista de textos cargados: \n");

    recorrerArch(nombreTextos);
}

///Aux de menu principal
int menu(){
    int opcion;

    printf("\n************************************************\n");
    printf("\n*** Bienvenido al motor de busqueda de LAB 2 ***\n");
    printf("\n************************************************\n");
    printf("\nIngrese el numero de la funcion que quiera utilizar.\n");
    printf("1.Buscar todas las apariciones de un termino en algun documento.\n");
    printf("2.Buscar todas las apariciones de un termino en un documento y otro.\n");
    printf("3.Buscar la aparicion de mas de un termino en el mismo documento.\n");
    printf("4.Buscar una frase completa.\n");
    printf("5.Buscar la palabra de mas frecuencia que aparece en alguno de los docs.\n");
    printf("6.Ingresar una palabra y buscar similares.\n");
    printf("7.Cargar textos al sistema.\n");
    printf("8.Mostrar diccionario.\n");
    printf("9.Mostrar arbol en PREORDER.\n");
    printf("\n0.Salir del programa.\n");
    printf("\n************************************************\n");

    printf("Ingrese su opcion:\n");
    fflush(stdin);
    scanf("%d", &opcion);
    system("cls");

    return opcion;
}

///Menu del programa
void menuUsuario() {
    nodoA* arbol = NULL;
    nodoA* mayorFREC = NULL;
    nodoFrase* lista = NULL;
    crearArbolDiccionario(&arbol,DICCIONARIO);
    char palabra [20];
    int control = 0;
    int flag = 0;
    int idBusqueda1 = 0;
    int idBusqueda2 = 0;
    int fraseEncontrada = 0;

    do {

        control = menu();

        switch(control) {
        case 1:
            printf("\nIngrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            buscarPalabra(arbol, palabra);
            break;
        case 2:
            do {
                flag = 0;
                printf("\nIngrese la palabra: ");
                fflush(stdin);
                gets(palabra);
                flag = verificarPalabra(arbol, palabra);
            } while(flag!=0);

            printf("\nTextos disponibles: \n");
            recorrerArch(nombreTextos);
            printf("\nVamos a comparar entre dos id's\n");
            printf("\nIngrese los id del los documentos que quiera buscar su palabra:\n");

            do {
                flag = 0;
                printf("\nPrimer idDoc\n");
                scanf("%d", &idBusqueda1);
                flag = verificarIdIngresado(idBusqueda1);
            } while(flag != 0);

            do {
                flag = 0;
                printf("\nSegundo idDoc\n");
                scanf("%d", &idBusqueda2);
                flag = verificarIdIngresado(idBusqueda2);
            } while(flag != 0);

            buscarPalabraPorAnd(arbol, palabra, idBusqueda1, idBusqueda2);
            break;
        case 3:
            printf("Ingrese las palabras a buscar:\n");
            ingresarFrase(&lista);

            fraseEncontrada = buscaPalabrasMismoDoc(arbol, lista);

            if(fraseEncontrada) {
                mostrarFraseEncontrada(lista);
            } else {
                printf("Palabras no encontradas o mal escritas\n");
            }

            liberarFrase(&lista);
            break;
        case 4:
            printf("Ingrese la frase a buscar:\n");
            ingresarFrase(&lista);
            fraseEncontrada = buscarFraseEnDiccionario(arbol, lista);

            if(fraseEncontrada) {
                mostrarFraseEncontrada(lista);
            } else {
                printf("Frase no encontrada o mal escrita\n");
            }

            liberarFrase(&lista);
            break;
        case 5:

            do {
                flag = 0;
                printf("Ingrese el idDoc donde quiera buscar la palabra con mayor frecuencia.\n");
                scanf("%d", &idBusqueda1);
                flag = verificarIdIngresado(idBusqueda1);
            } while (flag != 0);

            mayorFREC = mayorFrecuenciaDoc(arbol, idBusqueda1);
            mostrarNodoAFREC(mayorFREC, idBusqueda1);
            break;
        case 6:
            printf("\nIngrese la palabra: ");
            fflush(stdin);
            gets(palabra);
            printf("Palabras sugeridas a la palabra %s : \n", palabra);
            sugierePalabrasSimilares(arbol, palabra);
            break;
        case 7:
            menuTextoDiccionario();
            printf("\n");
            break;
        case 8:
            mostrarDiccionario(DICCIONARIO);
            break;
        case 9:
            mostrarArbolPreOrder(arbol);
            break;
        case 0:
            printf("\n--------------------------------\n");
            printf("\n**** Programa finalizado ****\n");
            printf("\n--------------------------------\n");
            exit(0);
        default:
            printf("\n***OPCION INCORRECTA***\n");
            printf("\n");
            break;
        }
        printf("\n");
        system("pause");
        system("cls");
    } while(control != 0);

}

int main() {
    menuUsuario();

    return 0;
}
