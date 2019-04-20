## Socket UDP - cliente servidor

- Instalar GitHub siguiendo los pasos de su [pagina oficial](https://github.com/).

- Instalar Docker siguiendo los pasos de su [pagina oficial](https://www.docker.com/get-started).

- Instalar docker-compose siguiendo los pasos de la [documentacion](https://docs.docker.com/compose/install/) de Docker.

- Clonar proyecto:
    ```
    git clone https://github.com/agustintabarez/socket.git
    ```
- Construir contenedor ubuntu-cliente desde /cliente:
    ```
    docker-compose up --build cliente
    ```
- Construir contenedor ubuntu-servidor desde /servidor:
    ```
    docker-compose up --build servidor
    ```
- Crear red-local para comunicación de los contenedores:
    ```
    docker network create red-local
    ```
- Conectar contenedor ubuntu-cliente a red-local:
    ```
    docker network connect red-local ubuntu-cliente
    ```
- Conectar contenedor ubuntu-servidor a red-local:
    ```
    docker network connect red-local ubuntu-servidor
    ```
- Abrir dos consolas una para el servidor (i) y otra para el cliente (ii)
    1. Acceder al cmd del ubuntu-servidor desde la consola del servidor:
        ```                                  
        docker exec -it ubuntu-servidor /bin/bash
        ```                               
    2. Acceder al cmd del ubuntu-cliente desde la consola del cliente:
        ```
        docker exec -it ubuntu-cliente /bin/bash
        ```
- Posibles errores:
    - Error al crear bind: Address already in use
        - Ejecutar el siguiente comando desde donde ocurrio dicho error (servidor o cliente)
          ```
          make kill
          ```
