#pragma once
#include "Skill.h"
#include "FieldReferee.h"

Skill::Data::Data(const String& n, const Genre& g, const Type& t, const int32& p, const Buff& b, const int32& s, const Size& r, const int32& a)
	: name(n), genre(g), type(t), power(p), buff(b), state(s), region(r), attackNum(a)
{}

Skill::Skill()
	: _effect(nullptr)
	, _data(U"", Data::Genre::Physical, Data::Type::Void, 0, { 0 }, 0, { 0, 0 }, 0)
	, _isActiveTileAnime(false)
	, _isActiveEffect(false)
	, _attackNumAccum(0)
{}

Skill::Skill(const EffectData& eData, const Data& sData)
	: _effect(std::make_shared<EffectAnime>(eData.textureStr, eData.layer, eData.tileSize, eData.endTime, eData.maxCount, eData.xNum, eData.yNum, eData.displayRegion))
	, _data(sData.name, sData.genre, sData.type, sData.power, sData.buff, sData.state, sData.region, sData.attackNum)
	, _isActiveTileAnime(false)
	, _isActiveEffect(false)
	, _attackNumAccum(0)
{}

/* --------------------------------------------------------------------------------------*/
/*		各スキルの処理																	 */
/* --------------------------------------------------------------------------------------*/
/* ※：スキルの戻り値はキャラタイルアニメとエフェクトの両方が終了した際にCompleteを返す  */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*																						 */
/*		ソードスキル																	 */
/*																						 */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*		スラッシュ																		 */
/* --------------------------------------------------------------------------------------*/
Slash::Slash()
	: Skill(
		EffectData
			{ U"Asset/Effect/sword01.png",	// テクスチャ 
				DisplayLayer::Middle,		// 表示レイヤー
				{ 192, 192 },				// 1コマのサイズ
				0.3,						// エフェクト終了までの時間   
				8,							// 全コマ数
				5,							// 横のコマ数
				2,							// 縦のコマ数
				Size(80, 40) },				// エフェクトの表示領域						
		Data(U"スラッシュ", Data::Genre::Physical, Data::Type::Slash, 30, {0}, 0x00000000, Size(20, 0), 1))
{}

Skill::State Slash::execute(
	RectF& actor,
	Direction& direction,
	const Ability& ability,
	const Group& targetGroup,
	TiledGameObjectTexture& tiledTexture,
	std::function<void(const int32)> func)
{
	Skill::State skillResult = Skill::State::Complete;
	if (_data.attackNum > _attackNumAccum)
		AudioAsset(U"Sword01").playOneShot(0.7);

	// キャラタイルのアニメ
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.15 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// エフェクト & スキル当たり判定
	EffectAnime::State effectResult = EffectAnime::State::Complete;
	const int32 margin = 10;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 }, 
				EffectAnime::DisplayFormat::_90deg, actor.pos.y, DisplayLayer::SecondTop);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 - margin, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Up:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 }, 
				EffectAnime::DisplayFormat::_270deg, actor.pos.y - 1, DisplayLayer::Middle);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 - margin, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Left:

			effectResult = _effect->update({ actor.pos.x - actor.w / 4, actor.pos.y - actor.h / 2 }, 
				EffectAnime::DisplayFormat::MirFlipped, actor.pos.y + 30, DisplayLayer::Middle);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x - actor.w / 4 - margin, actor.pos.y - actor.h / 2, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Right:

			effectResult = _effect->update({ actor.pos.x + actor.w / 4, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::NmlFlippedReverse, actor.pos.y + 30, DisplayLayer::Middle);
			
			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x + actor.w / 4 + margin, actor.pos.y - actor.h / 2, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		default:
			break;
		}
		
		if (EffectAnime::State::Complete == effectResult)
			_isActiveEffect = true;
	}
	
	// 初期化処理
	if (_isActiveTileAnime && _isActiveEffect) {
		skillResult = Skill::State::Complete;
		_isActiveTileAnime = false;
		_isActiveEffect = false;
		_attackNumAccum = 0;
	}
	else if (!_isActiveTileAnime || !_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}

/* --------------------------------------------------------------------------------------*/
/*		月閃衝																			 */
/* --------------------------------------------------------------------------------------*/
SonicBlade::SonicBlade()
	: Skill(
		EffectData
			{ U"Asset/Effect/sword02.png",	// テクスチャ 
				DisplayLayer::Middle,		// 表示レイヤー
				{ 192, 192 },				// 1コマのサイズ
				0.7,						// エフェクト終了までの時間   
				12,							// 全コマ数
				5,							// 横のコマ数
				3,							// 縦のコマ数
				Size(250, 60)},				// エフェクトの表示領域	
		Data(U"月閃衝", Data::Genre::Physical, Data::Type::Slash, 60, { 0 }, 0x00000000, Size(240, 20), 1))
{}

