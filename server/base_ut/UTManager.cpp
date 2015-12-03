#include <stdexcept>
#include <iostream>
#include "UTManager.hpp"

namespace UnitTesting
{
    /*
    ** Constructor/Destructor
    */
    UTManager::UTManager()
    {
    }

    UTManager::~UTManager()
    {
    }

    /*
    ** Public member functions
    */
    void              UTManager::run(std::vector<std::string> const& groups)
    {
        if (groups.empty())
        {
            for (auto&& group : _groups)
                group.second->run();
            return ;
        }
        for (auto&& name: groups)
        {
            try {
                _groups.at(name)->run();
            } catch (std::out_of_range const&) {
                std::cerr << "Group test '" << name << "' does not exist" << std::endl;
            }
        }
    }

    void              UTManager::add(ABaseUT* group)
    {
        _groups[group->getName()] = std::unique_ptr<ABaseUT>(group);
    }

    void              UTManager::remove(std::string const& name)
    {
        _groups.erase(name);
    }
}
