//
// Created by Denis Le Borgne on 19/11/2015.
//

#ifndef RTYPE_BUFFER_HPP
# define RTYPE_BUFFER_HPP

# include <vector>
# include <string>

class Buffer
{
public :
    Buffer();

    ~Buffer()
    { }

public:

    void append(char const *data, uint32_t size);
    void setData(char const *data, uint32_t size);

    template<typename T>
    void append(T const& data)
    {
        _data.insert(_data.end(), data.begin(), data.end());
    }

    template<typename T>
    void setData(T const& data)
    {
        _data.assign(data.begin(), data.end());
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
