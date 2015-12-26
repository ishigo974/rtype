#ifndef     ANIMATION_HPP_
# define    ANIMATION_HPP_

# include   "Behaviour.hpp"

class       Animation : public Behaviour
{
public:
    Animation();
    Animation(unsigned int _id, std::string const& _name, unsigned int frames,
              double duration, bool loop);
    Animation(Animation const& other);
    Animation(Animation&& other);
    Animation& operator=(Animation other);
    virtual ~Animation();

    bool operator==(Animation const& other);
    bool operator!=(Animation const& other);

    void swap(Animation& other);

    virtual void update(double elapsedTime);

    void    play();
    void    pause();
    void    stop();
    void    resume();

private:
    unsigned int    _currentFrame;
    unsigned int    _frames;
    double          _elapsedTime;
    double          _duration;
    bool            _loop;
    bool            _playing;
};

#endif      // !ANIMATION_HPP_
