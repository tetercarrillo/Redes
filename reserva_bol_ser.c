/*
* Fecha: 09/05/15 
* Nombre del archivo: reserva_bol_ser.c
* Descripción: Este archivo contiene el script del manejo de sockets 
* del servidor para el Sistema Ferroviario Nacional de Venezuela
* Integrantes: Jorge Luis León 09-11133
*			   Maria Esther Carrillo 10-10122
*
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_LEN 1024


int main(int argc, char *argv[])
{
     int sockfd, newsockfd, pto, clilen, n,estado;
     char buffer[BUFFER_LEN];
     struct sockaddr_in serv_addr;
     struct sockaddr_in cli_addr;
     
     if (argc < 5) {
        printf("ERROR: La línea de comandos debe ser: \n");
        printf("reserva_bol_ser -f <filas> -c <col> [-p puerto] : \n");
        exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){
     	perror("socket");
		exit(1);
     } 
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     pto = atoi(argv[6]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(pto);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("recvfrom");
			exit(3);
	}
     
     listen(sockfd,5);
     // Se guarda el tamano de la dirección del clientes
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0) perror("Error en accept()"); 

     bzero(buffer,BUFFER_LEN);
     n = read(newsockfd,buffer,BUFFER_LEN-1);

     if (n < 0) perror("ERROR en la lectura del socket");

     printf("Los asientos son: %s\n",buffer);


     // Recorrido del arreglo
     n = write(newsockfd,estado,4);

     if (n < 0) error("ERROR escribiendo en el socket");

     return 0; 
}

