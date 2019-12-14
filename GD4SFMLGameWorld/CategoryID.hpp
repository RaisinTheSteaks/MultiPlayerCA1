#pragma once

//Entity/SceneNode category, used to dispatch commands
enum class CategoryID
{
	None = 0,
	SceneAirLayer = 1 << 0,
	PlayerShip = 1 << 1,
	AlliedShip = 1 << 2,
	EnemyShip = 1 << 3,
	Pickup = 1 << 4,
	AlliedProjectile = 1 << 5,
	EnemyProjectile = 1 << 6,
	ParticleSystem = 1 << 7,
	SoundEffect = 1 << 8,

	Ship = PlayerShip | AlliedShip | EnemyShip,
	Projectile = AlliedProjectile | EnemyProjectile,
};