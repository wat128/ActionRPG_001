# include "Map01_1.hpp"
# include "../FieldManager.h"

Map01_1::Map01_1(const InitData& init)
	: IScene(init)
{
	//AudioAsset(U"MeridianChild").setLoop(true);
	//AudioAsset(U"MeridianChild").play();

	FieldManager::getInstance().transition(1);

	initSceneTransition();
}

void Map01_1::update()
{
	FieldManager& fieldManager = FieldManager::getInstance();
	fieldManager.update();

	setCameraPos();

	// 実行イベントが存在すればシーン遷移処理
	if (fieldManager.chkActiveEvent()) {
		changeScene(fieldManager.getActiveEvent().getToScene());
	}
}

void Map01_1::draw() const
{
	TextureAsset(U"horizon001").drawAt(0, 100);
	Scene::SetBackground(Palette::White);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance().draw();
	}
}