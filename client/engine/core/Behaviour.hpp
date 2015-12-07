#ifndef RTYPE_BEHAVIOUR_HPP
#define RTYPE_BEHAVIOUR_HPP

# include "Component.hpp"
# include "RTypes.hpp"

class Behaviour : public Component
{
public:
  static const unsigned int Mask = 3;

public:
  Behaviour();
  Behaviour(unsigned int _id, std::string const& _name);
  Behaviour(Behaviour const& other);
  Behaviour(Behaviour&& other);
  Behaviour& operator=(Behaviour other);
  virtual ~Behaviour();

  bool operator==(Behaviour const& other);
  bool operator!=(Behaviour const& other);

  virtual void update(double elapsedTime);

  bool isEnabled() const;
  void setEnabled(bool _enabled);

  virtual RTypes::my_uint16_t getMask() const;
  void swap(Behaviour& other);

protected:
  bool _enabled;
};


#endif //RTYPE_BEHAVIOUR_HPP
