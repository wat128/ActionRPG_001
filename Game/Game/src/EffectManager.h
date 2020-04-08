#pragma once
#include "Common.hpp"
#include "EffectAnime.h"

class EffectAnime;

class EffectManager
{
public:
	EffectManager();

	inline static void add(const std::shared_ptr<EffectAnime> effect)
	{
		_effects.emplace_back(effect);
	}

	void update();
	void draw(const DisplayLayer layer);

private:
	static Array<std::shared_ptr<EffectAnime>> _effects;
};