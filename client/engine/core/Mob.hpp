#ifndef MOB_HPP_
# define MOB_HPP_

# include "Behaviour.hpp"
# include "Transform.hpp"
# include "IMobType.hpp"
# include "REnums.hpp"
# include "GameObject.hpp"

class Mob : public Behaviour
{
public:
    Mob();
    Mob(unsigned int id, std::string const& name, RType::MobType::IMobType const* mobtype = nullptr);
    virtual ~Mob();

public:
    Mob(Mob const& other);
    Mob(Mob&& other);
    Mob& operator=(Mob other);

public:
    bool operator==(Mob const& other);
    bool operator!=(Mob const& other);

public:
    void            swap(Mob& other);
    virtual void    update(double);
    virtual bool    handleMessage(Collider *o);

public:
    void            init(RType::MobType::IMobType const* mobtype);
    void            addLives(unsigned int nb = 1);
    void            removeLives(unsigned int nb = 1);

public:
    unsigned int                    getMobId() const;
    std::string const&              getMobName() const;
    unsigned int                    getLives() const;
    unsigned int                    getScoreValue() const;
    std::string const&              getSpriteFilePath() const;
    RType::MobType::MovePattern const&     getMovePattern() const;
    bool                            getAvailable() const;

    void    setName(std::string const & name);
    void    setLives(unsigned int lives);
    void    setScoreValue(unsigned int scoreValue);
    void    setSpriteFilePath(std::string const& spriteFilePath);
    void    setMovePattern(RType::MobType::MovePattern const& movePattern);
    void    setAvailable(bool a);
    void    setX(float x);
    void    setY(float y);

    std::string                     toString() const;
    virtual RTypes::my_uint16_t      getMask() const;
    static const RTypes::my_uint16_t Mask      = ComponentMask::MobMask;

protected:
    void                    move(double elapsedTime);

protected:
    unsigned int            _id;
    std::string             _name;
    unsigned int            _lives;
    unsigned int            _scoreValue;
    std::string             _spriteFilePath;
    RType::MobType::MovePattern    _movePattern;
    Transform*              _transform;
    GameObject*              _parent;
    bool                     _available;
};

#endif /* !MOB_HPP_ */
