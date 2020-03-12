
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"

GameObjectManager allyManager;	// ゲームクラスのメンバとする予定
Field field;					// 上記同様暫定

Game::Game(const InitData& init)
	: IScene(init)
{	
	// 暫定処理
	Array<FilePath> tiles({ U"Asset/DeepForest-A2.png", U"Asset/ConiferForest1-A5.png", U"Asset/ConiferForest2-A1.png" });
	Array<Size> chipSizes = { { 16,16 }, { 16,16 }, {32, 32} };
	FilePath path(U"Asset/map.json");
	Field temp(tiles, chipSizes, path);
	field = temp;

	allyManager.spawn<Player>(1, Vec2(300.1, 300.1));
	//GameObjectManager enemyManager();
}

void Game::update()
{

	allyManager.update();
}

void Game::draw() const
{
	field.draw();
	allyManager.draw();
}