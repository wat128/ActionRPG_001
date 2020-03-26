#include "Field.h"

Field::Field() {};

Field::Field(const Array<FilePath>& tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath)
{
    // タイルテクスチャの読み込み
    int32 index = 0;
    for (const auto& path : tileTexturePaths) {
        TiledMapTexture texture(path, chipSizes[index]);
        _tiles.push_back(texture);
        ++index;
    }

    // マップデータ読み込み
    const JSONReader mapData(mapDataPath);
    if (!mapData)
        throw Error(U"Failed to read mapDataFile.json");

    for (const auto& layer : mapData[U"layers"].arrayView()) {
        Layer temp;
        for (const auto& tileData : layer[U"data"].arrayView()) {
            temp.data.push_back(tileData.get<int32>());
        }

        temp.height = layer[U"height"].get<int32>();
        temp.id = layer[U"id"].get<int32>();
        temp.name = layer[U"name"].get<String>();
        temp.opacity = layer[U"opacity"].get<int32>();
        temp.type = layer[U"type"].get<String>();
        temp.visible = layer[U"visible"].get<bool>();
        temp.width = layer[U"width"].get<int32>();
        temp.x = layer[U"x"].get<int32>();
        temp.y = layer[U"y"].get<int32>();

        for (const auto& property : layer[U"properties"].arrayView()){
            if (U"Collision" == property[U"name"].getString())
                temp.isCollisionLayer = property[U"value"].get<bool>();
            if (U"Hide" == property[U"name"].getString())
                temp.isHideLayer = property[U"value"].get<bool>();
            if (U"Lower" == property[U"name"].getString())
                temp.isLowerLayer = property[U"value"].get<bool>();
        }

        _layers.push_back(temp);
    }

    // 共通のマップ情報読み込み
    _size = Size(
        { mapData[U"tilewidth"].get<int32>() * mapData[U"width"].get<int32>()
        , mapData[U"tileheight"].get<int32>()* mapData[U"height"].get<int32>() });

}

void Field::draw(const bool& lower, const bool& upper, const bool& worldPos)
{
    Size chipSize(0, 0);

    Array<Layer> validLayer;
    for (const auto& layer : _layers) {
        if (layer.isHideLayer || layer.isCollisionLayer)
            continue;

        if (lower && layer.isLowerLayer) {
            validLayer.emplace_back(layer);
            continue;
        }

        if (upper && !(layer.isLowerLayer)) {   // レイヤー順 ＝ 表示する順 と想定したうえでの処理。表示する順でないなら別途for文を用意する
            validLayer.emplace_back(layer);
        }
    }

    for (const auto& layer : validLayer) {
        
        for (int32 y = 0; y < layer.height; ++y) {
            for (int32 x = 0; x < layer.width; ++x) {

                const int32 index = y * layer.width + x;
                if (0 >= layer.data[index]) {                       // マップデータがなければ次座標へ
                    continue;
                }

                if (true == worldPos) {
                    findTileToDisplay(layer.data[index], chipSize)
                        .draw(x * chipSize.x - layer.width / 2 * chipSize.x,
                              y * chipSize.y - layer.height / 2 * chipSize.y);
                }
                else {
                    findTileToDisplay(layer.data[index], chipSize)
                        .draw(x * (chipSize.x), y * (chipSize.y));
                }
            }
        }
    }
}

void Field::draw(const int32& layerIndex, const bool& worldPos)
{
    if (_layers[layerIndex].isHideLayer || _layers[layerIndex].isCollisionLayer)
        return;

    Size chipSize(0, 0);
    for (int32 y = 0; y < _layers[layerIndex].height; ++y) {
        for (int32 x = 0; x < _layers[layerIndex].width; ++x) {

            const int32 index = y * _layers[layerIndex].width + x;
            if (0 >= _layers[layerIndex].data[index]) {                       // マップデータがなければ次座標へ
                continue;
            }
            if (true == worldPos) {
                findTileToDisplay(_layers[layerIndex].data[index], chipSize)
                    .draw(x * chipSize.x - _layers[layerIndex].width / 2 * chipSize.x,
                          y * chipSize.y - _layers[layerIndex].height / 2 * chipSize.y);
            }
            else {
                findTileToDisplay(_layers[layerIndex].data[index], chipSize)
                    .draw(x * (chipSize.x), y * (chipSize.y));
            }
        }
    }
}

TextureRegion Field::findTileToDisplay(const int32& index, Size& chipSize)
{
    int32 offset = 0;
    for (auto& tile : _tiles) {
        if (tile.sum() + offset > index) {
            chipSize = tile.chipSize();
            return tile.getTile(index - 1 - offset);
        }
        offset += tile.sum();
    }
}