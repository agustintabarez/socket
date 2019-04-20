#include "./nodos/MensajeEnviado/MensajeEnviado.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>

using namespace std;

#define PUERTO_CLIENTE 3000
#define PUERTO_SERVIDOR 3001
#define NOMBRE_ARCHIVO_MENSAJES "mensajes.txt"

int main(int argc, char const *argv[])
{
  struct sockaddr_in myaddr, remaddr;         /* Direccion servidor y cliente */
  socklen_t addrlen = sizeof(remaddr);        /* Tamano de las direcciones */
  int fd, slen = sizeof(remaddr);             /* Defino socker y tamano de la direccion del cliente */
  struct hostent *hostCliente;                /* Informacion del host del servidor */
  const char *clienteHost = "ubuntu-cliente"; /* Nombre del host cual lo identificara por DNS */
  char bufferMensaje[TAMANO_MENSAJE];

  /* Creo socket UDP */
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Error al crear socket\n");
    return 0;
  }

  /* Relaciono direccion del cliente al puerto del cliente */
  memset((void *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(PUERTO_SERVIDOR);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
  {
    perror("Error al crear bind");
    return 0;
  }

  /* Relaciono direccion del servidor al puerto del servidor */
  memset((char *)&remaddr, 0, sizeof(remaddr));
  remaddr.sin_family = AF_INET;
  remaddr.sin_port = htons(PUERTO_CLIENTE);
  hostCliente = gethostbyname(clienteHost);
  if (!hostCliente)
  {
    fprintf(stderr, "No pudo obtener la direccion de %s\n", clienteHost);
    return 0;
  }

  /* Asigna ip del cliente a la direccion del cliente */
  memcpy((void *)&remaddr.sin_addr, hostCliente->h_addr_list[0], hostCliente->h_length);
  printf("Bind realizado con exito\n");
  printf("Numero de puerto del ubuntu-servidor = %d\n", ntohs(myaddr.sin_port));
  printf("-------------------------------------------\n");

  /* Primer mensaje enviado apunta a NULL */
  mensajeEnviado primerMensajeEnviado = crearMensajeEnviado();

  int id = 0;
  ifstream mensajes(NOMBRE_ARCHIVO_MENSAJES);
  for (string mensajeDeArchivo; getline(mensajes, mensajeDeArchivo);)
  {
    int idDelMensajeAEnviar = ++id;
    printf("Enviando paquete id: %d a %s puerto %d\n", idDelMensajeAEnviar, clienteHost, PUERTO_CLIENTE);
    char mensaje[TAMANO_MENSAJE];
    strcpy(mensaje, mensajeDeArchivo.c_str());
    mensajeEnviado me = crearMensajeEnviado(idDelMensajeAEnviar, mensaje);
    /* Apendeo ID al mensaje */
    strcat(mensaje, "-%d");
    sprintf(bufferMensaje, mensaje, idDelMensajeAEnviar);
    if (sendto(fd, bufferMensaje, strlen(bufferMensaje), 0, (struct sockaddr *)&remaddr, slen) == -1)
    {
      perror("Error al enviar paquete - sendto");
      exit(1);
    }
    primerMensajeEnviado = agregarMensajeEnviado(primerMensajeEnviado, me);
    bool mensajeEnviadoFueRecibido = false;
    while (!mensajeEnviadoFueRecibido)
    {
      /* Espera a recibir el id del mensaje que recibio el cliente */
      int recvlen = recvfrom(fd, bufferMensaje, TAMANO_MENSAJE, 0, (struct sockaddr *)&remaddr, &addrlen);
      if (recvlen >= 0)
      {
        bufferMensaje[recvlen] = 0; /* Agrega 0 a la ultima posicion del string para finalizarlo */
        int idDelMensajeRecibido = atoi(bufferMensaje);
        if(idDelMensajeRecibido == idDelMensajeAEnviar)
        {
          mensajeEnviadoFueRecibido = true;
        } 
        else
        {
          /* Cada vez que recibe un id de mensaje que no era el que esperaba */
          /* Vuelve a enviar el mensaje de nuevo */
          sprintf(bufferMensaje, mensaje, idDelMensajeAEnviar);
          if (sendto(fd, bufferMensaje, strlen(bufferMensaje), 0, (struct sockaddr *)&remaddr, slen) == -1)
          {
            perror("Error al enviar paquete - sendto");
            exit(1);
          }
        }
        if(!mensajeEnviadoFueYaConfirmado(primerMensajeEnviado, idDelMensajeRecibido))
        {
          primerMensajeEnviado = marcarMensajeEnviadoComoConfirmado(primerMensajeEnviado, idDelMensajeRecibido);
          printf("Confirmación del mensaje con id: %d\n", idDelMensajeRecibido);
        }
      }
    }
  }
  close(fd);
  mostrarMensajesEnviados(primerMensajeEnviado);
  return 0;
}