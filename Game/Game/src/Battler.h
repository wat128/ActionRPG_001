#pragma once
#include "GameObject.h"
#include "Ability.h"

enum class ActionPatternList;

class Battler : public GameObject
{
public:
	Battler();
	Battler(const int32& value, const Vec2& pos);
	void attack();
	void guard();
	void skill();
	void recieveDamage();
	void move() override;
	void update() override;
	void draw() override;
private:
	Ability _ability;
	TiledGameObjectTexture _tiledTexture;
	const bool _isEnemy;
	ActionPatternList _actionPattern;
};

enum class ActionPatternList {
	
	enemyUnset = 0,
	enemyPositive,
	enemyNegative,
	
	friendUnset = 100,
	friendPositive,
	friendNegative
};