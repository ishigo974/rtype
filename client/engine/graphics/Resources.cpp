#include <iostream>
#include <stdexcept>
#include "Resources.hpp"

Resources::Resources()
{
	this->_textures["MissingTexture"] = sf::Texture();
	if (! this->_textures["MissingTexture"].loadFromFile("res/MissingTexture.png"))
		throw std::runtime_error("res/MissingTexture.png not found");
	this->_textures["MissingTexture"].setRepeated(true);
}

const	sf::Texture &Resources::getTexture(const std::string & path) const
{
	try
	{
		return this->_textures.at(path);
	}
	catch (std::out_of_range &e)
	{
		std::cerr << e.what() << std::endl;
		return this->_textures.at("MissingTexture");
	}
}

bool	Resources::addTexture(const std::string & path, bool repeated)
{
	this->_textures[path] = sf::Texture();
	if (! this->_textures[path].loadFromFile(path))
	{
		this->_textures.erase(path);
		return false;
	}
	else
		this->_textures[path].setRepeated(repeated);
	return true;
}