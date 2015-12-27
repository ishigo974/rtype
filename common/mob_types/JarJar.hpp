#ifndef JARJAR_HPP_
# define JARJAR_HPP_

# include <string>
# include "IMobType.hpp"

namespace RType
{
    namespace MobType
    {
        class JarJar : public IMobType
        {
        public:
            JarJar();
            virtual ~JarJar();

        public:
            JarJar(JarJar const& other);
            JarJar&               operator=(JarJar const& other);

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

#endif /* !JARJAR_HPP_ */
