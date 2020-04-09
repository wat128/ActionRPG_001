#pragma once
#include "Skill.h"
#include "FieldReferee.h"

Skill::Skill() {}

Skill::Skill(
	const String textureStr,
	const DisplayLayer layer,
	const Size tileSize,
	const double endTime,
	const int32 maxCount,
	const int32 xNum,
	const int32 yNum,
	const Size region)
	: _effect(std::make_shared<EffectAnime>(textureStr, layer, tileSize, endTime, maxCount, xNum, yNum, region))
	, _isActiveTileAnime(false)
	, _isActiveEffect(false)
{}

/* --------------------------------------------------------------------------------------*/
/*		各スキルの処理																	 */
/* --------------------------------------------------------------------------------------*/
/* ※：スキルの戻り値はキャラタイルアニメとエフェクトの両方が終了した際にCompleteを返す  */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*		ソードスキル																	 */
/* --------------------------------------------------------------------------------------*/
Slash::Slash()
	: Skill(
		U"Asset/Effect/sword01.png",	// テクスチャ 
		DisplayLayer::SecondTop,		// 表示レイヤー
		{ 192, 192 },					// 1コマのサイズ
		0.3,							// エフェクト終了までの時間   
		8,								// 全コマ数
		5,								// 横のコマ数
		2,								// 縦のコマ数
		{ 80, 40 })						// 表示領域
{}

Skill::State Slash::execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
{
	Skill::State skillResult = Skill::State::Complete;

	// キャラタイルのアニメ
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.15 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// エフェクト
	EffectAnime::State effectResult = EffectAnime::State::Complete;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 }, 
				EffectAnime::DisplayFormat::_90deg);
			break;
		case Direction::Up:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 }, 
				EffectAnime::DisplayFormat::_270deg);
			break;
		case Direction::Left:
			effectResult = _effect->update({ actor.pos.x - actor.w / 4, actor.pos.y - actor.h / 2 }, 
				EffectAnime::DisplayFormat::MirFlipped);
			break;
		case Direction::Right:
			effectResult = _effect->update({ actor.pos.x + actor.w / 4, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::NmlFlippedReverse);
			break;
		default:
			break;
		}
		
		if (EffectAnime::State::Complete == effectResult)
			_isActiveEffect = true;
	}
	
	if (_isActiveTileAnime && _isActiveEffect) {
		skillResult = Skill::State::Complete;
		_isActiveTileAnime = false;
		_isActiveEffect = false;
	}
	else if (!_isActiveTileAnime || !_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}

SonicBlade::SonicBlade()
	: Skill(
		U"Asset/Effect/sword02.png",	// テクスチャ 
		DisplayLayer::SecondTop,		// 表示レイヤー
		{ 192, 192 },					// 1コマのサイズ
		0.7,							// エフェクト終了までの時間   
		12,								// 全コマ数
		5,								// 横のコマ数
		3,								// 縦のコマ数
		{ 250, 60 })					// 表示領域
{}

Skill::State SonicBlade::execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
{
	Skill::State skillResult = Skill::State::Complete;

	// キャラタイルのアニメ
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.55 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// エフェクト
	EffectAnime::State effectResult = EffectAnime::State::Complete;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 + 140 },
				EffectAnime::DisplayFormat::_90deg);
			break;
		case Direction::Up:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 - 140 },
				EffectAnime::DisplayFormat::_270deg);
			break;
		case Direction::Left:
			effectResult = _effect->update({ actor.pos.x - actor.w / 4 - 130, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::Mirror);
			break;
		case Direction::Right:
			effectResult = _effect->update({ actor.pos.x + actor.w / 4 + 130, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::Normal);
			break;
		default:
			break;
		}

		if (EffectAnime::State::Complete == effectResult)
			_isActiveEffect = true;
	}

	if (_isActiveTileAnime && _isActiveEffect) {
		skillResult = Skill::State::Complete;
		_isActiveTileAnime = false;
		_isActiveEffect = false;
	}
	else if (!_isActiveTileAnime || !_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}