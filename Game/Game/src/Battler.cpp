#include "Battler.h"
#include "FieldManager.h"	// テスト用：
#include "FieldReferee.h"

Battler::Battler()
	: _isEnemy(false)
{}

Battler::Battler(const int32& value, const Vec2& pos)
	: GameObject(value, pos)
	, _tiledTexture(
		_texture,
		ObjData::getInstance().TextureCharaNum(value),
		ObjData::getInstance().TextureTileWH(value),
		ObjData::getInstance().TextureTileXYNum(value),
		ObjData::getInstance().TextureWalkTileXYNum(value),
		{ 0,0 })	// 暫定（攻撃アニメ使用しない
	, _ability(value)
	, _isEnemy(true) // 暫定
{}

void Battler::attack()
{

}

void Battler::guard()
{

}

void Battler::skill()
{

}

void Battler::recieveDamage()
{

}

void Battler::move()
{
	// テスト用：
	int32 L, R, U, D;
	KeyA.pressed() ?	L = 1 : L = 0;
	KeyD.pressed() ?	R = 1 : R = 0;
	KeyW.pressed() ?	U = 1 : U = 0;
	KeyS.pressed() ?	D = 1 : D = 0;

	Vec2 offset = Vec2(R - L, D - U)
		.setLength((Scene::DeltaTime() + 0.5) * _ability.getSpeed() * (KeyShift.pressed() ? 0.5 : 1.0));

	const RectF movedCollision(						// 移動後の衝突判定用
		_actor.pos.x - _actor.w / 2 + offset.x
		, _actor.pos.y - _actor.h + offset.y
		, _actor.w, _actor.h);

	bool ret = FieldReferee::getInstance().isCollision(movedCollision , this);
	if (!ret)
		_actor.setPos(_actor.pos + offset);

	_tiledTexture.walkAnime(offset, 0.2);	// 暫定(アニメーションレート)
}

void Battler::update()
{
	move();
}

void Battler::draw()
{
	_tiledTexture.getTile()
		.draw(_actor.pos.x - _tiledTexture.getTile().size.x / 2		// 足元を_actor.posとするため、描画位置調整
			, _actor.pos.y - _tiledTexture.getTile().size.y);
	RectF(_actor.pos.x - _actor.w / 2, _actor.pos.y - _actor.h, _actor.w, _actor.h).drawFrame();	// テスト用：
	Circle(_actor.pos, 2).draw(Palette::Red);
}