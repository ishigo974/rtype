#include "GameClock.hpp"

namespace Time
{
    /*
    ** Constructor/Destructor
    */
    GameClock::GameClock()
    {
        _clock.now();
        _fixedClock.now();
        _last = _clock.now();
        _lastFixed = _fixedClock.now();
    }

    GameClock::~GameClock()
    {
    }

    /*
    ** Copy constructor and assign operator
    */
    GameClock::GameClock(GameClock const& other) :
        _clock(other._clock), _fixedClock(other._fixedClock),
        _last(other._last), _lastFixed(other._lastFixed)
    {
    }

    GameClock&      GameClock::operator=(GameClock const& other)
    {
        if (this != &other)
        {
            _clock = other._clock;
            _fixedClock = other._fixedClock;
            _last = other._last;
            _lastFixed = other._lastFixed;
        }
        return *this;
    }

    /*
    ** Public member functions
    */
    double          GameClock::updateElapsedTime()
    {
        auto                          newNow = _clock.now();
        std::chrono::duration<double> t      = newNow - _last;

        _last = newNow;
        return (t.count());
    }

    double          GameClock::updateFixedElapsed()
    {
        auto                          newFixedNow = _fixedClock.now();
        std::chrono::duration<double> t           = newFixedNow - _lastFixed;

        _lastFixed = newFixedNow;
        return (t.count());
    }

    GameClock::HRCTimePoint	GameClock::now() const
    {
        return _clock.now();
    }
}
