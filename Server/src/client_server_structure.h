/*
 * client_server_structure.h
 *
 *  Created on: 26 nov 2021
 *      Author: verio
 */

#ifndef CLIENT_SERVER_STRUCTURE_H_
#define CLIENT_SERVER_STRUCTURE_H_


// Libraries for Windows/Unix
#if defined WIN32
	#include <winsock.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#define closesocket close
#endif

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define BUFFERSIZE 512 //maximum buffer size
#define IP "127.0.0.1" //IP address
#define PROTOPORT 27015 //default port number

typedef struct {
	char operation;
	char result[BUFFERSIZE];
}message;

// Declarations of functions
void clearwinsock();
void errorHandler(char *errorMessage);
void setAndressPort(struct sockaddr_in *sad, int port, char *ip);
struct sockaddr_in constructionServerAddress(int argc, char  *argv[]);
void closeAndCleanSocket(int *my_socket);
int checkCharacter(char *character);
void initializeMessage(message *m);
void initializeSockaddr_in(struct sockaddr_in *sad);

/* WinSock data cleanup */
void clearWinsock() {
#if defined WIN32
	WSACleanup();
#endif
}

/* Error message */
void errorHandler(char *errorMessage) {
	printf("%s\n", errorMessage);
}

/*  Closing and cleaning of socket data */
void closeAndCleanSocket(int *my_socket) {
	closesocket(*(my_socket));
	clearWinsock();
}

/* Check if each character in the string is a number */
int checkCharacter(char *character) {
	int i = 0;
	int check = 0;
	do {
		if (isdigit(character[i]) == 0) {
			check = 1;
		}
		i++;
	} while (character[i] != '\0');

	return check; 	//0 = corrected value - 1 otherwise
}

/* Server address building */
struct sockaddr_in constructionServerAddress(int argc, char *argv[]) {
	struct sockaddr_in sad;
	initializeSockaddr_in(&sad);
	sad.sin_family = AF_INET;
	if (argc <= 1) {
		setAndressPort(&sad, PROTOPORT, IP);
	} else if (argc == 3) {
		if (checkCharacter(argv[2]) == 0) {
			if (atoi(argv[2]) >= 0 && atoi(argv[2]) <= 65535) {
				setAndressPort(&sad, atoi(argv[2]), argv[1]);
			} else {
				errorHandler("Bad port.\n");
			}
		} else {
			errorHandler("Illegal port value.\n");
		}
	} else if (argc == 2) {
		setAndressPort(&sad, PROTOPORT, argv[1]);
	}
	return sad;
}

/* Initialize message in memory */
void initializeMessage(message *m) {
	memset(&m, 0, sizeof(message));
}

/* Initialize sockaddr_in in memory */
void initializeSockaddr_in(struct sockaddr_in *sad) {
	memset(&sad, 0, sizeof(sad));
}

/* Address setting */
void setAndressPort(struct sockaddr_in *sad, int port, char *ip) {
	sad->sin_addr.s_addr = inet_addr(ip);
	sad->sin_port = htons(port);
}

#endif /* CLIENT_SERVER_STRUCTURE_H_ */
