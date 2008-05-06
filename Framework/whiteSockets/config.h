#include <iostream>

#ifdef WIN32
#include <winsock2.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#define SOCKET int
#define SOCKADDR sockaddr
#define closesocket close

#define INVALID_SOCKET 0
#define SOCKET_ERROR  -1

#endif

#define WHNET_VERSION 0.0.1

