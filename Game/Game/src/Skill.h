#pragma once
# include "Ability.h"
# include "TiledGameObjectTexture.h"


enum class DisplayLayer;
class EffectAnime;

// スキル内でのキャラ移動やアニメに沿った複数当たり判定等の実現のため、スキル毎にクラスを作成する。

// スキルの基底クラス
class Skill
{
public:
	enum class State {
		Complete,
		Continue,
	};

	struct EffectData {
		const String textureStr;		// テクスチャ 
		const DisplayLayer layer;		// 表示レイヤー
		const Size tileSize;			// 1コマのサイズ
		const double endTime;			// エフェクト終了までの時間（タイルアニメと同等時間とすること）
		const int32 maxCount;			// 全コマ数
		const int32 xNum;				// 横のコマ数
		const int32 yNum;				// 縦のコマ数
		const Size displayRegion;		// エフェクトの表示領域	
	};

	struct Data {
		const String name;		// 技名
		enum class Genre {
			Physical,					// 物理技
			AssistMyself,				// 自分への補助技
			AssistSomeone,				// 他への補助技
			SingleEffect,				// 他への単体魔法技
			AreaOfEffect,				// 他を中心とした魔法技
			AreaOfEffectFocusingMyself	// 自を中心とした魔法技
		}const genre;			// 技の分類
		//const Type type;		// 攻撃属性： 斬、打、突、火、水、…、無	
		const int32 power;		// 威力 ("+"ダメージ / "-"回復)
		const int32 state;		// 状態異常： 0x00000000 ～ 0x11111111
		const Size region;		// 技の当たり判定領域
		const int32  attackNum;	// 攻撃回数
		Data(const String& n, const Genre& g, const int32& p, const int32& s, const Size& r, const int32& a);
	}_data;

	Skill();

	Skill(const EffectData& eData, const Data& sData);	//このコンストラクタに渡す引数によりエフェクトが実現


	virtual State execute(
		RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}
	virtual State execute(
		Circle& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

protected:
	std::shared_ptr<EffectAnime> _effect;
	bool _isActiveTileAnime;		// タイルアニメ実行中か
	bool _isActiveEffect;			// エフェクトアニメ実行流か
	int32 _attackNumAccum;			// 攻撃判定を行った回数
};

/* --------------------------------------------------------------------------------------*/
/*		ソードスキル																	 */
/* --------------------------------------------------------------------------------------*/
class Slash : public Skill
{
public:
	Slash();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(
		RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};

class SonicBlade : public Skill
{
public:
	SonicBlade();

	//State execute(RectF& actor, Direction& direction, const Ability ability);
	State execute(RectF& actor,
		Direction& direction,
		const Ability ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};