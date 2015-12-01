//
// Created by Denis Le Borgne on 19/11/2015.
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Buffer.hpp"

/*
** Constructor/Destructor
*/
Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

/*
** Copy constructor and assign operator
*/
Buffer::Buffer(Buffer const& other) : _data(other._data)
{
}

Buffer& Buffer::operator=(Buffer const& other)
{
    if (this != &other)
        _data = other._data;
    return *this;
}

/*
** Overloaded operators
*/
uint8_t&            Buffer::operator[](size_t index)
{
    if (index >= _data.size())
        throw std::out_of_range("attempt to reach index " +
                                std::to_string(index) + ", buffer size is " +
                                std::to_string(_data.size()));
    return _data[index];
}

/*
** Public member functions
*/
void                Buffer::consume(size_t size)
{
    if (size > _data.size())
    {
        _data.erase(_data.begin(), _data.end());
        return;
    }
    _data.erase(_data.begin(), _data.begin() + size);
}

bool                Buffer::empty() const
{
    return (_data.empty());
}

uint8_t const*      Buffer::data() const
{
    return (_data.data());
}

size_t              Buffer::size() const
{
    return (_data.size());
}

void                Buffer::clear()
{
    _data.clear();
}

std::string         Buffer::toString() const
{
    std::ostringstream ss;

    ss << "Buffer {"
    << "\n\t Data" << this->data();
    ss << "\n}" << std::endl;

    return ss.str();
}

/*
** Template specializations
*/
template <>
void                Buffer::append(std::string const& data)
{
    _data.insert(_data.end(), data.begin(), data.end());
}

template <>
void                Buffer::append(Buffer const& data)
{
    _data.insert(_data.end(), data._data.begin(), data._data.end());
}

template <>
void                Buffer::setData(std::string const& data)
{
    _data.erase(_data.begin(), _data.end());
    _data.assign(data.begin(), data.end());
}
