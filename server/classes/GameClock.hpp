#ifndef GAMECLOCK_HPP_
# define GAMECLOCK_HPP_

# include <chrono>

namespace Time
{
    class GameClock
    {
    public:
        typedef std::chrono::high_resolution_clock::time_point  HRCTimePoint;
        typedef std::chrono::high_resolution_clock              HighResClock;
        typedef std::chrono::steady_clock::time_point           SCTimePoint;
        typedef std::chrono::steady_clock                       SteadyClock;

    public:
        GameClock();
        virtual ~GameClock();

    public:
        GameClock(GameClock const& other);
        GameClock&      operator=(GameClock const& other);

    public:
        double          updateElapsedTime();
        double          updateFixedElapsed();
        HRCTimePoint	now() const;

    private:
        HighResClock    _clock;
        SteadyClock     _fixedClock;
        HRCTimePoint    _last;
        SCTimePoint     _lastFixed;
    };
}

#endif /* !GAMECLOCK_HPP_ */
