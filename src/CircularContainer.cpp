#include "CircularContainer.h"

template <class T>
typename T::value_type &CircularContainer<T>::at(const typename T::difference_type i)
{
	typename T::difference_type n = T::size();
	return T::at((i % n + n) % n);
}

template <class T>
const typename T::value_type &CircularContainer<T>::at(const typename T::difference_type i) const
{
	typename T::difference_type n = T::size();
	return T::at((i % n + n) % n);
}

template <class T>
typename T::value_type &CircularContainer<T>::operator[](const typename T::difference_type i)
{
	return at(i);
}

template <class T>
const typename T::value_type &CircularContainer<T>::operator[](const typename T::difference_type i) const
{
	return at(i);
}
