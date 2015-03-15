/*
 -----------------------------------------------------------------------------
  $Id: connect_test.c,v 1.1 2001/04/23 03:28:42 sconnet Exp sconnet $

  $Log: connect_test.c,v $
  Revision 1.1  2001/04/23 03:28:42  sconnet
  Initial revision

 -----------------------------------------------------------------------------

compile with:
  cc -Wall -O2 -o ctest connect_test.c

  Coded by Steve Connet
  02/18/2001

  To test the number of connections the pgserver can handle without
  breaking. Tells me what linux out of the box can handle.

  /sbin/sysctl -a | grep fs
  fs.inode-max = 16384

  We shall see ... muwahaha!
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


int processargs(int argc, char *argv[], char *addr, int len, int *port, int *count)
{
    if(argc == 1) {
        printf("Usage: %s -a ipaddr -p port -c count\n", argv[0]);
        printf("Example: %s -a 192.168.0.1 -p 6667 -c 1024\n", argv[0]);
        return -1;
    }

    while(argc--) {
        if(argv[argc][0] == '-') {
            switch(argv[argc][1]) {
                case 'a':
                    if(argv[argc+1]) {
                        strncpy(addr, argv[argc+1], len);
                    }
                    break;
                case 'p':
                    if(argv[argc+1]) {
                        *port = atoi(argv[argc+1]);
                    }
                    break;
                case 'c':
                    if(argv[argc+1]) {
                        *count = atoi(argv[argc+1]);
                    }
                    break;
            }
        }
    }

    return 0;
}

#define ADDRLEN 16
int main(int argc, char *argv[])
{
    char *msg = "2";  /* arbitrary message */
    /* int msg = 2; */
    char addr[ADDRLEN] = { 0 };
    int *connections = NULL;
    int port = -1;
    int count = -1;
    int index = -1;
    int fd = -1;
    int done = 0;
    struct sockaddr_in sock;

    /* get ip address, port, and count from cmd line */
    if(processargs(argc, argv, addr, ADDRLEN, &port, &count) < 0) {
        exit(1);
    }

    /* allocate memory to hold our connections */
    connections = (int *)calloc(count, sizeof(int));
    if(connections == NULL) {
        perror("error allocating mem for connections");
        exit(-1);
    }

    fprintf(stdout, "Creating connections to %s:%d\n", addr, port);

    /* setup for connect */
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = inet_addr(addr);
    sock.sin_port = htons(port);

    /* perform 'count' connections */
    for(index = 0; index < count; index++) {
        if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("error creating socket");
            goto end;
        }

        if(connect(fd, (struct sockaddr *)&sock, sizeof(sock)) < 0) {
            perror("connect()");
            goto end;
        }

        /* write a msg */
        /* write(fd, (char*)&msg, sizeof(msg)); */
        write(fd, msg, strlen(msg));

        /* store connection */
        connections[index] = fd;

        /* progress feedback */
        done = ((index+1) * 100) / count;
        fprintf(stdout, "%d%%", done);
        if(done < 10) {
            fprintf(stdout, "\b\b");
        }
        else if(done < 100) {
            fprintf(stdout, "\b\b\b");
        }
    }

end:
    /* close up shop */
    for(index = 0; index < count; index++) {
        shutdown(connections[index], SHUT_RDWR);
        close(connections[index]);
    }

    /* free memory and bail */
    free(connections);
    fprintf(stdout, "\n\n");
    return EXIT_SUCCESS;
}

