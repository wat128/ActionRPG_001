#include "Battler.h"
#include "FieldReferee.h"

Battler::Battler()
	: _isEnemy(false)
{}

Battler::Battler(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _isEnemy(true) // �b��
{}

void Battler::skill()
{

}

void Battler::move()
{
	// �e�X�g�p�F
	int32 L, R, U, D;
	KeyQ.pressed() ?	L = 1 : L = 0;
	KeyR.pressed() ?	R = 1 : R = 0;
	KeyE.pressed() ?	U = 1 : U = 0;
	KeyW.pressed() ?	D = 1 : D = 0;

	double speed;
	if (_ability.agility.current < 500)
		speed = _ability.agility.current;
	else
		speed = 500;

	Vec2 offset = Vec2(R - L, D - U)
		.setLength((Scene::DeltaTime() + 2.5) + speed * 0.003);

	const RectF movedCollision(							// �ړ������ꍇ�̏Փ˔���p
		CollisionForMove().x + offset.x
		, CollisionForMove().y + offset.y
		, _collisionForMoveSize);

	bool ret = false;
	if(_isEnemy)
		ret = FieldReferee::getInstance().canMove(movedCollision, Group::Enemys);
	else
		ret = FieldReferee::getInstance().canMove(movedCollision, Group::Allys);

	if (ret)
		_actor.setPos(_actor.pos + offset);

	if (0 > offset.x)		_direction = Direction::Left;
	else if (0 < offset.x)	_direction = Direction::Right;
	if (0 > offset.y)		_direction = Direction::Up;
	else if (0 < offset.y)	_direction = Direction::Down;

	if (offset.x != 0 || offset.y != 0)
		_tiledTexture.walkAnime(_direction, 0.2);	// �b��(���s�A�j���[�V�������[�g)
}

void Battler::update()
{
	move();

	if (0 < _HurtTime)
		_HurtTime -= Scene::DeltaTime();

	_ability.update();
	_dispPriority = _actor.pos.y;
}

void Battler::draw()
{
	if (0 < _HurtTime) {
		_tiledTexture.getTile()
			.draw(_actor.pos.x - _actor.w / 2
				, _actor.pos.y - _actor.h
				, HURT_COLOR);
	}
	else {
		_tiledTexture.getTile()
			.draw(_actor.pos.x - _actor.w / 2
				, _actor.pos.y - _actor.h);
	}

	_ability.drawBuff(_actor);

	/*----------------------------------------------------------------------------*/
	/*		�e�X�g�p															�@*/
	/*----------------------------------------------------------------------------*/
#if 1
	{
		// �e�X�g�p�F�ړ��p�R���W����
		CollisionForMove().drawFrame();

		// �e�X�g�p�F�x�[�X���W
		Circle(_actor.pos, 2).draw(Palette::Red);

		// �e�X�g�p�F�R���W����
		if (0 == _collisionSize.y)
			Collision<Circle>().drawFrame(0.5, Palette::Orange);
		else
			Collision<RectF>().drawFrame(0.5, Palette::Orange);
	}
#endif
}