#include "DiagonalMobType.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

# include <windows.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport)
RType::MobType::IMobType*       getMobType()
{
    return new RType::MobType::Diagonal();
}

#else

extern "C"
{
    RType::MobType::IMobType*   getMobType()
    {
        return new RType::MobType::Diagonal();
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
        Diagonal::Diagonal()
        {
        }

        Diagonal::~Diagonal()
        {
        }

        /*
        ** Copy constructor and assign operator
        */
        Diagonal::Diagonal(Diagonal const& other)
        {
        }

        Diagonal&      Diagonal::operator=(Diagonal const& other)
        {
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int    Diagonal::getId() const
        {
            return 3;
        }

        gu::Rect<int>   Diagonal::getRekt() const
        {
            return (gu::Rect<int>(52, 3, 55, 54));
        }

        std::string     Diagonal::getName() const
        {
            return "DiagonalMob";
        }

        unsigned int    Diagonal::getNbLives() const
        {
            return 1;
        }

        unsigned int    Diagonal::getScoreValue() const
        {
            return 10;
        }

        std::string     Diagonal::getSpriteFilePath() const
        {
            return "r-typesheet9";
        }

        MovePattern     Diagonal::getMovePattern() const
        {
            return [](cu::Position const& pos, double elapsedTime,
                      int& state)->cu::Position
            {
                static const float  speed = 1.0f;

                if (pos.Y() >= 720 || pos.Y() <= 0)
                    state *= -1;
                return cu::Position(pos.X() - (0.25 * speed * elapsedTime),
                                    pos.Y() +
                                    (0.25 * speed * elapsedTime * state));
            };
        }

        IMobType*       Diagonal::clone() const
        {
            return new Diagonal(*this);
        }

        std::string     Diagonal::toString() const
        {
            return "Diagonal {"
                   "\n\tid: " + std::to_string(getId()) +
                   "\n\tname: " + getName() +
                   "\n\tlives: " + std::to_string(getNbLives()) +
                   "\n\tscore value: " + std::to_string(getScoreValue()) +
                   "\n\tsprite file path: " + getSpriteFilePath() +
                   "\n}\n";
        }
    }
}
