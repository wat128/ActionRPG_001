# include "FieldManager.h"
# include "FieldReferee.h"
# include "ObjectBase.h"

FieldManager* FieldManager::_instance = nullptr;

FieldManager::FieldManager()
	: _fields()
	, _currentFieldId(1)		// 暫定
	, _allyManager()
	, _enemyManager()
	, _effectManager()
	, _eventManager()
{
	// フィールドマップデータ取得 & 生成
	const int32 baseRow = 1;

	CSVData fieldData(U"Asset/FieldData.csv");
	if (!fieldData)
		throw Error(U"Failed to load FieldData.csv");

	for (size_t row = baseRow; row < fieldData.rows(); ++row) {

		Array<FilePath> tilePaths;
		for (size_t column = TEXTURE_PATH_BEGIN; column < fieldData.columns(row); ++column) {
			if (Parse<FilePath>(fieldData[row][column]).empty())
				break;

			tilePaths.emplace_back(Parse<FilePath>(fieldData[row][column]));
		}

		const int32 fieldId = Parse<int32>(fieldData[row][MAPID]);
		_fields.emplace(
			fieldId,
			Field(_eventManager, fieldId, tilePaths, Parse<FilePath>(fieldData[row][MAPDATA_PATH])));
	}

	// テスト用：ゲームオブジェクト生成
	_allyManager.spawn<Player>(1, Vec2(0, 0));
	_allyManager.spawn<Battler>(2, Vec2(0, 20));

};

void FieldManager::spawnEnemys()
{
	const auto spawnEnemysData = getCurrentField().getSpawnEnemyData();
	for (const auto& enemyData : spawnEnemysData) {
		_enemyManager.spawn<Battler>(enemyData.first, enemyData.second);
	}
}

void FieldManager::transition(const int32& fieldId)
{
	if (0 >= _fields.count(fieldId))
		return;

	_currentFieldId = fieldId;
}

void FieldManager::update()
{
	FieldReferee::getInstance().executeQueue();
	_allyManager.update();
	_enemyManager.update();
	_effectManager.update();
}

void FieldManager::draw()
{
	const Array<std::shared_ptr<GameObject>> allys = _allyManager.getObjects();
	const Array<std::shared_ptr<GameObject>> enemys = _enemyManager.getObjects();
	const Array<std::shared_ptr<EffectAnime>> effects = _effectManager.getEffects();
	Array<std::shared_ptr<ObjectBase>> displayOrder;

	for (const auto& ally : allys)
		displayOrder.emplace_back(ally);

	for (const auto& enemy : enemys)
		displayOrder.emplace_back(enemy);

	for (const auto& effect : effects) {
		if(effect->getLayer() == DisplayLayer::Middle)
			displayOrder.emplace_back(effect);
	}

	displayOrder.sort_by([](const std::shared_ptr<ObjectBase> a, const std::shared_ptr<ObjectBase> b)
		{
			return a->_dispPriority < b->_dispPriority;
		});

	getCurrentField().draw(true, false);

	_effectManager.draw(DisplayLayer::Bottom);
	_effectManager.draw(DisplayLayer::SecondBottom);

	for (const auto& obj : displayOrder)
		obj->draw();

	_effectManager.draw(DisplayLayer::SecondTop);
	_effectManager.draw(DisplayLayer::Top);

	getCurrentField().draw(false, true);

}	