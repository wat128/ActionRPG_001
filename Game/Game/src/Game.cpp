
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"


enum FIELD { FIRST = 1, SECOND };	// テスト用：
const int FIELD_NUM = FIRST;		// テスト用：フィールド切り替え（テスト用）


GameObjectManager allyManager;	// テスト用：ゲームクラスのメンバとする予定
Field field;					// テスト用：
Camera2D camera(Vec2(0, 0), 1.5);

Game::Game(const InitData& init)
	: IScene(init)
{
	// テスト用：
	if (FIRST == FIELD_NUM) {
		Array<FilePath> tiles({ U"Asset/DeepForest-A2.png", U"Asset/ConiferForest1-A5.png", U"Asset/ConiferForest2-A1.png" });
		Array<Size> chipSizes = { { 16,16 }, { 16,16 }, {32, 32} };
		FilePath path(U"Asset/map.json");
		Field temp(tiles, chipSizes, path);
		field = temp;
	}
	else {
		Array<FilePath> tiles({ U"Asset/ConiferForest2-A1.png", U"Asset/DeepForest-A2.png" });
		Array<Size> chipSizes = { { 16,16 }, { 16,16 } };
		FilePath path(U"Asset/Map1616.json");
		Field temp(tiles, chipSizes, path);
		field = temp;
	}
	allyManager.spawn<Player>(1, Vec2(0, 0));
	//GameObjectManager enemyManager();
}

void Game::update()
{

	allyManager.update();
}

void Game::draw() const
{
	camera.setCenter(allyManager.getObj(U"Hero").getPos());
	{
		const auto t = camera.createTransformer();
		field.draw(0);
		field.draw(1);
		field.draw(2);
		allyManager.draw();
		
		if(FIRST == FIELD_NUM)	// テスト用：
			field.draw(3);
	}
}