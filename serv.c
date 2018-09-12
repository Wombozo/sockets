#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8000


int main(void){
	int error;
	int sock, csock;
	struct sockaddr_in sin, csin;

	int msg = 2;
	socklen_t recsize=sizeof(sin);
	socklen_t crecsize=sizeof(csin);
	int sock_err;


	sock = socket(AF_INET, SOCK_STREAM,0);
	if (sock != INVALID_SOCKET){
		sin.sin_addr.s_addr=htonl(INADDR_ANY);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);

		sock_err = bind(sock,(struct sockaddr*) &sin, recsize);

		if (sock_err != SOCKET_ERROR){

			/* Démarrage du listage */
			sock_err = listen(sock,1);
			printf("Listage du port %d\n",PORT);

			if (sock_err != SOCKET_ERROR){
				
				/* Attente pendant laquelle le client se connecte */
				printf("On attend que le client se connecte..\n");
				csock = accept(sock,(struct sockaddr*) &csin, &crecsize);
				printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
			}
			else 
				perror("Listen");
		}else
			perror("Bind");

		while(1){
			/* Envoi de la donnée */
			if (send(csock, &msg, sizeof(int), 0) < 0){
				perror("send");
			}
			else{
				printf("Message envoyé : %d\n",msg);
			}
			sleep(5);
			msg++;
		}
	}

	/* Fermeture de la socket client et de la socket serveur */
	printf("Fermeture du serveur\n"); 
        close(csock);
	close(sock);

	return EXIT_SUCCESS;
}
