#include "Player.h"
#include "FieldManager.h"	// �e�X�g�p�F

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _tiledTexture(
		_texture,
		ObjData::getInstance()->TextureCharaNum(value),
		ObjData::getInstance()->TextureTileXYNum(value),
		ObjData::getInstance()->TextureTileRegionWH(value),
		0.2) // �b��(�A�j���[�V�������[�g)
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
	Vec2 offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() *(KeyShift.pressed() ? 0.5 : 1.0));

	// �e�X�g�p�F�b��Ńt�B�[���h�N���X�𒼐ڃR�[�����Ă����B�����ꋴ�n���p�̃N���X���쐬����B // 
	bool ret = FieldManager::getInstance()->getCurrentField().withinCollision(_actor.pos + offset);
	if(!ret)
		_actor.setPos(_actor.pos + offset);

	_tiledTexture.update(offset);

	return true;
}
void Player::update()
{
	move();
}

void Player::draw()
{
	_tiledTexture.getTile().drawAt(_actor.pos);
	RectF(Arg::center(_actor.pos), _actor.w, _actor.h).drawFrame();	// �e�X�g�p�F
}