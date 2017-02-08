#ifndef CLIENTHANDLER_H 
#define CLIENTHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <ctype.h>
#include <rpc/xdr.h>

#define MAX_MSG_SIZE 1024

typedef struct{
	int socket;
	struct sockaddr_in address;
	int addressLength;
}Client;

typedef struct{
	char name[30];
	char password[20];
}Player;

void startHandlingClient(Client* client);
void* handleClient(void* client_);
bool_t xdr_player(XDR* pt_xdr, Player* player);


#endif 
