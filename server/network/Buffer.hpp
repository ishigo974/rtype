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
    virtual std::string toString() const;

public:
    void append(char const *data, size_t size);
    void setData(char const *data, size_t size);

    template<typename T>
    void append(T const& data)
    {
        uint8_t tmp;
        int     i = sizeof(data);

        while (i > 0)
        {
            tmp = data >> (8 * i);
            _data.push_back(tmp);
            --i;
        }
    }

    void append(std::string const& data)
    {
        _data.insert(_data.end(), data.begin(), data.end());
    }

    void setData(std::string const& data)
    {
        _data.erase(_data.begin(), _data.end());
        _data.assign(data.begin(), data.end());
    }

    template<typename T>
    void setData(T const& data)
    {
        uint8_t tmp;
        int     i = sizeof(data);

        _data.erase(_data.begin(), _data.end());
        while (i > 0)
        {
            tmp = data >> (8 * i);
            _data.push_back(tmp);
            --i;
        }
    }

    void              consume(size_t size);
    bool              empty() const;
    uint8_t const     *data() const;
    std::string const *data();
    size_t            size() const;
    void              clear();

private:
    std::vector<uint8_t> _data;
};

#endif //RTYPE_BUFFER_HPP
