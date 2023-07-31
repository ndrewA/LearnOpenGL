#pragma once

#include <bitset>

template<typename T, size_t N>
class Signature
{
    using Bitset = std::bitset<N>;

public:
    Signature(Bitset bitset = Bitset())
        : bitset(bitset) { }
    
    template<typename U, size_t M, typename V>
    friend Signature<U, M> operator&(const Signature<U, M>& lhs, const Signature<V, M>& rhs);

    template<typename U, size_t M, typename V>
    friend bool operator==(const Signature<U, M>& lhs, const Signature<V, M>& rhs);

    bool test(size_t index) const { return bitset.test(index); }
    void set(size_t index, bool value = true) { bitset.set(index, value); }
    void reset(size_t index) { bitset.reset(index); }
    std::string to_string() const { return bitset.to_string(); }

private:
    Bitset bitset;
};

template<typename T, size_t N, typename U>
Signature<T, N> operator&(const Signature<T, N>& lhs, const Signature<U, N>& rhs)
{
    return { lhs.bitset & rhs.bitset };
}

template<typename T, size_t N, typename U>
bool operator==(const Signature<T, N>& lhs, const Signature<U, N>& rhs)
{
    return lhs.bitset == rhs.bitset;
}

template<size_t N>
using EntitySignature = Signature<void, N>;

template<typename SystemType, size_t N>
using SystemSignature = Signature<SystemType, N>;
