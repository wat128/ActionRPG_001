#pragma once
#include "EffectManager.h"
#include "ObjectBase.h"

enum class DisplayLayer;

// 一定時間でコマを切り替えるエフェクト / 本クラス継承で可変コマ切り替えのエフェクト等が実装可能
class EffectAnime : public std::enable_shared_from_this<EffectAnime>, public ObjectBase
{
public:

    enum class State {
        Complete,
        Continue,
    };

    enum class DisplayFormat {
        Normal,                 // 通常再生
        NmlReverse,             // 逆再生（通常）
        NmlFlipped,             // 上下反転再生（通常）
        NmlFlippedReverse,      // 上下反転逆再生（通常）
        Mirror,                 // 左右判定再生
        MirReverse,
        MirFlipped,
        MirFlippedReverse,
        _90deg,                 // 90度回転再生
        _90degReverse,
        _90degFlipped,
        _90degFlippedReverse,
        _270deg,                // 270(-90)度回転再生
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
    void initialize();           // 本クラス内で変更されるメンバを初期化する

    inline DisplayLayer getLayer() const { return _layer; }

private:
    const Texture _texture;     // テクスチャ
    DisplayLayer _layer;        // 表示レイヤー
    const Size _tileSize;       // 1コマのサイズ
    const double _endTime;      // エフェクト終了までの時間   
    const int32 _maxCount;      // 全コマ数
    const int32 _xNum;          // 横のコマ数
    const int32 _yNum;          // 縦のコマ数
    const Size _region;         // 表示領域
    Vec2 _pos;                  // 表示位置

    double _accum;              // 時間計測用
    int32 _count;               // コマのインデックス用
    Vec2 _tilePos;              // 表示タイルを示す座標
    bool _isActive;             // エフェクト実行中か
    DisplayFormat _format;      // エフェクトの再生形式
};
