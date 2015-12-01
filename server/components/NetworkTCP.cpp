#include <sstream>
#include "NetworkTCP.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const size_t      NetworkTCP::bufferSize    = 20;

        /*
        ** Constructor/Destructor
        */
        NetworkTCP::NetworkTCP() :
        _socket(nullptr), _toSend(), _received()
        {
        }

        NetworkTCP::NetworkTCP(UniqueITcpSockPtr socket) :
        _socket(std::move(socket)), _toSend(), _received()
        {
        }

        NetworkTCP::~NetworkTCP()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        NetworkTCP::NetworkTCP(NetworkTCP const& other) :
        _toSend(other._toSend), _received(other._received)
        {
        }

        NetworkTCP&     NetworkTCP::operator=(NetworkTCP const& other)
        {
            if (this != &other)
            {
                _toSend = other._toSend;
                _received = other._received;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void            NetworkTCP::update()
        {
            Buffer        tmp;

            while (_socket->receive(tmp, bufferSize) > 0)
                _received.append(tmp);
            _socket->send(_toSend);
            _toSend.clear();
        }

        void            NetworkTCP::pushData(Buffer const& buffer)
        {
            _toSend.append(buffer);
        }

        Buffer          NetworkTCP::popData()
        {
            Buffer      res = _received;

            _received.clear();
            return res;
        }

        void            NetworkTCP::setSocket(UniqueITcpSockPtr socket)
        {
            _socket = std::move(socket);
        }

        std::string     NetworkTCP::getName() const
        {
            return "NetworkTCP";
        }

        ECS::ComponentMask   NetworkTCP::getMask() const
        {
            return MASK_NETWORKTCP;
        }

        ECS::IComponent*     NetworkTCP::clone() const
        {
            return new NetworkTCP(*this);
        }

        void            NetworkTCP::clear()
        {
            _socket = nullptr;
        }

        std::string           NetworkTCP::toString() const
        {
            std::ostringstream  ss;

            ss << "Component::NetworkTCP {"
            << "\n\t_socket: " << _socket->getSocket()
            << "\n\t_toSend: " << _toSend.toString()
            << "\n\t_received: " << _received.toString()
            << std::endl;
            return ss.str();
        }
    }
}
