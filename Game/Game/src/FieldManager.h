#pragma once
# include "Field.h" 
# include "GameObjectManager.h" 
# include "Player.h"
# include "Battler.h"

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
	inline Array<GameObject*> getAllyList() { return _allyManager.getObjList(); };
	inline Array<GameObject*> getEnemyList() { return _enemyManager.getObjList(); };

	void transition(const String& fieldName);
	void update();
	void draw();

private:
	FieldManager();
	static FieldManager* _instance;
	std::map<String, Field> _fieldList;
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