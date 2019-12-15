#pragma once

//Entity/SceneNode category, used to dispatch commands
enum class CategoryID
{
	None = 0,
	SceneAirLayer = 1 << 0,
	PlayerShip = 1 << 1,
	Player2Ship = 1 << 2,
	AlliedShip = 1 << 3,
	EnemyShip = 1 << 4,
	Pickup = 1 << 5,
	AlliedProjectile = 1 << 6,
	EnemyProjectile = 1 << 7,
	ParticleSystem = 1 << 8,
	SoundEffect = 1 << 9,

	Ship = PlayerShip | Player2Ship | AlliedShip | EnemyShip,
	Projectile = AlliedProjectile | EnemyProjectile,
};