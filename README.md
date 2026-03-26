# EasyRemoteControl
EasyRemoteControl is a lightweight tool designed for basic remote PC management and task execution.

Educational Purpose Only: This repository was created solely for learning and educational purposes. It is not intended for use in production environments.

## Features
​Configurable Connection: Easily specify the IP address and port for both the client and server directly via command-line arguments at startup.
​Remote Task Execution: Choose from a predefined series of commands to be executed on the server side.
​Flexible Commands (Experimental): Support for passing full command strings for remote execution (currently under evaluation).

## ​How it Works
​The program establishes a connection between a client and a server. Once connected, the client can trigger specific operations on the host machine, making it a simple way to automate or manage basic tasks remotely.

## Documentation

You can see documentation right [here!](https://github.com/zSavT/EasyRemoteControl/blob/main/doc/NOTE.md)

## Directory

```
\---EasyRemoteControl-main<br>
    |   .gitignore
    |   LICENSE
    |   README.md
    |   
    +---doc
    |       NOTE.md
    |       
    \---workspace
        +---Client
        |   |   .gitignore
        |   |   .project
        |   |   
        |   \---src
        |           Client.c
        |           client.h
        |           client_server_structure.h
        |           
        \---Server
            |   .gitignore
            |   .project
            |   
            \---src
                    client_server_structure.h
                    Server.c
                    server.h
```

<p>
The code will always be in english.
