#ifndef RESOURCES_HPP_
# define RESOURCES_HPP_

# include <map>
# include <SFML/Graphics.hpp>

class Resources
{
public:
    Resources();
    ~Resources();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

public:
    const sf::Texture* getTexture(const std::string&) const;
    const sf::Texture* operator[](const std::string&) const;
    bool addTexture(const std::string& path, bool repeated = false);

private:
    std::map<const std::string, sf::Texture *> _textures;
};

#endif //! RESOURCES_HPP_