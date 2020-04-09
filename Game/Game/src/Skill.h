#pragma once
#include "GameObject.h"
#include "Ability.h"
#include "EffectAnime.h"


enum class DisplayLayer;
class EffectAnime;

// スキル内でのキャラ移動やアニメに沿った複数当たり判定等の実現のため、スキル毎にクラスを作成する。
class Skill
{
public:
	enum class State {
		Complete,
		Continue,
	};

	Skill();
	Skill(							//このコンストラクタに渡す引数によりエフェクトが実現
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
/*		ソードスキル																	 */
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