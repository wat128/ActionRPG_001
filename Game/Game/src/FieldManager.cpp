# include "FieldManager.h"

FieldManager* FieldManager::_instance = nullptr;

FieldManager::FieldManager()
	: _fields()
	, _currentField(U"テストマップ")
	, _allyManager()
	, _enemyManager()
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

		_fields.emplace(
			Parse<String>(fieldData[row][NAME]),
			Field(tilePaths, Parse<FilePath>(fieldData[row][MAPDATA_PATH])));
	}

	// テスト用：ゲームオブジェクト生成
	_allyManager.spawn<Player>(1, Vec2(0, 0));
	_enemyManager.spawn<Battler>(10, Vec2(50, 0));
	_enemyManager.spawn<Battler>(11, Vec2(-100, 0));

};

void FieldManager::transition(const String& fieldName)
{
	if (0 >= _fields.count(fieldName))
		return;

	_currentField = fieldName;
}

void FieldManager::update()
{
	_allyManager.update();
	_enemyManager.update();
	_effectManager.update();
}

void FieldManager::draw()
{
	const Array<std::shared_ptr<GameObject>> allys = _allyManager.getObjects();
	const Array<std::shared_ptr<GameObject>> enemys = _enemyManager.getObjects();
	Array<std::shared_ptr<GameObject>> displayOrder;

	for (const auto& ally : allys)
		displayOrder.emplace_back(ally);

	for (const auto& enemy : enemys)
		displayOrder.emplace_back(enemy);

	displayOrder.sort_by([](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b)
		{
			return (a->getPos().y < b->getPos().y);
		});

	getCurrentField().draw(true, false);
	
	for(const auto& obj : displayOrder)		// 描画（手前・奥）の関係から "GameObjectManager"が保持する
		obj->draw();						// 各objectへ直接draw()。設計上再検討すべきか

	getCurrentField().draw(false, true);
	
	_effectManager.draw(DisplayLayer::Middle);		// テスト用：　引数
}