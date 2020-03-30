#pragma once
# include "TiledMapTexture.h"

struct Layer {
    Array<int32> data;
    int32 height;
    int32 id;
    String name;
    int32 opacity;
    String type;
    bool visible;
    int32 width;
    int32 x;
    int32 y;
    bool isCollisionLayer;
    bool isHideLayer;
    bool isLowerLayer;
};

// --- �g�p��̒��ӓ_ ---
// 1.Tiled�œf���o�����}�b�v�f�[�^�̃e�N�X�`������Array�Ńe�N�X�`���̃p�X��n������
// 2.�S���C���[�̃T�C�Y�͓����ł��邱�ƁB(FieldSize�̎擾���ȈՉ����邽�߁j
// 3.�}�b�v�̃^�C���T�C�Y�ƃe�N�X�`���̃^�C���T�C�Y�͓����T�C�Y�Ƃ��ď������邽�߁A
//   �}�b�v�쐻�̒i�K�œ����T�C�Y�Ƃ��邱��
class Field
{
private:
    Array<TiledMapTexture> _tiles;
    Array<Layer> _layers;
    Array<Rect> _collisions;
    Size _mapSize;
    Size _tileSize;
    Size _tileNumWH;
public:
    Field();

    Field(const Array<FilePath>& tileTexturePaths, const FilePath& mapDataPath, const bool& worldPos = true);
    
    void draw(const bool& lower = true, const bool& upper = true, const bool& worldPos = true);   // ���ʏ�ʃ��C���[�`��i�f�t�H���g�S���C���[�`��j
    
    void draw(const int32& index, const bool& worldPos = true);     // �w�背�C���[�̕`��

    template <typename Shape>
    bool withinCollision(const Shape& area)
    {
        bool ret = false;
        for (const auto& collision : _collisions) {
            if (collision.intersects(area)) {
                ret = true;
                break;
            }
        }
        return ret;
    }

    TextureRegion findTileToDisplay(const int32& index);

    inline int32 cx() const { return -(_mapSize.x / 2); };
    inline int32 ex() const { return _mapSize.x / 2; };
    inline int32 cy() const { return -(_mapSize.y / 2); };
    inline int32 ey() const { return _mapSize.y / 2; };
    inline int32 w() const { return _mapSize.x; };
    inline int32 h() const { return _mapSize.y; };
    inline Size size() const { return _mapSize; };
};
