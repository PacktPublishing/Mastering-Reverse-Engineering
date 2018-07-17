#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, n;
    struct sockaddr_in serv_addr;
    struct sockaddr_in ctl_addr;
    int addrlen;
    char sendBuff[1025];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9999); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    
    printf("Genie is waiting for connections to port 9999.\n");
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&ctl_addr, &addrlen);
        printf("%s has connected.\n", inet_ntoa(ctl_addr.sin_addr));

        snprintf(sendBuff, sizeof(sendBuff), "You have connected to the Genie. Nothing to see here.\n\n");
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
    return 0;
}

