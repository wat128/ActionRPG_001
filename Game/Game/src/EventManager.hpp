#pragma once
#include "Common.hpp"
#include "Event.hpp"

class EventManager
{
public:
	enum class State {
		Waiting,	// 未実行
		Working,	// 実行中
		Completed	// 完了
	};

	EventManager();

	void registTransitionEvent(const int32& fieldId, const Event& ev);	// 遷移イベントの登録
	
	// 指定領域内にイベントが存在すれば実行イベントに設定後true。なければ何もせずfalse。
	bool setActiveEvent(const int32& fieldId, const RectF& region);

	// アクティブイベントがあるかを判定する
	bool chkActiveEvent();
	// アクティブイベントを取得する（ chkActiveEvent() が true の時のみコールすること）
	Event getActiveEvent();

	//　アクティブイベントを非アクティブ化する
	void initActiveEvent();

private:
	struct ActiveEvent {
		Event::Type eventType;
		int32 eventId;
	}_activeEvent;	//実行イベント

	std::multimap<int32, Event> _transitionEvents;	// <マップID, イベント>
};

