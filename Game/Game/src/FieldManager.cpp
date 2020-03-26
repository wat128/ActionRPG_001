# include "FieldManager.h"

FieldManager* FieldManager::_instance = nullptr;

FieldManager::FieldManager()
	: _fieldList()
	, _currentField(U"テストマップ")
{
	const int32 baseRow = 1;	// 取得を始める行
	const int32 nextPath = 2;	// TEXTURE_PATH_01 → TEXTURE_PATH_02のオフセット

	CSVData fieldData(U"Asset/FieldData.csv");
	if (!fieldData)
		throw Error(U"Failed to load FieldData.csv");

	for (size_t row = baseRow; row < fieldData.rows(); ++row) {

		Array<FilePath> tilePaths;
		for (size_t column = TEXTURE_PATH_BEGIN; column < fieldData.columns(row); column += nextPath) {
			if (Parse<FilePath>(fieldData[row][column]).empty())
				break;

			tilePaths.emplace_back(Parse<FilePath>(fieldData[row][column]));
		}

		Array<Size> chipSizes;
		for (size_t column = CHIPSIZE_BEGIN; column < fieldData.columns(row); column += nextPath) {
			if (Parse<FilePath>(fieldData[row][column]).empty())
				break;

			chipSizes.emplace_back(Parse<Size>(fieldData[row][column]));
		}

		_fieldList.emplace(
			Parse<String>(fieldData[row][NAME]),
			Field(tilePaths, chipSizes, Parse<FilePath>(fieldData[row][MAPDATA_PATH])));
	}
};

void FieldManager::transition(const String& fieldName)
{
	if (0 >= _fieldList.count(fieldName))
		return;

	_currentField = fieldName;
}