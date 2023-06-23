#include "LayerStack.h"

#include <algorithm>
#include <iostream>
#include <cassert>

void LayerStack::pushLayer(const std::shared_ptr<Layer>& layer)
{
	layers.insert(layers.begin() + lastLayerIndex, layer);
	++lastLayerIndex;
}

void LayerStack::pushOverlay(const std::shared_ptr<Layer>& overlay)
{
	layers.emplace_back(overlay);
}

void LayerStack::popLayer(const std::shared_ptr<Layer>& layer)
{
	assert(lastLayerIndex == 0 && "Cannot pop layer stack because it is empty!");
	layers.erase(layers.begin() + lastLayerIndex);
	--lastLayerIndex;
}

void LayerStack::popOverlay(const std::shared_ptr<Layer>& overlay)
{
	layers.pop_back();
}
