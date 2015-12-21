#include "VerticalMobType.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

# include <windows.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport)
RType::MobType::IMobType*       getMobType()
{
    return new RType::MobType::Vertical();
}

#else

extern "C"
{
    RType::MobType::IMobType*   getMobType()
    {
        return new RType::MobType::Vertical();
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
        Vertical::Vertical()
        {
        }

        Vertical::~Vertical()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Vertical::Vertical(Vertical const& other)
        {
        }

        Vertical&      Vertical::operator=(Vertical const& other)
        {
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int    Vertical::getId() const
        {
            return 2;
        }

        std::string     Vertical::getName() const
        {
            return "VerticalMob";
        }

        unsigned int    Vertical::getNbLives() const
        {
            return 1;
        }

        unsigned int    Vertical::getScoreValue() const
        {
            return 5;
        }

        std::string     Vertical::getSpriteFilePath() const
        {
            return "verticalType.png";
        }

        /*
        ** Moves forward, following a straight line
        */
        MovePattern     Vertical::getMovePattern() const
        {
            return [](cu::Position const& pos, double)->cu::Position
            {
                static const float   speed = 3.0f;

                if (pos.Y() < 720) // TODO
                    return cu::Position(pos.X(), pos.Y() + (1 * speed));
                return cu::Position(pos.X(), pos.Y() - (1 * speed));
            };
        }

        IMobType*       Vertical::clone() const
        {
            return new Vertical(*this);
        }

        std::string     Vertical::toString() const
        {
            return "Vertical {"
                   "\n\tid: " + std::to_string(getId()) +
                   "\n\tname: " + getName() +
                   "\n\tlives: " + std::to_string(getNbLives()) +
                   "\n\tscore value: " + std::to_string(getScoreValue()) +
                   "\n\tsprite file path: " + getSpriteFilePath() +
                   "\n}\n";
        }
    }
}
