#include "Map02_1.hpp"
#include "../FieldManager.h"

Map02_1::Map02_1(const InitData& init)
	: IScene(init)
{
	FieldManager::getInstance().transition(4);

	initSceneTransition();
}

void Map02_1::update()
{
	FieldManager& fieldManager = FieldManager::getInstance();
	fieldManager.update();
	
	setCameraPos();

	// ���s�C�x���g�����݂���΃V�[���J�ڏ���
	if (fieldManager.chkActiveEvent()) {
		changeScene(fieldManager.getActiveEvent().getToScene());
	}
}

void Map02_1::draw() const
{
	Scene::SetBackground(Palette::Black);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance().draw();
	}
}