#pragma once

#include <vector>
#include <memory>

#include "Layer.h"

class LayerStack
{
public:
	using LayerPtr = std::shared_ptr<Layer>;

	void pushLayer(const LayerPtr& layer);
	void pushOverlay(const LayerPtr& overlay);
	void popLayer(const LayerPtr& layer);
	void popOverlay(const LayerPtr& overlay);

	auto	begin()			{ return layers.begin();	}
	auto	begin() const	{ return layers.begin();	}
	auto	end()			{ return layers.end();		}
	auto	end() const		{ return layers.end();		}

private:
	std::vector<LayerPtr> layers;
	int lastLayerIndex = 0;
};