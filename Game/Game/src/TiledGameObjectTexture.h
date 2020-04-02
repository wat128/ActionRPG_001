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

	int32 _walkAnimeCount;		// 表示タイルのインデックス用（歩行アニメ用）
	double _walkTimeAccum;		// 毎フレーム時間蓄積（歩行アニメ用）
	bool _reverseAnime;

	int32 _attackAnimeCount;	// 表示タイルのインデックス用（攻撃アニメ用）
	double _attackTimeAccum;	// 毎フレーム時間蓄積（攻撃アニメ用）

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
					
	void walkAnime(const Vec2& offset, const double& shiftRate);		// 移動アニメーション用
	RunningState attackAnime(const Array<double>& shiftRates);		// 攻撃アニメーション用
};

