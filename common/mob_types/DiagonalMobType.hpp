#ifndef DIAGONALMOBTYPE_HPP_
# define DIAGONALMOBTYPE_HPP_

# include <string>
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class Diagonal : public IMobType
        {
        public:
            Diagonal();
            virtual ~Diagonal();

        public:
            Diagonal(Diagonal const& other);
            Diagonal&               operator=(Diagonal const& other);

        public:
            virtual unsigned int    getId() const;
            virtual gu::Rect<int>   getRekt() const;
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

#endif /* !DIAGONALMOBTYPE_HPP_ */
