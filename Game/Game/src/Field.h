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
// 1. tileTexturePaths��chipSizes�̗v�f���������ɂȂ�悤�Ăяo�����ŕۏ؂��邱��
// 2. TiledMapEditor�c�[���̃^�C��ID�ilayer.data�j���c�[�����ł̃^�C���Z�b�g�ǂݍ��ݏ��Ŋ���U���邽��
//    tileTexturePaths�ɓn���p�X�̏��Ԃ�ID�Ɠ������ԁi���j�Ƃ��邱�Ɓ@�i���F�^�C���Z�b�g���G�f�B�^�ɓǂݍ��񂾏��j
// 3. �S���C���[�̃T�C�Y�͓����ł��邱�ƁB(FieldSize�̎擾���ȈՉ����邽�߁j
// 4. �P�̃��C���[�ɈقȂ�T�C�Y�̃^�C���Z�b�g�͎g�p���Ȃ��B�P���C���[(16, 16), 2���C���[(32, 32)��OK�B�A��3�͌���B
class Field
{
private:
    Array<TiledMapTexture> _tiles;
    Array<Layer> _layers;
    Size _size;
public:
    Field();

    Field(const Array<FilePath>& tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath);
    
    void draw(const bool& lower = true, const bool& upper = true, const bool& worldPos = true);   // ���ʏ�ʃ��C���[�`��i�f�t�H���g�S���C���[�`��j
    
    void draw(const int32& index, const bool& worldPos = true);     // �w�背�C���[�̕`��

    TextureRegion findTileToDisplay(const int32& index, Size& chipSize);

    inline int32 cx() const { return -(_size.x / 2); };
    inline int32 ex() const { return _size.x / 2; };
    inline int32 cy() const { return -(_size.y / 2); };
    inline int32 ey() const { return _size.y / 2; };
    inline int32 w() const { return _size.x; };
    inline int32 h() const { return _size.y; };
    inline Size size() const { return _size; };
};
