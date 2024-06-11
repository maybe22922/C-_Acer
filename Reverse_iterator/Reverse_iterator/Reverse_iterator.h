#pragma once
#define _CRT_SECURE_NO_WARNIGS 1
#include<iostream>

namespace ws
{
	template<class Iterator, class Ref, class Ptr>
	struct ReverseIterator
	{
		typedef ReverseIterator<Iterator, Ref, Ptr> Self;

		Iterator _it;

		ReverseIterator(Iterator it)
			:_it(it)
		{}

		Self& operator++()
		{
			--_it;
			return *this;
		}

		Self& operator--()
		{
			++_it;
			return *this;
		}

		Ref operator*()
		{
			Iterator tmp = _it;
			return *(--tmp);
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		bool operator!=(const Self& s)
		{
			return _it != s._it;
		}

	};
}