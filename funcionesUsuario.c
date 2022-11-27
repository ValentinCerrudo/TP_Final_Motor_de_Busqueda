#include "funcionesUsuario.h"

///Verifica si la palabra está en el diccionario.
int verificarPalabra (nodoA* arbol, char palabra[])
{
    int flag = 0;
    nodoA* palabraNodo = existeNodo(arbol, palabra);
    if (!palabraNodo)
    {
        flag = 1;
        printf("\nLa palabra no se encuentra en el diccionario!\n");
        printf("\nIngrese nuevamente.\n");
    }
    return flag;
}

/// 1) Buscar el termino en alguno de los docs. (muestra tanto si esta en uno solo o en todos).
void buscarPalabra(nodoA* arbol, char palabra[])
{
    nodoA *palabraNodo = existeNodo(arbol, palabra);
    if(palabraNodo)
        mostrarNodoA(palabraNodo);
    else
        printf("\nLa palabra no se encuentra en el diccionario!\n");
}

/// 2) Busca todas las apariciones de un termino en un documento y otro  (operacion and).
int verificarIdIngresado (int idBusqueda)
{
    int flag = 0;
    if (idBusqueda <= 0 || idBusqueda > contarCantIdDoc(nombreTextos))
    {
        printf("ID NO VALIDO!\n");
        printf("\tVuelva a ingresarlo.\n");
        flag = 1;
    }
    return flag;
}

int buscarIdOcurrencias(nodoT* ocurrencias, int idDoc)
{
    int flag = 0;
    while (ocurrencias && ocurrencias->idDOC < idDoc)
    {
        ocurrencias = ocurrencias->sig;
    }
    if (ocurrencias && ocurrencias->idDOC == idDoc)
    {
        flag = 1;
    }
    return flag;
}

void buscarPalabraPorAnd (nodoA* arbol, char palabra[], int idDoc1, int idDoc2)
{
    nodoA* palabraNodo = existeNodo(arbol, palabra);
    if (palabraNodo)
    {
        nodoT* ocurrencias = palabraNodo->ocurrencias;

        int encontradoId1 = buscarIdOcurrencias(ocurrencias, idDoc1);
        int encontradoId2 = buscarIdOcurrencias(ocurrencias, idDoc2);
        if (encontradoId1 == 1 && encontradoId2 == 1)
        {
            printf("\nPalabra encontrada en los documentos %d y %d\n", idDoc1, idDoc2);
            mostrarNodoAAND(palabraNodo, idDoc1, idDoc2);
        }
        else
        {
            printf("\nLa palabra no se encuentra en los dos documentos!\n");
        }
    }
}

void mostrarNodoAAND(nodoA* arbol, int id1, int id2)
{
    printf("\n Palabra: %s", arbol->palabra);
    printf("\n Ocurrencias: ");
    mostrarListaNodoTAND(arbol->ocurrencias, id1, id2);
}

void mostrarListaNodoTAND(nodoT *lista, int id1, int id2)
{
    if(lista)
    {
        if (lista->idDOC == id1 || lista->idDOC == id2)
        {
            mostrarNodoT(lista);
        }
        mostrarListaNodoTAND(lista->sig, id1, id2);
    }
}

/// 3) Busca la aparicion de mas de un termino en el mismo documento.
int buscaPalabrasMismoDoc(nodoA* arbol, nodoFrase* listaP)
{

    int encontrado = 0;

    if (listaP && arbol)   //Si la lista con palabras o el arbol estan vacios, salgo.
    {

        //Busco la primer palabra en el arbol y retorno la lista de ocurrencias de dicha palabra o un NULL.
        nodoT* listaPalabra = buscarListaOcurrenciasPalabra(arbol, listaP->palabra);

        if (listaPalabra)   //Si encuentro la primer palabra.
        {
            if (listaP->sig == NULL)      //La frase era una sola palabra y la encontro.
            {
                encontrado = 1;
                listaP->idDOC = listaPalabra->idDOC;
                listaP->pos = listaPalabra->pos;
            }
            else
            {
                nodoFrase* primero = listaP; // guardo el primer nodo de la frase antes de avanzar para setear los valores luego
                listaP = listaP->sig;
                //Busco con cada ocurrencia de la primer palabra, si hay match con el resto de las palabras y sus ocurrencias.
                while(listaPalabra && encontrado == 0)
                {
                    encontrado = buscaPalabras(listaPalabra->idDOC, listaP, arbol);

                    if (encontrado == 1)     //Si encuentra un match, setteo los valores de la primer palabra.
                    {
                        primero->idDOC = listaPalabra->idDOC;
                        primero->pos = listaPalabra->pos;
                    }

                    //Si no hubo match, voy a pasar a buscar un match con la siguiente ocurrencia de la primer palabra
                    //que le cambia el id.
                    int auxId = listaPalabra->idDOC;
                    //Avanzo hasta pasar todas las ocurrencias con el mismo Id que no hubo match.
                    while (listaPalabra->idDOC == auxId && encontrado == 0)
                    {
                        listaPalabra = listaPalabra->sig;
                    }
                }
            }
        }
    }

    return encontrado;
}

