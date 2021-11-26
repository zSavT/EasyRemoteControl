/*
 ============================================================================
 Name        : Client.c
 Author      : Francesco Saverio Cassano
 Version     : 0.1
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
      return 0;
    }
  #endif

  // Socket creation
  int my_socket = 0;
  my_socket = socketCreation(my_socket);
  if (my_socket < 0) {
    errorHandler("Socket creation failed.\n");
    closeAndCleanSocket(&my_socket);
    return -1;
  }

  // Construction of the server andress
  struct sockaddr_in sad = constructionServerAddress(argc, argv);

  // Connection of the server
  connectionToServer(my_socket, sad);
  operationChoice(my_socket);

  closeAndCleanSocket(&my_socket);

  printf("\n");
  system("pause");
  return 0;

} // main end
