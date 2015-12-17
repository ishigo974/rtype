#include "ABasePacket.hpp"

namespace RType
{
    /*
    ** Constructors/Destructor
    */
    ABasePacket::ABasePacket(uint16_t code) : _code(code)
    {
    }

    ABasePacket::~ABasePacket()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    ABasePacket::ABasePacket(ABasePacket const& other) :
        _code(other._code), _data(other._data)
    {
    }

    ABasePacket&    ABasePacket::operator=(ABasePacket const& other)
    {
        if (this != &other)
        {
            _code = other._code;
            _data = other._data;
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    void            ABasePacket::setCode(uint16_t code)
    {
        _code = code;
    }

    void            ABasePacket::clear()
    {
        _code = 0;
        _data.clear();
    }

    uint16_t        ABasePacket::getCode() const
    {
        return _code;
    }

    std::string     ABasePacket::toString() const
    {
        std::string res("ABasePacket {");

        res += "\n\t_code " + std::to_string(_code);
        res += "\n\tnb data " + std::to_string(_data.size());
        return res;
    }

    template <>
    std::string         ABasePacket::get(std::string const& key) const
    {
        DataMap::const_iterator it = _data.find(key);

        if (it == _data.end())
            throw std::runtime_error("no such data: " + key); // TODO
        return it->second.getString();
    }
}
