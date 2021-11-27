# EasyRemoteControl
My simple program for remote PC control to start very simple tasks.<br>

We can switch from command line to program startup IP address and port (both client and server side).<br>

With this program we can choose a series of commands to be executed by the Server. Eventually passing also an entire string containing the command to be executed (To evaluate this option).

## Documentation

You can see documentation right [here!](https://github.com/zSavT/EasyRemoteControl/blob/main/doc/NOTE.md)

## Directory

`
\---EasyRemoteControl-main
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
`

<p>
The code will always be in english.
