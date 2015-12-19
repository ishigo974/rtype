//
// Created by Denis Le Borgne on 18/12/2015.
//

#include <sstream>
#include "IncompleteRequest.hpp"
#include "NotImplemented.hpp"
#include "SocketMonitor.hpp"
#include "NetworkTCP.hpp"

namespace RType
{
    const size_t                NetworkTCP::bufferSize = 1024;

    NetworkTCP::NetworkTCP(std::string const& addr, short int port)
            : _connector(addr, port), _connected(true)
    {
        SocketMonitor::getInstance().registerSocket(&_connector);
    }

    NetworkTCP::~NetworkTCP()
    {
        disconnection();
    }

    std::string NetworkTCP::toString() const
    {
        std::ostringstream ss;

        ss << "NetworkTCP {"
        << "\n\t Connector : " << this->_connector.toString()
        << "\n}" << std::endl;

        return ss.str();
    }

    void NetworkTCP::pushRequest(Request const& request)
    {
        _toSend.push_back(request);
    }

    void NetworkTCP::update()
    {
        Buffer tmp;

        if (!_connected)
            return;
        if (SocketMonitor::getInstance().isReadable(_connector.getSocket()))
        {
            try
            {
                _connector.receive(tmp, bufferSize);
            }
            catch (std::runtime_error const& e)
            {
                disconnection();
                e.what();
                return;
            }
            if (tmp.empty())
            {
                disconnection();
                return;
            }
            _receive.append(tmp);
        }
        buildRequest();
        if (SocketMonitor::getInstance().isWritable(_connector.getSocket())
            && !_toSend.empty())
        {
            for (auto& req : _toSend)
            {
                try
                {
                    _connector.send(req.toBuffer());
                }
                catch (std::runtime_error const& e)
                {
                    //TODO can't send request
                    e.what();
                    return;
                }
            }
            _toSend.clear();
        }
    }

    void NetworkTCP::buildRequest()
    {
        try
        {
            while (!_receive.empty())
            {
                Request request(_receive);

                _receive.consume(request.toBuffer().size());
                _requests.push(request);
            }
        }
        catch (Exception::IncompleteRequest const&)
        {
        }
        catch (Exception::NotImplemented const&)
        {
            _receive.clear();
            throw;
        }
    }

    Request NetworkTCP::popRequest()
    {
        Request ret;

        ret = _requests.front();
        _requests.pop();
        return ret;
    }

    bool NetworkTCP::pendingRequests() const
    {
        return _requests.empty();
    }

    void NetworkTCP::disconnection()
    {
        SocketMonitor::getInstance().deleteSocket(&_connector);
        _connector.close();
        _connected = false;
        //TODO Send UI disconnected
    }

    void NetworkTCP::connect()
    {
        if (_connected)
        {
            //TODO Send UI already connect
            return;
        }
        try
        {
            _connector.connect();
        }
        catch (std::runtime_error const&)
        {
            //TODO Send UI can't connect
            return;
        }
        _connected = true;
        SocketMonitor::getInstance().registerSocket(&_connector);
        //TODO Send UI connection success
        return;
    }

    bool NetworkTCP::isConnected() const
    {
        return _connected;
    }
}