#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include "Behaviour.hpp"

class GUIManager : public Behaviour
{
public:
  GUIManager(unsigned int id);
  virtual ~GUIManager();

private:
  unsigned int	_id;
};

#endif // !GUIMANAGER_HPP_
