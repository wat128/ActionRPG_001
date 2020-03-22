#pragma once
#include "GameObject.h"

class TiledGameObjectTexture
{
private:
	Texture _texture;
	Size _chipSize;
	Vec2 _tileXYNum;
	Vec2 _basePoint;
	Vec2 _currentDirection;
	//Stopwatch _animeTimer;		// �A�j���[�V�����^�C�}�[

public:
	TiledGameObjectTexture();
	TiledGameObjectTexture(
		const Texture& texture,
		const Size& textureCharaNum,
		const Size& textureTileXYNum, 
		const Size& textureTileRegionWH);

	TextureRegion getTile();

	void update();						
	void update(const Vec2& offset);	// �ړ��A�j���[�V�����p
};

