#ifndef IMOBTYPE_HPP_
# define IMOBTYPE_HPP_

# include <functional>
# include <vector>
# include "Utils.hpp"
# include "IStringable.hpp"

namespace RType
{
    namespace MobType
    {
        /*
        ** Function that defines the pattern of a mob
        ** Takes the current mob's positions and the game's elapsed time
        ** Returns the next positions of the mob
        */
        typedef
        std::function<cu::Position (cu::Position const&, double, int&)> MovePattern;

        class IMobType : public IStringable
        {
        public:
            virtual ~IMobType() {}

        public:
            virtual unsigned int    getId() const = 0;
            virtual std::string     getName() const = 0;
            virtual unsigned int    getNbLives() const = 0;
            virtual unsigned int    getScoreValue() const = 0;
            virtual std::string     getSpriteFilePath() const = 0;
            virtual MovePattern     getMovePattern() const = 0;
            virtual IMobType*       clone() const = 0;
        };

        typedef std::vector<IMobType*>   Collection;
    }
}

#endif /* !IMOBTYPE_HPP_ */
