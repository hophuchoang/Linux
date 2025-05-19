# Project Name

Application sending messages using tcp sockets

---

## Features

- Using Command Line Interface - CLI
- Display application Ip and Port information
- TCP connections between peers
- Manage connection list
- Manage up to 10 connections
- Exchange messages

---

## Requirements

- GCC
- Make
- Linux or Unix-like environment

---

## Build Instructions

```bash
make all # for build
make clean # for clean
```

## Run

```bash
./bin/chat_application [port]
```

## Help
Use the commands bellow:  
1. help                             : display user interface options  
2. myip                             : display IP address of this app  
3. myport                           : display listening port of this app  
4. connect <destination> <port no>  : connect to the app of another computer  
5. list                             : list all the connection of this app  
6. terminate <connection id>        : terminate a connection  
7. send <connection id> <message>   : send a message to a connection  
8. exit:                            : close all connection & terminate this app  


## Project Structure
Mini_project_Chat_Application/  
├── inc  
│   ├── app_define.h  
│   ├── app_func.h  
│   ├── sock_defs.h  
│   ├── socket.h  
│   └── ui_display.h  
├── Makefile  
├── README.md  
├── src  
│   ├── app_func.c  
│   ├── main.c  
│   ├── socket.c  
│   └── ui_display.c  
└── test  
    ├── test  
    └── test.c  



