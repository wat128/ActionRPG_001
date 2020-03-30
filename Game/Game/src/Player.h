#pragma once
#include "GameObject.h"
#include "Ability.h"

class Player : public GameObject
{
public:
	Player();
	Player(const int32& value, const Vec2& pos);
	bool attack();
	bool guard();
	bool skill();
	bool recieveDamage();
	bool talk();
	bool move() override;
	void update() override;
	void draw() override;
private:
	Ability _ability;
	TiledGameObjectTexture _tiledTexture;
};

