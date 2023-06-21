#pragma once

#include <vector>
#include <memory>

#include "Layer.h"

class LayerStack
{
public:
	void pushLayer(const std::shared_ptr<Layer>& layer);
	void pushOverlay(const std::shared_ptr<Layer>& overlay);
	void popLayer(const std::shared_ptr<Layer>& layer);
	void popOverlay(const std::shared_ptr<Layer>& overlay);

	std::vector<std::shared_ptr<Layer>>::iterator begin() { return layers.begin(); }
	std::vector<std::shared_ptr<Layer>>::iterator end() { return layers.end(); }
	std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return layers.begin(); }
	std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return layers.end(); }

private:
	std::vector<std::shared_ptr<Layer>> layers;
	int lastLayerIndex = 0;
};