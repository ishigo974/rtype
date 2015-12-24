//
// Created by fourdr_b on 24/12/15.
//

#include "CommandFactory.hpp"
#include "NetMoveCommand.hpp"
#include "UDPView.hpp"
#include "NetShotCommand.hpp"
#include "MobSpawner.hpp"
#include "NetSpawnCommand.hpp"

CommandFactory::CommandFactory(EntityManager *em)
        : _em(em)
{ }

ACommand *CommandFactory::createCommand(RType::InGameEvent const& event)
{
    if ((_gm = static_cast<GameManager *>(_em->getByTag("GameManager"))) == nullptr)
        throw (std::logic_error("Could not find GameManager"));

    switch (event.getCode())
    {
        case 301:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::UP));
        case 302:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::DOWN));
        case 303:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::LEFT));
        case 304:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::RIGHT));
        case 305:
            return (new NetShotCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       true));
        case 306:
            return (new NetShotCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       false));
        case 307:
            return (new NetSpawnCommand(_gm, event.get<RTypes::my_uint8_t>("mob_id"),
                                        event.get<RTypes::my_uint32_t>("x"),
                                        event.get<RTypes::my_uint32_t>("y")));

        default:
            return NULL;

    }
}
