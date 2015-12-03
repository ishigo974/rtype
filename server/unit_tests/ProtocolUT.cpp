#include <vector>
#include <iostream>
#include "ProtocolUT.hpp"
#include "Request.hpp"

namespace RType
{
    /*
    ** Constructor/Destructor
    */
    ProtocolUT::ProtocolUT()
    {
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
}
