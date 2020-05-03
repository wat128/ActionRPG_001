#include "Player.h"
#include "FieldReferee.h"
#include "FieldManager.h"// テスト用：

Player::Player() {}
Player::Player(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _motion(Motion::Excutable)
	, _targetHndl(0)
	, _chantEffect(pos, {0, 0})
	, _chantEffectParam()
{
	_skills.emplace_back(std::make_unique<Slash>());
	_skills.emplace_back(std::make_unique<SonicBlade>());
	//_skills.emplace_back(std::make_unique<BuildUp>());
	_skills.emplace_back(std::make_unique<Heal>());

	//詠唱エフェクトの設定
	_chantEffect.setTexture(Texture(U"Asset/Effect/particle01.png", TextureDesc::Mipped));
	
	RectEmitter2D rectEmitter;
	rectEmitter.width = 1;
	rectEmitter.height = 1;
	rectEmitter.sourceRadius = 40;
	_chantEffect.setEmitter(rectEmitter);
		
	_chantEffectParam.startColor = HSV(85, 0.3, 0.6, 1);
	_chantEffectParam.startSize = 8;
	_chantEffectParam.startLifeTime = 0.7;
	_chantEffectParam.startSpeed = 40;
	_chantEffect.setParameters(_chantEffectParam);

}

void Player::skill()
{
	Skill::State ret = Skill::State::Complete;
	int32 index = -1;

	// 実行スキルの選定
	if ((Motion::Excutable == _motion && KeyD.pressed())
		|| Motion::Chanting_S1 == _motion
		|| Motion::Executing_S1 == _motion) {
		index = 0;
	}
	else if ((Motion::Excutable == _motion && KeyS.pressed())
		|| Motion::Chanting_S2 == _motion
		|| Motion::Executing_S2 == _motion) {
		index = 1;
	}
	else if ((Motion::Excutable == _motion && KeyA.pressed())
		|| Motion::Chanting_S3 == _motion
		|| Motion::Executing_S3 == _motion) {
		index = 2;
	}
	else { return; }

	// 実行スキルのジャンルから処理を分ける
	switch (_skills.at(index)->_data.genre) {
	case Skill::Data::Genre::Physical:
		ret = _skills.at(index)->execute(_actor, _direction, _ability, Group::Enemys, _tiledTexture,
			[&](const int32& exp) { this->recieveExp(exp); });
		break;
	case Skill::Data::Genre::AssistMyself:
		ret = _skills.at(index)->execute(_actor, _ability, Group::Allys, _handle, _tiledTexture);
		break;
	case Skill::Data::Genre::AssistSomeone:
		if( 0 == _targetHndl || Motion::Chanting_S1 == _motion || Motion::Chanting_S2 == _motion || Motion::Chanting_S3 == _motion)
			setTarget({ camera.getRegion().x, camera.getRegion().y, camera.getRegion().w, camera.getRegion().h }, Group::Allys, _targetHndl);
		
		ret = _skills.at(index)->execute(_actor, _ability, Group::Allys, _targetHndl, _tiledTexture);
		break;
	case Skill::Data::Genre::SingleEffect:
	case Skill::Data::Genre::AreaOfEffect:
	case Skill::Data::Genre::AreaOfEffectFocusingMyself:
		break;
	}

	// 実行スキルの処理が次フレームでも必要か
	if (Skill::State::Executing == ret) {
		if(0 == index)		_motion = Motion::Executing_S1;
		else if(1 == index)	_motion = Motion::Executing_S2;
		else if(2 == index)	_motion = Motion::Executing_S3;
	}
	else if (Skill::State::Chanting == ret) {
		if (0 == index)		_motion = Motion::Chanting_S1;
		else if (1 == index)	_motion = Motion::Chanting_S2;
		else if (2 == index)	_motion = Motion::Chanting_S3;
	}
	else if (Skill::State::Complete == ret) {
		_motion = Motion::Excutable;
		_targetHndl = 0;
	}
}

void Player::talk()
{

}

void Player::move()
{
	double speed;
	if (_ability.agility.current < 500)
		speed = _ability.agility.current;
	else
		speed = 500;

	Vec2 offset = Vec2(KeyRight.pressed() - KeyLeft.pressed(), KeyDown.pressed() - KeyUp.pressed())
		.setLength((Scene::DeltaTime() + 2.5) + speed * 0.003);

	const RectF movedCollision(							// 移動した場合の衝突判定用
		CollisionForMove().x + offset.x
		, CollisionForMove().y + offset.y
		, _collisionForMoveSize);
	
	auto& fieldRef = FieldReferee::getInstance();
	bool ret = fieldRef.canMove(movedCollision, Group::Allys);
	if (ret) {
		_actor.setPos(_actor.pos + offset);
		fieldRef.setActiveEvent(CollisionForMove());	// 移動後の領域にイベントがあれば設定。
	}

	if (0 > offset.x)		_direction = Direction::Left;
	else if (0 < offset.x)	_direction = Direction::Right;
	if (0 > offset.y)		_direction = Direction::Up;
	else if (0 < offset.y)	_direction = Direction::Down;

	if (offset.x != 0 || offset.y != 0) 
		_tiledTexture.walkAnime(_direction, 0.2);		// 暫定(歩行アニメーションレート)
}

void Player::update()
{
	if(Motion::Excutable ==_motion)
		move();

	skill();

	if (0 < _HurtTime)
		_HurtTime -= Scene::DeltaTime();

	_ability.update();
	
	if (Motion::Chanting_S1 == _motion || Motion::Chanting_S2 == _motion || Motion::Chanting_S3 == _motion) {
		
		_chantEffectParam.rate = 50;
		_chantEffect.setParameters(_chantEffectParam);

		const Vec2 chantEffectPos(_actor.pos.x, _actor.pos.y - _actor.h / 2);
		_chantEffect.setPosition(chantEffectPos);

		_chantEffect.update();
	}
	else {
		_chantEffectParam.rate = 0;
		_chantEffect.setParameters(_chantEffectParam);
		_chantEffect.update();
	}

	_dispPriority = _actor.pos.y;
}

void Player::draw()
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

	//スキル詠唱中なら詠唱エフェクトとターゲットを示すカーソルを表示する。
	const auto target = (FieldReferee::getInstance().getObj(_targetHndl));
	if (Motion::Chanting_S1 == _motion || Motion::Chanting_S2 == _motion || Motion::Chanting_S3 == _motion) {
		_chantEffect.draw();
		
		RoundRect(Arg::center(target->getPos().x,
			target->getPos().y - target->getSize().y / 2),
			target->getSize(),
			10).drawFrame();
	}

	/*----------------------------------------------------------------------------*/
	/*		テスト用															　*/
	/*----------------------------------------------------------------------------*/
#if 1
	{
		// テスト用：移動用コリジョン
		CollisionForMove().drawFrame();

		// テスト用：ベース座標
		Circle(_actor.pos, 2).draw(Palette::Red);

		// テスト用：コリジョン
		Collision<RectF>().drawFrame(0.5, Palette::Orange);

		// テスト用：ソードスキル１の領域確認用

		//Circle(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2), 40).drawFrame(0.5, 0.5, Palette::Red);
		//const int32 margin = 10;
		//switch (_direction) {
		//case Direction::Down:
		//	const Circle(_actor.pos.x, _actor.pos.y - _actor.h / 2 + _actor.w / 4 + margin, 20).drawFrame();
		//	break;
		//case Direction::Up:
		//	const Circle(_actor.pos.x, _actor.pos.y - _actor.h / 2 - _actor.w / 4 - margin, 20).drawFrame();
		//	break;
		//case Direction::Left:
		//	const Circle(_actor.pos.x - _actor.w / 4 - margin, _actor.pos.y - _actor.h / 2, 20).drawFrame();
		//	break;
		//case Direction::Right:
		//	const Circle(_actor.pos.x + _actor.w / 4 + margin, _actor.pos.y - _actor.h / 2, 20).drawFrame();
		//	break;
		//}

		// テスト用：ソードスキル２の領域確認用
		//const Size size(240, 20);
		//const int32 margin = 120;
		//switch (_direction) {
		//case Direction::Down:
		//	const RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2 + _actor.w / 4 + margin), size.y, size.x).drawFrame();
		//	break;
		//case Direction::Up:
		//	const RectF(Arg::center(_actor.pos.x, _actor.pos.y - _actor.h / 2 - _actor.w / 4 - margin), size.y, size.x).drawFrame();
		//	break;
		//case Direction::Left:
		//	const RectF(Arg::center(_actor.pos.x - _actor.w / 4 - margin, _actor.pos.y - _actor.h / 2), size.x, size.y).drawFrame();
		//	break;
		//case Direction::Right:
		//	const RectF(Arg::center(_actor.pos.x + _actor.w / 4 + margin, _actor.pos.y - _actor.h / 2), size.x, size.y).drawFrame();
		//	break;
		//}

		// テスト用：
		ClearPrint();
		Print << U"_actor.pos :" << _actor.pos;
		Print << U"_actor.w :" << _actor.w;
		Print << U"_actor.h :" << _actor.h;
		Print << U"_actor.size :" << _actor.size;
		Print << U"_tiledTexture.size :" << _tiledTexture.getTile().size;
		Print << U"Hero_use_count :" << FieldManager::getInstance().getAllys().at(0).use_count();
		if (!FieldManager::getInstance().getEnemys().empty())
			Print << U"モンスター[0] _ HP :" << FieldManager::getInstance().getEnemys().at(0)->getAbility().hp.current;
		else
			Print << U"モンスター無し";
		Print << U"Hero_EXP :" << FieldManager::getInstance().getAllys().at(0)->getAbility().currentExp;
		//Print << U"WolF_use_count :" << FieldManager::getInstance().getEnemys().at(0).use_count();
		Print << U"Hero_attackBuffTime :" << FieldManager::getInstance().getAllys().at(0)->getAbility().attack.buffTime;

		RectF(-432, -240, 32, 48).drawFrame();	// EventID : 1001
		RectF(448, -176, 32, 64).drawFrame();	// EventID : 1002
		RectF(-112, 624, 144, 16).drawFrame();	// EventID : 1003
	}
#endif
}


namespace {		// 本ファイル内（Playerクラス）に使用限定関数

	// スキル実行先（ターゲット）を設定する
	void setTarget(const RectF& region, const Group& targetGroup, uint32& targetHndl)
	{
		FieldReferee fRef = FieldReferee::getInstance();
		Array<uint32> handles;									// ターゲット選定用

		if (fRef.exists(targetHndl, region, targetGroup)) {
			if (!KeyD.down() && !KeyS.down() && !KeyA.down())
				return;

			handles = fRef.getObjHandle(region, targetGroup);
			for (int32 i = 0; i < handles.size(); ++i) {
				if (handles.at(i) == targetHndl) {
					if (i >= handles.size() - 1)
						targetHndl = handles.at(0);
					else
						targetHndl = handles.at(i + 1);

					break;
				}
			}
		}
		else {
			handles = fRef.getObjHandle(region, targetGroup);
			if (0 < handles.size())
				targetHndl = handles.at(0);
			else
				targetHndl = 0;
		}

		return;
	}
}