#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "LayerID.hpp"
#include "CommandQueue.hpp"

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <array>


//Forward declaration
//namespace sf
//{
//	class RenderWindow;
//}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();
	CommandQueue& getCommandQueue();

private:
	void loadTextures();
	void buildScene();
	void adaptPlayerPosition();
	void adaptPlayerVelocity();

private:
	sf::RenderWindow& mWindow;
	sf::View mCamera;
	TextureHolder mTextures;

	SceneNode mSceneGraph;
	std::array<SceneNode*, static_cast<int>(LayerID::LayerCount)> mSceneLayers;
	CommandQueue mCommandQueue;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};