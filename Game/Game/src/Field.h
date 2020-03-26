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
// 1. tileTexturePathsとchipSizesの要素数が同等になるよう呼び出し側で保証すること
// 2. TiledMapEditorツールのタイルID（layer.data）がツール内でのタイルセット読み込み順で割り振られるため
//    tileTexturePathsに渡すパスの順番もIDと同じ順番（※）とすること　（※：タイルセットをエディタに読み込んだ順）
// 3. 全レイヤーのサイズは同等であること。(FieldSizeの取得を簡易化するため）
// 4. １つのレイヤーに異なるサイズのタイルセットは使用しない。１レイヤー(16, 16), 2レイヤー(32, 32)はOK。但し3は厳守。
class Field
{
private:
    Array<TiledMapTexture> _tiles;
    Array<Layer> _layers;
    Size _size;
public:
    Field();

    Field(const Array<FilePath>& tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath);
    
    void draw(const bool& lower = true, const bool& upper = true, const bool& worldPos = true);   // 下位上位レイヤー描画（デフォルト全レイヤー描画）
    
    void draw(const int32& index, const bool& worldPos = true);     // 指定レイヤーの描画

    TextureRegion findTileToDisplay(const int32& index, Size& chipSize);

    inline int32 cx() const { return -(_size.x / 2); };
    inline int32 ex() const { return _size.x / 2; };
    inline int32 cy() const { return -(_size.y / 2); };
    inline int32 ey() const { return _size.y / 2; };
    inline int32 w() const { return _size.x; };
    inline int32 h() const { return _size.y; };
    inline Size size() const { return _size; };
};
