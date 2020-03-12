#pragma once
#include <Siv3D.hpp>

class TiledTexture
{
private:
    Texture _texture;
    Size _chipSize;
    int32 _w, _h;     // É`ÉbÉvêî
    int32 _sum;
public:
    TiledTexture(const FilePath& path, const Size& chipSize)
        : _texture(path)
        , _chipSize(chipSize)
        , _w(_texture.width() / chipSize.x)
        , _h(_texture.height() / chipSize.y)
        , _sum(_w* _h) {}

    TextureRegion getTile(const int& index)
    {
        const int x = index % _w;
        const int y = index / _w;

        return _texture(RectF(x * _chipSize.x, y * _chipSize.y, _chipSize));
    }

    int32 width() const { return _w; }

    int32 height() const { return _h; }

    int32 sum() const { return _sum; }

    const Size& chipSize() const { return _chipSize; }

    const Texture& getTexture() const { return _texture; }
};

