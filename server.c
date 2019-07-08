#include "us_xfr.h"

void chat_func_server(int sfd)
{
    char buff[BUFF_SIZE];
    time_t now;
    // Used to iterate through each bit in the buffer
    int ret;
    int flag = 0;

    for (;;)
    {
        // Read message from client and copy it in buffer
        ret = read(sfd, buff, BUFF_SIZE);
        buff[ret] = 0;
        // Print buffer which contains the client contents
        printf("(%d)Log from Client: %s", flag, buff);
        
        if (strncmp("hello", buff, 5) == 0)
        {
            sprintf(buff, "hello. what do you want to do?\n");
            write(sfd, buff, sizeof(buff));
            flag = 1;
            
        }
        if((strncmp("login", buff, 5) == 0) && (flag == 1))
        {
            sprintf(buff, "welcome!\n");
            write(sfd, buff, sizeof(buff));
            flag = 2;
        }
        if(strncmp("please give me time", buff, 19) == 0 
            && (flag == 2))
        {
            time(&now);
            sprintf(buff, "Today is : %s", ctime(&now));
            write(sfd, buff, sizeof(buff));
        }
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server exit...\n");
            break;
        }
        else
        {
            sprintf(buff, "please log in or ask for something i know\n");
            write(sfd, buff, sizeof(buff));
        }               
    }
}

int main(int argc, char *argv[])
{
    // sfd = socket file descriptor / cfd = connection file descriptor
    struct sockaddr_in servaddr, cli;
    int sfd, cfd, len;

    // Create socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    // Check socket creation
    if (sfd == -1)
    {
        fprintf(stderr, "Socket creation failed");
        exit(0);
    }
    else
    {
        printf("Socket successfully created...\n");
    }

    // Fill block of memory with 0s starting from address 
    // of addr, for the size of AF_UNIX socket
    // We start creating the address:
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    
    // Assigns a local socket address "address" to a socket identified by descriptor 
    // "socket" that has no local socket address assigned.
    if ((bind(sfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) == -1)
    {
        // Printing the error message received:
        // printf("bind failed %d '%s'\n", stderr, strerror(stderr));
        fprintf(stderr, "Socket binding failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded...\n");
    }
    

    // Prepare to accept requests on socket sfd
    // MAX(=5) connection requests will be queued before further requests are refused
    if (listen(sfd, MAX) == -1)
    {
        fprintf(stderr, "Listening has failed...\n");
        exit(0);
    }
    else
    {
        printf("Server is listening...\n");
    }

    len = sizeof(cli);
    // Accept a connection. The connection is returned on a new socket, 'cfd';
    // The listenning socket ('sfd') remains open and can be used to accept further connections
    cfd = accept(sfd, (struct sockaddr *) &cli, (socklen_t *) &len);
    if (cfd == -1)
    {
        fprintf(stderr, "Server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("Server accepts the client...\n");
    }
    
    // Call chat function
    chat_func_server(cfd);

    if (close(cfd) == -1)
    {
        fprintf(stderr, "Failed to close the socket...\n");
        exit(0);
    }
    else
    {
        printf("Socket closed");
    }
    
}