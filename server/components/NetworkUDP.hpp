#ifndef NETWORKUDP_HPP_
# define NETWORKUDP_HPP_

# include <string>
# include <queue>
# include <functional>
# include <mutex>
# include "IBehaviour.hpp"
# include "ComponentMask.hpp"
# include "InGameEvent.hpp"
# include "Buffer.hpp"

namespace RType
{
    namespace Component
    {
        class NetworkUDP : public ECS::IBehaviour
        {
        public:
            typedef std::priority_queue<InGameEvent, std::vector<InGameEvent>,
                                        std::greater<InGameEvent> > EventQueue;

        public:
            NetworkUDP(std::string const& ipAddr = "0");
            virtual ~NetworkUDP();

        public:
            NetworkUDP(NetworkUDP const& other);
            NetworkUDP&                 operator=(NetworkUDP const& other);

        public:
            InGameEvent                 popEvent();
            bool                        isEvent() const;
            bool                        isToSend() const;
            Buffer                      popToSend();
            void                        send(Buffer const& buffer);
            void                        pushReceived(Buffer const& buffer);
            std::string const&          getIpAddr() const;

        public:
            virtual void                update(double lastElapsed);
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask mask;

        protected:
            std::string     _ip;
            Buffer          _toSend;
            Buffer          _received;
            EventQueue      _events;
            std::mutex      _mutex;
        };
    }
}

#endif /* !NETWORKUDP_HPP_ */
