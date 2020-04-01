#pragma once
# include "Field.h" 
# include "GameObjectManager.h" 
# include "Player.h"
# include "Battler.h"

class FieldManager
{
public:
	inline static FieldManager& getInstance()
	{
		if (!_instance) {
			_instance = new FieldManager();
		}
		return *_instance;
	}

	inline Field getCurrentField() { return _fields[_currentField]; };
	inline Array<std::shared_ptr<GameObject>> getAllys() { return _allyManager.getObjects(); };
	inline Array<std::shared_ptr<GameObject>> getEnemys() { return _enemyManager.getObjects(); };

	void transition(const String& fieldName);
	void update();
	void draw();

private:
	FieldManager();
	static FieldManager* _instance;
	std::map<String, Field> _fields;
	String _currentField;

	GameObjectManager _allyManager;		// 味方キャラ管理用
	GameObjectManager _enemyManager;	// エネミー管理用

	enum Info {
		VALUE = 0,
		NAME,
		MAPDATA_PATH,
		TEXTURE_PATH_BEGIN,
	};
};