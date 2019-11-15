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
	default:
		return ;
		break;
	}
}

float getTurnSpeed(ShipID type)
{

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
