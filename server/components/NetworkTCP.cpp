#include <sstream>
#include <iostream>
#include "NetworkTCP.hpp"
#include "ComponentsMasks.hpp"
#include "SocketMonitor.hpp"
#include "Server.hpp"
#include "Buffer.hpp"
#include "IncompleteRequest.hpp"

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
            _socket(std::move(socket)), _toSend(), _received(),
            _repr(_socket->getAddr() + ":" + std::to_string(_socket->getPort()))
        {
        }

        NetworkTCP::~NetworkTCP()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        NetworkTCP::NetworkTCP(NetworkTCP const& other) :
            _toSend(other._toSend), _received(other._received),
            _requests(other._requests), _repr(other._repr)
        {
        }

        NetworkTCP&     NetworkTCP::operator=(NetworkTCP const& other)
        {
            if (this != &other)
            {
                _toSend = other._toSend;
                _received = other._received;
                _requests = other._requests;
                _repr = other._repr;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        void            NetworkTCP::update()
        {
            if (_socket == nullptr)
                return ;
            if (SocketMonitor::getInstance().isReadable(_socket.get()))
            {
                Buffer        tmp;

                _socket->receive(tmp, bufferSize);
                if (tmp.empty())
                    onClientDisconnection();
                _received.append(tmp);
            }
            if (!_toSend.empty())
            {
                _socket->send(_toSend);
                _toSend.clear();
            }
            buildRequests();
        }

        void            NetworkTCP::send(Buffer const& buffer)
        {
            _toSend.append(buffer);
        }

        bool            NetworkTCP::isConnected() const
        {
            return _socket != nullptr;
        }

        bool            NetworkTCP::isRequest() const
        {
            return !_requests.empty();
        }

        Request         NetworkTCP::popRequest()
        {
            Request     request = _requests.front();

            _requests.pop();
            return request;
        }

        void            NetworkTCP::setSocket(UniqueITcpSockPtr socket)
        {
            _socket = std::move(socket);
            _repr = _socket->getAddr() + ":" +
                    std::to_string(_socket->getPort());
        }

        std::string const&     NetworkTCP::repr() const
        {
            return _repr;
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

        void                NetworkTCP::clear()
        {
            _socket = nullptr;
        }

        std::string           NetworkTCP::toString() const
        {
            std::ostringstream  ss;

            ss << "Component::NetworkTCP {"
                << "\n\t_socket: "
                << (_socket == nullptr ? -1 : _socket->getSocket())
                << "\n\t_toSend: " << _toSend.toString()
                << "\n\t_received: " << _received.toString()
                << std::endl;
            return ss.str();
        }

        /*
        ** Protected member functions
        */
        void                    NetworkTCP::onClientDisconnection()
        {
            Server::display("Client disconnected (" + _socket->getAddr() + ":" +
                            std::to_string(_socket->getPort()) + ")");
            SocketMonitor::getInstance().deleteSocket(_socket.get());
            _socket = nullptr;
        }

        void                    NetworkTCP::buildRequests()
        {
            try {
                while (!_received.empty())
                {
                    Request     request =
                        Request(Request::PROTOCOL_LOBBY, _received);

                    _received.consume(request.size());
                    _requests.push(request);
                }
            } catch (Exception::IncompleteRequest const& /*e*/) {
            }
        }
    }
}
