#ifndef INGAMESYSTEM_HPP_
# define INGAMESYSTEM_HPP_

# include <unordered_map>
# include <string>
# include <mutex>
# include "ASystem.hpp"
# include "Entity.hpp"
# include "UdpSocket.hpp"
# include "ComponentMask.hpp"
# include "CommandEventFactory.hpp"

namespace RType
{
    namespace System
    {
        class InGame : public ECS::ASystem
        {
        public:
            typedef std::unordered_map<std::string, Buffer>     IpBufferBook;
            typedef std::unordered_map<InGameEvent::Code, std::string,
                                       std::hash<uint16_t> >    EventCmdMap;

        public:
            InGame(short int port);
            virtual ~InGame();

        private:
            InGame() = delete;
            InGame(InGame const& other) = delete;
            InGame&                     operator=(InGame const& other) = delete;

        public:
            virtual void                update();
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual bool                shouldAutoUpdate() const;
            virtual bool                shouldAutoProcess() const;
            virtual std::string         toString() const;

        public:
            static const size_t         bufferSize;
            static const EventCmdMap    cmdsNames;

        protected:
            UdpSocket               _socket;
            IpBufferBook            _book;
            Command::EventFactory   _factory;
            std::mutex              _mutex;
        };
    }
}

#endif /* !INGAMESYSTEM_HPP_ */