Skill::State SonicBlade::execute(
	RectF& actor,
	Direction& direction,
	const Ability& ability,
	const Group& targetGroup,
	TiledGameObjectTexture& tiledTexture,
	std::function<void(const int32)> func)
{
	Skill::State skillResult = Skill::State::Complete;
	if (_data.attackNum > _attackNumAccum)
		AudioAsset(U"Sword02").playOneShot(0.2);

	// キャラタイルのアニメ
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.55 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// エフェクト & スキル当たり判定
	EffectAnime::State effectResult = EffectAnime::State::Complete;
	const int32 margin = 120;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 + margin },
				EffectAnime::DisplayFormat::_90deg, actor.pos.y, DisplayLayer::SecondTop);

			if (_data.attackNum > _attackNumAccum) {
				const RectF skillRegion(
					Arg::center(actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 + margin), _data.region.y, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		case Direction::Up:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 - margin },
				EffectAnime::DisplayFormat::_270deg, actor.pos.y - 1, DisplayLayer::Middle);

			if (_data.attackNum > _attackNumAccum) {
				const RectF skillRegion(
					Arg::center(actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 - margin), _data.region.y, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		case Direction::Left:
			effectResult = _effect->update({ actor.pos.x - actor.w / 4 - margin, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::Mirror, actor.pos.y + 30, DisplayLayer::Middle);

			if (_data.attackNum > _attackNumAccum) {
				const RectF skillRegion(
					Arg::center(actor.pos.x - actor.w / 4 - margin, actor.pos.y - actor.h / 2), _data.region.x, _data.region.y);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		case Direction::Right:
			effectResult = _effect->update({ actor.pos.x + actor.w / 4 + margin, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::Normal, actor.pos.y + 30, DisplayLayer::Middle);

			if (_data.attackNum > _attackNumAccum) {
				const RectF skillRegion(
					Arg::center(actor.pos.x + actor.w / 4 + margin, actor.pos.y - actor.h / 2), _data.region.x, _data.region.y);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		default:
			break;
		}

		if (EffectAnime::State::Complete == effectResult)
			_isActiveEffect = true;
	}

	// 初期化処理
	if (_isActiveTileAnime && _isActiveEffect) {
		skillResult = Skill::State::Complete;
		_isActiveTileAnime = false;
		_isActiveEffect = false;
		_attackNumAccum = 0;
	}
	else if (!_isActiveTileAnime || !_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}

/* --------------------------------------------------------------------------------------*/
/*																						 */
/*		バフ・回復スキル（使用者のみ）													 */
/*																						 */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*		昇華																			 */
/* --------------------------------------------------------------------------------------*/

BuildUp::BuildUp()
	: Skill(
		EffectData
		{ U"Asset/Effect/Charge01.png",	// テクスチャ 
			DisplayLayer::SecondTop,	// 表示レイヤー
			{ 192, 192 },				// 1コマのサイズ
			0.7,						// エフェクト終了までの時間   
			14,							// 全コマ数
			5,							// 横のコマ数
			3,							// 縦のコマ数
			Size(100, 100) },			// エフェクトの表示領域	
		Data(U"昇華", Data::Genre::AssistMyself, Data::Type::Void, 0, {1.1,0,0,0,0,30}, 0x00000000, Size(1, 1), 1))
{}

Skill::State BuildUp::execute(
	const Ability& ability,
	const Group& targetGroup,
	const int32& target,
	TiledGameObjectTexture& tiledTexture)
{
	Skill::State skillResult = Skill::State::Complete;
	
	const auto actor = FieldReferee::getInstance().getObj(target, targetGroup);
	if (!actor) {								// nullptrならスキル終了
		skillResult = Skill::State::Complete;
		_isActiveEffect = false;
		_attackNumAccum = 0;
		return skillResult;
	}		
		
	// エフェクト & スキル当たり判定
	EffectAnime::State effectResult = EffectAnime::State::Complete;

	if (!_isActiveEffect) {
		const auto pos = actor->getPos();
		const auto size = actor->getSize();

		effectResult = _effect->update({ pos.x, pos.y - size.y / 2},
			EffectAnime::DisplayFormat::Normal, pos.y, DisplayLayer::SecondTop);

		if (_data.attackNum > _attackNumAccum) {
			AudioAsset(U"Buff01").playOneShot(0.2);

			const RectF skillRegion(
				Arg::center(pos.x, pos.y - size.y / 2 + size.x / 4), _data.region);

			FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data);
			++_attackNumAccum;
		}

		if (EffectAnime::State::Complete == effectResult)
			_isActiveEffect = true;
	}

	// 初期化処理
	if (_isActiveEffect) {
		skillResult = Skill::State::Complete;
		_isActiveEffect = false;
		_attackNumAccum = 0;
	}
	else if (!_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}