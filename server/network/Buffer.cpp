//
// Created by Denis Le Borgne on 19/11/2015.
//

#include <iostream>
#include <sstream>
#include "Buffer.hpp"

Buffer::Buffer()
{ }

Buffer::~Buffer()
{ }

Buffer::Buffer(Buffer const& other) : _data(other._data)
{
}

Buffer& Buffer::operator=(Buffer const& other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}

void Buffer::consume(size_t size)
{
    if (size > _data.size())
    {
        _data.erase(_data.begin(), _data.end());
        return;
    }
    _data.erase(_data.begin(), _data.begin() + size);
}

bool Buffer::empty() const
{
    return (_data.empty());
}

template <>
void Buffer::append(std::string const& data)
{
    _data.insert(_data.end(), data.begin(), data.end());
}

template <>
void Buffer::append(Buffer const& data)
{
    _data.insert(_data.end(), data._data.begin(), data._data.end());
}


void Buffer::append(char const *data, size_t size)
{
    std::string tmp(data, size);

    if (_data.empty())
        setData(data, size);
    else
        _data.insert(_data.end(), tmp.begin(), tmp.end());
}

void Buffer::setData(char const *data, size_t size)
{
    std::string tmp(data, size);

    _data.assign(tmp.begin(), tmp.end());
}

uint8_t const *Buffer::data() const
{
    return (_data.data());
}

std::string const *Buffer::data()
{
    return (new std::string(_data.begin(), _data.end()));
}

size_t Buffer::size() const
{
    return (_data.size());
}

void    Buffer::clear()
{
    _data.clear();
}

std::string Buffer::toString() const
{
    std::ostringstream ss;

    ss << "Buffer {"
    << "\n\t Data" << this->data();
    ss << "\n}" << std::endl;

    return ss.str();
}
