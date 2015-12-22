#ifndef SINUSOIDMOBTYPE_HPP_
# define SINUSOIDMOBTYPE_HPP_

# include <string>
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class Sinusoid : public IMobType
        {
        public:
            Sinusoid();
            virtual ~Sinusoid();

        public:
            Sinusoid(Sinusoid const& other);
            Sinusoid&                operator=(Sinusoid const& other);

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

#endif /* !SINUSOIDMOBTYPE_HPP_ */
