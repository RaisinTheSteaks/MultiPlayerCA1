#include "Ship.hpp"

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

Ship::Ship(ShipID type, const TextureHolder & textures)
{
}

unsigned int Ship::getCategory() const
{
	return 0;
}

void Ship::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
}
