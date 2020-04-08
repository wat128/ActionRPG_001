#pragma once
# include "Common.hpp"

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

	//�Ȍチ���o�ϐ��̒ǉ�����initialize�ւ̒ǉ����������邱��

public:
	enum class State {
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
	void initialize();			// �{�N���X���ŕύX����郁���o������������
					
	void walkAnime(const Direction& direction, const double& shiftRate);	// �ړ��A�j���[�V�����p
	State attackAnime(const Array<double>& shiftRates);						// �U���A�j���[�V�����p
};

