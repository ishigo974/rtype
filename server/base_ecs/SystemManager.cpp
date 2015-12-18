#include "SystemManager.hpp"
#include "ValueError.hpp"

namespace ECS
{
    /*
    ** Static variables
    */
    SystemManager::UniqueSmPtr      SystemManager::instance = nullptr;

    /*
    ** Constructor/Destructor
    */
    SystemManager::SystemManager()
    {
    }

    SystemManager::~SystemManager()
    {
    }

    /*
    ** Static functions
    */
    SystemManager&       SystemManager::getInstance()
    {
        if (SystemManager::instance == nullptr)
            SystemManager::instance =
                std::unique_ptr<SystemManager>(new SystemManager());
        return *SystemManager::instance;
    }

    /*
    ** Public member functions
    */
    void      SystemManager::processAll() const
    {
        for (auto& sys : _systems)
        {
            if (sys.second->shouldAutoUpdate())
                sys.second->update();
            if (sys.second->shouldAutoProcess())
                sys.second->process();
        }
    }

    void      SystemManager::process(std::string const& name) const
    {
        auto    it = _systems.find(name);

        if (it == _systems.end())
            throw Exception::ValueError("System '" + name + "' does not exist");
        it->second->process();
    }

    void      SystemManager::process(ComponentMask mask) const
    {
        for (auto& sys : _systems)
        {
            if ((sys.second->getMask() & mask) == mask)
                sys.second->process();
        }
    }

    void      SystemManager::update(ComponentMask mask) const
    {
        for (auto& sys : _systems)
        {
            if ((sys.second->getMask() & mask) == mask)
                sys.second->update();
        }
    }

    void      SystemManager::registerSystem(std::unique_ptr<ASystem> system)
    {
        _systems[system->getName()] = std::move(system);
    }

    bool      SystemManager::removeSystem(std::string const& name)
    {
        return _systems.erase(name) > 0;
    }

    std::string     SystemManager::toString() const
    {
        std::string   res = "SystemManager {";

        for (auto& sys : _systems)
            res += "\n\t" + sys.second->getName();
        res += "\n}";
        return res;
    }
}
