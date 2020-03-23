
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"
# include "Field.h"

enum FIELD { FIRST = 1, SECOND };	// �e�X�g�p�F
const int FIELD_NUM = FIRST;		// �e�X�g�p�F�t�B�[���h�؂�ւ��i�e�X�g�p�j
GameObjectManager allyManager;	// �e�X�g�p�F�Q�[���N���X�̃����o�Ƃ���\��
Field field;					// �e�X�g�p�F
Camera2D camera(Vec2(0, 80),2.0);
Vec2 cameraPos = { 0,0 };

Game::Game(const InitData& init)
	: IScene(init)
{
	AudioAsset(U"MeridianChild").setLoop(true);
	AudioAsset(U"MeridianChild").play();

	// �e�X�g�p�F
	if (FIRST == FIELD_NUM) {
		Array<FilePath> tiles(
			{ U"Asset/Map/Texture/BrightForest-A1.png"
			, U"Asset/Map/Texture/BrightForest-A2.png"
			, U"Asset/Map/Texture/BrightForest-A5.png"	
			, U"Asset/Map/Texture/Tent-F.png"
			, U"Asset/Map/Texture/BrightForest-B.png"
			, U"Asset/Map/Texture/Ruin-F.png" });
		Array<Size> chipSizes = { { 16,16 }, { 16,16 }, {16, 16}, { 16,16 }, {16, 16}, { 16,16 } };
		FilePath path(U"Asset/Map/Data/Map001.json");
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

	allyManager.spawn<Player>(1, Vec2(0, 80));

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
	TextureAsset(U"horizon001").drawAt(0, 0);

	{
		const auto t = camera.createTransformer();
		field.draw(2);
		field.draw(3);
		field.draw(4);
		allyManager.draw();
		field.draw(5);
	}
}