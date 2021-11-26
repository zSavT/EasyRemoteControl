/*
 ============================================================================
 Name        : Server.c
 Author      : zSavT
 Version     : 0.1
 Copyright   : Free to use, just notice me.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "server.h"

/* Program execution */
int main(int argc, char *argv[]) {

#if defined WIN32
	// Initialize Winsock for Windows
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != NO_ERROR) {
		errorHandler("Error at WSAStartup().\n");
		return -1;
	}
#endif

	int my_socket = 0;
	my_socket = socketCreation(argc, argv);
	if (my_socket < 0) {
		errorHandler("Socket creation failed.\n");
		closeAndCleanSocket(&my_socket);
		return -1;
	}
	while (1) {
		acceptConnection(my_socket);
	}
	system("pause");
	return 0;

} // main end

