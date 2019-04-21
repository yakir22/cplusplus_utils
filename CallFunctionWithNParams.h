#pragma once

#include <initializer_list>
#include <vector>

static std::vector<int> _values;

template<typename _Container>
static void PushFunctionVariables(_Container &values) {}

template<typename _Container,typename T, typename ...Args>
void PushFunctionVariables(_Container &values,T v, Args... args)
{
	values.push_back(v);
	PushFunctionVariables(values, args...);
}

void my_func(const char *lala)
{
}
template<typename T,typename ...Args>
void my_func(const char *lala,T v, Args... args)
{
	_values.push_back(v);
	PushFunctionVariables(_values,args...);
}



template<typename TypeA, typename TypeB>
bool IsOneOf(TypeA value, TypeB last)
{
	return value == last;
}

template<typename TypeA, typename TypeB, typename ...Args>
bool IsOneOf(TypeA value, TypeB first, Args... args)
{
	return value == first || IsOneOf(value, args...);
}

template<typename TypeA, typename TypeB>
bool IsNotOneOf(TypeA value, TypeB last)
{
	return value != last;
}

template<typename TypeA, typename TypeB, typename ...Args>
bool IsNotOneOf(TypeA value, TypeB first, Args... args)
{
	return value != first && IsNotOneOf(value, args...);
}

void TestCallFunction()
{
	my_func("hello");
	my_func("hello", 3, 4, 5, 6, 6, 3, 2);

	std::string v = "hello";
	auto of = IsOneOf(v, "lala", "kaka", "hello");
	of = IsNotOneOf(v, "lala", "kaka", "hello1");
}
