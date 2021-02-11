/*-------------------------------------------------------------*/
/* client.c - Vladislav Dubrovenski                            */
/*-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "inet.h"
#include <signal.h>
#include <unistd.h>

#define MAX 100

static volatile int flag = 1;


void sig_handler(int signo)
{
  if (signo == SIGINT)
  {
	flag=0;
  }
}

int get_response(void);

int main(int argc, char **argv)
{
    int                 sockfd;
    struct sockaddr_in  cli_addr, serv_addr;
    char                s[MAX];      /* array to hold output */
    int                 response;    /* user response        */
    int                 nread;       /* number of characters */
    int					servlen;     /* length of server addr*/
    char				request;

    /* Set up the address of the server to be contacted. */
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port        = htons(SERV_UDP_PORT);

    /* Set up the address of the client. */
    memset((char *) &cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family      = AF_INET;
    cli_addr.sin_addr.s_addr = htonl(0);
    cli_addr.sin_port        = htons(0);

    /* Create a socket (an endpoint for communication). */
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("client: can't open datagram socket");
        exit(1);
    }

    /* Bind the client's socket to the client's address */
    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
        perror("client: can't bind local address");
        exit(1);
    }

	
		struct sigaction act;
		act.sa_handler = sig_handler;
		sigaction(SIGINT, &act, NULL);
		
    /* Display the menu, read user's response, and send it to the server. */
    while(1) {
		
		
	if((response = get_response()) == -1){
		
			//handling exit	
	if(flag){
		printf("\nInvalid input, goodbye.\n");
		return 1;}
	printf("\nGoodbye!\n");
	
	
	servlen = sizeof(serv_addr);
	request = (char)('0' + 0);
        sendto (sockfd, (char *) &request, sizeof(request), 0,
                 (struct sockaddr *) &serv_addr, servlen);
    exit(0); 
	}
	
        /* Send the user's response to the server. */
	servlen = sizeof(serv_addr);
	request = (char)('0' + response);
        sendto (sockfd, (char *) &request, sizeof(request), 0,
                 (struct sockaddr *) &serv_addr, servlen);

        /* Read the server's response. */
        nread = recvfrom(sockfd, s, MAX, 0,
                 (struct sockaddr *) &serv_addr, &servlen);
        if (nread > 0) {
			printf("   %s\n", s);
	} else {
		printf("Nothing read. \n");
	}
    }
	
}

/* Display menu and retrieve user's response */
int get_response()
{
			
    int choice;
    char str[MAX];

    printf("===========================================\n");
    printf("                   Menu: \n");
    printf("-------------------------------------------\n");
    printf("                1. Time\n");
    printf("                2. PID\n");
    printf("                3. Random number between 1 and 30, inclusive\n");
    printf("-------------------------------------------\n");
    printf("               Choice (1-3):");

	char term;
	if( scanf("%d%c",&choice,&term)!=2||choice<1 || choice > 3|| term!='\n'){//validating input	
        return -1;
	}
    printf("===========================================\n");
    return(choice);

}



