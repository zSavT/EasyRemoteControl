/*
 ============================================================================
 Name        : Client.c
 Author      : Francesco Saverio Cassano
 Version     : 0.2
 Copyright   : Free to use, just notice me.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "client.h"

/* Program execution */
int main(int argc, char *argv[]) {

  #if defined WIN32
    // Initialize Winsock
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != NO_ERROR) {
      errorHandler("Error at WSAStartup()\n");
      return WSA_STARTUP_FAILURE;
    }
  #endif

  // Socket creation
  int my_socket = 0;
  if (socketCreation(&my_socket) != APP_SUCCESS) {
	clearWinsock();
    return SOCKET_CREATION_FAILURE;
  }

  // Construction of the server andress
  struct sockaddr_in sad;
  if(constructionServerAddress(argc, argv, &sad) != APP_SUCCESS) {
	  closeAndCleanSocket(&my_socket);
	  return INVALID_PORT;
  }

  // Connection of the server
  if(connectionToServer(my_socket, sad) != APP_SUCCESS) {
	  closeAndCleanSocket(&my_socket);
	  return SOCKET_CONNECT_FAILURE;
  }
  
  AppErrorCode op_result = operationChoice(my_socket);

  closeAndCleanSocket(&my_socket);

  printf("\n");
  system("pause");
  return op_result;

} // main end
