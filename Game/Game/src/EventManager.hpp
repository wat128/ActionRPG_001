#pragma once
#include "Common.hpp"
#include "Event.hpp"

class EventManager
{
public:
	enum class State {
		Waiting,	// �����s
		Working,	// ���s��
		Completed	// ����
	};

	EventManager();

	void registTransitionEvent(const int32& fieldId, const Event& ev);	// �J�ڃC�x���g�̓o�^
	
	// �w��̈���ɃC�x���g�����݂���Ύ��s�C�x���g�ɐݒ��true�B�Ȃ���Ή�������false�B
	bool setActiveEvent(const int32& fieldId, const RectF& region);

	// �A�N�e�B�u�C�x���g�����邩�𔻒肷��
	bool chkActiveEvent();
	// �A�N�e�B�u�C�x���g���擾����i chkActiveEvent() �� true �̎��̂݃R�[�����邱�Ɓj
	Event getActiveEvent();

	//�@�A�N�e�B�u�C�x���g���A�N�e�B�u������
	void initActiveEvent();

private:
	struct ActiveEvent {
		Event::Type eventType;
		int32 eventId;
	}_activeEvent;	//���s�C�x���g

	std::multimap<int32, Event> _transitionEvents;	// <�}�b�vID, �C�x���g>
};