int buscaPalabras(int idDOC, nodoFrase* listaP, nodoA* arbol)
{
    int encontrado = 0;
    int flag = 0;

    //Recorro la lista con la frase a encontrar.
    while (listaP && flag == 0)
    {

        // Setteo encontrado en 0 aca, para cada nueva busqueda
        encontrado = 0;
        //Busco la lista de ocurrencias de la palabra actual en el arbol.
        nodoT* nodoPalabra = buscarListaOcurrenciasPalabra(arbol, listaP->palabra);

        //Comparo si de esa lista, alguna de las ocurrencias matchean con el id y la posición contigua.
        while(nodoPalabra && nodoPalabra->idDOC < idDOC)   // Si el idDOC de la lista se mantiene menor al del parametro
        {
            // avanzo en la lista de ocurrencias
            nodoPalabra = nodoPalabra->sig;
        }

        if(nodoPalabra && idDOC == nodoPalabra->idDOC)   // Significa que hubo match
        {
            //Guardo en la lista los datos del match.
            listaP->idDOC = nodoPalabra->idDOC;
            listaP->pos = nodoPalabra->pos;

            encontrado = 1;
        }

        //De no encontrar un match, corto el while con el flag.
        if (encontrado == 0)
        {
            flag = 1;
        }
        else
        {
            //Si no, avanzo en la lista hacia la siguiente palabra de la frase.
            listaP = listaP->sig;

        }
    }

    return encontrado;
}
///  4): Busca una frase en un arbol, pasandole una lista con dicha frase. Retorna si encontro o no la frase. La lista queda setteado con los valores donde fueron hallados.

int buscarFraseEnDiccionario(nodoA* arbol, nodoFrase* listaF)
{

    int encontrado = 0;

    if (listaF && arbol)   //Si la lista con la frase o el arbol estan vacios, salgo.
    {

        //Busco la primer palabra en el arbol y retorno la lista de ocurrencias de dicha palabra o un NULL.
        nodoT* listaPalabra = buscarListaOcurrenciasPalabra(arbol, listaF->palabra);

        if (listaPalabra)   //Si encuentro la primer palabra.
        {

            if (listaF->sig == NULL)      //La frase era una sola palabra y la encontro.
            {
                encontrado = 1;
                listaF->idDOC = listaPalabra->idDOC;
                listaF->pos = listaPalabra->pos;
            }
            else
            {
                nodoFrase* primero = listaF; // guardo el primer nodo de la frase antes de avanzar para setear los valores luego
                listaF = listaF->sig;
                //Busco con cada ocurrencia de la primer palabra, si hay match con el resto de las palabras y sus ocurrencias.
                while(listaPalabra && encontrado == 0)
                {
                    encontrado = buscarFrase(listaPalabra->idDOC, listaPalabra->pos, listaF, arbol);

                    if (encontrado == 1)     //Si encuentra un match, setteo los valores de la primer palabra.
                    {
                        primero->idDOC = listaPalabra->idDOC;
                        primero->pos = listaPalabra->pos;
                    }
                    //Si no hubo match, voy a pasar a buscar un match con la siguiente ocurrencia de la primer palabra.
                    listaPalabra = listaPalabra->sig;
                }
            }
        }
    }

    return encontrado;
}

/**
 *  Sireve para encontrar desde la segunda palabra en adelante si la frase existe en el diccionario. Recibe el idDOC y pos de la primer palabra, la lista que contiene
 *  la frase (sin la primer palabra) y el arbol para buscar.
 */

int buscarFrase(int idDOC, int pos, nodoFrase* listaF, nodoA* arbol)
{
    int encontrado = 0;
    int flag = 0;

    //Recorro la lista con la frase a encontrar.
    while (listaF && flag == 0)
    {

        // Seteo encontrado en 0 aca, para cada nueva busqueda
        encontrado = 0;
        //Busco la lista de ocurrencias de la palabra actual en el arbol.
        nodoT* nodoPalabra = buscarListaOcurrenciasPalabra(arbol, listaF->palabra);

        //Comparo si de esa lista, alguna de las ocurrencias matchean con el id y la posición contigua.
        while(nodoPalabra && nodoPalabra->idDOC < idDOC)   // Si el idDOC de la lista se mantiene menor al del parametro
        {
            // avanzo en la lista de ocurrencias
            nodoPalabra = nodoPalabra->sig;
        }

        while(nodoPalabra && idDOC == nodoPalabra->idDOC && nodoPalabra->pos < pos)
        {

            nodoPalabra = nodoPalabra->sig;
        }
        if(nodoPalabra && idDOC == nodoPalabra->idDOC && nodoPalabra->pos == pos + 1)   // Significa que hubo match
        {
            //Guardo en la lista los datos del match.
            listaF->idDOC = nodoPalabra->idDOC;
            listaF->pos = nodoPalabra->pos;

            encontrado = 1;
        }

        //De no encontrar un match, corto el while con el flag.
        if (encontrado == 0)
        {
            flag = 1;
        }
        else
        {
            //Si no, avanzo en la lista hacia la siguiente palabra de la frase.
            listaF = listaF->sig;

            //Aumento la posición para que la siguiente palabra buscada sea contigua a esta.
            pos++;
        }
    }

    return encontrado;
}
///5) Busca la palabra que aparece con mas frecuencia en alguno de los docs.
void buscarMayorFrecuenciaDoc(nodoA* arbol, nodoA** mayorFrec, int idDoc, int* maxFrec)
{
    if (arbol)
    {

        buscarMayorFrecuenciaDoc(arbol->izq, mayorFrec, idDoc, maxFrec);
        buscarMayorFrecuenciaDoc(arbol->der, mayorFrec, idDoc, maxFrec);

        int frecActual, frecMayor;
        frecActual = cuentaFrecuenciaOcurrencias(arbol->ocurrencias, idDoc);
        frecMayor = cuentaFrecuenciaOcurrencias((*mayorFrec)->ocurrencias, idDoc);

        if (frecActual > frecMayor)
        {
            *mayorFrec = arbol;
            *maxFrec = frecActual;
        }
    }
}

