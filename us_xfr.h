#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

typedef enum { FALSE, TRUE } Boolean;

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUFF_SIZE 80
#define MAX 5
#define PORT 8082

#endif