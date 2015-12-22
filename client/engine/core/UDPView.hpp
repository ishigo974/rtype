//
// Created by naliwe on 22/12/15.
//

#ifndef RTYPE_UDPVIEW_HPP_
# define RTYPE_UDPVIEW_HPP_

# include <deque>
# include "InGameEvent.hpp"
# include "Component.hpp"

class UDPView : public Component
{
public:
    UDPView();
    UDPView(unsigned int id, std::string const& name);
    UDPView(UDPView const& other);
    UDPView(UDPView&& other);

    UDPView& operator=(UDPView other);

    ~UDPView();

    void swap(UDPView& other);

public:
    RType::InGameEvent pop();
    void               push(RType::InGameEvent const& request);

private:
    std::deque<RType::InGameEvent> _requests;
};


#endif /* !RTYPE_UDPVIEW_HPP_ */
