#include <vector>
#include <iostream>
#include <string>
#include "ProtocolUT.hpp"
#include "Request.hpp"

namespace RType
{
    /*
    ** Static variables
    */
    std::string     ProtocolUT::ip      = "0";
    short int       ProtocolUT::port    = 6667;

    /*
    ** Constructor/Destructor
    */
    ProtocolUT::ProtocolUT(std::string const& ip, short int port)
    {
        ProtocolUT::ip = ip;
        ProtocolUT::port = port;
    }

    ProtocolUT::~ProtocolUT()
    {
    }

    /*
    ** Public member functions
    */
    void            ProtocolUT::registerTests()
    {
        registerTest("LobbyRequestParsingWithoutData",
                    &ProtocolUT::lobbyRequestParsingWithoutData);
        registerTest("LobbyRequestParsingWithData",
                    &ProtocolUT::lobbyRequestParsingWithData);
        registerTest("CreateSingleRoomAndList",
                    &ProtocolUT::createSingleRoomAndList);
        registerTest("CreateMultipleRoomsAndList",
                    &ProtocolUT::createMultipleRoomsAndList);
        registerTest("FullTestRoom", &ProtocolUT::fullTestRoom);
    }

    std::string     ProtocolUT::getName() const
    {
        return "Protocol";
    }

    /*
    ** Unit tests
    */
    void            ProtocolUT::lobbyRequestParsingWithoutData()
    {
        static const std::vector<Request::LobbyRequest> tests =
        {   Request::LR_LISTROOMS,  Request::LR_QUITROOM,
            Request::LR_READY,      Request::LR_NOTREADY };

        for (auto& code: tests)
        {
            Buffer      buffer;
            Request     request;

            buffer.append<uint16_t>(code);
            buffer.append<uint32_t>(0);
            UT_ASSERT(buffer.size() == Request::headerSize);
            request = Request(Request::PROTOCOL_LOBBY, buffer);
            UT_ASSERT(request.getProtocol() == Request::PROTOCOL_LOBBY);
            UT_ASSERT(request.getCode() == code);
            UT_ASSERT(request.size() == Request::headerSize);
        }
    }

    void            ProtocolUT::lobbyRequestParsingWithData()
    {
        static const std::map<std::string, Request::LobbyRequest> stringTests =
        {
            { "Room2Bogoss",                        Request::LR_CREATEROOM },
            { "  13624!@#)$!*%(#@) ///\\\\fsiodj",  Request::LR_CREATEROOM },
            { "Username2Bogoss",                    Request::LR_USERNAME },
            { "   ,./AS>D/><<<§±`~`1j{}[||]",       Request::LR_USERNAME }
        };
        static const std::vector<uint32_t>  idTests =
        { 0, 1, 42, 99, 999, 9999, 99999 };

        for (auto& test: stringTests)
        {
            Buffer      buffer;
            size_t      dataSize;
            Request     request;

            dataSize = test.first.size() + Request::dataSizes.at("size");
            buffer.append<uint16_t>(test.second);
            buffer.append<uint32_t>(dataSize);
            buffer.append<uint32_t>(test.first.size());
            buffer.append(test.first);
            UT_ASSERT(buffer.size() == Request::headerSize + dataSize);
            request = Request(Request::PROTOCOL_LOBBY, buffer);
            UT_ASSERT(request.getProtocol() == Request::PROTOCOL_LOBBY);
            UT_ASSERT(request.getCode() == test.second);
            UT_ASSERT(request.size() == Request::headerSize + dataSize);
            UT_ASSERT(request.get<std::string>(Request::lobbyRequests
                .at(test.second).at(0)) == test.first);
        }
        for (auto& test: idTests)
        {
            Buffer      buffer;
            size_t      dataSize;
            Request     request;

            dataSize = Request::dataSizes.at("room_id");
            buffer.append<uint16_t>(Request::LR_JOINROOM);
            buffer.append<uint32_t>(dataSize);
            buffer.append<uint32_t>(test);
            UT_ASSERT(buffer.size() == Request::headerSize + dataSize);
            request = Request(Request::PROTOCOL_LOBBY, buffer);
            UT_ASSERT(request.getProtocol() == Request::PROTOCOL_LOBBY);
            UT_ASSERT(request.getCode() == Request::LR_JOINROOM);
            UT_ASSERT(request.size() == Request::headerSize + dataSize);
            UT_ASSERT(request.get<uint32_t>("room_id") == test);
        }
    }

