#include "Player.h"
#include "FieldManager.h"	// �e�X�g�p�F
#include "FieldReferee.h"

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _tiledTexture(
		_texture,
		ObjData::getInstance().TextureCharaNum(value),
		ObjData::getInstance().TextureTileWH(value),
		ObjData::getInstance().TextureTileXYNum(value),
		ObjData::getInstance().TextureWalkTileXYNum(value),
		ObjData::getInstance().TextureAttackTileXYNum(value))
	, _ability(value)
	, _motion(Motion::Excutable)
{}

void Player::attack()
{
	TiledGameObjectTexture::RunningState ret = _tiledTexture.attackAnime({0.1, 0.07, 0.2}); // �b��(�U���A�j���[�V�������[�g)

	if (TiledGameObjectTexture::RunningState::Continue == ret)
		_motion = Motion::Attacking;
	else if (TiledGameObjectTexture::RunningState::Complete == ret)
		_motion = Motion::Excutable;
}

void Player::guard()
{

}

void Player::skill()
{

}

void Player::talk()
{

}

void Player::recieveDamage()
{

}

void Player::move()
{
	Vec2 offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() *(KeyShift.pressed() ? 0.5 : 1.0));

	const RectF movedCollision(						// �ړ���̏Փ˔���p
		_actor.pos.x - _actor.w / 2 + offset.x
		, _actor.pos.y - _actor.h + offset.y
		, _actor.w, _actor.h);
	
	bool ret = FieldReferee::getInstance().isCollision(movedCollision, this);
	if (!ret)
		_actor.setPos(_actor.pos + offset);

	_tiledTexture.walkAnime(offset, 0.2);	// �b��(���s�A�j���[�V�������[�g)
}

void Player::update()
{
	if(Motion::Excutable ==_motion)
		move();

	if ((Motion::Excutable == _motion && KeyZ.pressed())
		|| Motion::Attacking == _motion)
		attack();
}

void Player::draw()
{
	_tiledTexture.getTile()
		.draw(_actor.pos.x - _tiledTexture.getTile().size.x / 2		// ������_actor.pos�Ƃ��邽�߁A�`��ʒu����
			, _actor.pos.y - _tiledTexture.getTile().size.y);
	RectF(_actor.pos.x - _actor.w / 2, _actor.pos.y - _actor.h, _actor.w, _actor.h).drawFrame();	// �e�X�g�p�F
	Circle(_actor.pos, 2).draw(Palette::Red);

	ClearPrint();
	Print << U"_actor.pos :" << _actor.pos;
	Print << U"_actor.w :" << _actor.w;
	Print << U"_actor.h :" << _actor.h;
	Print << U"_actor.size :" << _actor.size;
	Print << U"_tiledTexture.size.w :" << _tiledTexture.getTile().size.x;
	Print << U"_tiledTexture.size.h :" << _tiledTexture.getTile().size.y;
}