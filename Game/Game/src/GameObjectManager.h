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
	// ¦ “G–¡•û–â‚í‚¸yÀ•W‚Ì’l‚ª‘å‚«‚¢‚à‚Ì‚ðŽè‘O‚É•`‰æ‚·‚é‚½‚ß‚É‚Í
	//    –{ƒNƒ‰ƒX‚Ìdraw()‚Å‚ÍŽÀŒ»‚Å‚«‚È‚¢‚½‚ß”pŽ~
	// -------------------------------------------------------------
	//void draw()
	//{
	//	for (auto obj : _objects) {
	//		obj->draw();
	//	}
	//}

	inline GameObject getObj(const int32& index) const { return *(_objects.at(index)); }
	
	inline Array<std::shared_ptr<GameObject>> getObjects() const { return _objects;}

private:
	Array<std::shared_ptr<GameObject>> _objects;
};