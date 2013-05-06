#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    socklen_t server_addrlen = sizeof(struct sockaddr);
    char buf[64];
    ssize_t recv_len;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(server_addr.sin_zero, 8);
    
    connect(client_fd, (struct sockaddr*)&server_addr, server_addrlen);


    /**
     *  How can i do when I receive some really big file from server?
     */
    recv_len = recv(client_fd, buf, sizeof(buf), 0);
    buf[recv_len]='\0';
    printf("Client received \"%s\" from Server.\n", buf);
    close(client_fd);
    
    return 0;
}

