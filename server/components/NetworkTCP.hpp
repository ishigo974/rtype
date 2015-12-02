#ifndef NETWORKTCP_HPP_
# define NETWORKTCP_HPP_

# include <memory>
# include <string>
# include "IComponent.hpp"
# include "IBehaviour.hpp"
# include "ComponentMask.hpp"
# include "ITcpSocket.hpp"

namespace RType
{
    namespace Component
    {
        class NetworkTCP : public ECS::IBehaviour
        {
        public:
            typedef std::unique_ptr<ITcpSocket>   UniqueITcpSockPtr;

        public:
            NetworkTCP();
            NetworkTCP(UniqueITcpSockPtr socket);
            virtual ~NetworkTCP();

        public:
            NetworkTCP(NetworkTCP const& other);
            NetworkTCP&         operator=(NetworkTCP const& other);

        public:
            void                setSocket(UniqueITcpSockPtr socket);
            void                pushData(Buffer const& buffer);
            Buffer              popData();
            bool                isConnected() const;

        public:
            virtual void        update();

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();

        public:
            virtual std::string         toString() const;

        protected:
            void                        onClientDisconnection();

        protected:
            static const size_t     bufferSize;

        protected:
            UniqueITcpSockPtr       _socket;
            Buffer                  _toSend;
            Buffer                  _received;
        };
    }
}

#endif /* !NETWORKTCP_HPP_ */
