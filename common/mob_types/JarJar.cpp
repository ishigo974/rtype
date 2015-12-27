#include "JarJar.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

# include <windows.h>

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
    return TRUE;
}

extern "C" __declspec(dllexport)
RType::MobType::IMobType*       getMobType()
{
    return new RType::MobType::JarJar();
}

#else

extern "C"
{
    RType::MobType::IMobType*   getMobType()
    {
        return new RType::MobType::JarJar();
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
        JarJar::JarJar()
        {}

        JarJar::~JarJar()
        {}

        /*
        ** Copy constructor and assign operator
        */
        JarJar::JarJar(JarJar const& other)
        {
        }

        JarJar&      JarJar::operator=(JarJar const& other)
        {
            return *this;
        }

        /*
        ** Public member functions
        */
        unsigned int    JarJar::getId() const
        {
            return 4;
        }

        gu::Rect<int>   JarJar::getRekt() const
        {
            return (gu::Rect<int>(0, 0, 471, 416));
        }

        std::string     JarJar::getName() const
        {
            return "JarJarMob";
        }

        unsigned int    JarJar::getNbLives() const
        {
            return 100;
        }

        unsigned int    JarJar::getScoreValue() const
        {
            return 10;
        }

        std::string     JarJar::getSpriteFilePath() const
        {
            return "jarjar";
        }

        MovePattern     JarJar::getMovePattern() const
        {
            return [](cu::Position const& pos, double elapsedTime,
                      int& state)->cu::Position
            {
                static const float  speed = .5f;

                if (pos.X() >= 1280 - 471 || pos.X() <= 0)
                    state *= -1;
                return cu::Position(pos.X() - (0.25 * speed * elapsedTime
                                               * state),
                                    304);
            };
        }

        IMobType*       JarJar::clone() const
        {
            return new JarJar(*this);
        }

        std::string     JarJar::toString() const
        {
            return "JarJar {"
                   "\n\tid: " + std::to_string(getId()) +
                   "\n\tname: " + getName() +
                   "\n\tlives: " + std::to_string(getNbLives()) +
                   "\n\tscore value: " + std::to_string(getScoreValue()) +
                   "\n\tsprite file path: " + getSpriteFilePath() +
                   "\n}\n";
        }

        unsigned int    JarJar::getNumberFrames() const
        {
            return 3;
        }

        double          JarJar::getDuration() const
        {
            return 64.0;
        }

        bool            JarJar::getLoop() const
        {
            return true;
        }

    }
}
