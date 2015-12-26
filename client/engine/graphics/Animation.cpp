#include "Animation.hpp"
#include "GameObject.hpp"
#include "SpriteRenderer.hpp"

Animation::Animation()
{}

Animation::Animation(unsigned int _id,
                     std::string const& _name,
                     unsigned int frames,
                     double duration,
                     bool loop) :
    Behaviour(_id, _name),
    _currentFrame(0),
    _frames(frames),
    _elapsedTime(0.0),
    _duration(duration),
    _loop(loop),
    _playing(true)
{
    _enabled = true;
}

Animation::Animation(Animation const& other) :
    Behaviour(other)
{
    _enabled = other.isEnabled();
}

Animation::Animation(Animation&& other) :
    Animation(other)
{
    swap(other);
}

Animation& Animation::operator=(Animation other)
{
    swap(other);

    return (*this);
}

Animation::~Animation()
{}

bool Animation::operator==(Animation const& other)
{
    return (Behaviour::operator==(other));
}

bool Animation::operator!=(Animation const& other)
{
    return (!Animation::operator==(other));
}

void Animation::swap(Animation& other)
{
    using std::swap;

    swap(_enabled, other._enabled);
}

namespace std
{
    template<>
    void swap<Animation>(Animation& a, Animation& b)
    {
        a.swap(b);
    }
}

void Animation::update(double elapsedTime)
{
    SpriteRenderer *sr = static_cast<GameObject *>(parent())->getComponent<SpriteRenderer>();
    if (sr == nullptr)
        return;

    auto rect = sr->getRect();
    _elapsedTime += elapsedTime;
    if (_elapsedTime >= (_duration / _frames) * (_currentFrame + 1))
    {
        _currentFrame = _elapsedTime / (_duration / _frames);
        rect.x = _currentFrame * rect.w;
    }
    if (_currentFrame >= _frames)
    {
        while (_elapsedTime > _duration)
            _elapsedTime -= _duration;
        if (!_loop)
        {
            rect.x = 0;
            _playing = false;
            _currentFrame = 0;
        }
        else
        {
            _currentFrame %= _frames;
            rect.x = _currentFrame * rect.w;
        }
    }
    sr->setRect(rect);
}

void    Animation::play()
{
    _playing = true;
    _elapsedTime = 0;
}

void    Animation::pause()
{
    _playing = false;
}

void    Animation::stop()
{
    _playing = false;
    _elapsedTime = 0.0;
    _currentFrame = 0;
}

void    Animation::resume()
{
    _playing = true;
}

unsigned int    Animation::getFrames() const
{
    return _frames;
}

void            Animation::setFrames(unsigned int f)
{
    _frames = f;
}

double          Animation::getDuration() const
{
    return _duration;
}

void            Animation::setDuration(double d)
{
    _duration = d;
}

bool            Animation::getLoop() const
{
    return _loop;
}

void            Animation::setLoop(bool l)
{
    _loop = l;
}
