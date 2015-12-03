//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_BUFFER_HPP
# define RTYPE_BUFFER_HPP

# include <vector>
# include <string>
# include "IStringable.hpp"

class Buffer : public IStringable
{
public:
    Buffer();
    ~Buffer();

public:
    Buffer(Buffer const& buffer);
    Buffer& operator=(Buffer const& buffer);

public:
    uint8_t& operator[](size_t index);

public:
    virtual std::string toString() const;

public:
    void          consume(size_t size);
    bool          empty() const;
    uint8_t       *data();
    uint8_t const *data() const;
    size_t        size() const;
    void          clear();

    template<typename T>
    T get(unsigned int offset = 0) const
    {
        T      ret  = 0;
        size_t size = sizeof(T);

        while (size > 0)
        {
            ret = ret << 8;
            ret = ret | _data[offset];
            ++offset;
            --size;
        }
        return ret;
    }

    template<typename T>
    void append(T const *data, size_t size)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            append(data[i]);
        }
    }

    template<typename T>
    void append(T const& data)
    {
        uint8_t tmp;
        size_t  i = sizeof(T); //TODO change endianess

        while (i > 0)
        {
            tmp = (data >> (8 * (i - 1)));
            _data.push_back(tmp);
            --i;
        }
    }

    template<typename T>
    void    setData(T const& data)
    {
        uint8_t tmp;
        size_t  i = sizeof(T); //TODO change endianess

        _data.erase(_data.begin(), _data.end());
        while (i > 0)
        {
            tmp = data >> (8 * (i - 1));
            _data.push_back(tmp);
            --i;
        }
    }

    template<typename T>
    void    setData(T const *data, size_t size)
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
void Buffer::setData(Buffer const& data);

template<>
void Buffer::setData(std::string const& data);

#endif //RTYPE_BUFFER_HPP
