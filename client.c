#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
 
#include <stdio.h>
#include <stdlib.h>
#define PORT 8000 
#define SERVERIP "51.38.238.67"
 
 
 
int main(void)
{
    int erreur = 0;
 
    int sock;
    struct sockaddr_in sin;
    int msg = -1;
 
    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr(SERVERIP);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /* Si le client arrive à se connecter */
        if(connect(sock, (struct sockaddr*)&sin, sizeof(sin)) != SOCKET_ERROR){
            	printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

		while(1){

			/* Le client essaye de recevoir */
			if (recv(sock,&msg,32,NULL) < 0 ){
				perror("recv");
				close(sock);
				return EXIT_FAILURE;
			}
			if (msg == -1)
				printf("Message non reçu.\n");
			else{
 			printf("received : %d\n",msg);
			}
		}
    	}
        else
            printf("Impossible de se connecter\n");
        /* On ferme la socket précédemment ouverte */
        close(sock);
    }
 
    return EXIT_SUCCESS;
}
