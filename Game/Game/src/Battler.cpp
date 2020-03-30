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
		ObjData::getInstance()->TextureCharaNum(value),
		ObjData::getInstance()->TextureTileXYNum(value),
		ObjData::getInstance()->TextureTileWH(value),
		0.2) // 暫定(アニメーションレート)
	, _ability(value)
	,  _isEnemy(true) // 暫定
{}

bool Battler::attack()
{
	return false;
}

bool Battler::guard()
{
	return false;
}

bool Battler::skill()
{
	return false;
}

bool Battler::recieveDamage()
{
	return false;
}

bool Battler::move()
{
	return true;
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