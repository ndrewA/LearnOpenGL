#pragma once

#include <bitset>

template<typename T, size_t N>
class Signature
{
    using Bitset = std::bitset<N>;

public:
    Signature(Bitset signature = Bitset())
        : signature(signature) { }

    template<typename U, size_t M, typename V>
    friend Signature<U, M> operator&(const Signature<U, M>& lhs, const Signature<V, M>& rhs);

    template<typename U, size_t M, typename V>
    friend bool operator==(const Signature<U, M>& lhs, const Signature<V, M>& rhs);

    bool test(size_t index) const { return signature.test(index); }
    void set(size_t index, bool value = true) { signature.set(index, value); }
    void reset(size_t index) { signature.reset(index); }
    std::string to_string() const { return signature.to_string(); }

private:
    Bitset signature;
};


template<typename T, size_t N, typename U>
Signature<T, N> operator&(const Signature<T, N>& lhs, const Signature<U, N>& rhs)
{
    return { lhs.signature & rhs.signature };
}

template<typename T, size_t N, typename U>
bool operator==(const Signature<T, N>& lhs, const Signature<U, N>& rhs)
{
    return lhs.signature == rhs.signature;
}

template<size_t N>
using EntitySignature = Signature<void, N>;

template<typename SystemType, size_t N>
using SystemSignature = Signature<SystemType, N>;
