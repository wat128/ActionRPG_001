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

	// 指定領域内に他コリジョンがあるかを判定し、あればキューに追加する
	template <typename Shape>
	void hitConfirm(const Shape& area, 
		const Group& targetGroup, 
		const Skill::Data& data, 
		std::function<void(const int32)> func = [](const int32& a){ return; })
	{
		bool ret = false;
		FieldManager& fieldMng = FieldManager::getInstance();

		if (Group::Allys == targetGroup) {
			const Array<std::shared_ptr<GameObject>> allys = fieldMng.getAllys();
			for (const auto& ally : allys) {
				if (ally->withinCollision(area))
					_queue.emplace_back(std::make_tuple(ally, data, func));
			}
		}
		else if (Group::Enemys == targetGroup) {
			const Array<std::shared_ptr<GameObject>> enemys = fieldMng.getEnemys();
			for (const auto& enemy : enemys) {
				if (enemy->withinCollision(area))
					_queue.emplace_back(std::make_tuple(enemy, data, func));
			}
		}
	}

	// 使用上メモ：ignoreObj に 自身のハンドルをを渡すことで自身のコリジョン判定を省略する
	template <typename Shape>
	bool canMove(const Shape& area, const uint32& ignoreObj) const
	{

		FieldManager& fieldMng = FieldManager::getInstance();
		if(fieldMng.getCurrentField().withinCollision(area))
			return false;

		const Array<std::shared_ptr<GameObject>> allys = fieldMng.getAllys();
		for (const auto& ally : allys) {
			if (ally->_handle == ignoreObj)
				continue;

			if (ally->withinCollisionForMove(area))
				return false;
		}

		const Array<std::shared_ptr<GameObject>> enemys = fieldMng.getEnemys();
		for (const auto& enemy : enemys) {
			if (enemy->_handle == ignoreObj)
				continue;

			if (enemy->withinCollisionForMove(area))
				return false;
		}

		return true;
	}

	// ハンドル値をもつオブジェクトを取得する。なければnullptrを返す。
	std::shared_ptr<GameObject> getObj(const uint32& handle) const
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

	// region内にhandleをもつバトルオブジェクトが存在するかを取得する
	bool exists(const uint32& handle, const RectF& region, const Group& targetGroup = Group::All)
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

	// region内にいるバトルオブジェクトのハンドルリストを取得する
	Array<uint32> getObjHandle(const RectF& region, const Group& targetGroup = Group::All) 
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

	void executeQueue()
	{
		for (auto actor : _queue) {
			const int32& exp = std::get<0>(actor)->onDamage(std::get<1>(actor));
			std::get<2>(actor)(exp);
		}
		_queue.clear();
	}

private:
	FieldReferee();
	static FieldReferee* _instance;
	Array<std::tuple<std::shared_ptr<GameObject>,Skill::Data, std::function<void(const int32&)>>> _queue;
};