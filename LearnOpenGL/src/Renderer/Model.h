#pragma once

#include <vector>
#include <string>

#include "Mesh.h"

class Model
{
public:
    virtual ~Model() = default;

    virtual void loadModel(const std::string& path) = 0;
    virtual const std::vector<std::shared_ptr<Mesh>>& getMeshes() const = 0;
};