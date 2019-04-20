#include "MensajeEnviado.h"
#include <string.h>
#include <iostream>

using namespace std;

int headId(mensajeEnviado me)
{
    return me->id;
}

char *headMensaje(mensajeEnviado me)
{
    return me->mensaje;
}

bool headFueConfirmado(mensajeEnviado me)
{
    return me->fueConfirmado;
}

mensajeEnviado tailMensajeEnviado(mensajeEnviado me)
{
    return me->sigMensajeEnviado;
}

bool estaVacio(mensajeEnviado me)
{
    return me == NULL;
}

mensajeEnviado crearMensajeEnviado()
{
    return NULL;
}

mensajeEnviado crearMensajeEnviado(int id, char *mensaje)
{
    mensajeEnviado me = new (nodoMensajeEnviado);
    me->id = id;
    me->mensaje = new char[TAMANO_MENSAJE];
    strcpy(me->mensaje, mensaje);
    me->fueConfirmado = false;
    me->sigMensajeEnviado = NULL;
    return me;
}

mensajeEnviado agregarMensajeEnviado(mensajeEnviado primerMensajeEnviado, mensajeEnviado mensajeEnviadoParaAgregar)
{
    if (estaVacio(primerMensajeEnviado))
    {
        return mensajeEnviadoParaAgregar;
    }
    else
    {
        mensajeEnviado aux = primerMensajeEnviado;
        primerMensajeEnviado = agregarMensajeEnviado(tailMensajeEnviado(primerMensajeEnviado), mensajeEnviadoParaAgregar);
        aux->sigMensajeEnviado = primerMensajeEnviado;
        return aux;
    }
}

void mostrarMensajesEnviados(mensajeEnviado me)
{
    cout << "Mensajes Enviados" << endl;
    cout << "-----------------" << endl;
    while (!estaVacio(me))
    {
        cout << "Id: " << me->id << endl;
        cout << "Mensaje: " << me->mensaje << endl;
        cout << "Fue confirmado: " << me->fueConfirmado << endl;
        me = tailMensajeEnviado(me);
    }
}

mensajeEnviado marcarMensajeEnviadoComoConfirmado(mensajeEnviado primerMensajeEnviado, int id)
{
    if (estaVacio(primerMensajeEnviado))
    {
        return NULL;
    }
    else
    {
        mensajeEnviado aux = primerMensajeEnviado;
        if (id == aux->id) aux->fueConfirmado = true; 
        primerMensajeEnviado = marcarMensajeEnviadoComoConfirmado(tailMensajeEnviado(primerMensajeEnviado), id);
        aux->sigMensajeEnviado = primerMensajeEnviado;
        return aux;
    }
}

bool mensajeEnviadoFueYaConfirmado(mensajeEnviado primerMensajeEnviado, int id)
{
    if(primerMensajeEnviado == NULL)
    {
        /* Llego un id de mensaje que nunca fue enviado */
        return true;
    }
    else if(primerMensajeEnviado->id == id)
    {
        return primerMensajeEnviado->fueConfirmado;
    } else 
    {
        return mensajeEnviadoFueYaConfirmado(tailMensajeEnviado(primerMensajeEnviado), id);
    }
}