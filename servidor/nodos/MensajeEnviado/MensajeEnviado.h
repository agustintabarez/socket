#ifndef MensajeEnviado
#define MensajeEnviado
#define TAMANO_MENSAJE 100

typedef struct nodoMensajeEnviado *mensajeEnviado;

struct nodoMensajeEnviado
{
  int id;
  char *mensaje;
  bool fueConfirmado;
  mensajeEnviado sigMensajeEnviado;
};

int headId(mensajeEnviado me);
// Retorna el id del mensaje enviado

char * headMensaje(mensajeEnviado me);
// Retorna el mensaje del mensaje enviado

bool headFueConfirmado(mensajeEnviado me);
// Retorna si el mensaje fue confirmado por el cliente

mensajeEnviado tailMensajeEnviado(mensajeEnviado me);
// Retorna el siguiente mensaje enviado

bool estaVacio(mensajeEnviado me);
// Retorna true si el mensaje enviado esta vacio, false de lo contrario

mensajeEnviado crearMensajeEnviado();
// Retorna NULL

mensajeEnviado crearMensajeEnviado(int id, char * mensaje);
// Retorna un mensaje enviado

mensajeEnviado agregarMensajeEnviado(mensajeEnviado primerMensajeEnviado, mensajeEnviado mensajeEnviadoParaAgregar);
// Agrega un mensaje enviado a la lista de mensajes enviados

void mostrarMensajesEnviados(mensajeEnviado me);
// Muestra los mensajes enviados

mensajeEnviado marcarMensajeEnviadoComoConfirmado(mensajeEnviado primerMensajeEnviado, int id);
// Marcar mensaje enviado como confirmado

bool mensajeEnviadoFueYaConfirmado(mensajeEnviado primerMensajeEnviado, int id);
// Retorna true si el mensaje enviado fue confirmado, de lo contrario retorna false

#endif