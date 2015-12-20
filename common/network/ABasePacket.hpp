#ifndef ABASEPACKET_HPP_
# define ABASEPACKET_HPP_

# include <string>
# include <unordered_map>
# include "IStringable.hpp"
# include "ValueError.hpp"
# include "Buffer.hpp"

namespace RType
{
    class ABasePacket : public IStringable
    {
    public:
        typedef std::unordered_map<std::string, Buffer> DataMap;
        typedef std::unordered_map<std::string, size_t> DataSizeMap;
        typedef std::vector<std::string>                DataArgs;

    public:
        ABasePacket(uint16_t code = 0);
        virtual ~ABasePacket();

    public:
        ABasePacket(ABasePacket const& other);
        ABasePacket& operator=(ABasePacket const& other);

    public:
        bool            operator==(ABasePacket const& other) const;

    public:
        template<typename Type>
        Type get(std::string const& key) const
        {
            DataMap::const_iterator it = _data.find(key);

            if (it == _data.end())
                throw Exception::ValueError("No such data: " + key);
            return it->second.get<Type>();
        }

        template<typename Type>
        void push(std::string const& key, Type const& data)
        {
            Buffer buffer;

            buffer.setData(data);
            _data.insert(std::make_pair(key, buffer));
        }

    public:
        virtual void   parse(Buffer const& raw) = 0;
        virtual Buffer toBuffer() const         = 0;

    public:
        void         setCode(uint16_t code);
        virtual void clear();

    public:
        uint16_t getCode() const;
        Buffer const& getRaw() const;
        virtual std::string toString() const;

    protected:
        uint16_t _code;
        DataMap  _data;
    };

    template<>
    std::string             ABasePacket::get(std::string const& key) const;
}


#endif /* !ABASEPACKET_HPP_ */
