#ifndef FORWARDMOBTYPE_HPP_
# define FORWARDMOBTYPE_HPP_

# include <string>
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class Forward : public IMobType
        {
        public:
            Forward();
            virtual ~Forward();

        public:
            Forward(Forward const& other);
            Forward&                operator=(Forward const& other);

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
            virtual unsigned int    getNumberFrames() const;
            virtual double          getDuration() const;
            virtual bool            getLoop() const;
        };
    }
}

#endif /* !FORWARDMOBTYPE_HPP_ */
