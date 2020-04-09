#pragma once
#include "GameObject.h"
#include "Ability.h"
#include "EffectAnime.h"


enum class DisplayLayer;
class EffectAnime;

// �X�L�����ł̃L�����ړ���A�j���ɉ��������������蔻�蓙�̎����̂��߁A�X�L�����ɃN���X���쐬����B
class Skill
{
public:
	enum class State {
		Complete,
		Continue,
	};

	Skill();
	Skill(							//���̃R���X�g���N�^�ɓn�������ɂ��G�t�F�N�g������
		const String textureStr,
		const DisplayLayer layer,
		const Size tileSize,
		const double endTime,
		const int32 maxCount,
		const int32 xNum,
		const int32 yNum,
		const Size region);
	
	virtual State execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
	{
		return State::Complete;
	}
	virtual State execute(Circle& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
	{
		return State::Complete;
	}

protected:
	std::shared_ptr<EffectAnime> _effect;
	bool _isActiveTileAnime;
	bool _isActiveEffect;
};

/* --------------------------------------------------------------------------------------*/
/*		�\�[�h�X�L��																	 */
/* --------------------------------------------------------------------------------------*/
class Slash : public Skill
{
public:
	Slash();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture);
private:

};

class SonicBlade : public Skill
{
public:
	SonicBlade();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture);
private:

};