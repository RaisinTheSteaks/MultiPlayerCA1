#pragma once

#include "ResourceIdentifiers.hpp"
#include "TextureID.hpp"
#include "ActionID.hpp"
#include "CategoryID.hpp"


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <functional>
#include <map>

class Ship;

struct PlayerData
{
	std::map<sf::Keyboard::Key, ActionID> mKeyBinding;
	CategoryID categoryID;
};

struct Direction
{
	Direction(float angle, float distance)
		:angle(angle), distance(distance)
	{}

	float angle;
	float distance;
};

struct ShipData
{
	int hitpoints;
	float speed;
	float turnSpeed;
	TextureID texture;
	sf::IntRect textureRect;
	sf::Time fireInterval;
	std::vector<Direction> directions;
	bool hasRollAnimation;
};

struct ProjectileData
{
	int damage;
	float speed;
	TextureID texture;
	sf::IntRect textureRect;
};

struct PickupData
{
	std::function<void(Ship&)> action;
	TextureID texture;
	sf::IntRect textureRect;
};

struct ParticleData
{
	sf::Color color;
	sf::Time lifetime;
};

std::vector<PlayerData> initializePlayerData();
std::vector<ShipData> initializeShipData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();
std::vector<ParticleData> initializeParticleData();



