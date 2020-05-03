#include "EventManager.hpp"

EventManager::EventManager()
	: _transitionEvents()
	, _activeEvent()
{}

void EventManager::registTransitionEvent(const int32& fieldId, const Event& ev)
{
	_transitionEvents.emplace(fieldId, ev);
}

bool EventManager::setActiveEvent(const int32& fieldId, const RectF& region)
{
	// 暫定：遷移イベントのみを対象とする
	for (auto& event : _transitionEvents) {
		if (fieldId != event.first)
			continue;

		if (event.second.getRegion().intersects(region)) {
			_activeEvent.eventType = event.second.getType();
			_activeEvent.eventId = event.second.getEventId();
			return true;
		}
	}
	return false;
}

bool EventManager::chkActiveEvent()
{
	if (0 < _activeEvent.eventId)
		return true;
	
	return false;
}

Event EventManager::getActiveEvent()
{
	// if(Event::Type::Main == _activeEvent.eventType)
	// if(Event::Type::Sub == _activeEvent.eventType)
	if (Event::Type::Transition == _activeEvent.eventType){
		for (const auto& event : _transitionEvents) {
			if (event.second.getEventId() != _activeEvent.eventId)
				continue;

			return event.second;
		}
	}
}

void EventManager::initActiveEvent()
{
	if (0 < _activeEvent.eventId) {
		_activeEvent.eventId = -1;
		_activeEvent.eventType = Event::Type::Non;
	}
}