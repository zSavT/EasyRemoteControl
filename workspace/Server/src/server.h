/*
 * server.h
 *
 *  Created on: 26 nov 2021
 *      Author: zSavT
 */

#ifndef SERVER_H_
#define SERVER_H_

// Personal libraries
#include "client_server_structure.h"

// Constants
#define QLEN 5 // size of request queue

// Declarations of functions
AppErrorCode socketCreation(int argc, char *argv[], int *sock_out);
void acceptConnection(int my_socket);

/*Check if the program has been started as an administrator */
BOOL IsElevated( ) {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken ) {
        CloseHandle( hToken );
    }
    return fRet;
}

/* Socket creation */
AppErrorCode socketCreation(int argc, char *argv[], int *sock_out) {
	// Socket creation
	*sock_out = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*sock_out < 0) {
		errorHandler("Socket creation failed.\n");
		return SOCKET_CREATION_FAILURE;
	}

	// Construction of the server address:
	struct sockaddr_in sad;

	// Address assignment to the socket
	if (constructionServerAddress(argc, argv, &sad) != APP_SUCCESS) {
		closesocket(*sock_out);
		return INVALID_PORT;
	}

	if (bind(*sock_out, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		errorHandler("Error with bind().\n");
		closesocket(*sock_out);
		return SOCKET_BIND_FAILURE;
	}

	// Socket setting for listening
	if (listen(*sock_out, QLEN) < 0) {
		errorHandler("Listen() failed.\n");
		closesocket(*sock_out);
		return SOCKET_LISTEN_FAILURE;
	}
	return APP_SUCCESS;
}

/* Interaction with the client */
void acceptConnection(int my_socket) {

	// Acceptance of new connection
	struct sockaddr_in cad; // Structure for the client address
	int client_socket; // Socket descriptor for the client
	int client_len; // Size of the client address
	printf("Waiting for a client to connect...\n");
	client_len = sizeof(cad); // Set the size of the client address
	bool check = false;
	if ((client_socket = accept(my_socket, (struct sockaddr*) &cad, &client_len))
			< 0) {
		errorHandler("Acceptance of connection failed.\n"); // Do not close an invalid socket
	} else {
		printf("\nConnection established with %s:%d\n\n",
				inet_ntoa(cad.sin_addr), cad.sin_port); //clientSocket is connected to a client
	}
	while (check == false) {
		// Sending successful message to the client
		message m;
		initializeMessage(&m);
		if (recv(client_socket, (char*) &m, sizeof(message), 0) >= 0) {
			if (m.operation == '=') {
				check = true;
				closesocket(client_socket);
			} else {
				switch (m.operation) {
				case '1':
					system("sfc /scannow");
					strcpy(m.result, "Command Done.");
					break;
				case '2':
					system("DISM.exe /Online /Cleanup-image /Restorehealth");
					strcpy(m.result, "Command Done.");
					break;
				case '3':
					system("shutdown.exe /s /t 30");
					strcpy(m.result, "Command Done.");
					break;
				case '4':
					system("shutdown.exe /r /t 30");
					strcpy(m.result, "Command Done.");
					break;
				case '5':
					system("rd %temp% /s /q && md %temp%");
					strcpy(m.result, "Command Done.");
					break;
				case '6':
					system(m.customMessage);
					strcpy(m.result, "Command Done.");
					break;
				}
				if (send(client_socket, (char*) &m, sizeof(message), 0) < 0) {
					errorHandler("Error of sending data.\n");
					check = true;
					closesocket(client_socket);
				}
			}
		} else {
			errorHandler("Error in receiving data.\n");
			check = true;
			closesocket(client_socket);
		}
	} // while end
} // main end

#endif /* SERVER_H_ */
