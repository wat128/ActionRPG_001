#include "Battler.h"

Battler::Battler()
	: _isEnemy(false)
{}

Battler::Battler(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _isEnemy(false)
{}

bool Battler::attack()
{
	return false;
}

bool Battler::guard()
{
	return false;
}

bool Battler::skill()
{
	return false;
}

bool Battler::recieveDamage()
{
	return false;
}

bool Battler::move()
{
	return false;
}
void Battler::update()
{
}

void Battler::draw()
{
}