#pragma once
#include <Siv3D.hpp>

class TiledTexture
{
private:
    Texture _texture;
    Size _tileSize;
    int32 _column, _row;     // É^ÉCÉãêî
    int32 _sum;
public:
    TiledTexture(const FilePath& path, const Size& tileSize)
        : _texture(path)
        , _tileSize(tileSize)
        , _column(_texture.width() / tileSize.x)
        , _row(_texture.height() / tileSize.y)
        , _sum(_column* _row) {}

    TextureRegion getTile(const int& index)
    {
        const int x = index % _column;
        const int y = index / _column;

        return _texture(RectF(x * _tileSize.x, y * _tileSize.y, _tileSize));
    }

    int32 column() const { return _column; }

    int32 row() const { return _row; }

    int32 sum() const { return _sum; }

    const Size& tileSize() const { return _tileSize; }

    const Texture& getTexture() const { return _texture; }
};

