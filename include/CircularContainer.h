#ifndef GEOMETRY_CIRCULARCONTAINER_H
#define GEOMETRY_CIRCULARCONTAINER_H

template <class T>
struct CircularContainer : public T // 可循环索引的容器模板（需支持T::size()和T::at()）
{
	using T::T;
	typename T::value_type &at(const typename T::difference_type);
	const typename T::value_type &at(const typename T::difference_type) const;
	typename T::value_type &operator[](const typename T::difference_type);
	const typename T::value_type &operator[](const typename T::difference_type) const;
};

#endif // GEOMETRY_CIRCULARCONTAINER_H
