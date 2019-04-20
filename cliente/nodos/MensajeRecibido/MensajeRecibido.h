#ifndef MensajeRecibido
#define MensajeRecibido

typedef struct nodoMensajeRecibido *mensajeRecibido;

struct nodoMensajeRecibido
{
  int id;
  mensajeRecibido sigMensajeRecibido;
};

int headId(mensajeRecibido mr);
// Retorna el id del mensaje recibido

mensajeRecibido tailMensajeRecibido(mensajeRecibido mr);
// Retorna el siguiente mensaje recibido

bool estaVacio(mensajeRecibido mr);
// Retorna true si el mensaje recibido esta vacio, false de lo contrario

mensajeRecibido crearMensajeRecibido();
// Retorna NULL

mensajeRecibido crearMensajeRecibido(int id);
// Retorna un mensaje recibido

mensajeRecibido agregarMensajeRecibido(mensajeRecibido primerMensajeRecibido, mensajeRecibido mensajeRecibidoParaAgregar);
// Agrega un mensaje enviado a la lista de mensajes recibidos

void mostrarMensajesRecibidos(mensajeRecibido mr);
// Muestra los mensajes recibidos

bool mensajeRecibidoExiste(mensajeRecibido primerMensajeRecibido,  int id);
// Retorna true si el mensaje recibido existe, de lo contrario retorna false

#endif