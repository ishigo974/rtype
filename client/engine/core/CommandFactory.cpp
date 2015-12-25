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
                                       ACommand::Action::UP,
                                       std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 302:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::DOWN,
                                       std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 303:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::LEFT,
                                       std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 304:
            return (new NetMoveCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       ACommand::Action::RIGHT,
                                       std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 305:
            return (new NetShotCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       true, std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 306:
            return (new NetShotCommand((*_gm)[event.get<RTypes::my_uint8_t>("player_id")],
                                       false, std::chrono::microseconds(event.get<uint64_t>("time"))));
        case 307:
            return (new NetSpawnCommand(static_cast<GameObject *>(_em->getByTag("mobSpawn")),
                                        std::chrono::microseconds(event.get<uint64_t>("time")),
                                        event.get<RTypes::my_uint8_t>("mob_id"),
                                        event.get<RTypes::my_uint32_t>("x"),
                                        event.get<RTypes::my_uint32_t>("y")));

        default:
            return NULL;

    }
}
