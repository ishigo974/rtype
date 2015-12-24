//
// Created by naliwe on 22/12/15.
//

#ifndef RTYPE_UDPVIEW_HPP_
# define RTYPE_UDPVIEW_HPP_

# include <deque>
#include <Utils.hpp>
# include "InGameEvent.hpp"
# include "Component.hpp"

class UDPView : public Component
{
public:
    enum Action
    {
        MOVE_UP = 0,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        SHOT_START,
        SHOT_STOP,
        MOB_SPAWN,
        MOB_DIE
    };

public:
    static const RTypes::my_uint16_t Mask = ComponentMask::UDPMask;
public:
    UDPView();
    UDPView(unsigned int id, std::string const& name);
    UDPView(UDPView const& other);
    UDPView(UDPView&& other);

    UDPView& operator=(UDPView other);

    ~UDPView();

    void swap(UDPView& other);

public:
    Action             popReceive();
    RType::InGameEvent popToSend();
    void               pushReceive(Action dir);
    void               pushToSend(RType::InGameEvent event);

    size_t sizeRecv() const;
    size_t sizeToSend() const;

    virtual RTypes::my_uint16_t getMask() const;

private:
    std::deque<Action>             _receive;
    std::deque<RType::InGameEvent> _toSend;
};


#endif /* !RTYPE_UDPVIEW_HPP_ */
