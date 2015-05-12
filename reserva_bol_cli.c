/*
* Fecha: 09/05/15 
* Nombre del archivo: reserva_bol_ser.c
* Descripción: Este archivo contiene el script del manejo de sockets 
* del cliente para el Sistema Ferroviario Nacional de Venezuela
* Integrantes: Jorge Luis León 09-11133
*              Maria Esther Carrillo 10-10122
*
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFFER_LEN 1024

int main(int argc, char *argv[]){
    int sockfd, pto, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_LEN];

    if (argc < 7) {
        printf("ERROR: La línea de comandos debe ser: \n");
        printf("reserva_bol_cli <ip-servidor> -p <puerto servicio> -f <fila> -c <col> \n");
        exit(1);
     }

    pto = atoi(argv[3]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        perror("socket");
        exit(1);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no existe ese host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(pto);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Procensando su solicitud... ");
    bzero(buffer,BUFFER_LEN);
    buffer[0]= atoi(argv[5]);
    buffer[1]= atoi(argv[7]);
    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0) 
         error("ERROR escribiendo en el socket");
    bzero(buffer,BUFFER_LEN);
    n = read(sockfd,buffer,BUFFER_LEN-1);

    if (n < 0) 
         error("ERROR leyendo del socket");
    // printf("%s\n",buffer);
    return 0;
}