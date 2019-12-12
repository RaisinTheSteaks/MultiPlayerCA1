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
	//mCamera.move(0.f, mScrollSpeed * dt.asSeconds());

	mPlayer1Ship->setVelocity(0.f, 0.f);

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
	//Assets sourced from:
	//https://opengameart.org/content/water
	mTextures.load(TextureID::Ocean, "Media/Textures/Ocean/Water1.png");
	//https://opengameart.org/content/sea-warfare-set-ships-and-more
	mTextures.load(TextureID::Battleship, "Media/Textures/Battleship/ShipBattleshipHullTest.png");
	mTextures.load(TextureID::Island, "Media/Textures/Island/Island.png");

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
	sf::Texture& texture = mTextures.get(TextureID::Ocean);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	sf::Texture& island = mTextures.get(TextureID::Island);
	sf::IntRect islandRect(0, 0, 200, 500);

	//Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[static_cast<int>(LayerID::Background)]->attachChild(std::move(backgroundSprite));

	////Add player ship
	std::unique_ptr<Ship> firstShip(new Ship(ShipID::Battleship, mTextures));
	mPlayer1Ship = firstShip.get();
	mPlayer1Ship->setPosition(mSpawnPosition);
	mPlayer1Ship->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[static_cast<int>(LayerID::WaterSurface)]->attachChild(std::move(firstShip));



	//adding island(s) 
	// will add collision later for islands
	std::unique_ptr<SpriteNode> islandSprite(new SpriteNode(island, textureRect));
	islandSprite->setPosition(mCamera.getSize().x / 4.f, mWorldBounds.height - mCamera.getSize().y / 3.f);
	mSceneLayers[static_cast<int>(LayerID::WaterSurface)]->attachChild(std::move(islandSprite));


	std::unique_ptr<SpriteNode> islandSprite1(new SpriteNode(island, textureRect));
	islandSprite1->setPosition(mCamera.getSize().x / 5.f, mWorldBounds.height - mCamera.getSize().y / 1.5f);
	mSceneLayers[static_cast<int>(LayerID::WaterSurface)]->attachChild(std::move(islandSprite1));



	std::unique_ptr<SpriteNode> islandSprite2(new SpriteNode(island, textureRect));
	islandSprite2->setPosition(mCamera.getSize().x / 1.5f, mWorldBounds.height - mCamera.getSize().y / 1.7f);
	mSceneLayers[static_cast<int>(LayerID::WaterSurface)]->attachChild(std::move(islandSprite2));






	////ForwardGun
	////[TODO] Make gun class
	//std::unique_ptr<Gun> player1ForwardGun(new Gun(GunID::Raptor, mTextures));
	//player1ForwardGun->setPosition(80.f, 50.f);
	//mPlayer1Ship->attachChild(std::move(player1ForwardGun));


	//Vector2 offset = new Vector2(0, 0);
	//firstShip->setPosition(mSpawnPosition );


	////Add players aircraft
	//std::unique_ptr<Aircraft> leader(new Aircraft(AircraftID::Eagle, mTextures));
	//mPlayerAircraft = leader.get();
	//mPlayerAircraft->setPosition(mSpawnPosition);
	//mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	//mSceneLayers[static_cast<int>(LayerID::LowerAir)]->attachChild(std::move(leader));

	////Add the two escorts
	//std::unique_ptr<Aircraft> leftEscort(new Aircraft(AircraftID::Raptor, mTextures));
	//leftEscort->setPosition(-80.f, 50.f);
	//mPlayerAircraft->attachChild(std::move(leftEscort));

	//std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftID::Raptor, mTextures));
	//rightEscort->setPosition(80.f, 50.f);
	//mPlayerAircraft->attachChild(std::move(rightEscort));
	
}

void World::adaptPlayerPosition()
{
	//Keep the player's position inside the screen bounds
	sf::FloatRect viewBounds(mCamera.getCenter() - mCamera.getSize() / 2.f, mCamera.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayer1Ship->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayer1Ship->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	//Don't give the player an advantage of they move diagonally
	sf::Vector2f velocity = mPlayer1Ship->getVelocity();

	//If moving diagonally, reduce the velocity by root 2
	if (velocity.x != 0 && velocity.y != 0)
	{
		mPlayer1Ship->setVelocity(velocity / std::sqrt(2.f));
	}
	//add the scrolling velocity
	//mPlayer1Ship->accelerate(0.f, mScrollSpeed);
}
