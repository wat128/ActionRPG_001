
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
	FieldManager::getInstance()->update();
	
	const double marginX = (FieldManager::getInstance()->getCurrentField().w() - camera.getRegion().w) / 2;
	const double marginY = (FieldManager::getInstance()->getCurrentField().h() - camera.getRegion().h) / 2;
	
	if (-marginX < FieldManager::getInstance()->getAllyList().at(0)->getPos().x		//allyManagerの最初の要素はプレイヤーとする
		&& marginX > FieldManager::getInstance()->getAllyList().at(0)->getPos().x)
		cameraPos.x = FieldManager::getInstance()->getAllyList().at(0)->getPos().x;

	if (-marginY < FieldManager::getInstance()->getAllyList().at(0)->getPos().y
		&& marginY > FieldManager::getInstance()->getAllyList().at(0)->getPos().y)
		cameraPos.y = FieldManager::getInstance()->getAllyList().at(0)->getPos().y;

	camera.setCenter(cameraPos);
}

void Game::draw() const
{
	TextureAsset(U"horizon001").drawAt(0, 100);
	Scene::SetBackground(Palette::White);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance()->draw();
	}
}