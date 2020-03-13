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

// --- 使用上の注意点 ---
// 1. tileTexturePathとchipSizesの要素数が同等になるよう呼び出し側で保証すること
// 2. TiledMapEditorツールのタイルID（layer.data）がタイルセット読み込み順で割り振られるため
//    tileTexturePathsに渡すパスの順番もIDと同じ順番（※）とすること　（※：タイルセットをエディタに読み込んだ順）

class Field
{
private:
    Array<TiledTexture> _tiles;
    Array<Layer> _layers;
    // Size _square;                    // 1マスのサイズ
public:
    Field();

    Field(const Array<FilePath> tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath);
    
    void draw();                        // 全レイヤー描画
    
    void draw(const int32 index);       // 指定レイヤーの描画

    TextureRegion FindTileToDisplay(const int32& index, Size& chipSize);
};
