#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include "Renderer.hpp"

class   Camera
{
public:
    Camera(Renderer *);
    ~Camera();

public:
    gu::Rect<float>     getFrustrum() const;
    void                setFrustrum(gu::Rect<float> const& frustrum);

private:
    Renderer            *_renderer;
};

#endif // !CAMERA_HPP_
