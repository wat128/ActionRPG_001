# include "FieldReferee.h"
# include "EventManager.hpp"

FieldReferee* FieldReferee::_instance = nullptr;

FieldReferee::FieldReferee() {};

std::shared_ptr<GameObject> FieldReferee::getObj(const uint32& handle) const
{
	FieldManager& fieldMng = FieldManager::getInstance();

	for (const auto& ally : fieldMng.getAllys()) {
		if (ally->_handle == handle)
			return ally;
	}

	for (const auto& enemy : fieldMng.getEnemys()) {
		if (enemy->_handle == handle)
			return enemy;
	}

	return nullptr;
}

bool FieldReferee::exists(const uint32& handle, const RectF& region, const Group& targetGroup = Group::All)
{
	FieldManager& fieldMng = FieldManager::getInstance();

	if (Group::Allys == targetGroup || Group::All == targetGroup) {
		for (const auto& ally : fieldMng.getAllys()) {
			if (!region.intersects(ally->getPos()))
				continue;

			if (ally->_handle == handle)
				return true;
		}
	}

	if (Group::Enemys == targetGroup || Group::All == targetGroup) {
		for (const auto& enemy : fieldMng.getEnemys()) {
			if (!region.intersects(enemy->getPos()))
				continue;

			if (enemy->_handle == handle)
				return true;
		}
	}

	return false;
}

Array<uint32> FieldReferee::getObjHandle(const RectF& region, const Group& targetGroup = Group::All)
{
	Array<uint32> handles;
	FieldManager& fieldMng = FieldManager::getInstance();

	if (Group::Allys == targetGroup || Group::All == targetGroup) {
		for (const auto& ally : fieldMng.getAllys()) {
			if (region.intersects(ally->getPos()))
				handles.emplace_back(ally->_handle);
		}
	}

	if (Group::Enemys == targetGroup || Group::All == targetGroup) {
		for (const auto& enemy : fieldMng.getEnemys()) {
			if (region.intersects(enemy->getPos()))
				handles.emplace_back(enemy->_handle);
		}
	}
	return handles;
}

void FieldReferee::executeQueue()
{
	for (auto actor : _queue) {
		const int32& exp = std::get<0>(actor)->onDamage(std::get<1>(actor));
		std::get<2>(actor)(exp);
	}
	_queue.clear();
}