#include "MensajeEnviado.h"
#include <string.h>
#include <iostream>

using namespace std;

// Retorna el id del mensaje enviado
int headId(mensajeEnviado me)
{
    return me->id;
}

// Retorna el mensaje del mensaje enviado
char *headMensaje(mensajeEnviado me)
{
    return me->mensaje;
}

// Retorna si el mensaje fue confirmado por el cliente
bool headFueConfirmado(mensajeEnviado me)
{
    return me->fueConfirmado;
}

// Retorna el siguiente mensaje enviado
mensajeEnviado tailMensajeEnviado(mensajeEnviado me)
{
    return me->sigMensajeEnviado;
}

// Retorna true si el mensaje enviado esta vacio, false de lo contrario
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

// Agrega un mensaje enviado a la lista de mensajes enviados
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

// Muestra los mensajes enviados
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

// Marcar mensaje enviado como confirmado
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