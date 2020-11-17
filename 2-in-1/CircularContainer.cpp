#ifndef GEOMETRY_CIRCULARCONTAINER_CPP
#define GEOMETRY_CIRCULARCONTAINER_CPP

template <class T>
struct CircularContainer : public T // 可循环索引的容器模板（需支持T::size()和T::at()）
{
	using T::T;
	typename T::value_type &at(const typename T::difference_type i)
	{
		typename T::difference_type n = T::size();
		return T::at((i % n + n) % n);
	}
	const typename T::value_type &at(const typename T::difference_type) const
	{
		typename T::difference_type n = T::size();
		return T::at((i % n + n) % n);
	}
	typename T::value_type &operator[](const typename T::difference_type)
	{
		return at(i);
	}
	const typename T::value_type &operator[](const typename T::difference_type) const
	{
		return at(i);
	}
};

#endif // GEOMETRY_CIRCULARCONTAINER_CPP
