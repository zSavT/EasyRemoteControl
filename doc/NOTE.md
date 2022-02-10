# NOTE

## Structure

You can start both the server and the client in the following ways.

-  Starting the program normally will start with the basic IP address and port (__Default IP__: _127.0.0.1_; __Default Port__: _27015_).
- Start the program from command line by passing as IP address and port parameters.
- Start the program from the command line passing only the IP address, in this case the port will be the default one.

It is possible to change the IP and the default port in the file "_client_server_structure.h_".

## Client

Once the client is started and connected to the server correctly, we can choose from a list of commands already preset (by selecting the number corresponding to the command), we can start this command in the Server.
We can eventually pass the entire command string to the client that will try to send it to the server and have it run. To stop communication, just enter the character '_=_'.

## Server

Once started, the Server will listen to a connection. Once the connection is started correctly, the server will be waiting for a command to be executed, requested by the client. Once the client is disconnected, the server will be continuously waiting.
