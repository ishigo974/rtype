#include <iostream>
#include "Resources.hpp"

Resources::Resources()
{
	this->_textures["MissingTexture"] = new sf::Texture();
	if (! this->_textures["MissingTexture"]->loadFromFile("MissingTexture.png"))
		throw std::runtime_error("../../res/MissingTexture.png not found");
	//this->_textures["MissingTexture"].setRepeated(true);
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

const sf::Texture* Resources::getTexture(const std::string& path) const
{
    try
    {
        return this->_textures.at(path);
    }
    catch (std::out_of_range& e)
    {
        std::cerr << e.what() << std::endl;
        return this->_textures.at("MissingTexture");
    }
}

const sf::Texture* Resources::operator[](const std::string& path) const
{
	return this->getTexture(path);
}

bool    Resources::addTexture(const std::string& path, bool repeated)
{
    this->_textures[path] = new sf::Texture();
	if (!this->_textures[path]->loadFromFile(path))
	{
		delete this->_textures[path];
		this->_textures.erase(path);
		return false;
	}
	else
		return false;
}
