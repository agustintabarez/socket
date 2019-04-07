#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PUERTO_CLIENTE 3000
#define PUERTO_SERVIDOR 3001
#define TAMANO_BUFFER 2048

main(int argc, char **argv)
{
  struct sockaddr_in myaddr, remaddr;  /* Direccion servidor y cliente */
  socklen_t addrlen = sizeof(remaddr); /* Tamano de las direcciones */
  int recvlen;                         /* Bytes recibidos por paquete */
  int fd;                              /* Defino socket */
  int cantidadMensajesRecibidos = 0;   /* Cantidad de mensajes recibidos */
  char buf[TAMANO_BUFFER];           

  /* Creo socket UDP */
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Error al crear socket\n");
    return 0;
  }

  /* Relaciono socket al puerto del cliente */
  memset((char *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(PUERTO_CLIENTE);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
  {
    perror("Error al crear bind");
    return 0;
  }

  while (true)
  {
    printf("Esperando en puerto %d\n", PUERTO_CLIENTE);
    recvlen = recvfrom(fd, buf, TAMANO_BUFFER, 0, (struct sockaddr *)&remaddr, &addrlen);
    printf("Recibio %d bytes\n", recvlen);
    if (recvlen > 0)
    {
      buf[recvlen] = 0; /* Agrega 0 a la ultima posicion del string para finalizarlo */
      printf("Mensaje recibido: \"%s\"\n", buf);
    }
    else
    {
      printf("Error ocurrio al leer contenido del paquete\n");
    }
    sprintf(buf, "ack %d", cantidadMensajesRecibidos++);
    printf("Enviando respuesta \"%s\"\n", buf);
    if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
      perror("Error al enviar respuesta (sendto)");
  }
}