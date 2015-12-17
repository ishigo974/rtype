#ifndef NETWORKTCP_HPP_
# define NETWORKTCP_HPP_

# include <memory>
# include <queue>
# include <string>
# include "IComponent.hpp"
# include "IBehaviour.hpp"
# include "ComponentMask.hpp"
# include "ITcpSocket.hpp"
# include "Request.hpp"

namespace RType
{
    namespace Component
    {
        class NetworkTCP : public ECS::IBehaviour
        {
        public:
            typedef std::unique_ptr<ITcpSocket>         UniqueITcpSockPtr;
            typedef std::function<void (unsigned int)>  ServerCallback;

        public:
            NetworkTCP();
            NetworkTCP(UniqueITcpSockPtr socket);
            virtual ~NetworkTCP();

        public:
            NetworkTCP(NetworkTCP const& other);
            NetworkTCP&         operator=(NetworkTCP const& other);

        public:
            void                setEntityId(unsigned int id);
            void                setSocket(UniqueITcpSockPtr socket);
            void                send(Buffer const& buffer);
            bool                isConnected() const;
            bool                isRequest() const;
            void                setOnDisconnect(ServerCallback const& c);
            Request             popRequest();
            std::string const&  repr() const;

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
            void                        buildRequests();

        protected:
            static const size_t             bufferSize;

        public:
            static const ECS::ComponentMask mask;

        protected:
            unsigned int            _entityId;
            UniqueITcpSockPtr       _socket;
            Buffer                  _toSend;
            Buffer                  _received;
            std::queue<Request>     _requests;
            std::string             _repr;
            ServerCallback          _onDisconnect;
        };
    }
}

#endif /* !NETWORKTCP_HPP_ */
