#pragma once
#include "Entity.hpp"
#include "ShipID.hpp"
#include "ResourceIdentifiers.hpp"

class Ship :public Entity
{
public:
	Ship(ShipID type, const TextureHolder& textures);
	virtual unsigned int getCategory() const;

private: 
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
private: 
	//Get it.... because ships 'float'
	float mForwardSpeed;
	float mTurnSpeed;
	ShipID mType;
	sf::Sprite mSprite;
};