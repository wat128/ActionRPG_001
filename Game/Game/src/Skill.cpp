#pragma once
#include "Skill.h"
#include "FieldReferee.h"

Skill::Data::Data(const String& n, const Genre& g, const int32& p,  const int32& s, const Size& r, const int32& a)
	: name(n), genre(g), power(p), state(s), region(r), attackNum(a)
{}

Skill::Skill()
	: _effect(nullptr)
	, _data(U"", Data::Genre::Physical, 0, 0, { 0, 0 }, 0)
	, _isActiveTileAnime(false)
	, _isActiveEffect(false)
	, _attackNumAccum(0)
{}

Skill::Skill(const EffectData& eData, const Data& sData)
	: _effect(std::make_shared<EffectAnime>(eData.textureStr, eData.layer, eData.tileSize, eData.endTime, eData.maxCount, eData.xNum, eData.yNum, eData.displayRegion))
	, _data(sData.name, sData.genre, sData.power, sData.state, sData.region, sData.attackNum)
	, _isActiveTileAnime(false)
	, _isActiveEffect(false)
	, _attackNumAccum(0)
{}

/* --------------------------------------------------------------------------------------*/
/*		�e�X�L���̏���																	 */
/* --------------------------------------------------------------------------------------*/
/* ���F�X�L���̖߂�l�̓L�����^�C���A�j���ƃG�t�F�N�g�̗������I�������ۂ�Complete��Ԃ�  */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*																						 */
/*		�\�[�h�X�L��																	 */
/*																						 */
/* --------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------*/
/*		�X���b�V��																		 */
/* --------------------------------------------------------------------------------------*/
Slash::Slash()
	: Skill(
		EffectData
			{ U"Asset/Effect/sword01.png",	// �e�N�X�`�� 
				DisplayLayer::SecondTop,	// �\�����C���[
				{ 192, 192 },				// 1�R�}�̃T�C�Y
				0.3,						// �G�t�F�N�g�I���܂ł̎���   
				8,							// �S�R�}��
				5,							// ���̃R�}��
				2,							// �c�̃R�}��
				Size(80, 40) },				// �G�t�F�N�g�̕\���̈�						
		Data(U"�X���b�V��", Data::Genre::Physical, 30, 0x00000000, Size(20, 0), 1))
{}

Skill::State Slash::execute(
	RectF& actor,
	Direction& direction,
	const Ability ability,
	const Group& targetGroup,
	TiledGameObjectTexture& tiledTexture,
	std::function<void(const int32)> func)
{
	Skill::State skillResult = Skill::State::Complete;

	// �L�����^�C���̃A�j��
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.15 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// �G�t�F�N�g & �X�L�������蔻��
	EffectAnime::State effectResult = EffectAnime::State::Complete;
	const int32 margin = 10;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 }, 
				EffectAnime::DisplayFormat::_90deg);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 - margin, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Up:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 }, 
				EffectAnime::DisplayFormat::_270deg);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x, actor.pos.y - actor.h / 2 - actor.w / 4 - margin, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Left:

			effectResult = _effect->update({ actor.pos.x - actor.w / 4, actor.pos.y - actor.h / 2 }, 
				EffectAnime::DisplayFormat::MirFlipped);

			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x - actor.w / 4 - margin, actor.pos.y - actor.h / 2, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
			break;
		
		case Direction::Right:

			effectResult = _effect->update({ actor.pos.x + actor.w / 4, actor.pos.y - actor.h / 2 },
				EffectAnime::DisplayFormat::NmlFlippedReverse);
			
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
	
	if (_isActiveTileAnime && _isActiveEffect) {			// ����������
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
/*		���M��																			 */
/* --------------------------------------------------------------------------------------*/
SonicBlade::SonicBlade()
	: Skill(
		EffectData
			{ U"Asset/Effect/sword02.png",	// �e�N�X�`�� 
				DisplayLayer::SecondTop,	// �\�����C���[
				{ 192, 192 },				// 1�R�}�̃T�C�Y
				0.7,						// �G�t�F�N�g�I���܂ł̎���   
				12,							// �S�R�}��
				5,							// ���̃R�}��
				3,							// �c�̃R�}��
				Size(250, 60)},				// �G�t�F�N�g�̕\���̈�	
		Data(U"���M��", Data::Genre::Physical, 30, 0x00000000, Size(250, 60), 1))

{}

Skill::State SonicBlade::execute(
	RectF& actor,
	Direction& direction,
	const Ability ability,
	const Group& targetGroup,
	TiledGameObjectTexture& tiledTexture,
	std::function<void(const int32)> func)
{
	Skill::State skillResult = Skill::State::Complete;

	// �L�����^�C���̃A�j��
	if (!_isActiveTileAnime) {
		TiledGameObjectTexture::State tileAnimeResult = tiledTexture.attackAnime({ 0.1, 0.05, 0.55 });
		if (TiledGameObjectTexture::State::Complete == tileAnimeResult)
			_isActiveTileAnime = true;
	}

	// �G�t�F�N�g & �X�L�������蔻��
	EffectAnime::State effectResult = EffectAnime::State::Complete;
	const int32 margin = 10;

	if (!_isActiveEffect) {

		switch (direction) {
		case Direction::Down:
			effectResult = _effect->update({ actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 + 140 },
				EffectAnime::DisplayFormat::_90deg);

			// �b��
			if (_data.attackNum > _attackNumAccum) {
				const Circle skillRegion(
					actor.pos.x, actor.pos.y - actor.h / 2 + actor.w / 4 - margin, _data.region.x);

				FieldReferee::getInstance().hitConfirm(skillRegion, targetGroup, _data, func);
				++_attackNumAccum;
			}
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
		_attackNumAccum = 0;
	}
	else if (!_isActiveTileAnime || !_isActiveEffect) {
		skillResult = Skill::State::Continue;
	}

	return skillResult;
}