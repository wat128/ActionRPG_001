# include "TiledGameObjectTexture.h"

TiledGameObjectTexture::TiledGameObjectTexture() {};

TiledGameObjectTexture::TiledGameObjectTexture(
	const Texture& texture,
	const Size& textureCharaNum,
	const Size& textureTileXYNum,
	const Size& textureTileWH,
	const double& shiftRate)
	: _texture(texture) 
	, _tileSize(textureTileWH)
	, _tileXYNum(textureTileXYNum)
	, _basePoint(
		(_tileSize.x * _tileXYNum.x) * (textureCharaNum.x - 1),
		(_tileSize.y * _tileXYNum.y) * (textureCharaNum.y - 1))
	, _currentDirection(_basePoint.x + _tileSize.x, _basePoint.y)
	, _count(0)
	, _shiftRate(shiftRate)
	, _timeAccum(0)
	, _reverseAnime(false)
{};

void update()
{

}

// タイルセットのX軸がアニメーションであることが前提
void TiledGameObjectTexture::update(const Vec2& offset)
{
	if (0 >= _shiftRate) return;

	if (0 >= _count)				{ _reverseAnime = false; }
	if (_tileXYNum.x - 1 <= _count)	{ _reverseAnime = true; }

	_timeAccum += Scene::DeltaTime();
	if (_timeAccum > _shiftRate) {
		_reverseAnime ? --_count : ++_count;
		_timeAccum = 0.0;
	}
	
	if (0 > offset.x) {			// 左
		_currentDirection.x = _basePoint.x + (_tileSize.x * _count);
		_currentDirection.y = _basePoint.y + (_tileSize.y * 1);
	}
	else if (0 < offset.x) {	// 右
		_currentDirection.x = _basePoint.x + (_tileSize.x * _count);
		_currentDirection.y = _basePoint.y + (_tileSize.y * 2);
	}

	if (0 > offset.y) {			// 下
		_currentDirection.x = _basePoint.x + (_tileSize.x * _count);
		_currentDirection.y = _basePoint.y + (_tileSize.y * 3);
	}
	else if (0 < offset.y) {	// 上
		_currentDirection.x = _basePoint.x + (_tileSize.x * _count);
		_currentDirection.y = _basePoint.y + (_tileSize.y * 0);
	}
}

TextureRegion TiledGameObjectTexture::getTile()
{
	return _texture(_currentDirection, _tileSize);
}