#pragma once
#include "GameObject.h"
#include "Ability.h"
#include "Skill.h"

class Skill;

class Player : public GameObject
{
public:
	Player();
	Player(const int32& value, const Vec2& pos);
	void skill();
	void recieveDamage();
	void talk();
	void move() override;
	void update() override;
	void draw() override;
private:
	Ability _ability;
	Array<std::unique_ptr<Skill>> _skills;
	enum class Motion {
		Excutable,
		Executing_Skill1,
		Executing_Skill2,
		Executing_Skill3,
		Talking,
	}_motion;
};

