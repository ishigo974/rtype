#ifndef SYSTEMMANAGER_HPP_
# define SYSTEMMANAGER_HPP_

# include <memory>
# include <string>
# include <unordered_map>
# include "ASystem.hpp"
# include "IStringable.hpp"

namespace ECS
{
    class SystemManager : public IStringable
    {
    public:
        typedef std::unique_ptr<SystemManager>          UniqueSmPtr;
        typedef std::unique_ptr<ASystem>                UniqueSystemPtr;
        typedef std::unordered_map<std::string,
                                    UniqueSystemPtr>    SystemMap;

    protected:
        SystemManager();

    public:
        virtual ~SystemManager();

    private:
        SystemManager(SystemManager const& other) = delete;
        SystemManager&          operator=(SystemManager const& other) = delete;

    public:
        static SystemManager&   getInstance();

    public:
        void                processAll() const;
        void                process(std::string const& name) const;
        void                process(ComponentMask mask) const;
        void                update(ComponentMask mask) const;

        template <typename SystemType>
        SystemType*         get(std::string const& name)
        {
            return dynamic_cast<SystemType*>(_systems.at(name).get());
        }

    public:
        void                registerSystem(UniqueSystemPtr system);
        bool                removeSystem(std::string const& name);

    public:
        std::string         toString() const;

    protected:
        SystemMap           _systems;

    protected:
        static UniqueSmPtr  instance;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
