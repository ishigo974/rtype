#ifndef UTMANAGER_HPP_
# define UTMANAGER_HPP_

# include <string>
# include <vector>
# include <map>
# include <memory>
# include "ABaseUT.hpp"

namespace UnitTesting
{
  class UTManager
  {
  protected:
    typedef std::map<std::string,
                     std::unique_ptr<ABaseUT> >    UTMap;

  public:
    UTManager();
    virtual ~UTManager();

  private:
    UTManager(UTManager const& other) = delete;
    UTManager&        operator=(UTManager const& other) = delete;

  public:
    void              run(std::vector<std::string> const& groups = {});
    void              add(ABaseUT* group);
    void              remove(std::string const& name);

  protected:
    UTMap             _groups;
  };
}

#endif /* !UTMANAGER_HPP_ */
