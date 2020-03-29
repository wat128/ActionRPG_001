#pragma once
#include "GameObject.h"

class TiledGameObjectTexture
{
private:
	Texture _texture;
	Size _tileSize;
	Vec2 _tileXYNum;
	Vec2 _basePoint;
	Vec2 _currentDirection;
	int32 _count;
	double _shiftRate;		// アニメ切り替え時間
	double _timeAccum;		// 毎フレーム時間蓄積（アニメーション用）
	bool _reverseAnime;

public:
	TiledGameObjectTexture();
	TiledGameObjectTexture(
		const Texture& texture,
		const Size& textureCharaNum,
		const Size& textureTileXYNum,
		const Size& textureTileRegionWH,
		const double& shiftRate = 0);

	TextureRegion getTile();

	void update();						
	void update(const Vec2& offset);	// 移動アニメーション用
};

