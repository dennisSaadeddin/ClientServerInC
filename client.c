#include "us_xfr.h"

void chat_func_client(int sfd)
{
    char buff[BUFF_SIZE];
    int ret;

    for (;;)
    {
        printf("Enter your hessage: ");

        ret = 0;
        // Copy message in the buffer...
        while ((buff[ret++] = getchar()) != '\n')
        {
            continue;
        }
        // ... and send that buffer to server
        write(sfd, buff, sizeof(buff));

        ret = read(sfd, buff, BUFF_SIZE);
        buff[ret] = 0;
        printf("Message from server: %s", buff);

        if (strncmp(buff, "exit", 4) == 0)
        {
            write(sfd, buff, sizeof(buff));
            printf("Client exits...\n");
            break;
        }
    }
    
}

int main(int argc, char *argv[])
{
    // sfd = socket file descriptor / cfd = connection file descriptor
    struct sockaddr_in clientaddr;
    int sfd;

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

    // Construct server address and make the connetion
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(PORT);

    if(connect(sfd, (struct sockaddr *) &clientaddr, sizeof(struct sockaddr_in)) == -1)
    {
        fprintf(stderr, "Could not connect to the server...\n");
        exit(0);
    }
    else
    {
        printf("Connected to the server...\n");
    }
    
    // Call chat function
    chat_func_client(sfd);

    exit(EXIT_SUCCESS); // closes our socket; server sees EOF
}