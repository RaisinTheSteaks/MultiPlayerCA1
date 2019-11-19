#include "Ship.hpp"
#include "ResourceHolder.hpp"
#include "CategoryID.hpp"

//Used to paint the skin and movement speed of ships
TextureID toTextureID(ShipID type)
{
	switch (type)
	{
	case ShipID::Battleship:
		return TextureID::Battleship;
		break;
	case ShipID::Cruiser:
		return TextureID::Cruiser;
		break;
	case ShipID::Submarine:
		return TextureID::Submarine;
		break;


	default:
		return TextureID::Battleship;
		break;
	}
}

float getForwardSpeed(ShipID type)
{
	switch (type)
	{
	case ShipID::Battleship:
		return 1.0f;
		break;
	case ShipID::Cruiser:
		return 1.7f;
		break;
	case ShipID::Submarine:
		return 1.2f;
		break;
		
	default:
		return 0.0f;
		break;
		
	}
}

float getTurnSpeed(ShipID type)
{
	switch (type)
	{
	case ShipID::Battleship:
		return 0.7f;
		break;
	case ShipID::Cruiser:
		return 1.5f;
		break;
	case ShipID::Submarine:
		return 1.5;
		break;

	default:
		return 0.0f;
		break;
	}
}

Ship::Ship(ShipID type, const TextureHolder & textures) : 
	mType(type), 
	mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

unsigned int Ship::getCategory() const
{
	switch (mType)
	{
	case ShipID::Battleship:
		return static_cast<int>(CategoryID::PlayerShip);
	case ShipID::Cruiser:
		return static_cast<int>(CategoryID::PlayerShip);
	case ShipID::Submarine:
		return static_cast<int>(CategoryID::PlayerShip);

	default:
		return static_cast<int>(CategoryID::EnemyAircraft);
	}
}

void Ship::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
