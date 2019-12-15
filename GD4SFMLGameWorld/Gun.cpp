#include "Gun.hpp"
#include "ResourceHolder.hpp"
#include "CategoryID.hpp"

TextureID  toTextureID(ShipID type)
{
	switch (type)
	{
	case ShipID::Battleship:
		return TextureID::BattleshipGun;
	case ShipID::Cruiser:
		return TextureID::CruiserGun;
	case ShipID::Submarine:
		return TextureID::SubmarineGun;
	}
}


Gun::Gun(ShipID type, const TextureHolder& textures) :
	Entity(0)
	,mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Gun::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
