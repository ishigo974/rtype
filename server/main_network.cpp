#include <string>
#include <iostream>
#include "Buffer.hpp"

/*
 * TODO Patch Select
 */

union lol
{
    int  a;
    char b[4];
};

int main()
{
    Buffer toto;

//    toto.append(" TAMERE", 7);
    toto.setData<uint32_t>(4042);
//    toto.append(" TONPERE", 9);
    std::cout << toto.get<uint32_t>() << std::endl;
}
