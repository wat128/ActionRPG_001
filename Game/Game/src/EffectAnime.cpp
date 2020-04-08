#include "EffectAnime.h"

EffectAnime::EffectAnime()
    : _texture()
    , _layer()
    , _tileSize()
    , _endTime()
    , _maxCount()
    , _xNum()
    , _yNum()
    , _region()
    , _pos()
    , _accum(0)
    , _count()
    , _tilePos()
    , _isActive(false)
    , _format(DisplayFormat::Normal)
{}

EffectAnime::EffectAnime(
    const String textureStr,
    const DisplayLayer layer,
    const Size tileSize,
    const double endTime,
    const int32 maxCount,
    const int32 xNum,
    const int32 yNum,
    const Size region)
    : _texture(textureStr)
    , _layer(layer)
    , _tileSize(tileSize)
    , _endTime(endTime)
    , _maxCount(maxCount)
    , _xNum(xNum)
    , _yNum(yNum)
    , _region(region)
    , _pos({ 0, 0 })
    , _accum(0)
    , _count(0)
    , _tilePos({ 0, 0 })
    , _isActive(false)
    , _format(DisplayFormat::Normal)
{}

EffectAnime::State EffectAnime::update(const Vec2& pos, const DisplayFormat& format)
{
    _pos = pos;
    _accum += Scene::DeltaTime();
    _format = format;

    switch(_format) {
    case DisplayFormat::Normal:
    case DisplayFormat::NmlFlipped:
    case DisplayFormat::Mirror:
    case DisplayFormat::MirFlipped:
    case DisplayFormat::_90deg:
    case DisplayFormat::_90degFlipped:
    case DisplayFormat::_270deg:
    case DisplayFormat::_270degFlipped:

        if (_isActive && _count >= _maxCount - 1) {
            _isActive = false;
            _count = 0;
            _accum = 0;
            _tilePos = { 0,0 };
            return EffectAnime::State::Complete;
        }

        if (!_isActive) {
            _isActive = true;
            EffectManager::add(shared_from_this());
        }

        if (_accum >= _endTime / _maxCount) {
            ++_count;
            _accum = 0;
            ++_tilePos.x;
            if (_count % _xNum == _xNum - 1) {
                ++_tilePos.y;
                _tilePos.x = 0;
            }
        }
        break;

    case DisplayFormat::NmlReverse:
    case DisplayFormat::NmlFlippedReverse:
    case DisplayFormat::MirReverse:
    case DisplayFormat::MirFlippedReverse:
    case DisplayFormat::_90degReverse:
    case DisplayFormat::_90degFlippedReverse:
    case DisplayFormat::_270degReverse:
    case DisplayFormat::_270degFlippedReverse:

        if (_isActive && 0 >= _count) {
            _isActive = false;
            _count = 0;
            _accum = 0;
            _tilePos = { 0,0 };
            return EffectAnime::State::Complete;
        }

        if (!_isActive) {
            _isActive = true;
            _count = _maxCount - 1;
            _maxCount% _xNum == 0 ? _tilePos.x = _xNum - 1 : _tilePos.x = _maxCount % _xNum - 1;
            _tilePos.y = _yNum - 1;
            EffectManager::add(shared_from_this());
        }

        if (_accum >= _endTime / _maxCount) {
            --_count;
            _accum = 0;
            --_tilePos.x;
            if (0 > _tilePos.x && 1 >= _tilePos.y) {
                --_tilePos.y;
                _tilePos.x = _xNum - 1;
            }
        }
        break;

    default:
        break;
    }
    

    return EffectAnime::State::Continue;
}

void EffectAnime::draw()
{
    switch (_format) {
    case DisplayFormat::Normal:
    case DisplayFormat::NmlReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::NmlFlipped:
    case DisplayFormat::NmlFlippedReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).flipped().drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::Mirror:
    case DisplayFormat::MirReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).mirrored().drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::MirFlipped:
    case DisplayFormat::MirFlippedReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).mirrored().flipped().drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::_90deg:
    case DisplayFormat::_90degReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).rotated(90_deg).drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::_90degFlipped:
    case DisplayFormat::_90degFlippedReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).flipped().rotated(90_deg).drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::_270deg:
    case DisplayFormat::_270degReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).rotated(270_deg).drawAt(_pos.x, _pos.y);
        break;
    case DisplayFormat::_270degFlipped:
    case DisplayFormat::_270degFlippedReverse:
        _texture(_tileSize.x * _tilePos.x, _tileSize.y * _tilePos.y, _tileSize)
            .resized(_region.x, _region.y).flipped().rotated(270_deg).drawAt(_pos.x, _pos.y);
        break;
    default:
        break;
    }
}

void EffectAnime::initialize()
{
    _accum = 0;
    _count = 0;
    _tilePos = { 0, 0 };
    _isActive = false;
    _format = DisplayFormat::Normal;
}