#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>

#include <arpa/inet.h>


#define BACKLOGS 5

void do_routing(char* method,char* path, int client_fd);
void free_everything(int *fd, int *client_fd);

#endif