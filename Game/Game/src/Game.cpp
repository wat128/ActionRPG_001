
# include "Game.hpp"
# include "GameObject.h"
# include "GameObjectManager.h"
# include "Battler.h"
# include "ObjData.h"
# include "Player.h"

GameObjectManager allyManager; //ゲームクラスのメンバとする予定

Game::Game(const InitData& init)
	: IScene(init)
{	
	allyManager.spawn<Player>(1, Vec2(300.1, 300.1));
	//GameObjectManager enemyManager();
}

void Game::update()
{
	allyManager.update();
}

void Game::draw() const
{
	allyManager.draw();
}