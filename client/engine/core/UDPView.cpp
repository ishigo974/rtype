//
// Created by naliwe on 22/12/15.
//

#include "UDPView.hpp"

UDPView::UDPView()
{ }

UDPView::UDPView(unsigned int id, std::string const& name) : Component(id, name)
{ }

UDPView::UDPView(UDPView const& other) : Component(other)
{
    _requests = other._requests;
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

    swap(_requests, other._requests);
}

namespace std
{
    template<>
    void swap<UDPView>(UDPView &a, UDPView &b)
    {
        a.swap(b);
    }
}

RType::InGameEvent UDPView::pop()
{
    RType::InGameEvent tmp = _requests.front();

    _requests.pop_front();
    return (tmp);
}

void UDPView::push(RType::InGameEvent const& request)
{
    _requests.push_back(request);
}

RTypes::my_uint16_t UDPView::getMask() const
{
    return (Mask);
}

size_t UDPView::size() const
{
    return (_requests.size());
}
