
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"

# include "FieldManager.h"

GameObjectManager allyManager;		// テスト用：ゲームクラスのメンバとする予定
Camera2D camera(Vec2(0, 0),1.5);
Vec2 cameraPos = { 0,0 };

Game::Game(const InitData& init)
	: IScene(init)
{
	AudioAsset(U"MeridianChild").setLoop(true);
	AudioAsset(U"MeridianChild").play();

	FieldManager::getInstance();

	allyManager.spawn<Player>(1, Vec2(0, 0));

	//GameObjectManager enemyManager();
}

void Game::update()
{	
	// テスト用：
	if (MouseL.pressed())
		FieldManager::getInstance()->transition(U"はじまりの街");
	if (MouseR.pressed())
		FieldManager::getInstance()->transition(U"テストマップ");

	const double marginX = (FieldManager::getInstance()->getCurrentField().w() - camera.getRegion().w) / 2;
	const double marginY = (FieldManager::getInstance()->getCurrentField().h() - camera.getRegion().h) / 2;

	allyManager.update();

	if (-marginX < allyManager.getObj(U"Hero").getPos().x
		&& marginX > allyManager.getObj(U"Hero").getPos().x)
		cameraPos.x = allyManager.getObj(U"Hero").getPos().x;

	if (-marginY < allyManager.getObj(U"Hero").getPos().y
		&& marginY > allyManager.getObj(U"Hero").getPos().y)
		cameraPos.y = allyManager.getObj(U"Hero").getPos().y;


	camera.setCenter(cameraPos);
}

void Game::draw() const
{
	TextureAsset(U"horizon001").drawAt(0, 100);
	Scene::SetBackground(Palette::White);
	{
		const auto t = camera.createTransformer();
		FieldManager::getInstance()->getCurrentField().draw(true, false);
		allyManager.draw();
		FieldManager::getInstance()->getCurrentField().draw(false, true);
	}
}