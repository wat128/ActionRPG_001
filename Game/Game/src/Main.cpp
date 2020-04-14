
# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"

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
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.setFadeColor(ColorF(1.0));

	// （ゲームシーンから開始する場合はコメントを外す）
	manager.init(State::Game);
	
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
}