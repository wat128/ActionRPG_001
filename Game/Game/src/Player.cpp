#include "Player.h"

Vec2 offset;
Vec2 moved;
Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _ability(value)
{}

bool Player::attack()
{
	return false;
}

bool Player::guard()
{
	return false;
}

bool Player::skill()
{
	return false;
}

bool Player::talk()
{
	return false;
}

bool Player::recieveDamage()
{
	return false;
}

bool Player::move()
{
	offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() *(KeyShift.pressed() ? 0.5 : 1.0));
	
	// --- Õ“Ë”»’èˆ—À‘•—\’è --- //

	_actor.setPos(_actor.pos + offset);
	return true;
}
void Player::update()
{
	move();
}

void Player::draw()
{
	RectF(_actor.pos, 100, 100)(_texture).draw();
}