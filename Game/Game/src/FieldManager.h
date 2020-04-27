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

	inline Field getCurrentField() { return _fields[_currentFieldId]; };
	inline Array<std::shared_ptr<GameObject>> getAllys() const { return _allyManager.getObjects(); };
	inline Array<std::shared_ptr<GameObject>> getEnemys() const { return _enemyManager.getObjects(); };

	void transition(const int32& fieldId);
	void update();
	void draw();

private:
	FieldManager();
	static FieldManager* _instance;
	std::map<int32, Field> _fields;
	int32 _currentFieldId;

	GameObjectManager _allyManager;		// �����L�����Ǘ��p
	GameObjectManager _enemyManager;	// �G�l�~�[�Ǘ��p
	EffectManager _effectManager;		// �G�t�F�N�g�Ǘ��p

	enum Info {
		MAPID = 0,
		NAME,
		MAPDATA_PATH,
		TEXTURE_PATH_BEGIN,
	};
};