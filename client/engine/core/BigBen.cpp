//
// Created by naliwe on 01/12/15.
//

#include "BigBen.hpp"

std::chrono::time_point<std::chrono::high_resolution_clock> BigBen::_last;
std::chrono::time_point<std::chrono::steady_clock>          BigBen::_lastFixed;

double BigBen::getElapsedtime()
{
    auto                      newNow = _clock.now();
    std::chrono::microseconds t((newNow - _last).count());

    _last = newNow;

    return (t.count());
}

double BigBen::getFixedElapsedtime()
{
    auto                      newFixedNow = _fixedClock.now();
    std::chrono::microseconds t((newFixedNow - _lastFixed).count());

    _lastFixed = newFixedNow;

    return (t.count());
}

std::chrono::time_point<std::chrono::high_resolution_clock>    BigBen::getTimeNow()
{
    return _clock.now();
}

BigBen::BigBen()
{
    _clock.now();
    _fixedClock.now();

    _last      = _clock.now();
    _lastFixed = _fixedClock.now();
}

BigBen::~BigBen()
{ }
