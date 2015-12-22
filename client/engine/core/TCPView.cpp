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
    _requests = other._requests;
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

    swap(_requests, other._requests);
}

namespace std
{
    template<>
    void swap<TCPView>(TCPView &a, TCPView &b)
    {
        a.swap(b);
    }
}

RType::Request TCPView::pop()
{
    RType::Request tmp = _requests.front();

    _requests.pop_front();
    return (tmp);
}

void TCPView::push(RType::Request const& request)
{
    _requests.push_back(request);
}
