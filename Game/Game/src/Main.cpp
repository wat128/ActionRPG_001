
# include "Common.hpp"
# include "Title.hpp"
# include "Map/Map01_1.hpp"
# include "Map/Map01_2.hpp"
# include "Map/Map01_3.hpp"
# include "FieldManager.h"

void AssetRegist();

void Main()
{
	// タイトルを設定
	Window::SetTitle(U"No name");
	
	// 使用するアセットを登録
	AssetRegist();

	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		.add<Title>(SceneState::Title)
		.add<Map01_1>(SceneState::Map01_1)
		.add<Map01_2>(SceneState::Map01_2)
		.add<Map01_3>(SceneState::Map01_3)
		.setFadeColor(ColorF(1.0));

	// （ゲームシーンから開始する場合はコメントを外す）
	manager.init(SceneState::Map01_1);
	
	// フィールドデータの作成
	FieldManager::getInstance();

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}

void AssetRegist()
{
	FontAsset::Register(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Score", 36, Typeface::Bold);

	TextureAsset::Register(U"horizon001", U"Asset/Background/horizon001.jpg");

	AudioAsset::Register(U"MeridianChild", U"Asset/Audio/Bgm/MeridianChild.mp3");	// テスト用：
	AudioAsset::Register(U"Damage01", U"Asset/Audio/Damage/01.mp3");
	AudioAsset::Register(U"Sword01", U"Asset/Audio/Sword/01.mp3");
	AudioAsset::Register(U"Sword02", U"Asset/Audio/Sword/02.mp3");
	AudioAsset::Register(U"Recovery01", U"Asset/Audio/Recovery/01.mp3");
	AudioAsset::Register(U"Buff01", U"Asset/Audio/Buff/B01.mp3");
	AudioAsset::Register(U"Debuff01", U"Asset/Audio/Buff/D01.mp3");
}