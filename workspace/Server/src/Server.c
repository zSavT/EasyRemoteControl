/*
 ============================================================================
 Name        : Server.c
 Author      : zSavT
 Version     : 0.2
 Copyright   : Free to use, just notice me.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "server.h"

/* Program execution */
int main(int argc, char *argv[]) {

	if (IsElevated() == FALSE) {
		printf(
				"Please start the program as an administrator to unlock all its features.\n");
		system("pause");
		return NOT_ELEVATED;
	} else {

#if defined WIN32
		// Initialize Winsock for Windows
		WSADATA wsa_data;
		int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
		if (result != NO_ERROR) {
			errorHandler("Error at WSAStartup().\n");
			return WSA_STARTUP_FAILURE;
		}
#endif

		int my_socket = 0;
		AppErrorCode err = socketCreation(argc, argv, &my_socket);
		if (err != APP_SUCCESS) {
			clearWinsock();
			return err;
		}
		while (true) {
			acceptConnection(my_socket);
		}
		system("pause");
		return APP_SUCCESS;

	}

} // main end
