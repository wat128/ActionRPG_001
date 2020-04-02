#pragma once
#include "GameObject.h"

class TiledGameObjectTexture
{
private:
	Texture _texture;
	Size _tileSize;
	Vec2 _tileXYNum;
	Vec2 _walkTileXYNum;
	Vec2 _attackTileXYNum;
	Vec2 _basePoint;
	Vec2 _currentPoint;

	int32 _walkAnimeCount;		// �\���^�C���̃C���f�b�N�X�p�i���s�A�j���p�j
	double _walkTimeAccum;		// ���t���[�����Ԓ~�ρi���s�A�j���p�j
	bool _reverseAnime;

	int32 _attackAnimeCount;	// �\���^�C���̃C���f�b�N�X�p�i�U���A�j���p�j
	double _attackTimeAccum;	// ���t���[�����Ԓ~�ρi�U���A�j���p�j

public:
	enum class RunningState {
		Complete,
		Continue,
	};

	TiledGameObjectTexture();
	TiledGameObjectTexture(
		const Texture& texture,
		const Vec2& textureCharaNum,
		const Size& textureTileWH,
		const Size& textureTileXYNum,
		const Vec2& textureWalkTileXYNum,
		const Vec2& textureAttackTileXYNum = { 0,0 });

	TextureRegion getTile();
					
	void walkAnime(const Vec2& offset, const double& shiftRate);		// �ړ��A�j���[�V�����p
	RunningState attackAnime(const Array<double>& shiftRates);		// �U���A�j���[�V�����p
};

