#include <string>
#include "NetworkUDP.hpp"
#include "ComponentsMasks.hpp"
#include "IncompleteRequest.hpp"
#include "NotImplemented.hpp"
#include "ComponentsMasks.hpp"

namespace RType
{
    namespace Component
    {
        /*
        ** Static variables
        */
        const ECS::ComponentMask    NetworkUDP::mask    = MASK_NETWORKUDP;

        /*
        ** Constructor/Destructor
        */
        NetworkUDP::NetworkUDP(std::string const& ipAddr) :
            _ip(ipAddr), _toSend(), _received()
        {
        }

        NetworkUDP::~NetworkUDP()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        NetworkUDP::NetworkUDP(NetworkUDP const& other) :
            _ip(other._ip), _toSend(other._toSend),
            _received(other._received), _events(other._events)
        {
        }

        NetworkUDP&         NetworkUDP::operator=(NetworkUDP const& other)
        {
            if (this != &other)
            {
                _ip = other._ip;
                _toSend = other._toSend;
                _received = other._received;
                _events = other._events;
            }
            return *this;
        }

        /*
        ** Public member functions
        */
        InGameEvent         NetworkUDP::popEvent()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            InGameEvent                 event(_events.top());

            _events.pop();
            return event;
        }

        bool                NetworkUDP::isEvent() const
        {
            return !_events.empty();
        }

        void                NetworkUDP::update()
        {
            std::lock_guard<std::mutex> lock(_mutex);

            try {
                while (!_received.empty())
                {
                    InGameEvent     event(_received);

                    _received.consume(event.toBuffer().size());
                    _events.push(event);
                }
            } catch (Exception::IncompleteRequest const& e) {
                std::cout << "incomplete: " << e.what() << std::endl;
            } catch (Exception::NotImplemented const& e) {
                std::cout << "notimplem: " << e.what() << std::endl;
                _received.clear();
                throw ;
            }
        }

        void                NetworkUDP::send(Buffer const& buffer)
        {
            _toSend.append(buffer);
        }

        void                NetworkUDP::pushReceived(Buffer const& buffer)
        {
            std::lock_guard<std::mutex> lock(_mutex);

            _received.append(buffer);
        }

        bool                NetworkUDP::isToSend() const
        {
            return !_toSend.empty();
        }

        Buffer              NetworkUDP::popToSend()
        {
            Buffer          b = _toSend;

            _toSend.clear();
            return b;
        }

        std::string const&  NetworkUDP::getIpAddr() const
        {
            return _ip;
        }

        std::string         NetworkUDP::getName() const
        {
            return "NetworkUDP";
        }

        ECS::ComponentMask  NetworkUDP::getMask() const
        {
            return MASK_NETWORKUDP;
        }

        ECS::IComponent*    NetworkUDP::clone() const
        {
            return new NetworkUDP(*this);
        }

        void                NetworkUDP::clear()
        {
            _ip.clear();
            _toSend.clear();
            _received.clear();
            while (!_events.empty())
                _events.pop();
        }

        std::string         NetworkUDP::toString() const
        {
            std::string     res;

            res += "NetworkUDP {";
            res += "\n\t_ip: " + _ip;
            res += "\n\ttoSend nb bytes: " + std::to_string(_toSend.size());
            res += "\n\treceived nb bytes: " + std::to_string(_received.size());
            res += "\n\tnb events: " + std::to_string(_events.size());
            res += "\n}\n";
            return res;
        }
    }
}
