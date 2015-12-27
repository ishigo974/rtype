#include "ForwardMobType.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

# include <windows.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport)
RType::MobType::IMobType*       getMobType()
{
    return new RType::MobType::Forward();
}

#else

extern "C"
{
    RType::MobType::IMobType*   getMobType()
    {
        return new RType::MobType::Forward();
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
        Forward::Forward()
        {
        }

        Forward::~Forward()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Forward::Forward(Forward const& other)
        {
        }

        Forward&      Forward::operator=(Forward const& other)
        {
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int    Forward::getId() const
        {
            return 1;
        }

        gu::Rect<int>   Forward::getRekt() const
        {
            return (gu::Rect<int>(0, 0, 21, 24));
        }

        std::string     Forward::getName() const
        {
            return "ForwardMob";
        }

        unsigned int    Forward::getNbLives() const
        {
            return 1;
        }

        unsigned int    Forward::getScoreValue() const
        {
            return 5;
        }

        std::string     Forward::getSpriteFilePath() const
        {
            return "forward";
        }

        /*
        ** Moves forward, following a straight line
        */
        MovePattern     Forward::getMovePattern() const
        {
            return [](cu::Position const& pos, double elapsedTime, int&)->cu::Position
            {
                static const float   speed = 0.75f;

                return cu::Position(pos.X() - (0.25 * speed * elapsedTime), pos.Y());
            };
        }

        IMobType*       Forward::clone() const
        {
            return new Forward(*this);
        }

        std::string     Forward::toString() const
        {
            return "Forward {"
                   "\n\tid: " + std::to_string(getId()) +
                   "\n\tname: " + getName() +
                   "\n\tlives: " + std::to_string(getNbLives()) +
                   "\n\tscore value: " + std::to_string(getScoreValue()) +
                   "\n\tsprite file path: " + getSpriteFilePath() +
                   "\n}\n";
        }

        unsigned int    Forward::getNumberFrames() const
        {
            return 8;
        }

        double          Forward::getDuration() const
        {
            return 256.0;
        }

        bool            Forward::getLoop() const
        {
            return true;
        }
    }
}
