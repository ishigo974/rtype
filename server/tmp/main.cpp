#include <unistd.h>
#include <iostream>
#include "Buffer.hpp"
#include "UdpSocket.hpp"
#include "TcpSocket.hpp"
#include "TcpConnector.hpp"
#include "InGameEvent.hpp"
#include "Request.hpp"

using namespace RType;

void            receiveAll(TcpConnector& client,
                                       Buffer& buffer)
{
    if (buffer.empty())
        client.receive(buffer, 4096);
}

Request         recvRequest(TcpConnector& client,
                                        Buffer& buffer)
{
    Request     request;

    receiveAll(client, buffer);
    request = Request(buffer);
    buffer.consume(request.toBuffer().size());
    return request;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
        return 1;
    }

    TcpConnector            client(std::string(argv[1]), std::atoi(argv[2]));
    UdpSocket               u(std::atoi(argv[2]) + 1);
    Request                 request;
    InGameEvent             event;
    Buffer                  received;

        client.connect();

      request.setCode(Request::CL_CREATEROOM);
      request.push<std::string>("room_name", "Room2BoGoss");
    client.send(request.toBuffer());
    request = recvRequest(client, received);

    client.send(Request(Request::CL_READY).toBuffer());
    request = recvRequest(client, received);
    request = recvRequest(client, received);
    u.bind();

    int i = 1;

    while (42)
    {

    event.setCode(InGameEvent::CL_PLAYERDOWN);
    event.push<double>("time", i);
    u.sendTo(event.toBuffer(), std::string(argv[1]));
    
        usleep(1);
    }
    return 0;
}
