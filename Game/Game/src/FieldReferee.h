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

	// 使用上メモ：ignoreObj に thisポインタを渡すことで自身のコリジョン判定を省略する
	template <typename Shape>
	bool canMove(const Shape& area, const std::shared_ptr<GameObject> ignoreObj) const
	{
		if (!ignoreObj)
			return false;

		FieldManager fieldMng = FieldManager::getInstance();
		if(fieldMng.getCurrentField().withinCollision(area))
			return false;

		const Array<std::shared_ptr<GameObject>> allys = fieldMng.getAllys();
		for (const auto& ally : allys) {
			if (ally == ignoreObj)
				continue;

			if (ally->withinCollisionForMove(area))
				return false;
		}

		const Array<std::shared_ptr<GameObject>> enemys = fieldMng.getEnemys();
		for (const auto& enemy : enemys) {
			if (enemy == ignoreObj)
				continue;

			if (enemy->withinCollisionForMove(area))
				return false;
		}

		return true;
	}

private:
	FieldReferee();
	static FieldReferee* _instance;
};