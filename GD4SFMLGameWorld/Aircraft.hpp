#pragma once
#include "Entity.hpp"
#include "AircraftID.hpp"
#include "ResourceIdentifiers.hpp"

class Aircraft : public Entity
{
public:
	Aircraft(AircraftID type, const TextureHolder& textures);
	virtual unsigned int getCategory() const;

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	AircraftID mType;
	sf::Sprite mSprite;
};