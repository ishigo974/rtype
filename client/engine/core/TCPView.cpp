//
// Created by fourdr_b on 22/12/15.
//

#include "TCPView.hpp"

TCPView::TCPView()
{ }

TCPView::TCPView(unsigned int id, std::string const& name) : Component(id, name)
{ }

TCPView::TCPView(TCPView const& other) : Component(other)
{
    _receive = other._receive;
    _toSend  = other._toSend;
}

TCPView::TCPView(TCPView&& other) : TCPView(other)
{
    swap(other);
}

TCPView& TCPView::operator=(TCPView other)
{
    swap(other);

    return (*this);
}

TCPView::~TCPView()
{

}

void TCPView::swap(TCPView& other)
{
    using std::swap;

    swap(_receive, other._receive);
    swap(_toSend, other._toSend);
}

namespace std
{
    template<>
    void swap<TCPView>(TCPView& a, TCPView& b)
    {
        a.swap(b);
    }
}

RType::Request TCPView::popToSend()
{
    RType::Request tmp = _toSend.front();

    _toSend.pop_front();
    return (tmp);
}

void TCPView::pushToSend(RType::Request const& request)
{
    _toSend.push_back(request);
}

RType::Request TCPView::popReceive()
{
    RType::Request tmp = _receive.front();

    _receive.pop_front();
    return (tmp);
}

void TCPView::pushReceive(RType::Request const& request)
{
    _receive.push_back(request);
}

RTypes::my_uint16_t TCPView::getMask() const
{
    return Mask;
}

size_t TCPView::sizeToSend() const
{
    return (_toSend.size());
}

size_t TCPView::sizeReceive() const
{
    return (_receive.size());
}
