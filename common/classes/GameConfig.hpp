#ifndef GAMECONFIG_HPP_
# define GAMECONFIG_HPP_

# include <unordered_map>

namespace RType
{
    namespace Config
    {
        const double        fixedStep       = 0.003;
        const double        dftElapsedTime  = 0.025;
    }

    namespace Map
    {
        const unsigned int  height       = 720;
        const unsigned int  width        = 1280;

        const std::unordered_map<unsigned int, unsigned int>
        defaultPosY =
        {
            { 1, 200 },
            { 2, 300 },
            { 3, 400 },
            { 4, 500 }
        };

        const unsigned int defaultPosX  = 100;
    }

    namespace Speed
    {
        const float ship    = 1.25f;
        const float bullet  = 2.0f;
    }
}

#endif /* !GAMECONFIG_HPP_ */
