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
			AssistMyself,				// 補助技（自）
			AssistSomeone,				// 補助技（他）
			SingleEffect,				// 単体魔法（他）
			AreaOfEffect,				// 範囲魔法（他中心）
			AreaOfEffectFocusingMyself	// 範囲魔法技（自中心）
		}const genre;			// 技の分類

		enum class Type {
			Void,						// 無
			Slash,						// 斬		
			Strike,						// 打
			Spear,						// 突
			Fire,						// 炎
			Water,						// 水
			Thunder,					// 雷
			Wind,						// 風
			Earth,						// 土
			Shine,						// 光
			Dark,						// 闇
		}const type;			// 技タイプ	

		int32 power;			// 威力 ("+"ダメージ / "-"回復)
		struct Buff {
			double attack;
			double defense;
			double agility;
			double intel;
			double resist;
			double time;				// 秒単位
		}const buff;			// バフデバフ（"1"が基準 ："1.1"バフ / "0.9"デバフ）

		const int32 state;		// 状態異常： 0x00000000 ～ 0x11111111
		const Size region;		// 技の当たり判定領域
		const int32  attackNum;	// 攻撃回数

		Data(const String& n, const Genre& g, const Type& t, const int32& p, const Buff& b, const int32& s, const Size& r, const int32& a);
	}_data;

	Skill();

	Skill(const EffectData& eData, const Data& sData);	//このコンストラクタに渡す引数によりエフェクトが実現
	
	virtual State execute(
		RectF& actor,
		Direction& direction,
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

	virtual State execute(
		Circle& actor,
		Direction& direction,
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func)
	{
		return State::Complete;
	}

	virtual State execute(
		const Ability& ability,
		const Group& targetGroup,
		const int32& target,
		TiledGameObjectTexture& tiledTexture)
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
		const Ability& ability,
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
		const Ability& ability,
		const Group& targetGroup,
		TiledGameObjectTexture& tiledTexture,
		std::function<void(const int32)> func);
private:

};

/* --------------------------------------------------------------------------------------*/
/*		バフ・回復スキル（使用者のみ）													 */
/* --------------------------------------------------------------------------------------*/

class BuildUp : public Skill
{
public:
	BuildUp();

	State execute(
		const Ability& ability,
		const Group& targetGroup,
		const int32 &target,
		TiledGameObjectTexture& tiledTexture);
private:

};