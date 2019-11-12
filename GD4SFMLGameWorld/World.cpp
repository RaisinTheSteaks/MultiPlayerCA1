#include "World.hpp"

World::World(sf::RenderWindow& window) : mWindow(window), mCamera(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, mCamera.getSize().x, 2000.f), mSpawnPosition(mCamera.getSize().x/2.f, mWorldBounds.height - mCamera.getSize().y/2.f), mScrollSpeed(-50.f), mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	//Prepare the Camera
	mCamera.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	//Scroll the world
	mCamera.move(0.f, mScrollSpeed * dt.asSeconds());

	mPlayerAircraft->setVelocity(0.f, 0.f);

	//Forward commands to the scene graph, adapt velocity
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}
	adaptPlayerVelocity();
	//Regular update, adapt position if outisde view	
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mCamera);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(TextureID::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(TextureID::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(TextureID::Desert, "Media/Textures/Desert.png");
}

void World::buildScene()
{
	//Initialize the different
	for (std::size_t i = 0; i < static_cast<int>(LayerID::LayerCount); ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	//Prepare the tiled background
	sf::Texture& texture = mTextures.get(TextureID::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	//Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[static_cast<int>(LayerID::Background)]->attachChild(std::move(backgroundSprite));

	//Add players aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(AircraftID::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[static_cast<int>(LayerID::Air)]->attachChild(std::move(leader));

	//Add the two escorts
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(AircraftID::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftID::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
	
}

void World::adaptPlayerPosition()
{
	//Keep the player's position inside the screen bounds
	sf::FloatRect viewBounds(mCamera.getCenter() - mCamera.getSize() / 2.f, mCamera.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	//Don't give the player an advantage of they move diagonally
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//If moving diagonally, reduce the velocity by root 2
	if (velocity.x != 0 && velocity.y != 0)
	{
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	}
	//add the scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}
