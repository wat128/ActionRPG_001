#pragma once
#include <Siv3D.hpp>

class TiledMapTexture
{
private:
    Texture _texture;
    Size _chipSize;
    int32 _column, _row;     // É`ÉbÉvêî
    int32 _sum;
public:
    TiledMapTexture(const FilePath& path, const Size& chipSize)
        : _texture(path)
        , _chipSize(chipSize)
        , _column(_texture.width() / chipSize.x)
        , _row(_texture.height() / chipSize.y)
        , _sum(_column* _row) {}

    TextureRegion getTile(const int& index)
    {
        const int x = index % _column;
        const int y = index / _column;

        return _texture(RectF(x * _chipSize.x, y * _chipSize.y, _chipSize));
    }

    int32 column() const { return _column; }

    int32 row() const { return _row; }

    int32 sum() const { return _sum; }

    const Size& chipSize() const { return _chipSize; }

    const Texture& getTexture() const { return _texture; }
};

