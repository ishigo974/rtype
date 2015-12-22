#include <cmath>
#include "SinusoidMobType.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

# include <windows.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport)
RType::MobType::IMobType*       getMobType()
{
    return new RType::MobType::Sinusoid();
}

#else

extern "C"
{
    RType::MobType::IMobType*   getMobType()
    {
        return new RType::MobType::Sinusoid();
    }
}
#endif

namespace RType
{
    namespace MobType
    {
        /*
        ** Constructor/Destructor
        */
        Sinusoid::Sinusoid()
        {
        }

        Sinusoid::~Sinusoid()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Sinusoid::Sinusoid(Sinusoid const& other)
        {
        }

        Sinusoid&      Sinusoid::operator=(Sinusoid const& other)
        {
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int    Sinusoid::getId() const
        {
            return 1;
        }

        std::string     Sinusoid::getName() const
        {
            return "SinusoidMob";
        }

        unsigned int    Sinusoid::getNbLives() const
        {
            return 1;
        }

        unsigned int    Sinusoid::getScoreValue() const
        {
            return 5;
        }

        std::string     Sinusoid::getSpriteFilePath() const
        {
            return "sinusoidType.png";
        }

        /*
        ** Moves forward, following a straight line
        */
        MovePattern     Sinusoid::getMovePattern() const
        {
            return [](cu::Position const& pos, double elapsedTime)->cu::Position
            {
                static const float   speed = 1.0f;

                return cu::Position(pos.X() - (0.25 * speed * elapsedTime),
                                    pos.Y() + (90 * std::sin(pos.X())));
            };
        }

        IMobType*       Sinusoid::clone() const
        {
            return new Sinusoid(*this);
        }

        std::string     Sinusoid::toString() const
        {
            return "Sinusoid {"
                   "\n\tid: " + std::to_string(getId()) +
                   "\n\tname: " + getName() +
                   "\n\tlives: " + std::to_string(getNbLives()) +
                   "\n\tscore value: " + std::to_string(getScoreValue()) +
                   "\n\tsprite file path: " + getSpriteFilePath() +
                   "\n}\n";
        }
    }
}
