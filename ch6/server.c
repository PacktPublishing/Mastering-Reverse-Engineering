#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, n;
    struct sockaddr_in serv_addr = { 0 };
    struct sockaddr_in ctl_addr = { 0 };
    int addrlen;
    char sendBuff[1025];
    char recvBuff[1025];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9999); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    
    printf("Genie is waiting for connections to port 9999.\n");
    snprintf(sendBuff, sizeof(sendBuff), "You have connected to the Genie. Nothing to see here.\n\n");
    while(1)
    {
        memset(&ctl_addr, 0, sizeof(ctl_addr));
        addrlen = sizeof(ctl_addr);
        connfd = accept(listenfd, (struct sockaddr*)&ctl_addr, &addrlen);
        memset(&recvBuff, 0, 1024);
        read(connfd, recvBuff, 1024);
        printf("%s has connected.\n", inet_ntoa(ctl_addr.sin_addr));
        send(connfd, sendBuff, strlen(sendBuff),0); 

        close(connfd);
        sleep(1);
     }
    return 0;
}

