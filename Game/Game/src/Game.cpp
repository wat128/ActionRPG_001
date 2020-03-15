
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"

GameObjectManager allyManager;	// ƒQ[ƒ€ƒNƒ‰ƒX‚Ìƒƒ“ƒo‚Æ‚·‚é—\’è
Field field;					// ã‹L“¯—lb’è
Camera2D camera(Vec2(0, 0), 1.5);

Game::Game(const InitData& init)
	: IScene(init)
{	
	// b’èˆ—
	Array<FilePath> tiles({ U"Asset/DeepForest-A2.png", U"Asset/ConiferForest1-A5.png", U"Asset/ConiferForest2-A1.png" });
	Array<Size> chipSizes = { { 16,16 }, { 16,16 }, {32, 32} };
	FilePath path(U"Asset/map.json");
	Field temp(tiles, chipSizes, path);
	field = temp;

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
		field.draw(3);
	}
}