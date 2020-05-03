#pragma once
#include "Common.hpp"

class Event
{
public:
	// �X�g�[���[��̃C�x���g�̐i�����
	enum class State {
		Non,		// ��ԂȂ��i��ɃA�N�e�B�u�j
		Waiting,	// �����s
		Working,	// ���s��
		Completed	// ����
	};

	enum class Type {
		Non,
		Main,
		Sub,
		Transition
	};

	Event()
		: _scene(SceneState::Non)
		, _eventId(-1)
		, _type(Type::Non)
		, _state(State::Non)
		, _region(Vec2(0,0), Size(0,0))
		, _toScene(SceneState::Non)
		, _toPos(Vec2(0,0))
	{}

	Event(
		const int32& eventId,
		const RectF& region,
		const SceneState& scene,
		const SceneState& toScene,
		const Vec2& toPos,
		const Type type,
		const State state = State::Non)
		: _scene(scene)
		, _eventId(eventId)
		, _type(type)
		, _state(state)
		, _region(region)
		, _toScene(toScene)
		, _toPos(toPos)
	{};

	inline SceneState getScene() const { return _scene; }
	inline int32 getEventId() const { return _eventId; }
	inline Type getType() const { return _type; }
	inline State getState() const { return _state; }
	inline RectF getRegion() const { return _region; }
	inline SceneState getToScene() const { return _toScene; }
	inline Vec2 getToPos() const { return _toPos; }

private:
	const SceneState _scene;	// �ǂ̃V�[���̃C�x���g��
	const int32 _eventId;
	const Type _type;
	State _state;
	const RectF _region;
	const SceneState _toScene;	// �ǂ̃V�[���Ɉړ����邩
	const Vec2 _toPos;			// �V�[���ړ���̃L�������W
};

