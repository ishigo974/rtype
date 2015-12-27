#include <iostream>
#include "Resources.hpp"

std::string const Resources::resFile = "../client/res/textures.json";

Resources::Resources()
{
	this->_textures["MissingTexture"] = new sf::Texture();
	if (!this->_textures["MissingTexture"]->
                                    loadFromFile("../client/res/MissingTexture.png"))
		throw std::runtime_error("MissingTexture not found");
	else
		this->_textures["MissingTexture"]->setRepeated(true);
}

Resources::~Resources()
{
	for (auto it = this->_textures.begin();
	    it != this->_textures.end();
		++it)
	{
		delete it->second;
	}
}

const sf::Texture* Resources::getTexture(const std::string& name) const
{
    try
    {
        return this->_textures.at(name);
    }
    catch (std::out_of_range& e)
    {
        std::cerr << "Can't find texture" << std::endl;
        return this->_textures.at("MissingTexture");
    }
}

const sf::Texture* Resources::operator[](const std::string& name) const
{
	return this->getTexture(name);
}

bool    Resources::addTexture(std::string const& name,
                            std::string const& path,
                            bool repeated)
{
  this->_textures[name] = new sf::Texture();
  if (!this->_textures[name]->loadFromFile(path))
    {
      delete this->_textures[name];
      this->_textures.erase(name);
      return false;
    }
  this->_textures[name]->setRepeated(repeated);
  return true;
}
