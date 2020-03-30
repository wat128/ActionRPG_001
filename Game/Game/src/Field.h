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

// --- 使用上の注意点 ---
// 1.Tiledで吐き出したマップデータのテクスチャ順にArrayでテクスチャのパスを渡すこと
// 2.全レイヤーのサイズは同等であること。(FieldSizeの取得を簡易化するため）
// 3.マップのタイルサイズとテクスチャのタイルサイズは同等サイズとして処理するため、
//   マップ作製の段階で同等サイズとすること
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
    
    void draw(const bool& lower = true, const bool& upper = true, const bool& worldPos = true);   // 下位上位レイヤー描画（デフォルト全レイヤー描画）
    
    void draw(const int32& index, const bool& worldPos = true);     // 指定レイヤーの描画

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
