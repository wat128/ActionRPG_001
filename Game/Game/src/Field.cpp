#include "Field.h"

Field::Field() {};

Field::Field(const Array<FilePath> tileTexturePaths, const Array<Size>& chipSizes, const FilePath& mapDataPath)
{
    // �^�C���e�N�X�`���̓ǂݍ���
    int32 index = 0;
    for (const auto& path : tileTexturePaths) {
        TiledTexture texture(path, chipSizes[index]);
        _tiles.push_back(texture);
        ++index;
    }

    // �}�b�v�f�[�^�ǂݍ���
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

        _layers.push_back(temp);
    }

    // ���ʂ̃}�b�v���ǂݍ���
    //_square = Size({ mapData[U"tilewidth"].get<int32>(), mapData[U"tileheight"].get<int32>() });

}

void Field::draw()
{
    Size chipSize(0, 0);

    for (const auto& layer : _layers) {
        for (int32 y = 0; y < layer.height; ++y) {
            for (int32 x = 0; x < layer.width; ++x) {

                const int32 index = y * layer.width + x;
                if (0 >= layer.data[index]) {                       // �}�b�v�f�[�^���Ȃ���Ύ����W��
                    continue;
                }

                FindTileToDisplay(layer.data[index], chipSize)
                    .draw(x * (chipSize.x), y * (chipSize.y));
            }
        }
    }
}

TextureRegion Field::FindTileToDisplay(const int32& index, Size& chipSize)
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