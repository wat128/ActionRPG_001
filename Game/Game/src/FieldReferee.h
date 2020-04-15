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

	// 使用上メモ：ignoreObj に thisポインタを渡すことで自身のコリジョン判定を省略する
	template <typename Shape>
	bool canMove(const Shape& area, const std::shared_ptr<GameObject> ignoreObj) const
	{
		if (!ignoreObj)
			return false;

		FieldManager& fieldMng = FieldManager::getInstance();
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

	// 自分のインデックスを取得する。scopeはAllys, Enemysのみ有効。その他の場合-1を返す。
	int32 findMyIndex(const std::shared_ptr<GameObject>& target,const Group& group)
	{
		FieldManager& fieldMng = FieldManager::getInstance();
		int32 index = -1;
		int32 accum = 0;

		if (Group::Allys == group) {
			const Array<std::shared_ptr<GameObject>> allys = fieldMng.getAllys();
			for (const auto& ally : allys) {
				if (ally != target) {
					++accum;
					continue;
				}
				else if (ally == target) {
					index = accum;
				}
			}
		}
		else if (Group::Enemys == group) {
			const Array<std::shared_ptr<GameObject>> enemys = fieldMng.getEnemys();
			for (const auto& enemy : enemys) {
				if (enemy != target) {
					++accum;
					continue;
				}
				else if (enemy == target) {
					index = accum;
				}
			}
		}
		return index;
	}
	
	// 指定グループの指定インデックスのオブジェクトを取得する。当てはまらないならnullptr。
	std::shared_ptr<GameObject> getObj(const int32& index, const Group& group) const
	{
		FieldManager& fieldMng = FieldManager::getInstance();

		if (Group::Allys == group) {
			if (index >= fieldMng.getAllys().size())
				return nullptr;
			else
				return fieldMng.getAllys().at(index);
		}

		if (Group::Enemys == group) {
			if (index >= fieldMng.getEnemys().size())
				return nullptr;
			else
				return fieldMng.getEnemys().at(index);
		}

		return nullptr;
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