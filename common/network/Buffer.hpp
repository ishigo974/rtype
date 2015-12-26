//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_BUFFER_HPP
# define RTYPE_BUFFER_HPP

# include <vector>
# include <string>
# include <cstring>
// # include <stdint.h>
#include <iostream>

class Buffer
{
public:
    Buffer();
    ~Buffer();

public:
    Buffer(Buffer const& buffer);
    Buffer&     operator=(Buffer const& buffer);

public:
    uint8_t&    operator[](size_t index);
    bool        operator==(Buffer const& other) const;

public:
    virtual std::string toString() const;

public:
    void          consume(size_t size);
    bool          empty() const;
    uint8_t       *data();
    uint8_t const *data() const;
    size_t        size() const;
    void          clear();
    std::string   getString(size_t len = 0, size_t offset = 0) const;

    template<typename T>
    T get(size_t offset = 0) const
    {
        T      ret  = 0;
        size_t size = sizeof(T);

        std::memcpy(&ret, _data.data() + offset, size);
        return ret;
    }

    template<typename T>
    void append(T const *data, size_t size)
    {
        for (unsigned int i = 0; i < size; ++i)
            append(data[i]);
    }

    template<typename T>
    void append(T const& data)
    {
        size_t  size = _data.size();

        _data.resize(size + sizeof(data), 0);
        std::memcpy(_data.data() + size, &data, sizeof(T));
    }

    template<typename T>
    void setData(T const& data)
    {
        _data.clear();
        append(data);
    }

    template<typename T>
    void setData(T const *data, size_t size)
    {
        _data.clear();
        append(data, size);
    }

private:
    std::vector<uint8_t> _data;
};

template<>
void Buffer::append(Buffer const& data);

template<>
void Buffer::append(std::string const& data);

template<>
void Buffer::setData(Buffer const& data);

template<>
void Buffer::setData(std::string const& data);

#endif //RTYPE_BUFFER_HPP
