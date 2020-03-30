#include "Field.h"

Field::Field() {};

Field::Field(const Array<FilePath>& tileTexturePaths, const FilePath& mapDataPath, const bool& worldPos)
{
    // マップデータ読み込み
    const JSONReader mapData(mapDataPath);
    if (!mapData)
        throw Error(U"Failed to read mapDataFile.json");

    // 共通のマップ情報読み込み
    _mapSize = Size(
        { mapData[U"tilewidth"].get<int32>() * mapData[U"width"].get<int32>()
        , mapData[U"tileheight"].get<int32>()* mapData[U"height"].get<int32>() });
    
    _tileSize = Size(mapData[U"tilewidth"].get<int32>(), mapData[U"tileheight"].get<int32>());
    _tileNumWH = Size(mapData[U"width"].get<int32>(), mapData[U"height"].get<int32>());

    // 各レイヤーデータの読み込み
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

    // コリジョンデータの読み込み
    for (const auto& layer : _layers) {
        if (!layer.isCollisionLayer)
            continue;

        for (int32 y = 0; y < layer.height; ++y) {
            for (int32 x = 0; x < layer.width; ++x) {
                if (0 >= layer.data[y * layer.width + x])
                    continue;

                if (true == worldPos) {
                    _collisions.emplace_back(
                        Rect(x * _tileSize.x - layer.width / 2 * _tileSize.x
                            , y * _tileSize.y - layer.height / 2 * _tileSize.y
                            , _tileSize));
                }
                else {
                    _collisions.emplace_back(
                        Rect(x * (_tileSize.x)
                            , y * (_tileSize.y)
                            , _tileSize));
                }
            }
        }
    }

    // タイルテクスチャの読み込み
    for (const auto& path : tileTexturePaths) {
        TiledMapTexture texture(path, _tileSize);
        _tiles.push_back(texture);
    }
}

void Field::draw(const bool& lower, const bool& upper, const bool& worldPos)
{
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
                    findTileToDisplay(layer.data[index])
                        .draw(x * _tileSize.x - layer.width / 2 * _tileSize.x,
                              y * _tileSize.y - layer.height / 2 * _tileSize.y);
                }
                else {
                    findTileToDisplay(layer.data[index])
                        .draw(x * (_tileSize.x), y * (_tileSize.y));
                }
            }
        }
    }
}

void Field::draw(const int32& layerIndex, const bool& worldPos)
{
    if (_layers[layerIndex].isHideLayer || _layers[layerIndex].isCollisionLayer)
        return;

    for (int32 y = 0; y < _layers[layerIndex].height; ++y) {
        for (int32 x = 0; x < _layers[layerIndex].width; ++x) {

            const int32 index = y * _layers[layerIndex].width + x;
            if (0 >= _layers[layerIndex].data[index]) {                       // マップデータがなければ次座標へ
                continue;
            }
            if (true == worldPos) {
                findTileToDisplay(_layers[layerIndex].data[index])
                    .draw(x * _tileSize.x - _layers[layerIndex].width / 2 * _tileSize.x,
                          y * _tileSize.y - _layers[layerIndex].height / 2 * _tileSize.y);
            }
            else {
                findTileToDisplay(_layers[layerIndex].data[index])
                    .draw(x * (_tileSize.x), y * (_tileSize.y));
            }
        }
    }
}

TextureRegion Field::findTileToDisplay(const int32& index)
{
    int32 offset = 0;
    for (auto& tile : _tiles) {
        if (tile.sum() + offset > index) {
            return tile.getTile(index - 1 - offset);
        }
        offset += tile.sum();
    }
}