#include "Player.h"
#include "FieldReferee.h"

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _ability(value)
	, _motion(Motion::Excutable)
{
	_skills.emplace_back(std::make_unique<Slash>());
	_skills.emplace_back(std::make_unique<SonicBlade>());
}

void Player::skill()
{
	Skill::State ret = Skill::State::Complete;
	int32 skill = 0;	// �b��

	if ((Motion::Excutable == _motion && KeyD.pressed())
		|| Motion::Executing_Skill1 == _motion) {
		ret = _skills.at(0)->execute(_actor, _direction, _ability, _tiledTexture);
		skill = 1;
	}

	if ((Motion::Excutable == _motion && KeyS.pressed())
		|| Motion::Executing_Skill2 == _motion) {
		ret = _skills.at(1)->execute(_actor, _direction, _ability, _tiledTexture);
		skill = 2;
	}

	if ((Motion::Excutable == _motion && KeyA.pressed())
		|| Motion::Executing_Skill3 == _motion) {
		ret = _skills.at(2)->execute(_actor, _direction, _ability, _tiledTexture);
		skill = 3;
	}

	//�e�X�g�p�F
	if (Skill::State::Continue == ret) {
		if(1 == skill)		_motion = Motion::Executing_Skill1;
		else if(2 == skill)	_motion = Motion::Executing_Skill2;
		else if(3 == skill)	_motion = Motion::Executing_Skill3;
	}
	else if (Skill::State::Complete == ret) {
		_motion = Motion::Excutable;
	}
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

	const RectF movedCollision(						// �ړ������ꍇ�̏Փ˔���p
		_actor.pos.x - _collisionForMove.x / 2 + offset.x
		, _actor.pos.y - _collisionForMove.y + offset.y
		, _collisionForMove.x, _collisionForMove.y);
	
	bool ret = FieldReferee::getInstance().isCollision(movedCollision, this);
	if (!ret)
		_actor.setPos(_actor.pos + offset);

	if (0 > offset.x)		_direction = Direction::Left;
	else if (0 < offset.x)	_direction = Direction::Right;
	if (0 > offset.y)		_direction = Direction::Up;
	else if (0 < offset.y)	_direction = Direction::Down;

	if (offset.x != 0 || offset.y != 0) 
		_tiledTexture.walkAnime(_direction, 0.2);	// �b��(���s�A�j���[�V�������[�g)
}

void Player::update()
{
	if(Motion::Excutable ==_motion)
		move();

	skill();
}

void Player::draw()
{
	// ������_actor.pos�Ƃ��邽�߁A�`��ʒu����
	_tiledTexture.getTile()
		.draw(_actor.pos.x - _actor.w / 2
			, _actor.pos.y - _actor.h);

	// �e�X�g�p�F�ړ��p�R���W����
	RectF(_actor.pos.x - _collisionForMove.x / 2, _actor.pos.y - _collisionForMove.y, _collisionForMove).drawFrame();
	
	// �e�X�g�p�F�x�[�X���W
	Circle(_actor.pos, 2).draw(Palette::Red);

	// �e�X�g�p�F�R���W����
	RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2) , _collision).drawFrame(0.5, Palette::Orange);

	// �e�X�g�p�F�\�[�h�X�L���P�̗̈�m�F�p
	//Circle(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), 40).drawFrame(0.5, 0.5, Palette::Red);

	// �e�X�g�p�F
	ClearPrint();
	Print << U"_actor.pos :" << _actor.pos;
	Print << U"_actor.w :" << _actor.w;
	Print << U"_actor.h :" << _actor.h;
	Print << U"_actor.size :" << _actor.size;
	Print << U"_tiledTexture.size.w :" << _tiledTexture.getTile().size.x;
	Print << U"_tiledTexture.size.h :" << _tiledTexture.getTile().size.y;
}