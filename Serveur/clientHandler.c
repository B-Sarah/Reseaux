#include "clientHandler.h"


void startHandlingClient(Client* client){
	int pthread_return;
	pthread_t thread;

	//creation de thread d'acceptation de clients
	pthread_return = pthread_create(&thread, NULL, handleClient, (void*)client);

	if(pthread_return){
		printf("ERROR; return code from pthread_create() is %d\n", pthread_return);
		return;
	}
}

void* handleClient(void* client_){
	XDR xdr_encode, xdr_decode;
	char sent[MAX_MSG_SIZE];
	char received[MAX_MSG_SIZE];
	Player player;

	/*creation des flots */
	xdrmem_create(&xdr_encode,sent, MAX_MSG_SIZE, XDR_ENCODE);
	xdrmem_create(&xdr_decode,received, MAX_MSG_SIZE, XDR_DECODE);

	Client* client = (Client*)client_;
	//Un client est la !!
	printf("Un client vient de se connecter a la socket %d\n", client->socket);
	fflush(stdout);

	//sleep(5);
	/*reception d'un message contenant un player encode*/

	/*FILE* sockStream = fdopen(client->socket, "w+");
	if(sockStream == NULL){
		printf("fail to open socket stream\n");
		fflush(stdout);
	}*/


	if(read(client->socket, received, MAX_MSG_SIZE) < 0){
		perror("read");
	}

	/*if(xdr_player(&xdr_decode, &player) == FALSE){
		printf("fail to decode \n");
		fflush(stdout);		
	}*/

	char machaine[80];
	char* pt = machaine;

	if(xdr_string(&xdr_decode, &pt, 80) == FALSE){
		printf("fail to decode \n");
		fflush(stdout);
	}

	printf("Msg received : %s\n", pt);
	fflush(stdout);
				
	/*printf("Msg received :\nname : %s\npassword : %s\n", player.name, player.password);
	fflush(stdout);*/
	
	
	printf("Un client vient de se deconnecter de la socket %d\n", client->socket);
	fflush(stdout);
	
	close(client->socket);
	free(client);
	client = NULL;
	pthread_exit(NULL);
}


bool_t xdr_player(XDR* pt_xdr, Player* player){
	char* pName = player->name;
	char* pPwd = player->password;
	char** ppName = &pName;
	char** ppPwd = &pPwd;
	return(xdr_string(pt_xdr, ppName, 30));

}


