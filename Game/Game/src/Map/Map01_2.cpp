#include "Map01_2.hpp"
#include "../FieldManager.h"

Map01_2::Map01_2(const InitData& init)
	: IScene(init)
{
	FieldManager::getInstance().transition(2);

	initSceneTransition();
}

void Map01_2::update()
{
	FieldManager& fieldManager = FieldManager::getInstance();
	fieldManager.update();
	
	setCameraPos();

	// 実行イベントが存在すればシーン遷移処理
	if (fieldManager.chkActiveEvent()) {
		changeScene(fieldManager.getActiveEvent().getToScene());
	}
}

void Map01_2::draw() const
{
	Scene::SetBackground(Palette::Black);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance().draw();
	}
}