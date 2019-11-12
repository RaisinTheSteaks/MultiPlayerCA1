#pragma once
#include <sstream>
namespace sf
{
	class Sprite;
	class Text;
}

template<typename T>
std::string toString(const T& value);

void centreOrigin(sf::Sprite& sprite);
void centreOrigin(sf::Text& text);

#include "Utility.inl"