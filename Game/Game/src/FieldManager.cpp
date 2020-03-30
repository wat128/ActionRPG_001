# include "FieldManager.h"

FieldManager* FieldManager::_instance = nullptr;

FieldManager::FieldManager()
	: _fieldList()
	, _currentField(U"テストマップ")
	, _allyManager()
	//, _enemyManager()
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

		_fieldList.emplace(
			Parse<String>(fieldData[row][NAME]),
			Field(tilePaths, Parse<FilePath>(fieldData[row][MAPDATA_PATH])));
	}

	// テスト用：ゲームオブジェクト生成
	_allyManager.spawn<Player>(1, Vec2(0, 0));
	//_enemyManager.spawn<Battler>(10, Vec2(30, 0));

};

void FieldManager::transition(const String& fieldName)
{
	if (0 >= _fieldList.count(fieldName))
		return;

	_currentField = fieldName;
}

void FieldManager::update()
{
	_allyManager.update();
	//_enemyManager.update();
}

void FieldManager::draw()
{
	getCurrentField().draw(true, false);
	//_enemyManager.draw();
	_allyManager.draw();
	getCurrentField().draw(false, true);
}