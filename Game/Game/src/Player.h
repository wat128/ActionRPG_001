#pragma once
#include "GameObject.h"
#include "Skill.h"

class Skill;
namespace {
	void setTarget(const RectF& region, const Group& targetGroup, uint32& targetHndl);
}

class Player : public GameObject
{
public:
	Player();
	Player(const int32& value, const Vec2& pos);
	void skill();
	void talk();
	void move() override;
	void update() override;
	void draw() override;
	uint32 _targetHndl;		// スキルやアイテムのターゲット（※：必要なら基底クラスに移動）
private:
	Array<std::unique_ptr<Skill>> _skills;
	enum class Motion {
		Excutable,
		Chanting_S1,
		Executing_S1,
		Chanting_S2,
		Executing_S2,
		Chanting_S3,
		Executing_S3,
		Talking,
	}_motion;

	ParticleSystem2D _chantEffect;
	ParticleSystem2DParameters _chantEffectParam;

};

