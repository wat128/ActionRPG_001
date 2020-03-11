#pragma once
#include "GameObject.h"
#include "Ability.h"

enum class ActionPatternList;

class Battler : public GameObject
{
public:
	Battler();
	Battler(const int32& value, const Vec2& pos);
	bool attack();
	bool guard();
	bool skill();
	bool recieveDamage();
	bool move() override;
	void update() override;
	void draw() override;
private:
	const bool _isEnemy;
	ActionPatternList _actionPattern;
	//Ability _ability;

};

enum class ActionPatternList {
	
	enemyUnset = 0,
	enemyPositive,
	enemyNegative,
	
	friendUnset = 100,
	friendPositive,
	friendNegative
};