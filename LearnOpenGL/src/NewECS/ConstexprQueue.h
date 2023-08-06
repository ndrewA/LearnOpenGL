#pragma once

#include <array>

template <typename T, size_t Size>
class ConstexprQueue
{
public:
    constexpr void push(const T& value) { data[back++ % Size] = value; }
    constexpr T pop() { return data[front++ % Size]; }
    constexpr bool empty() const { return front == back; }

private:
    std::array<T, Size> data{};
    size_t front = 0;
    size_t back = 0;
};