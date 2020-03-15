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
			delete obj.second;
		}
	}

	template <typename Type>
	void spawn(const int32& value, const Vec2& pos)
	{
		Type* obj = new Type(value, pos);
		_objList.emplace(obj->getName(), obj);
	}

	void update()
	{
		for (auto obj : _objList) {
			obj.second->update();
		}
	}
	
	void draw()
	{
		for (auto obj : _objList) {
			obj.second->draw();
		}
	}

	inline GameObject getObj(const String& index) const { return *(_objList.at(index)); }
	
	inline std::map<String, GameObject> getObjList() const { 
		std::map<String, GameObject> temp;
		for (auto obj : _objList) {
			temp.emplace(obj.first, *(obj.second));
		}
		return temp;
	}

private:
	std::map<String, GameObject*> _objList;
};