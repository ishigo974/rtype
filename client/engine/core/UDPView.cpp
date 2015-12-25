//
// Created by naliwe on 22/12/15.
//

#include "UDPView.hpp"

UDPView::UDPView() : _receive(), _toSend()
{ }

UDPView::UDPView(unsigned int id, std::string const& name) :
    Component(id, name), _receive(), _toSend()
{
    std::cout << "constructor " << &_receive << std::endl;
}

UDPView::UDPView(UDPView const& other) : Component(other)
{
    _receive = other._receive;
}

UDPView::UDPView(UDPView&& other) : UDPView(other)
{
    swap(other);
}

UDPView& UDPView::operator=(UDPView other)
{
    swap(other);

    return (*this);
}

UDPView::~UDPView()
{

}

void UDPView::swap(UDPView& other)
{
    using std::swap;

    swap(_receive, other._receive);
}

namespace std
{
    template<>
    void swap<UDPView>(UDPView& a, UDPView& b)
    {
        a.swap(b);
    }
}

UDPView::Action UDPView::popReceive()
{
    UDPView::Action tmp = _receive.front();

    _receive.pop_front();
    return (tmp);
}

void UDPView::pushReceive(UDPView::Action dir)
{
    _receive.push_back(dir);
}

RTypes::my_uint16_t UDPView::getMask() const
{
    return (Mask);
}

size_t UDPView::sizeRecv() const
{
    return (_receive.size());
}

RType::InGameEvent UDPView::popToSend()
{
    auto tmp = _toSend.front();

    _toSend.pop_front();
    return (tmp);
}

void UDPView::pushToSend(RType::InGameEvent event)
{
    _toSend.push_back(event);
}

size_t UDPView::sizeToSend() const
{
    return (_toSend.size());
}
