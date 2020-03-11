#pragma once
#include <Siv3D.hpp>
#include "GameObject.h"


class GameObjectManager
{
public:
	GameObjectManager()
		: _objList(0)
	{ }

	template <typename Type>
	void spawn(const int32& value, const Vec2& pos)
	{
		Type* obj = new Type(value, pos);
		_objList.push_back(obj);
	}

	void update()
	{
		for (const auto& obj : _objList) {
			obj->update();
		}
	}
	
	void draw()
	{
		for (const auto& obj : _objList) {
			obj->draw();
		}
	}

private:
	Array<GameObject*> _objList;
};
