#pragma once
# include "TiledTexture.h"

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
};

// --- �g�p��̒��ӓ_ ---
// 1. tileTexturePath��chipSizes�̗v�f���������ɂȂ�悤�Ăяo�����ŕۏ؂��邱��
// 2. TiledMapEditor�c�[���̃^�C��ID�ilayer.data�j���^�C���Z�b�g�ǂݍ��ݏ��Ŋ���U���邽��
//    tileTexturePaths�ɓn���p�X�̏��Ԃ�ID�Ɠ������ԁi���j�Ƃ��邱�Ɓ@�i���F�^�C���Z�b�g���G�f�B�^�ɓǂݍ��񂾏��j

class Field
{
private:
    Array<TiledTexture> _tiles;
    Array<Layer> _layers;
    // Size _square;                    // 1�}�X�̃T�C�Y
public:
    Field();

    Field(const Array<FilePath> tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath);
    
    void draw();                        // �S���C���[�`��
    
    void draw(const int32 index);       // �w�背�C���[�̕`��

    TextureRegion FindTileToDisplay(const int32& index, Size& chipSize);
};
