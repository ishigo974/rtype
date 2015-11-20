//
// Created by Denis Le Borgne on 19/11/2015.
//

#include "Buffer.hpp"

Buffer::Buffer()
{ }

void Buffer::consume(uint32_t size)
{
    if (size > _data.size())
    {
        _data.erase(_data.begin(), _data.end());
        return ;
    }
    _data.erase(_data.begin(), _data.begin() + size);
}

bool Buffer::empty() const
{
    return (_data.empty());
}

void Buffer::append(char const* data, uint32_t size)
{
    std::string tmp(data, size);

    _data.insert(_data.end(), tmp.begin(), tmp.end());
}

void Buffer::setData(char const *data, uint32_t size)
{
    std::string tmp(data, size);

    _data.assign(tmp.begin(), tmp.end());
}

uint8_t const* Buffer::data() const
{
    return (_data.data());
}

std::string const* Buffer::data()
{
    return (new std::string(_data.begin(), _data.end()));
}