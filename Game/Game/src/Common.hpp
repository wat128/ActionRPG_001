
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

// シーンの名前
enum class State
{
	Title,
	Game
};

// ゲームデータ
struct GameData
{


};

// 表示レイヤー
enum class DisplayLayer
{
	Top,
	SecondTop,
	Middle,			// キャラクターと同等のレイヤー
	SecondBottom,
	Bottom
};

// 向き
enum class Direction {
	Non,
	Down,
	Up,
	Left,
	Right
};

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;
