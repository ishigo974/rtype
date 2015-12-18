#ifndef LOBBYSYSTEM_HPP_
# define LOBBYSYSTEM_HPP_

# include <string>
# include <unordered_map>
# include "Entity.hpp"
# include "ASystem.hpp"
# include "ComponentMask.hpp"
# include "RequestCommand.hpp"
# include "CommandFactory.hpp"
# include "RoomComponent.hpp"

namespace RType
{
    namespace System
    {
        class Lobby : public ECS::ASystem
        {
        public:
            typedef std::unordered_map<Request::Code, std::string,
                                       std::hash<uint16_t> >    RequestCmdMap;
            typedef std::unordered_map<uint32_t, ECS::Entity*>  RoomsMap;

        public:
            Lobby();
            virtual ~Lobby();

        private:
            Lobby(Lobby const& other) = delete;
            Lobby&                      operator=(Lobby const& other) = delete;

        public:
            void                        addRoom(ECS::Entity& room);
            RoomsMap const&             getRooms() const;
            Component::Room*            getRoom(unsigned int id) const;

        public:
            virtual void                update();
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual std::string         toString() const;
            virtual bool                shouldAutoUpdate() const;
            virtual bool                shouldAutoProcess() const;

        protected:
            Command::Request*           buildCommand(Request const& request,
                                                     ECS::Entity& entity);

        protected:
            static const RequestCmdMap  cmdsNames;

        protected:
            RoomsMap            _rooms;
            Command::Factory    _factory;
        };
    }
}

#endif /* !LOBBYSYSTEM_HPP_ */
