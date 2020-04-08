# include "TiledGameObjectTexture.h"

TiledGameObjectTexture::TiledGameObjectTexture() {};

TiledGameObjectTexture::TiledGameObjectTexture(
	const Texture& texture,
	const Vec2& textureCharaNum,
	const Size& textureTileWH,
	const Size& textureTileXYNum,
	const Vec2& textureWalkTileXYNum,
	const Vec2& textureAttackTileXYNum)
	: _texture(texture) 
	, _tileSize(textureTileWH)
	, _tileXYNum(textureTileXYNum)
	, _walkTileXYNum(textureWalkTileXYNum)
	, _attackTileXYNum(textureAttackTileXYNum)
	, _basePoint(
		(_tileSize.x * _tileXYNum.x) * (textureCharaNum.x - 1),
		(_tileSize.y * _tileXYNum.y) * (textureCharaNum.y - 1))
	, _currentPoint(_basePoint.x + _tileSize.x, _basePoint.y)
	, _walkAnimeCount(0)
	, _walkTimeAccum(0)
	, _reverseAnime(false)
	, _attackAnimeCount(0)
	, _attackTimeAccum(0)
{};

// タイルセットのX軸がアニメーションであることが前提
void TiledGameObjectTexture::walkAnime(const Direction& direction, const double& shiftRate)
{
	if (0 >= shiftRate) return;

	if (0 >= _walkAnimeCount)						{ _reverseAnime = false; }
	if (_walkTileXYNum.x - 1 <= _walkAnimeCount)	{ _reverseAnime = true; }

	_walkTimeAccum += Scene::DeltaTime();
	if (_walkTimeAccum > shiftRate) {
		_reverseAnime ? --_walkAnimeCount : ++_walkAnimeCount;
		_walkTimeAccum = 0.0;
	}
	
	if (Direction::Left == direction) {
		_currentPoint.x = _basePoint.x + (_tileSize.x * _walkAnimeCount);
		_currentPoint.y = _basePoint.y + (_tileSize.y * 1);
	}
	else if (Direction::Right == direction) {
		_currentPoint.x = _basePoint.x + (_tileSize.x * _walkAnimeCount);
		_currentPoint.y = _basePoint.y + (_tileSize.y * 2);
	}

	if (Direction::Down == direction) {
		_currentPoint.x = _basePoint.x + (_tileSize.x * _walkAnimeCount);
		_currentPoint.y = _basePoint.y + (_tileSize.y * 0);
	}
	else if (Direction::Up == direction) {
		_currentPoint.x = _basePoint.x + (_tileSize.x * _walkAnimeCount);
		_currentPoint.y = _basePoint.y + (_tileSize.y * 3);
	}
}

TiledGameObjectTexture::State TiledGameObjectTexture::attackAnime(const Array<double>& shiftRates)
{
	_attackTimeAccum += Scene::DeltaTime();
	if (_attackTimeAccum > shiftRates[_attackAnimeCount]) {
	
		if (_attackTimeAccum >= shiftRates.back() && _attackAnimeCount >= shiftRates.size() - 1)
		{
			_currentPoint.x = _basePoint.x + (_tileSize.x * _walkAnimeCount);
			_attackTimeAccum = 0;
			_attackAnimeCount = 0;
			return State::Complete;
		}

		++_attackAnimeCount;
		_attackTimeAccum = 0.0;
	}

	const int32 startPointOfAttackTile = _basePoint.x +_tileSize.x * _walkTileXYNum.x;
	_currentPoint.x = startPointOfAttackTile + _tileSize.x * _attackAnimeCount;

	return State::Continue;
}

TextureRegion TiledGameObjectTexture::getTile()
{
	return _texture(_currentPoint, _tileSize);
}

void TiledGameObjectTexture::initialize()
{
	_currentPoint = { _basePoint.x + _tileSize.x, _basePoint.y };
	_walkAnimeCount = 0;
	_walkTimeAccum = 0;
	_reverseAnime = false;
	_attackAnimeCount = 0;
	_attackTimeAccum = 0;
}