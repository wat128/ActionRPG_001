#include "EffectManager.h"

Array<std::shared_ptr<EffectAnime>> EffectManager::_effects(0);

EffectManager::EffectManager()
{}

void EffectManager::update()
{
	_effects.remove_if([](const std::shared_ptr<EffectAnime>& effect) { return !effect->isActive(); });
}

void EffectManager::draw(const DisplayLayer layer)
{
	for (const auto& effect : _effects) {
		effect->draw();
	}
}