# include "TiledGameObjectTexture.h"

TiledGameObjectTexture::TiledGameObjectTexture() {};

TiledGameObjectTexture::TiledGameObjectTexture(
	const Texture& texture,
	const Size& textureCharaNum,
	const Size& textureTileXYNum,
	const Size& textureTileRegionWH,
	const double& shiftRate)
	: _texture(texture) 
	, _chipSize(textureTileRegionWH)
	, _tileXYNum(textureTileXYNum)
	, _basePoint(
		(_chipSize.x * _tileXYNum.x) * (textureCharaNum.x - 1),
		(_chipSize.y * _tileXYNum.y) * (textureCharaNum.y - 1))
	, _currentDirection(_basePoint.x + _chipSize.x, _basePoint.y)
	, _count(0)
	, _shiftRate(shiftRate)
	, _timeAccum(0)
	, _reverseAnime(false)
{};

void update()
{

}

// �^�C���Z�b�g��X�����A�j���[�V�����ł��邱�Ƃ��O��
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
	
	if (0 > offset.x) {			// ��
		_currentDirection.x = _basePoint.x + (_chipSize.x * _count);
		_currentDirection.y = _basePoint.y + (_chipSize.y * 1);
	}
	else if (0 < offset.x) {	// �E
		_currentDirection.x = _basePoint.x + (_chipSize.x * _count);
		_currentDirection.y = _basePoint.y + (_chipSize.y * 2);
	}

	if (0 > offset.y) {			// ��
		_currentDirection.x = _basePoint.x + (_chipSize.x * _count);
		_currentDirection.y = _basePoint.y + (_chipSize.y * 3);
	}
	else if (0 < offset.y) {	// ��
		_currentDirection.x = _basePoint.x + (_chipSize.x * _count);
		_currentDirection.y = _basePoint.y + (_chipSize.y * 0);
	}
}

TextureRegion TiledGameObjectTexture::getTile()
{
	return _texture(_currentDirection, _chipSize);
}