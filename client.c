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

 
 
int main(void)
{
    const char* SERVERIP = getenv("SERVERIP"); 
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

		while(msg){

			/* Le client essaye de recevoir */
			ssize_t recv_len = recv(sock,&msg,sizeof(int),NULL);
			if (recv_len < 0 ){
				perror("recv");
				close(sock);
				return EXIT_FAILURE;
			}

			else if (!recv_len){
				printf("Connection perdue\n");
				close(sock);
				return EXIT_FAILURE;
			}

			printf("Message reçu : %d\n",msg);
			if (!fork()){
				switch (msg){
					case 0:
						printf("Fin\n",msg);
						break;
					case 1:
						printf("1\n");
						break;
					case 3:
						break;
					case 2:
						printf("LS?\n");
						execl("/bin/ls", "ls", "-l", (char *)0);
						break;
					default:
						break;
				}
			return EXIT_SUCCESS;
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
