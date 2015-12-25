//
// Created by Denis Le Borgne on 14/12/2015.
//

#ifndef RTYPE_SERVER_NETTYPES_HPP
# define RTYPE_SERVER_NETTYPES_HPP

# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif

# include <WinSock2.h>
# include <WS2tcpip.h>
# include <Windows.h>

# pragma comment(lib,"ws2_32")

typedef SOCKET rSocket;

#endif //RTYPE_SERVER_NETTYPES_HPP
