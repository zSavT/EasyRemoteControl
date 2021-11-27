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
int socketCreation(int my_socket);
void connectionToServer(int my_socket, struct sockaddr_in sad);
void operationChoice(int my_socket);
void flushKeyBoard();

/* Tokenization function */
void stripString(message *m) {
	char operator;
	short check = 0;
	while (check == 0) {
		scanf("%c", &operator);
		if (operator == '\n') {
			check = 0;
			errorHandler(
					"Operation not allowed. Enter the value again:\n");
		} else {
			if (operator != '=') {
				flushKeyBoard();
				if (operator != '1' && operator != '2' && operator != '3'
						&& operator != '4') {
					errorHandler(
							"\nError! Wrong operator. Enter the value again:\n");
					check = 0;
				} else {
					check = 1;
				}
			} else {
				check = 1;
			}
		}
		m->operation = operator;
	}
}

/* Socket creation */
int socketCreation(int my_socket) {
	my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (my_socket < 0) {
		errorHandler("Socket creation failed.\n");
		closeAndCleanSocket(&my_socket);
		return -1;
	}
	return my_socket;
}

/* Function for connecting to the socket */
void connectionToServer(int my_socket, struct sockaddr_in sad) {
	if (connect(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
		errorHandler("Failed to connect.\n");
		closeAndCleanSocket(&my_socket);
		exit(-1);
	}
}

/*   Choice of operation and insertion of values */
void operationChoice(int my_socket) {
	message m;
	initializeMessage(&m);
	printf("Connection established.\n\n\a");
	m.operation = '+';
	while (m.operation != '=') {
		printf("Choose  the operation to be performed:\n\t1: Windows Integrity Check\n\t2: Windows Image Integrity Check\n\t3: Shutdown Remote PC\n\t4: Restart Remote PC\n\t"
				"\"=\" to close.\n");
		stripString(&m);
		if (m.operation != '=') {
			printf(
					"\nYou have entered the following values:\n Operation = %c\n",
					m.operation);
			if (send(my_socket, (char*) &m, sizeof(message), 0) < 0) {
				errorHandler("Error of sending data.\n");
				closeAndCleanSocket(&my_socket);
				system("pause");
				exit(1);
			}
			if (recv(my_socket, (char*) &m, sizeof(message), 0) >= 0) {
				printf(" Result: %s\n\n", m.result);
			} else {
				errorHandler("Error in receiving data.\n");
				closeAndCleanSocket(&my_socket);
			}
		} else {
			if (send(my_socket, (char*) &m, sizeof(message), 0) < 0) {
				errorHandler("Error of sending data.\n");
				closeAndCleanSocket(&my_socket);
				system("pause");
				exit(1);
			}
			printf("\nClosing...");
		}
	}
}

/* Clean scanf buffer */
void flushKeyBoard() {
	while ((getchar()) != '\n');
}

#endif /* CLIENT_H_ */
