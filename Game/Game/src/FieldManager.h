#pragma once
# include "Field.h" 

class FieldManager
{
public:
	inline static FieldManager* getInstance()
	{
		if (!_instance) {
			_instance = new FieldManager();
		}
		return _instance;
	}

	inline Field getCurrentField() { return _fieldList[_currentField]; };

	void transition(const String& fieldName);
	
	//メモ：Fieldクラスで座標を引数で受け、コリジョン判定をする関数を作成する
private:
	FieldManager();
	static FieldManager* _instance;
	std::map<String, Field> _fieldList;
	String _currentField;

	enum Info {
		VALUE = 0,
		NAME,
		MAPDATA_PATH,
		TEXTURE_PATH_BEGIN,
		CHIPSIZE_BEGIN,
	};
};