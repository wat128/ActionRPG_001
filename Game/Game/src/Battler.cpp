#include "Battler.h"
#include "FieldReferee.h"

Battler::Battler()
	: _isEnemy(false)
{}

Battler::Battler(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _ability(value)
	, _isEnemy(true) // �b��
{}

void Battler::skill()
{

}

void Battler::recieveDamage()
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

	Vec2 offset = Vec2(R - L, D - U)
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() * (KeyShift.pressed() ? 0.5 : 1.0));

	const RectF movedCollision(						// �ړ���̏Փ˔���p
		_actor.pos.x - _actor.w / 2 + offset.x
		, _actor.pos.y - _actor.h + offset.y
		, _actor.w, _actor.h);

	bool ret = FieldReferee::getInstance().isCollision(movedCollision , this);
	if (!ret)
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
}

void Battler::draw()
{
	_tiledTexture.getTile()
		.draw(_actor.pos.x - _tiledTexture.getTile().size.x / 2		// ������_actor.pos�Ƃ��邽�߁A�`��ʒu����
			, _actor.pos.y - _tiledTexture.getTile().size.y);
	RectF(_actor.pos.x - _actor.w / 2, _actor.pos.y - _actor.h, _actor.w, _actor.h).drawFrame();	// �e�X�g�p�F
	Circle(_actor.pos, 2).draw(Palette::Red);
}