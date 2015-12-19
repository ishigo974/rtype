#ifndef ASYSTEM_HPP_
# define ASYSTEM_HPP_

# include <vector>
# include "Entity.hpp"
# include "ComponentMask.hpp"
# include "IStringable.hpp"

namespace ECS
{
    class ASystem : public IStringable
    {
    public:
        ASystem();
        virtual ~ASystem();

    private:
        ASystem(ASystem const& other) = delete;
        ASystem&                operator=(ASystem const& other) = delete;

    public:
        void                    process();

    public:
        virtual void            update() = 0;
        virtual void            processEntity(Entity& e) = 0;
        virtual ComponentMask   getMask() const = 0;
        virtual std::string     getName() const = 0;
        virtual bool            shouldAutoUpdate() const = 0;
        virtual bool            shouldAutoProcess() const = 0;
    };
}

#endif /* !ASYSTEM_HPP_ */
