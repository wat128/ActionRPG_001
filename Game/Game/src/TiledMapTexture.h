#pragma once
#include <Siv3D.hpp>

class TiledMapTexture
{
private:
    Texture _texture;
    Size _tileSize;
    int32 _column, _row;     // �^�C����
    int32 _sum;
public:
    TiledMapTexture(const FilePath& path, const Size& tileSize)
        : _texture(path)
        , _tileSize(tileSize)
        , _column(_texture.width() / tileSize.x)
        , _row(_texture.height() / tileSize.y)
        , _sum(_column* _row) {}

    TextureRegion getTile(const int& index)
    {
        const double x = index % _column;
        const double y = index / _column;

        // �}�b�v�ɍ������i���Ӄ^�C���̐F�j��������̂�h�����߁A1�^�C����-0.5�s�N�Z���i������Ȃ��j���A���̌�^�C���T�C�Y�Ƀ��T�C�Y����
        return _texture(RectF(  
            (x * _tileSize.x) + 0.5,
            (y * _tileSize.y) + 0.5,
            _tileSize - Size(1, 1))).resized(_tileSize);
    }

    int32 column() const { return _column; }

    int32 row() const { return _row; }

    int32 sum() const { return _sum; }

    const Size& tileSize() const { return _tileSize; }

    const Texture& getTexture() const { return _texture; }
};

