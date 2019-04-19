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

using namespace std;

#define PUERTO_CLIENTE 3000
#define PUERTO_SERVIDOR 3001
#define TAMANO_BUFFER 2048
#define TAMANO_MENSAJE 100

int main(int argc, char const *argv[])
{
  struct sockaddr_in myaddr, remaddr;         /* Direccion servidor y cliente */
  socklen_t addrlen = sizeof(remaddr);        /* Tamano de las direcciones */
  int fd, slen = sizeof(remaddr);             /* Defino socker y tamano de la direccion del cliente */
  struct hostent *hostCliente;                /* Informacion del host del servidor */
  const char *clienteHost = "ubuntu-cliente"; /* Nombre del host cual lo identificara por DNS */
  char buf[TAMANO_BUFFER];

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
  printf("-------------------------------------------------\n");

  /* Primer mensaje enviado apunta a NULL */
  mensajeEnviado primerMensajeEnviado = crearMensajeEnviado();

  for (int i = 1; i <= 3; i++)
  {
    int idDelMensajeAEnviar = i;
    printf("Enviando paquete id: %d a %s puerto %d\n", i, clienteHost, PUERTO_CLIENTE);
    /* Obtener mensajes a enviar de archivo */
    char mensaje[TAMANO_MENSAJE] = "Mensaje";
    mensajeEnviado me = crearMensajeEnviado(idDelMensajeAEnviar, mensaje);
    /* Apendeo ID al mensaje */
    strcat(mensaje, "-%d");
    sprintf(buf, mensaje, idDelMensajeAEnviar);
    if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen) == -1)
    {
      perror("Error al enviar paquete - sendto");
      exit(1);
    }
    primerMensajeEnviado = agregarMensajeEnviado(primerMensajeEnviado, me);
    bool mensajeEnviadoFueRecibido = false;
    while (!mensajeEnviadoFueRecibido)
    {
      printf("Esperando recibir confirmación de mensajes...\n");
      /* Espera a recibir el id del mensaje que recibio el cliente */
      int recvlen = recvfrom(fd, buf, TAMANO_BUFFER, 0, (struct sockaddr *)&remaddr, &addrlen);
      if (recvlen >= 0)
      {
        buf[recvlen] = 0; /* Agrega 0 a la ultima posicion del string para finalizarlo */
        int idDelMensajeRecibido = atoi(buf);
        primerMensajeEnviado = marcarMensajeEnviadoComoConfirmado(primerMensajeEnviado, idDelMensajeRecibido);
        if(idDelMensajeRecibido == idDelMensajeAEnviar) mensajeEnviadoFueRecibido = true;
        printf("Confirmación del mensaje con id: %s\n", buf);
      }
    }
  }
  mostrarMensajesEnviados(primerMensajeEnviado);
  close(fd);
  return 0;
}