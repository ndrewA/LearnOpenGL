#include "LayerStack.h"

#include <algorithm>
#include <iostream>
#include <cassert>

void LayerStack::pushLayer(const LayerPtr& layer)
{
	layers.insert(layers.begin() + lastLayerIndex, layer);
	++lastLayerIndex;
}

void LayerStack::pushOverlay(const LayerPtr& overlay)
{
	layers.emplace_back(overlay);
}

void LayerStack::popLayer(const LayerPtr& layer)
{
	assert(lastLayerIndex == 0 && "Cannot pop layer stack because it is empty!");
	layers.erase(layers.begin() + lastLayerIndex);
	--lastLayerIndex;
}

void LayerStack::popOverlay(const LayerPtr& overlay)
{
	layers.pop_back();
}
