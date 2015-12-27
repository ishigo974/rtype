#include "VerticalMobType.hpp"
#include "GameConfig.hpp"

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

        gu::Rect<int>   Vertical::getRekt() const
        {
            return (gu::Rect<int>(0, 0, 176, 144));
        }


        std::string     Vertical::getName() const
        {
            return "VerticalMob";
        }

        unsigned int    Vertical::getNbLives() const
        {
            return 256;
        }

        unsigned int    Vertical::getScoreValue() const
        {
            return 256;
        }

        std::string     Vertical::getSpriteFilePath() const
        {
            return "boss";
        }

        MovePattern     Vertical::getMovePattern() const
        {
            return [](cu::Position const& pos, double elapsedTime,
                      int& state)->cu::Position
            {
                static const float  speed = 0.75f;

                if (pos.Y() >= Map::height - 144 || pos.Y() <= 0)
                    state = state ^ 1;
                if (pos.X() >= Map::width - 176 || pos.X() <= 0)
                    state = state ^ 2;
                return cu::Position(pos.X() + (0.25 * speed * elapsedTime
                                               * (state & 2) ? 1 : -1),
                                    pos.Y() + (0.25 * speed * elapsedTime
                                               * (state & 1) ? 1 : -1));
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

        unsigned int    Vertical::getNumberFrames() const
        {
            return 2;
        }

        double          Vertical::getDuration() const
        {
            return 512.0;
        }

        bool            Vertical::getLoop() const
        {
            return true;
        }
    }
}
