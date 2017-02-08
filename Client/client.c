#include "client.h"


void connectToServer(Server* server,char* serverAddress){
	XDR xdr_encode, xdr_decode;
	char sent[MAX_MSG_SIZE] = {'\0'};
	char received[MAX_MSG_SIZE] = {'\0'};
	Player player;

	strcpy(player.name, "Dorwed");
	strcpy(player.password, "ifucanreadthis");
	
	/*creation des flots */
	xdrmem_create(&xdr_encode,sent, MAX_MSG_SIZE, XDR_ENCODE);
	xdrmem_create(&xdr_decode,received, MAX_MSG_SIZE, XDR_DECODE);

	memset(&server->address, '\0', sizeof(server->address));
	// creation de la socket locale
	if((server->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);	
	}	

	// recuperation de l'adresse ip du serveur
	if((server->host = gethostbyname(serverAddress)) == NULL){
		perror("gethostbyname");
		exit(2);
	}
	
	// preparation de l'adresse du serveur
	server->port = (unsigned short)PORT;

	server->address.sin_family = AF_INET;
	server->address.sin_port = htons(server->port);
	bcopy(server->host->h_addr, &(server->address).sin_addr, server->host->h_length);

	printf("Connexion en cours...\n");
	fflush(stdout);

	// demande de connexion au serveur
	if(connect(server->socket, (struct sockaddr*)(&(server->address)), sizeof(server->address)) == -1){
		perror("connect");
		exit(3);
	}

	printf("Connexion acceptee\n");
	fflush(stdout);

	/*encodage du player*/
	/*if(xdr_player(&xdr_encode, &player) == FALSE){
		printf("fail to encode \n");
		fflush(stdout);
	}*/

	char machaine[80];
	strcpy(machaine, "hello world");
	char* pt = machaine;
	if(xdr_string(&xdr_encode, &pt,80) == FALSE){
		printf("fail to encode \n");
		fflush(stdout);
	}

	printf("message to send \"%s\"\n", sent);
	fflush(stdout);

	/*envoi du message contenant le player encode*/
	if(write(server->socket, sent, strlen(sent)+1) != strlen(sent)+1){
		perror("write");
	}

	printf("message has been sent \"%s\"\n", sent);
	fflush(stdout);
}

bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;

	return(xdr_string(pt_xdr, ppName, 30) &&
			xdr_string(pt_xdr, ppPwd, 20));

}




int main(int argc, char** argv){
	Server server;

	connectToServer(&server, argv[1]);

	return 0;
}

