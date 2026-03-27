/*
 * client.h
 *
 *  Created on: 26 nov 2021
 *      Author: verio
 */

#ifndef CLIENT_H_
#define CLIENT_H_

// Personal libraries
#include "client_server_structure.h"

// Declarations of functions
void stripString(message *m);
AppErrorCode socketCreation(int *sock_out);
AppErrorCode connectionToServer(int my_socket, struct sockaddr_in sad);
AppErrorCode operationChoice(int my_socket);
void flushKeyBoard();
void custumCommand(message *m);

/* Tokenization function */
void stripString(message *m) {
	char operator;
	bool check = false;
	while (check == false) {
		scanf("%c", &operator);
		if (operator == '\n') {
			check = false;
			errorHandler("Operation not allowed. Enter the value again:\n");
		} else {
			if (operator != '=') {
				flushKeyBoard();
				if (operator != '1' && operator != '2' && operator != '3'
				&& operator != '4' && operator != '5' && operator != '6') {
					errorHandler(
							"\nError! Wrong operator. Enter the value again:\n");
					check = false;
				} else {
					check = true;
					if (operator == '6') {
						custumCommand(m);
					}
				}
			} else {
				check = true;
			}
		}
	m->operation = operator;
}
}

/* Socket creation */
AppErrorCode socketCreation(int *sock_out) {
	*sock_out = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*sock_out < 0) {
		errorHandler("Socket creation failed.\n");
		return SOCKET_CREATION_FAILURE;
	}
	return APP_SUCCESS;
}

/* Function for connecting to the socket */
AppErrorCode connectionToServer(int my_socket, struct sockaddr_in sad) {
	if (connect(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		errorHandler("Failed to connect.\n");
		return SOCKET_CONNECT_FAILURE;
	}
	return APP_SUCCESS;
}

/*   Choice of operation and insertion of values */
AppErrorCode operationChoice(int my_socket) {
	message m;
	initializeMessage(&m);
	printf("Connection established.\n\n\a");
	m.operation = '+';
	while (m.operation != '=') {
		printf(
				"Choose the operation to be performed:\n\t1: Windows Integrity Check\n\t2: Windows Image Integrity Check\n\t3: Shutdown Remote PC\n\t4: Restart Remote PC\n\t5: Delete Temp Files\n\t6: Custum command\n\t" "\"=\" to close.\n");
		stripString(&m);
		if (m.operation != '=') {
			printf("\nYou have entered the following values:\n Operation = %c\n",
					m.operation);
			if (send(my_socket, (char*) &m, sizeof(message), 0) < 0) {
				errorHandler("Error of sending data.\n");
				return SEND_FAILURE;
			}
			if (recv(my_socket, (char*) &m, sizeof(message), 0) < 0) {
				errorHandler("Error in receiving data.\n");
				return RECV_FAILURE;
			}
			printf(" Result: %s\n\n", m.result);
		} else {
			if (send(my_socket, (char*) &m, sizeof(message), 0) < 0) {
				errorHandler("Error of sending data.\n");
				return SEND_FAILURE;
			}
			printf("\nClosing...");
		}
	}
}

/* Clean scanf buffer */
void flushKeyBoard() {
	while ((getchar()) != '\n');
}

void custumCommand(message *m) {
	char temp[BUFFERSIZE];
	memset(&temp, '\0', sizeof(temp));
	bool check = false;
	while (check == false) {
		printf("\nInsert your custom message. Max 510 characters\n --> ");
			scanf("%510s", temp);
			if ((int) strlen(temp) > 510) {
				printf("\nError, string too long.");
				memset(temp, '\0', sizeof(temp));
		} else {
			check = true;
		}
	}
	strcpy(m->customMessage, temp);
}

#endif /* CLIENT_H_ */
