#ifndef LOBBYSYSTEM_HPP_
# define LOBBYSYSTEM_HPP_

# include <string>
# include "Entity.hpp"
# include "ASystem.hpp"
# include "ComponentMask.hpp"
# include "ACommand.hpp"

namespace RType
{
    namespace System
    {
        class Lobby : public ECS::ASystem
        {
        public:
            typedef std::unordered_map<Request::LobbyRequest,
                        std::string, std::hash<uint16_t> > RequestCmdMap;

        public:
            Lobby();
            virtual ~Lobby();

        private:
            Lobby(Lobby const& other) = delete;
            Lobby&      operator=(Lobby const& other) = delete;

        public:
            virtual void                processEntity(ECS::Entity& e);
            virtual ECS::ComponentMask  getMask() const;
            virtual std::string         getName() const;
            virtual std::string         toString() const;

        protected:
            void                        handleRequest();

        public:
            static Command::ACommand*   buildCommand(Request const& request);

        protected:
            static const RequestCmdMap  cmdsNames;
        };
    }
}

#endif /* !LOBBYSYSTEM_HPP_ */
