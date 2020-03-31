#pragma once
#include <Siv3D.hpp>
#include "GameObject.h"


class GameObjectManager
{
public:
	GameObjectManager()
		: _objList()
	{ }

	~GameObjectManager()
	{
		for (auto obj : _objList) {
			delete obj;
		}
	}

	template <typename Type>
	void spawn(const int32& value, const Vec2& pos)
	{
		Type* obj = new Type(value, pos);
		_objList.emplace_back(obj);
	}

	void update()
	{
		for (auto obj : _objList) {
			obj->update();
		}
	}
	
	void draw()
	{
		for (auto obj : _objList) {
			obj->draw();
		}
	}

	inline GameObject& getObj(const int32& index) const { return *(_objList.at(index)); }
	
	inline Array<GameObject*> getObjList() const { return _objList;}

private:
	Array<GameObject*> _objList;
};