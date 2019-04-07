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
#define BUFLEN 2048

int main(int argc, char const *argv[])
{
  struct sockaddr_in myaddr, remaddr;   /* Direccion servidor y cliente */
  socklen_t addrlen = sizeof(remaddr);  /* Tamano de las direcciones */
  int fd, slen = sizeof(remaddr);       /* Defino socker y tamano de la direccion del cliente */
  struct hostent *hostCliente;          /* Informacion del host del servidor */
  char *clienteHost = "ubuntu-cliente"; /* Nombre del host cual lo identificara por DNS */
  char buf[BUFLEN];

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
  // Asigna ip del cliente a la direccion del cliente
  memcpy((void *)&remaddr.sin_addr, hostCliente->h_addr_list[0], hostCliente->h_length);
  printf("Bind realizado con exito. Numero de puerto = %d\n", ntohs(myaddr.sin_port));

  for (int i = 0; i < 3; i++)
  {
    printf("Enviando paquete %d to %s puerto %d\n", i, clienteHost, PUERTO_CLIENTE);
    sprintf(buf, "Este es el paquete %d", i);
    if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen) == -1)
    {
      perror("Error al enviar paquete (sendto)");
      exit(1);
    }
    /* Espera a recibir ack del servidor */
    int recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &addrlen);
    if (recvlen >= 0)
    {
      buf[recvlen] = 0; /* Agrega 0 a la ultima posicion del string para finalizarlo */
      printf("Mensaje recibido: \"%s\"\n", buf);
    }
  }
  close(fd);
  return 0;
}