    void            ProtocolUT::createSingleRoomAndList()
    {
        TcpConnector        client(ip, port);
        Buffer              tmp;
        Request             request;
        Request::RoomsTab   rooms;
        std::string         str;

        client.connect();
        client.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 0);
        str = "Room2BoGoss";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client.send(formatRequest(Request::LR_CREATEROOM, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        client.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 1);
        UT_ASSERT(rooms[0].name == str);
        UT_ASSERT(rooms[0].nbPlayers == 1);
        client.send(formatRequest(Request::LR_QUITROOM));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        client.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 0);
    }

    void            ProtocolUT::createMultipleRoomsAndList()
    {
        TcpConnector        client1(ip, port);
        TcpConnector        client2(ip, port);
        Buffer              tmp;
        Request             request;
        Request::RoomsTab   rooms;
        std::string         str;

        client1.connect();
        client2.connect();

        // client1 list rooms
        client1.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 0);

        // client2 creates room
        str = "Room2BoGoss";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client2.send(formatRequest(Request::LR_CREATEROOM, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client1 list rooms
        client1.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 1);
        UT_ASSERT(rooms[0].name == str);
        UT_ASSERT(rooms[0].nbPlayers == 1);

        // client1 creates room
        str = "'Sssssup bitches ?!";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client1.send(formatRequest(Request::LR_CREATEROOM, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client2 list rooms
        client2.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 2);
        UT_ASSERT(rooms[1].name == "Room2BoGoss");
        UT_ASSERT(rooms[0].name == str);
        UT_ASSERT(rooms[0].nbPlayers == 1);
        UT_ASSERT(rooms[1].nbPlayers == 1);

        // client1/client2 quits rooms
        client1.send(formatRequest(Request::LR_QUITROOM));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        client2.send(formatRequest(Request::LR_QUITROOM));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);
    }

    void            ProtocolUT::fullTestRoom()
    {
        TcpConnector            client1(ip, port);
        TcpConnector            client2(ip, port);
        Buffer                  tmp;
        Request                 request;
        Request::RoomsTab       rooms;
        Request::PlayersTab     players;
        std::string             str;
        unsigned int            id;

        client1.connect();
        client2.connect();

        // client1 renames
        str = "Toto";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client1.send(formatRequest(Request::LR_USERNAME, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client2 renames
        str = "Tata";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client2.send(formatRequest(Request::LR_USERNAME, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client2 creates room
        str = "Room2BoGoss";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client2.send(formatRequest(Request::LR_CREATEROOM, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client1 list rooms
        client1.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 1);
        UT_ASSERT(rooms[0].name == str);
        UT_ASSERT(rooms[0].nbPlayers == 1);

        // client1 joins room
        tmp.append<uint32_t>(rooms[0].id);
        client1.send(formatRequest(Request::LR_JOINROOM, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_ROOMINFO);
        id = request.get<uint8_t>("player_id");
        UT_ASSERT(id == 2);
        players = request.get<Request::PlayersTab>("players");
        UT_ASSERT(players[0].id == 1);
        UT_ASSERT(players[0].username == "Tata");
        UT_ASSERT(players[0].isReady == false);
        tmp.clear();

        // client2 is notified of client1 joining his room
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_JOINROOM);
        UT_ASSERT(request.get<uint8_t>("player_id") == 2);
        UT_ASSERT(request.get<std::string>("username") == "Toto");

        // client1 list rooms
        client1.send(formatRequest(Request::LR_LISTROOMS));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_LISTROOMS);
        rooms = request.get<Request::RoomsTab>("rooms");
        UT_ASSERT(rooms.size() == 1);
        UT_ASSERT(rooms[0].name == str);
        UT_ASSERT(rooms[0].nbPlayers == 2);

        // client2 renames
        str = "Titi";
        tmp.append<uint32_t>(str.size());
        tmp.append<std::string>(str);
        client2.send(formatRequest(Request::LR_USERNAME, tmp));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);
        tmp.clear();

        // client1 is notified of client2 changing his nickname
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_CLIUSRNM);
        UT_ASSERT(request.get<uint8_t>("player_id") == players[0].id);
        UT_ASSERT(request.get<std::string>("username") == "Titi");

        // client1 is ready
        client1.send(formatRequest(Request::LR_READY));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_OK);

        // client2 is notified of client1 getting ready
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_CLIENTRDY);
        UT_ASSERT(request.get<uint8_t>("player_id") == id);

        // client2 is ready
        client2.send(formatRequest(Request::LR_READY));
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_OK);

        // client1 is notified of client2 getting ready
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_CLIENTRDY);
        UT_ASSERT(request.get<uint8_t>("player_id") == players[0].id);

        // client1 is notified that the game starts
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client1));
        UT_ASSERT(request.getCode() == Request::SE_CLIENTRDY);
        UT_ASSERT(request.get<uint8_t>("player_id") == players[0].id);

        // client2 is notified that the game starts
        request = Request(Request::PROTOCOL_LOBBY, receiveAll(client2));
        UT_ASSERT(request.getCode() == Request::SE_CLIENTRDY);
        UT_ASSERT(request.get<uint8_t>("player_id") == players[0].id);
    }

    /*
    ** Static functions
    */
    Buffer          ProtocolUT::receiveAll(TcpConnector& client)
    {
        Buffer      b;

        client.receive(b, 4096);
        return b;
    }

    Buffer          ProtocolUT::formatRequest(Request::LobbyRequest code,
                                              Buffer const& data)
    {
        Buffer      request;

        request.append<uint16_t>(code);
        request.append<uint32_t>(data.size());
        request.append(data);
        return request;
    }
}
