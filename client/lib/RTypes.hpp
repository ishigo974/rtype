//
// Created by naliwe on 25/11/15.
//

#ifndef RTYPE_RTYPES_HPP
# define RTYPE_RTYPES_HPP

namespace RTypes
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    typedef unsigned __int8  my_uint8_t;
    typedef unsigned __int16 my_uint16_t;
    typedef unsigned __int32 my_uint32_t;

    typedef __int8  my_int8_t;
    typedef __int16 my_int16_t;
    typedef __int32 my_int32_t;
#else
    typedef uint8_t  my_uint8_t;
    typedef uint16_t my_uint16_t;
    typedef uint32_t my_uint32_t;

    typedef int8_t  my_int8_t;
    typedef int16_t my_int16_t;
    typedef int32_t my_int32_t;
#endif
}

#endif //RTYPE_RTYPES_HPP
