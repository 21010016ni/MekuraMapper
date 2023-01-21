#pragma once
#include <cmath>
#include <functional>

namespace ext
{
	template<typename T>
	T sum(size_t first, size_t last, std::function<T(size_t)> functinon)
	{
		T ret = 0;
		for (size_t i = first; i != last; (first < last) ? ++i : --i)
			ret += functinon(i);
		return ret;
	}
}

