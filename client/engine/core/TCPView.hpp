//
// Created by fourdr_b on 22/12/15.
//

#ifndef RTYPE_TCPVIEW_HPP
# define RTYPE_TCPVIEW_HPP

# include <deque>
# include <Request.hpp>
# include "Component.hpp"

class TCPView : public Component
{
public:
    static const RTypes::my_uint16_t Mask = ComponentMask::TCPMask;

public:
    TCPView();
    TCPView(unsigned int id, std::string const& name);
    TCPView(TCPView const& other);
    TCPView(TCPView&& other);

    TCPView& operator=(TCPView other);

    ~TCPView();

    void swap(TCPView& other);

public:
    RType::Request              popToSend();
    RType::Request              popReceive();
    void                        pushToSend(RType::Request const& request);
    void                        pushReceive(RType::Request const& request);
    virtual RTypes::my_uint16_t getMask() const;
    size_t                      sizeReceive() const;
    size_t                      sizeToSend() const;

private:
    std::deque<RType::Request> _receive;
    std::deque<RType::Request> _toSend;
};


#endif //RTYPE_TCPVIEW_HPP