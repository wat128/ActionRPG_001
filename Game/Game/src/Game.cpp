
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"

enum FIELD { FIRST = 1, SECOND };	// �e�X�g�p�F
const int FIELD_NUM = FIRST;		// �e�X�g�p�F�t�B�[���h�؂�ւ��i�e�X�g�p�j
GameObjectManager allyManager;		// �e�X�g�p�F�Q�[���N���X�̃����o�Ƃ���\��
Field field;						// �e�X�g�p�F
Camera2D camera(Vec2(0, 0),1.5);
Vec2 cameraPos = { 0,0 };
const Size PX8 = { 8,8 };			// 8�s�N�Z��

Game::Game(const InitData& init)
	: IScene(init)
{
	AudioAsset(U"MeridianChild").setLoop(true);
	AudioAsset(U"MeridianChild").play();

	// �e�X�g�p�F
	if (FIRST == FIELD_NUM) {
		Array<FilePath> tiles(
			{ U"Asset/Map/Texture/BrightForest-A2.png"
			, U"Asset/Map/Texture/BrightForest-A5.png"	
			, U"Asset/Map/Texture/BrightForest-B.png"
			, U"Asset/Map/Texture/Tent-F.png" });
			//, U"Asset/Map/Texture/BrightForest-B.png" });
		Array<Size> chipSizes = { PX8, PX8, PX8, PX8 };
		FilePath path(U"Asset/Map/Data/Map001.json");
		Field temp(tiles, chipSizes, path);
		field = temp;
	}

	allyManager.spawn<Player>(1, Vec2(0, -30));

	//GameObjectManager enemyManager();
}

void Game::update()
{	
	const double marginX = (field.w() - camera.getRegion().w) / 2;
	const double marginY = (field.h() - camera.getRegion().h) / 2;

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
		field.draw(0);
		field.draw(1);
		allyManager.draw();
		field.draw(2);
	}
}