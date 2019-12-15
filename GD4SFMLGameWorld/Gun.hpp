#pragma once
#include "Entity.hpp"
#include "ShipID.hpp"
#include "ResourceIdentifiers.hpp"

class Gun : public Entity
{
public:
	Gun(ShipID type,const TextureHolder& textures);
	
	
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	//Different ship categories have different gun textures
	ShipID mType;
	sf::Sprite mSprite;

};