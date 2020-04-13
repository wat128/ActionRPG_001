
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
	Ignore,
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

// 対象範囲
enum class Group {
	All,
	Allys,
	Enemys
};

const int32 IGNORE = -9999999;

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;