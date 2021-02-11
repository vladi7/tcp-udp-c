/*-------------------------------------------------------------*/
/* client.c  Vladislav Dubrovenski                             */
/*-------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "inet.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


#define MAX 100

static volatile int flag = 1;

int get_response(void);
int readn(int, char *, int);

void sig_handler(int signo)
{
  if (signo == SIGINT)
  {
	flag=0;
  }
}

int main(int argc, char **argv)
{
    int                 sockfd;
    struct sockaddr_in  serv_addr;
    char                s[MAX];      /* array to hold output */
    int                 response;    /* user response        */
    int                 nread;       /* number of characters */

    /* Set up the address of the server to be contacted. */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port        = htons(SERV_TCP_PORT);

		
	struct sigaction act;
	act.sa_handler = sig_handler;
	sigaction(SIGINT, &act, NULL);
	
    /* Display the menu, read user's response, and send it to the server. */
    while(1) {

		if((response = get_response()) == -1){
		//input check failed
		if(flag){
			printf("\nInvalid input, goodbye.\n");
			return 1;
			}

		}
        /* Create a socket (an endpoint for communication). */
        if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("client: can't open stream socket");
            exit(1);
        }

        /* Connect to the server. */
        if (connect(sockfd, (struct sockaddr *) &serv_addr,
          sizeof(serv_addr)) < 0) {
            perror("client: can't connect to server");
            exit(1);
        }
        snprintf(s,MAX,"%d",response);
			
			//if ctrl-c was pressed
				if(!flag){
					response = 0;	
				snprintf(s,MAX,"%d",response);
					printf("\nGoodbye!\n");
					 /* Send the user's request to the server. */
					write (sockfd, s, sizeof(char));
					exit(0); 
				}
        /* Send the user's request to the server. */
        write (sockfd, s, sizeof(char));

        /* Read the server's reply. */
        nread = readn (sockfd, s, MAX);
        if (nread > 0) {
			printf("   %s\n", s);
	} else {
		printf("Nothing read. \n");
	}
        close(sockfd);
    }
}

/* Display menu and retrieve user's response */
int get_response()
{		
    int choice;
    printf("-------------------------------------------\n");
    printf("                1. Time\n");
    printf("                2. PID\n");
    printf("                3. Random number between 1 and 30, inclusive\n");
    printf("-------------------------------------------\n");
    printf("               Choice (1-3):");

	char term;
	if( scanf("%d%c",&choice,&term)!=2||choice<1 || choice > 3|| term!='\n'){//protection against invalid input	
        return -1;
	}
    printf("===========================================\n");
    return(choice);

}

/*
 * Read up to "n" bytes from a descriptor.
 * Use in place of read() when fd is a stream socket.
 */

int
readn(fd, ptr, nbytes)
register int	fd;
register char	*ptr;
register int	nbytes;
{
	int	nleft, nread;

	nleft = nbytes;
	while (nleft > 0) {
		nread = read(fd, ptr, nleft);
		if (nread < 0)
			return(nread);		/* error, return < 0 */
		else if (nread == 0)
			break;			/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(nbytes - nleft);		/* return >= 0 */
}

