#ifndef HRCLOCK_HPP_
# define HRCLOCK_HPP_

# include <chrono>

namespace Time
{
    class HRChrono
    {
    public:
        typedef std::chrono::high_resolution_clock::time_point  HRCTimePoint;
        typedef std::chrono::high_resolution_clock              HighResClock;

    public:
        HRChrono();
        virtual ~HRChrono();

    public:
        HRChrono(HRChrono const& other);
        HRChrono&        operator=(HRChrono const& other);

    public:
        void            start();
        void            reset();
        uintmax_t       getElapsedTime() const;

    protected:
        HRCTimePoint    _start;
    };
}

#endif /* !HRCLOCK_HPP_ */
