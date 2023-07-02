#pragma once

template <typename ComponentType>
struct ComponentTypeTag 
{
	inline static size_t index = []() {
		static size_t typeCounter = 0;
		return typeCounter++;
	}();
};

template <typename SystemType>
struct SystemTypeTag 
{
	inline static size_t index = []() {
		static size_t typeCounter = 0;
		return typeCounter++;
	}();
};

struct BaseVariadicTypeTag 
{
	inline static size_t typeCounter = 0;
};

template <typename... ComponentTypes>
struct VariadicTypeTag : BaseVariadicTypeTag 
{
	inline static size_t index = typeCounter++;
};