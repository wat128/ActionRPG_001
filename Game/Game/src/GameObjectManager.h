#pragma once
#include <Siv3D.hpp>
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager()
		: _objects()
	{ }

	~GameObjectManager()
	{ }

	template <typename Type>
	void spawn(const int32& value, const Vec2& pos)
	{
		std::shared_ptr<Type> obj = std::make_shared<Type>(value, pos);
		_objects.emplace_back(obj);
	}

	void update()
	{
		_objects.remove_if([](std::shared_ptr<GameObject> obj) { return obj->getAbility().hp.current <= 0; });

		for (auto obj : _objects) {
			obj->update();
		}
	}
	
	// -------------------------------------------------------------
	// ※ 敵味方問わずy座標の値が大きいものを手前に描画するためには
	//    本クラスのdraw()では実現できないため廃止
	// -------------------------------------------------------------
	//void draw()
	//{
	//	for (auto obj : _objects) {
	//		obj->draw();
	//	}
	//}

	inline GameObject getObj(const int32& index) const { return *(_objects.at(index)); }
	
	inline Array<std::shared_ptr<GameObject>> getObjects() const { return _objects;}

	inline void clearObjects()
	{
		_objects.clear();
	}

private:
	Array<std::shared_ptr<GameObject>> _objects;
};