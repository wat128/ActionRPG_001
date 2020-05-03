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

	// �w��̈���ɑ��R���W���������邩�𔻒肵�A����΃L���[�ɒǉ�����
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

	// �g�p�チ���FignoreObj �� ���g�̃n���h������n�����ƂŎ��g�̃R���W����������ȗ�����
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

	// �n���h���l�����I�u�W�F�N�g���擾����B�Ȃ����nullptr��Ԃ��B
	std::shared_ptr<GameObject> getObj(const uint32& handle) const;

	// region����handle�����o�g���I�u�W�F�N�g�����݂��邩���擾����
	bool exists(const uint32& handle, const RectF& region, const Group& targetGroup);

	// region���ɂ���o�g���I�u�W�F�N�g�̃n���h�����X�g���擾����
	Array<uint32> getObjHandle(const RectF& region, const Group& targetGroup);

	// �w��̈���ɃC�x���g������Ύ��s���C�x���g�ɐݒ肷��B�Ȃ���Ή������Ȃ��B
	inline void setActiveEvent(const RectF& region) 
	{
		auto& fieldMng = FieldManager::getInstance();
		const auto fieldId = fieldMng.getCurrentField().getFieldId();

		fieldMng.setActiveEvent(fieldId, region);
	}

	void executeQueue();

private:
	FieldReferee();
	static FieldReferee* _instance;
	Array<std::tuple<std::shared_ptr<GameObject>,Skill::Data, std::function<void(const int32&)>>> _queue;
};