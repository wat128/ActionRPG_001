#include "Map01_3.hpp"
#include "../FieldManager.h"

Map01_3::Map01_3(const InitData& init)
	: IScene(init)
{
	FieldManager::getInstance().transition(3);

	initSceneTransition();
}

void Map01_3::update()
{
	FieldManager& fieldManager = FieldManager::getInstance();
	fieldManager.update();
	
	setCameraPos();

	// 実行イベントが存在すればシーン遷移処理
	if (fieldManager.chkActiveEvent()) {
		changeScene(fieldManager.getActiveEvent().getToScene());
	}
}

void Map01_3::draw() const
{
	Scene::SetBackground(Palette::Black);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance().draw();
	}
}