
# pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

// シーンの名前	(シーン追加時はMapIdToSceneTableを更新すること)
enum class SceneState
{
	Non,
	Title,
	Map01_1,	// はじまりの丘（外）
	Map01_2,	// はじまりの丘（自宅）
	Map01_3		// はじまりの丘（小屋）
};

// シーン⇔マップIDの変換テーブル
const struct MapIdToScene {
	SceneState scene;
	int32 mapId;
};
extern Array<MapIdToScene> MapIdToSceneTable;

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

extern Camera2D camera;
extern Vec2 cameraPos;
const int32 IGNORE = -9999999;
const double HURTTIME = 0.3;
const HSV HURT_COLOR = { 0, 0.5, 1, 1 };

// シーン管理クラス
using MyApp = SceneManager<SceneState, GameData>;


/*----- 共通関数 -----*/

// 現在のフィールドサイズからXYの限界値を算出し、カメラ位置を設定する
void setCameraPos();

// シーン遷移した際の初期処理を行う
void initSceneTransition();