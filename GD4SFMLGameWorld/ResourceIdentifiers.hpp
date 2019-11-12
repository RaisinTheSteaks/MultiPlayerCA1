#pragma once
#include "TextureID.hpp"
#include "FontID.hpp"

namespace sf
{
	class Texture;
	class Font;
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
typedef ResourceHolder<sf::Font, FontID> FontHolder;