nodoA* mayorFrecuenciaDoc(nodoA* arbol, int idDoc)
{
    nodoA* mayorFrec = NULL;
    int maxFrec;

    if (arbol)
    {


        mayorFrec = arbol;

        //Seteo nodo con mayor frecuencia.
        buscarMayorFrecuenciaDoc(arbol, &mayorFrec, idDoc, &maxFrec);

        //Guardo la lista de ocurrencias para poder mostrar todas las ocurrencias
        nodoT* aux = mayorFrec->ocurrencias;

        //Creo un nodo nuevo con la palabra para no modificar el nodo del árbol
        mayorFrec = crearNodoA(mayorFrec->palabra);

        //Setteo la frencuencia
        mayorFrec->frecuencia = maxFrec;

        //Setteo las ocurrencias
        mayorFrec->ocurrencias = aux;
    }

    return mayorFrec;
}

int cuentaFrecuenciaOcurrencias (nodoT* ocurrencias, int idDoc)
{
    int contador = 0;
    while (ocurrencias && ocurrencias->idDOC < idDoc)
    {
        ocurrencias = ocurrencias->sig;
    }

    while (ocurrencias && ocurrencias->idDOC == idDoc)
    {
        contador ++;
        ocurrencias = ocurrencias->sig;
    }

    return contador;
}

void mostrarNodoAFREC(nodoA* arbol, int id)
{
    printf("\n Palabra: %s", arbol->palabra);
    printf("\n Frecuencia en el ID %d : %d", id, arbol->frecuencia);
    printf("\n Ocurrencias: ");
    mostrarListaNodoTFREC(arbol->ocurrencias, id);
}

void mostrarListaNodoTFREC(nodoT *lista, int id)
{
    if(lista)
    {
        if (lista->idDOC == id)
        {
            mostrarNodoT(lista);
        }
        mostrarListaNodoTFREC(lista->sig, id);
    }
}
///6) Utilizar la distancia de levenshtein en el ingreso de una palabra y sugerir similares a partir de una distancia <= 3.
int Minimo(int a, int b, int c)
{
    if(a <= b && a <= c)
    {
        return a;
    }
    else if(b <= a && b <= c)
    {
        return b;
    }
    else if(c <= a && c <= b)
    {
        return c;
    }
}

int Levenshtein(char *s1,char *s2)
{
    int t1,t2,i,j,*m,costo,res,ancho;

// Calcula tamanios strings
    t1=strlen(s1);
    t2=strlen(s2);

// Verifica que exista algo que comparar
    if (t1==0)
        return(t2);
    if (t2==0)
        return(t1);
    ancho=t1+1;

// Reserva matriz con malloc                     m[i,j] = m[j*ancho+i] !!
    m=(int*)malloc(sizeof(int)*(t1+1)*(t2+1));
    if (m==NULL)
        return(-1); // ERROR!!

// Rellena primera fila y primera columna
    for (i=0; i<=t1; i++)
        m[i]=i;
    for (j=0; j<=t2; j++)
        m[j*ancho]=j;

// Recorremos resto de la matriz llenando pesos
    for (i=1; i<=t1; i++)
        for (j=1; j<=t2; j++)
        {
            if (s1[i-1]==s2[j-1])
                costo=0;
            else
                costo=1;
            m[j*ancho+i]=Minimo(m[j*ancho+i-1]+1, m[(j-1)*ancho+i]+1, m[(j-1)*ancho+i-1]+costo);
        }      // Sustitucion

// Devolvemos esquina final de la matriz
    res=m[t2*ancho+t1];
    free(m);
    return(res);
}

void sugierePalabrasSimilares(nodoA* arbol, char* palabra)   //Funcion que llama a levenshtein y muestra por pantalla las palabras con distancia <=3 a la palabra buscada
{
    if (arbol)
    {
        sugierePalabrasSimilares(arbol->izq, palabra); //El recorrido del arbol es inOrder
        if(Levenshtein(arbol->palabra, palabra)<=3)
        {
            printf("[ %s ] ", arbol->palabra);
            printf("\n");
        }
        sugierePalabrasSimilares(arbol->der, palabra);
    }
}
