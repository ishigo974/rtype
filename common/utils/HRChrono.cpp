#include <iostream>
#include "HRChrono.hpp"

namespace Time
{
    /*
    ** Constructor/Destructor
    */
    HRChrono::HRChrono() : _start(HighResClock::now())
    {
    }

    HRChrono::~HRChrono()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    HRChrono::HRChrono(HRChrono const& other) :
        _start(other._start)
    {
    }

    HRChrono&        HRChrono::operator=(HRChrono const& other)
    {
        if (this != &other)
            _start = other._start;
        return *this;
    }

    /*
    ** Public member functions
    */
    void            HRChrono::start()
    {
        _start = HighResClock::now();
    }

    void            HRChrono::reset()
    {
        start();
    }

    uintmax_t       HRChrono::getElapsedTime() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                    HighResClock::now() - _start
                ).count();
    }
}
