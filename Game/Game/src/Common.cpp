#include "Common.hpp"
#include "FieldManager.h"

Camera2D camera(Vec2(0, 0), 1.5);
Vec2 cameraPos = { 0,0 };
Array<MapIdToScene> MapIdToSceneTable = {
	{ SceneState::Non, -1 },
	{ SceneState::Title, 0 },
	{ SceneState::Map01_1, 1 },
	{ SceneState::Map01_2, 2 },
	{ SceneState::Map01_3, 3 },
	{ SceneState::Map02_1, 4 },

};

void setCameraPos()
{
	FieldManager& fieldManager = FieldManager::getInstance();

	const double marginX = (fieldManager.getCurrentField().w() - camera.getRegion().w) / 2;
	const double marginY = (fieldManager.getCurrentField().h() - camera.getRegion().h) / 2;

	if (-marginX < fieldManager.getAllys().at(0)->getPos().x) {		//allyManagerの最初の要素はプレイヤーとする
		if (marginX > fieldManager.getAllys().at(0)->getPos().x)
			cameraPos.x = fieldManager.getAllys().at(0)->getPos().x;
		else
			cameraPos.x = marginX;
	}
	else {
		cameraPos.x = -marginX;
	}

	if (-marginY < fieldManager.getAllys().at(0)->getPos().y) {
		if (marginY - 1 > fieldManager.getAllys().at(0)->getPos().y)
			cameraPos.y = fieldManager.getAllys().at(0)->getPos().y;
		else
			cameraPos.y = marginY - 1;	// -1はエラー対策
	}
	else {
		cameraPos.y = -marginY;
	}

	camera.setCenter(cameraPos);
}

void initSceneTransition()
{
	FieldManager& fieldManager = FieldManager::getInstance();

	if (fieldManager.chkActiveEvent()) {

		Vec2 toPos = fieldManager.getActiveEvent().getToPos();
		for (auto& ally : fieldManager.getAllys()) {
			ally->setPos(toPos);
			// 味方の行動リセット
		}
		setCameraPos();
		
		// Enemyの消去と生成

		fieldManager.initActiveEvent();
	}
}