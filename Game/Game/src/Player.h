#pragma once
#include "GameObject.h"
#include "Ability.h"

class Player : public GameObject
{
public:
	Player();
	Player(const int32& value, const Vec2& pos);
	void attack();
	void guard();
	void skill();
	void recieveDamage();
	void talk();
	void move() override;
	void update() override;
	void draw() override;
private:
	Ability _ability;
	TiledGameObjectTexture _tiledTexture;
	enum class Motion {
		Excutable,
		Attacking,
		Guarding,
		Talking,
		Activating_Skill,
	}_motion;
};

