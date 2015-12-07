#include <iostream>
#include <sstream>
#include "LobbySystem.hpp"
#include "ComponentsMasks.hpp"
#include "NetworkTCP.hpp"
#include "Request.hpp"
#include "ValueError.hpp"
#include "ACommand.hpp"
#include "Server.hpp"
#include "CommandFactory.hpp"

namespace RType
{
    namespace System
    {
        /*
        ** Static variables
        */
        const Lobby::RequestCmdMap      Lobby::cmdsNames    = {
            { Request::LR_USERNAME, "UsernameCommand" }
        };

        /*
        ** Constructor/Destructor
        */
        Lobby::Lobby()
        {
        }

        Lobby::~Lobby()
        {
        }

        /*
        ** Public member functions
        */
        void                Lobby::processEntity(ECS::Entity& e)
        {
            Component::NetworkTCP*  network = e
                .getComponent<Component::NetworkTCP>(Component::MASK_NETWORKTCP);

            while (network->isRequest())
            {
                try {
                    Lobby::buildCommand(network->popRequest())->execute();
                } catch (Exception::ValueError const& e) {
                    Server::display(std::string(e.what()), true);
                } catch (std::out_of_range const&) {
                    Server::display("Can't build command from \
                                    request, ignored", true);
                }
            }
        }

        ECS::ComponentMask  Lobby::getMask() const
        {
            return Component::MASK_NETWORKTCP;
        }

        std::string         Lobby::getName() const
        {
            return "LobbySystem";
        }

        std::string         Lobby::toString() const
        {
            return "LobbySystem { mask: " + std::to_string(getMask()) + "}";
        }

        /*
        ** Protected member functions
        */
        void                Lobby::handleRequest()
        {
        }

        /*
        ** Static functions
        */
        Command::ACommand*  Lobby::buildCommand(Request const& request)
        {
            Command::ACommand*       cmd =
                Command::Factory::getInstance()
                    .generate(cmdsNames.at(
                        static_cast<Request::LobbyRequest>(request.getCode())
                    ));

            if (cmd == nullptr)
                throw Exception::ValueError("No command corresponding \
                    to request code " + std::to_string(request.getCode()));
            cmd->initFromRequest(request);
            return cmd;
        }
    }
}
