#pragma once
# include "Field.h" 
# include "GameObjectManager.h" 
# include "Player.h"
# include "Battler.h"
# include "Common.hpp"
# include "EffectManager.h"

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
	inline Array<std::shared_ptr<GameObject>> getAllys() const { return _allyManager.getObjects(); };
	inline Array<std::shared_ptr<GameObject>> getEnemys() const { return _enemyManager.getObjects(); };

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
	EffectManager _effectManager;		// エフェクト管理用

	enum Info {
		VALUE = 0,
		NAME,
		MAPDATA_PATH,
		TEXTURE_PATH_BEGIN,
	};
};