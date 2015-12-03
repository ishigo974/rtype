#ifndef PROTOCOLUT_HPP_
# define PROTOCOLUT_HPP_

# include <string>
# include "ABaseUT.hpp"

namespace RType
{
    class ProtocolUT : public UnitTesting::ABaseUT
    {
    public:
        ProtocolUT();
        virtual ~ProtocolUT();

    private:
        ProtocolUT(ProtocolUT const& other) = delete;
        ProtocolUT&             operator=(ProtocolUT const& other) = delete;

    protected:
        static void             lobbyRequestParsingWithoutData();
        static void             lobbyRequestParsingWithData();

    public:
        virtual void            registerTests();
        virtual std::string     getName() const;
    };
}

#endif /* !PROTOCOLUT_HPP_ */
