#pragma once
#include "FieldManager.h"

class FieldReferee
{
public:
	inline static FieldReferee& getInstance()
	{
		if (!_instance) {
			_instance = new FieldReferee();
		}
		return *_instance;
	}

	template <typename Shape>
	bool isCollision(const Shape& area) const
	{
		if(FieldManager::getInstance().getCurrentField().withinCollision(area))
			return true;

		Array<GameObject*> enemys = FieldManager::getInstance().getEnemyList();
		for (const auto& enemy : enemys) {
			if (enemy->withinCollision(area))
				return true;
		}

		return false;
	}

private:
	FieldReferee();
	static FieldReferee* _instance;
};