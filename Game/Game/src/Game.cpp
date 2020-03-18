
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"


enum FIELD { FIRST = 1, SECOND };	// テスト用：
const int FIELD_NUM = SECOND;		// テスト用：フィールド切り替え（テスト用）


GameObjectManager allyManager;	// テスト用：ゲームクラスのメンバとする予定
Field field;					// テスト用：
Camera2D camera(Vec2(0, 0),2.0);

Vec2 cameraPos = { 0,0 };

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
	const int32 marginX = (field.w() - camera.getRegion().w) / 2;
	const int32 marginY = (field.h() - camera.getRegion().h) / 2;

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