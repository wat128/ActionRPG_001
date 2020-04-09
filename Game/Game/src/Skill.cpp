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
/*		�e�X�L���̏���																	 */
/* --------------------------------------------------------------------------------------*/
/* ���F�X�L���̖߂�l�̓L�����^�C���A�j���ƃG�t�F�N�g�̗������I�������ۂ�Complete��Ԃ�  */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*		�\�[�h�X�L��																	 */
/* --------------------------------------------------------------------------------------*/
Slash::Slash()
	: Skill(
		U"Asset/Effect/sword01.png",	// �e�N�X�`�� 
		DisplayLayer::SecondTop,		// �\�����C���[
		{ 192, 192 },					// 1�R�}�̃T�C�Y
		0.3,							// �G�t�F�N�g�I���܂ł̎���   
		8,								// �S�R�}��
		5,								// ���̃R�}��
		2,								// �c�̃R�}��
		{ 80, 40 })						// �\���̈�
{}

Skill::State Slash::execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
{
	Skill::State skillResult = Skill::State::Complete;

	// �L�����^�C���̃A�j��
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.15 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// �G�t�F�N�g
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
		U"Asset/Effect/sword02.png",	// �e�N�X�`�� 
		DisplayLayer::SecondTop,		// �\�����C���[
		{ 192, 192 },					// 1�R�}�̃T�C�Y
		0.7,							// �G�t�F�N�g�I���܂ł̎���   
		12,								// �S�R�}��
		5,								// ���̃R�}��
		3,								// �c�̃R�}��
		{ 250, 60 })					// �\���̈�
{}

Skill::State SonicBlade::execute(RectF& actor, Direction& direction, const Ability ability, TiledGameObjectTexture& tiledTexture)
{
	Skill::State skillResult = Skill::State::Complete;

	// �L�����^�C���̃A�j��
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.55 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// �G�t�F�N�g
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