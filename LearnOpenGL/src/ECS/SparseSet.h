#pragma once

#include <vector>

class SparseSet {
public:
    void insert(size_t key);
    const std::vector<size_t>& getAll() const;
    size_t get(size_t key) const;
    bool has(size_t key) const;
    void remove(size_t key);

private:
    std::vector<size_t> sparse;
    std::vector<size_t> dense;
    size_t size = 0;
};
