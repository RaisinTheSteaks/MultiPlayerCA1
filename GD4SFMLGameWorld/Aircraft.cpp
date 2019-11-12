#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "CategoryID.hpp"

TextureID toTextureID(AircraftID type)
{
	switch (type)
	{
	case AircraftID::Eagle:
		return TextureID::Eagle;

	case AircraftID::Raptor:
		return TextureID::Raptor;
	}
	return TextureID::Eagle;
}

Aircraft::Aircraft(AircraftID type, const TextureHolder& textures) : mType(type), mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case AircraftID::Eagle:
		return static_cast<int>(CategoryID::PlayerAircraft);

	default:
		return static_cast<int>(CategoryID::EnemyAircraft);
	}
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
