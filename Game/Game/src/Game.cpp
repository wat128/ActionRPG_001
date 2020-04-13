# include "Game.hpp"
# include "FieldManager.h"

Camera2D camera(Vec2(0, 0),1.5);
Vec2 cameraPos = { 0,0 };

Game::Game(const InitData& init)
	: IScene(init)
{
	AudioAsset(U"MeridianChild").setLoop(true);
	AudioAsset(U"MeridianChild").play();

	FieldManager::getInstance();
}

void Game::update()
{
	FieldManager& fieldManager = FieldManager::getInstance();
	fieldManager.update();
	
	const double marginX = (fieldManager.getCurrentField().w() - camera.getRegion().w) / 2;
	const double marginY = (fieldManager.getCurrentField().h() - camera.getRegion().h) / 2;
	
	if (-marginX < fieldManager.getAllys().at(0)->getPos().x		//allyManagerの最初の要素はプレイヤーとする
		&& marginX > fieldManager.getAllys().at(0)->getPos().x)
		cameraPos.x = fieldManager.getAllys().at(0)->getPos().x;

	if (-marginY < fieldManager.getAllys().at(0)->getPos().y
		&& marginY > fieldManager.getAllys().at(0)->getPos().y)
		cameraPos.y = fieldManager.getAllys().at(0)->getPos().y;

	camera.setCenter(cameraPos);
}

void Game::draw() const
{
	TextureAsset(U"horizon001").drawAt(0, 100);
	Scene::SetBackground(Palette::White);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance().draw();
	}
}