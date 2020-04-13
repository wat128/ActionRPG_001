#pragma once
#include "EffectManager.h"
#include "ObjectBase.h"

enum class DisplayLayer;

// ��莞�ԂŃR�}��؂�ւ���G�t�F�N�g / �{�N���X�p���ŉσR�}�؂�ւ��̃G�t�F�N�g���������\
class EffectAnime : public std::enable_shared_from_this<EffectAnime>, public ObjectBase
{
public:

    enum class State {
        Complete,
        Continue,
    };

    enum class DisplayFormat {
        Normal,                 // �ʏ�Đ�
        NmlReverse,             // �t�Đ��i�ʏ�j
        NmlFlipped,             // �㉺���]�Đ��i�ʏ�j
        NmlFlippedReverse,      // �㉺���]�t�Đ��i�ʏ�j
        Mirror,                 // ���E����Đ�
        MirReverse,
        MirFlipped,
        MirFlippedReverse,
        _90deg,                 // 90�x��]�Đ�
        _90degReverse,
        _90degFlipped,
        _90degFlippedReverse,
        _270deg,                // 270(-90)�x��]�Đ�
        _270degReverse,
        _270degFlipped,
        _270degFlippedReverse,
    };

    EffectAnime();

    EffectAnime(
        const String textureStr,
        const DisplayLayer layer,
        const Size tileSize,
        const double endTime,
        const int32 maxCount,
        const int32 xNum,
        const int32 yNum,
        const Size region);

    virtual EffectAnime::State update(
        const Vec2& pos,
        const DisplayFormat& format,
        const int32& dispPriority = IGNORE,
        const DisplayLayer& layer = DisplayLayer::Ignore);

    virtual void draw();

    bool isActive() const { return _isActive; }
    void initialize();           // �{�N���X���ŕύX����郁���o������������

    inline DisplayLayer getLayer() const { return _layer; }

private:
    const Texture _texture;     // �e�N�X�`��
    DisplayLayer _layer;        // �\�����C���[
    const Size _tileSize;       // 1�R�}�̃T�C�Y
    const double _endTime;      // �G�t�F�N�g�I���܂ł̎���   
    const int32 _maxCount;      // �S�R�}��
    const int32 _xNum;          // ���̃R�}��
    const int32 _yNum;          // �c�̃R�}��
    const Size _region;         // �\���̈�
    Vec2 _pos;                  // �\���ʒu

    double _accum;              // ���Ԍv���p
    int32 _count;               // �R�}�̃C���f�b�N�X�p
    Vec2 _tilePos;              // �\���^�C�����������W
    bool _isActive;             // �G�t�F�N�g���s����
    DisplayFormat _format;      // �G�t�F�N�g�̍Đ��`��
};
