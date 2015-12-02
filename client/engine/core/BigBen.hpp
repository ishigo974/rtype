//
// Created by naliwe on 01/12/15.
//

#ifndef RTYPE_BIGBEN_HPP_
# define RTYPE_BIGBEN_HPP_

# include <chrono>

class BigBen
{
public:
    static double getElapsedtime();
    static double getFixedElapsedtime();

    static BigBen& get()
    {
        static BigBen instance;

        return instance;
    }

  static std::chrono::time_point<std::chrono::high_resolution_clock>	getTimeNow();

private:
    BigBen();
    ~BigBen();

    BigBen(BigBen& other) = delete;
    BigBen& operator=(BigBen const& other) = delete;

private:
    static std::chrono::high_resolution_clock                          _clock;
    static std::chrono::steady_clock                                   _fixedClock;
    static std::chrono::time_point<std::chrono::high_resolution_clock> _last;
    static std::chrono::time_point<std::chrono::steady_clock>          _lastFixed;
};


#endif /* !RTYPE_BIGBEN_HPP_ */
