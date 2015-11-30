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
public :
    Buffer();

    ~Buffer()
    { }

public:
    virtual std::string toString() const;

public:

    void append(char const *data, uint32_t size);
    void setData(char const *data, uint32_t size);

    template<typename T>
    void append(T const& data)
    {
        _data.insert(_data.end(), sizeof(data), data);
    }

    template<typename T>
    void setData(T const& data)
    {
        _data.erase(_data.begin(), _data.end());
        _data.insert(data.end(), sizeof(data), data);
    }

    void              consume(uint32_t size);
    bool              empty() const;
    uint8_t const     *data() const;
    std::string const *data();
    size_t            size() const;

private:
    Buffer(Buffer const& buffer) = delete;
    Buffer& operator=(Buffer const& buffer) = delete;

private:
    std::vector<uint8_t> _data;
};

#endif //RTYPE_BUFFER_HPP
