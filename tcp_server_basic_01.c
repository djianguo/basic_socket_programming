#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>/*bzero*/
#include <netinet/in.h>/*struct sockaddr_in*/
#include <arpa/inet.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(struct sockaddr);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(server_addr.sin_zero, 8);
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
    listen(server_fd, 5);

    printf("*PID:%d.\n", getpid());
    while(1)
    {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addrlen);
        if(!fork())
        {
            char* client_ip = inet_ntoa(client_addr.sin_addr);
            printf("A connection from %s.\n", client_ip);
            printf("PID: %d.\n", getpid());
            printf("PPID: %d.\n", getppid());



            /**
             *  if i want to sent some files to the client as a response,
             *  how can i do rigth now?
             */
            send(client_fd, "Hello, This is JiangGuo.", 32, 0);
            close(client_fd);
            exit(0);
        }
        close(client_fd);
    }
    
    return 0;
}

