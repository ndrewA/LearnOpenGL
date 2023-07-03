#pragma once

struct BaseComponentTypeTag
{
	inline static size_t typeCounter = 0;
};

template <typename ComponentType>
struct ComponentTypeTag : public BaseComponentTypeTag
{
	inline static size_t index = typeCounter++;
};

struct BaseSystemTypeTag
{
	inline static size_t typeCounter = 0;
};

template <typename ComponentType>
struct SystemTypeTag : public BaseSystemTypeTag
{
	inline static size_t index = typeCounter++;
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