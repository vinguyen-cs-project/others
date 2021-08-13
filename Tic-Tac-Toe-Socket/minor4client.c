/* Vi Nguyen -- EUID: 11300388
* CSCE3600.003
* Minor4
* Server and Client
* Version: 1.0
* Date: Jan 24, 2019
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0, portno, soc;
    char recvBuff[1025];
    struct sockaddr_in serv_addr;
    fd_set fds;
    int maxfd;
    
    memset(recvBuff, '0', sizeof(recvBuff));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }
 
    serv_addr.sin_family = AF_INET;
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connect error\n");
        exit(EXIT_FAILURE);
    }
    maxfd = sockfd +1;
   while (1) {
        FD_ZERO(&fds);
       FD_SET(sockfd,&fds);
       FD_SET(0,&fds);
        select(maxfd, &fds, NULL, NULL, NULL);
        
        if (FD_ISSET(sockfd,&fds)) {
            if (read(sockfd, recvBuff, 1025) > 0) printf("%s",recvBuff);
            else break;
        }
        if (FD_ISSET(0,&fds)) {
            fgets(recvBuff, 1025, stdin);
            write(sockfd, recvBuff, strlen(recvBuff)+1);
        }
    }
    close(sockfd);
    return 0;
}


