/*
 * Definitions for TCP and UDP client/server programs.
 * Vladislav Dubrovenski
 */

#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	SERV_TCP_PORT	12345
#define	SERV_HOST_ADDR	"129.130.10.39" /* Change to your host IP-addr */
