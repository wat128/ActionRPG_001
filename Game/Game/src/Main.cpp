
# include "Common.hpp"
# include "Title.hpp"
# include "Game.hpp"

void AssetRegist();

void Main()
{
	// タイトルを設定
	Window::SetTitle(U"No name");
	
	// 使用するフォントアセットを登録
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

	AudioAsset::Register(U"MeridianChild", U"Asset/MeridianChild.mp3");	// テスト用：
}