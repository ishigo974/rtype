//
// Created by Denis Le Borgne on 26/11/2015.
//

#ifndef RTYPE_NETTYPES_HPP
#define RTYPE_NETTYPES_HPP

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) \
    && !defined(__CYGWIN__)
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

typedef SOCKET rSocket;
# else
typedef int rSocket;
# endif

#endif //RTYPE_NETTYPES_HPP
