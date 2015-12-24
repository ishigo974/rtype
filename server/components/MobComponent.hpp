#ifndef MOBCOMPONENT_HPP_
# define MOBCOMPONENT_HPP_

# include <string>
# include "ComponentMask.hpp"
# include "IBehaviour.hpp"
# include "IMobType.hpp"

namespace RType
{
    namespace Component
    {
        class Mob : public ECS::IBehaviour
        {
        public:
            Mob();
            Mob(MobType::IMobType const* type);
            virtual ~Mob();

        public:
            Mob(Mob const& other);
            Mob&           operator=(Mob const& other);

        public:
            void            init(MobType::IMobType const* type);
            virtual void    update();

        public:
            void            addLives(unsigned int nb = 1);
            void            removeLives(unsigned int nb = 1);

        public:
            unsigned int                    getId() const;
            std::string const&              getMobName() const;
            unsigned int                    getLives() const;
            unsigned int                    getScoreValue() const;
            std::string const&              getSpriteFilePath() const;
            MobType::MovePattern const&     getMovePattern() const;

        public:
            virtual std::string         getName() const;
            virtual ECS::ComponentMask  getMask() const;
            virtual ECS::IComponent*    clone() const;
            virtual void                clear();
            virtual std::string         toString() const;

        public:
            static const ECS::ComponentMask     mask;

        protected:
            unsigned int            _id;
            std::string             _name;
            unsigned int            _lives;
            unsigned int            _scoreValue;
            std::string             _spriteFilePath;
            MobType::MovePattern    _movePattern;
            int                     _state;
        };
    }
}

#endif /* !MOBCOMPONENT_HPP_ */
