#ifndef VERTICALMOBTYPE_HPP_
# define VERTICALMOBTYPE_HPP_

# include <string>
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class Vertical : public IMobType
        {
        public:
            Vertical();
            virtual ~Vertical();

        public:
            Vertical(Vertical const& other);
            Vertical&               operator=(Vertical const& other);

        public:
            virtual unsigned int    getId() const;
            virtual std::string     getName() const;
            virtual unsigned int    getNbLives() const;
            virtual unsigned int    getScoreValue() const;
            virtual std::string     getSpriteFilePath() const;
            virtual MovePattern     getMovePattern() const;
            virtual IMobType*       clone() const;
            virtual std::string     toString() const;
        };
    }
}

#endif /* !VERTICALMOBTYPE_HPP_ */
