#include "Field.h"
#include "Common.hpp"

Field::Field()
    : _fieldId(0)
{};

Field::Field(EventManager& evMng, const int32& fieldId, const Array<FilePath>& tileTexturePaths, const FilePath& mapDataPath, const bool& worldPos)
    : _fieldId(fieldId)
{
    // �}�b�v�f�[�^�ǂݍ���
    const JSONReader mapData(mapDataPath);
    if (!mapData)
        throw Error(U"Failed to read mapDataFile.json");

    // �J�ڃC�x���g�f�[�^�̓ǂݍ���
    const CSVData transitionEventData(U"Asset/TransitionEventData.csv");
    if (!transitionEventData)
        throw Error(U"Failed to load TransitionEventData.csv");

    // ���ʂ̃}�b�v���ǂݍ���
    _mapSize = Size(
        { mapData[U"tilewidth"].get<int32>() * mapData[U"width"].get<int32>()
        , mapData[U"tileheight"].get<int32>()* mapData[U"height"].get<int32>() });
    
    _tileSize = Size(mapData[U"tilewidth"].get<int32>(), mapData[U"tileheight"].get<int32>());
    _tileNumWH = Size(mapData[U"width"].get<int32>(), mapData[U"height"].get<int32>());

    // �e���C���[�f�[�^�̓ǂݍ���
    for (const auto& layer : mapData[U"layers"].arrayView()) {
        
        if (U"event" == layer[U"name"].getString()) {

            // �J�ڃC�x���g����
            for (const auto& event : layer[U"objects"].arrayView()) {
                int32 eventId = 0;
                Event::Type type = Event::Type::Transition;
                for (const auto& property : event[U"properties"].arrayView()) {

                    if (U"EventID" == property[U"name"].getString()) {
                        eventId = property[U"value"].get<int32>();
                    }
                    else if (U"Type" == property[U"name"].getString()) {
                        if (1 == property[U"value"].get<int32>())
                            type = Event::Type::Main;
                        else if (2 == property[U"value"].get<int32>())
                            type = Event::Type::Sub;
                        else if (3 == property[U"value"].get<int32>())
                            type = Event::Type::Transition;
                    }
                }

                SceneState scene = SceneState::Non, toScene = SceneState::Non;
                double toPosX = 0.0, toPosY = 0.0;
                for (size_t row = 1; row < transitionEventData.rows(); ++row) {
                    if (eventId != Parse<int32>(transitionEventData[row][0]))    // �����̃C�x���gID�𑖍�
                        continue;

                    for (const auto data : MapIdToSceneTable) {
                        if (data.mapId == Parse<int32>(transitionEventData[row][3]))
                            scene = data.scene;

                        if (data.mapId == Parse<int32>(transitionEventData[row][4]))
                            toScene = data.scene;
                    }

                    toPosX = Parse<double>(transitionEventData[row][5]);
                    toPosY = Parse<double>(transitionEventData[row][6]);
                    break;
                }
                
                const double evPosX = event[U"x"].get<double>() - _mapSize.x / 2;
                const double evPosY = event[U"y"].get<double>() - _mapSize.y / 2;

                RectF region(evPosX, evPosY, event[U"width"].get<double>(), event[U"height"].get<double>());
                evMng.registTransitionEvent(fieldId, Event(eventId, region, scene, toScene, Vec2(toPosX, toPosY), type));

            }
        }
        else {

            // �}�b�v����
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

            for (const auto& property : layer[U"properties"].arrayView()) {
                if (U"Collision" == property[U"name"].getString())
                    temp.isCollisionLayer = property[U"value"].get<bool>();
                if (U"Hide" == property[U"name"].getString())
                    temp.isHideLayer = property[U"value"].get<bool>();
                if (U"Lower" == property[U"name"].getString())
                    temp.isLowerLayer = property[U"value"].get<bool>();
            }

            _layers.push_back(temp);
        }
    }

    // �R���W�����f�[�^�̓ǂݍ���
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

    // �^�C���e�N�X�`���̓ǂݍ���
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

        if (upper && !(layer.isLowerLayer)) {   // ���C���[�� �� �\�����鏇 �Ƒz�肵�������ł̏����B�\�����鏇�łȂ��Ȃ�ʓrfor����p�ӂ���
            validLayer.emplace_back(layer);
        }
    }
    
    // �}�b�v��\�����Ă����ʗ̈�̂ݕ`�悷��v�Z
    const int32 cx = (camera.getRegion().x + _mapSize.x / 2) / _tileSize.x ;                            // �}�b�v�\���J�n : x�C���f�b�N�X
    const int32 ex = (camera.getRegion().x + _mapSize.x / 2 + camera.getRegion().w) / _tileSize.x + 1;  // �}�b�v�\���I�� : x�C���f�b�N�X
    const int32 cy = (camera.getRegion().y + _mapSize.y / 2) / _tileSize.y;                             // �}�b�v�\���J�n : y�C���f�b�N�X
    const int32 ey = (camera.getRegion().y + _mapSize.y / 2 + camera.getRegion().h) / _tileSize.y + 1;  // �}�b�v�\���I�� : y�C���f�b�N�X

    for (const auto& layer : validLayer) {
        
        for (int32 y = cy; y < ey; ++y) {
            for (int32 x = cx; x < ex; ++x) {

                const int32 index = y * layer.width + x;
                if (0 >= layer.data[index]) {                       // �}�b�v�f�[�^���Ȃ���Ύ����W��
                    continue;
                }

                if (true == worldPos) {
                    findTileToDisplay(layer.data[index])
                        .draw(x * _tileSize.x - _mapSize.x / 2,
                              y * _tileSize.y - _mapSize.y / 2);
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
            if (0 >= _layers[layerIndex].data[index]) {                       // �}�b�v�f�[�^���Ȃ���Ύ����W��
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