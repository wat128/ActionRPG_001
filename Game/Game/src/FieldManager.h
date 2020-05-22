#pragma once
# include "Field.h" 
# include "GameObjectManager.h" 
# include "Player.h"
# include "Battler.h"
# include "Common.hpp"
# include "EffectManager.h"
# include "EventManager.hpp"

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

	inline void clearEnemys() { _enemyManager.clearObjects(); }
	void spawnEnemys();

	bool chkActiveEvent() { return _eventManager.chkActiveEvent(); }	// EventManager�̊֐��R�����g�Q�ƕK�{
	Event getActiveEvent() { return _eventManager.getActiveEvent(); }	// EventManager�̊֐��R�����g�Q�ƕK�{
	bool setActiveEvent(const int32& fieldId, const RectF& region) { return _eventManager.setActiveEvent(fieldId, region); }
	void initActiveEvent() { _eventManager.initActiveEvent(); }

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
	EventManager _eventManager;			// �C�x���g�Ǘ��p

	enum Info {
		MAPID = 0,
		NAME,
		MAPDATA_PATH,
		TEXTURE_PATH_BEGIN,
	};
};