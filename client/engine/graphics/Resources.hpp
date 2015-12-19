#ifndef RESOURCES_HPP_
# define RESOURCES_HPP_

# include <map>
# include <string>
# include <SFML/Graphics.hpp>

class Resources
{
public:
    static std::string const resFile;

public:
    Resources();
    ~Resources();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

public:
    const sf::Texture* getTexture(const std::string&) const;
    const sf::Texture* operator[](const std::string&) const;
    bool addTexture(std::string const& name,
                    std::string const& path,
                    bool repeated = false);

private:
    std::map<const std::string, sf::Texture *> _textures;
};

#endif //! RESOURCES_HPP_
