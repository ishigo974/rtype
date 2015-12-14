#ifndef GUIMANAGER_HPP_
# define GUIMANAGER_HPP_

# include "Component.hpp"

class GUIManager : public Component
{
public:
  GUIManager(unsigned int id);
  virtual ~GUIManager();

private:
  unsigned int	_id;
};

#endif // !GUIMANAGER_HPP_
