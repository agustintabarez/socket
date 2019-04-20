#include "MensajeRecibido.h"
#include <string.h>
#include <iostream>

using namespace std;

int headId(mensajeRecibido mr)
{
    return mr->id;
}

mensajeRecibido tailMensajeRecibido(mensajeRecibido mr)
{
    return mr->sigMensajeRecibido;
}

bool estaVacio(mensajeRecibido mr)
{
    return mr == NULL;
}

mensajeRecibido crearMensajeRecibido()
{
    return NULL;
}

mensajeRecibido crearMensajeRecibido(int id)
{
    mensajeRecibido mr = new (nodoMensajeRecibido);
    mr->id = id;
    mr->sigMensajeRecibido = NULL;
    return mr;
}

mensajeRecibido agregarMensajeRecibido(mensajeRecibido primerMensajeRecibido, mensajeRecibido mensajeRecibidoParaAgregar)
{
    if (estaVacio(primerMensajeRecibido))
    {
        return mensajeRecibidoParaAgregar;
    }
    else
    {
        mensajeRecibido aux = primerMensajeRecibido;
        primerMensajeRecibido = agregarMensajeRecibido(tailMensajeRecibido(primerMensajeRecibido), mensajeRecibidoParaAgregar);
        aux->sigMensajeRecibido = primerMensajeRecibido;
        return aux;
    }
}

void mostrarMensajesRecibidos(mensajeRecibido mr)
{
    cout << "IDs - Mensajes Recibidos" << endl;
    cout << "------------------------" << endl;
    while (!estaVacio(mr))
    {
        cout << "Id: " << mr->id << endl;
        mr = tailMensajeRecibido(mr);
    }
}

bool mensajeRecibidoExiste(mensajeRecibido primerMensajeRecibido,  int id)
{
    if(primerMensajeRecibido == NULL)
    {
        return false;
    }
    else if(primerMensajeRecibido->id == id)
    {
        return true;
    } else 
    {
        return mensajeRecibidoExiste(tailMensajeRecibido(primerMensajeRecibido), id);
    }
}