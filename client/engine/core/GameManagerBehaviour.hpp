#ifndef GAMEMANAGERBEHAVIOUR_HPP_
# define GAMEMANAGERBEHAVIOUR_HPP_

# include <queue>
# include "Behaviour.hpp"
# include "EntityManager.hpp"
# include "TCPView.hpp"

class GameManagerBehaviour : public Behaviour
{
public:
    GameManagerBehaviour();
    GameManagerBehaviour(unsigned int _id, std::string const& _name);
    virtual ~GameManagerBehaviour();

    GameManagerBehaviour(GameManagerBehaviour const& other);
    GameManagerBehaviour(GameManagerBehaviour&& other);
    GameManagerBehaviour& operator=(GameManagerBehaviour other);
    void            swap(GameManagerBehaviour& other);

    bool operator==(GameManagerBehaviour const& other);
    bool operator!=(GameManagerBehaviour const& other);
    virtual RTypes::my_uint16_t      getMask() const;
    static const RTypes::my_uint16_t Mask      = ComponentMask::GMBehaviourMask;

    virtual void    update(double elapsed);

protected:
    std::string    toString() const;

protected:
};

#endif /* !GAMEMANAGERBEHAVIOUR_HPP_ /*/
