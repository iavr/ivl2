/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_ARRAY_ITER_ITER_HPP
#define IVL_CORE_ARRAY_ITER_ITER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
class iterator <data::iter <>, I, R, T> :
	public base_iter <I, R, T>,
	private raw_tuple <I>
{
	using B = base_iter <I, R, T>;
	using B::ref;

	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using E = raw_tuple <I>;
	using iter = elem <0, I>;

	INLINE           l_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_ref <I> i() const { return iter::get(); }

public:
	using E::E;

	INLINE constexpr R operator*()  const { return ref(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return ++i(), *this; }
	INLINE iterator& operator--() { return --i(), *this; }

	INLINE iterator operator++(int) { return iterator(i()++); }
	INLINE iterator operator--(int) { return iterator(i()--); }

	INLINE constexpr R operator[](D n) const { return ref(i()[n]); }

	INLINE iterator& operator+=(D n) { return i() += n, *this; }
	INLINE iterator& operator-=(D n) { return i() -= n, *this; }

	INLINE iterator operator+(D n) { return iterator(i() + n); }
	INLINE iterator operator-(D n) { return iterator(i() - n); }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
class traversor <data::iter <>, I, R, T> :
	public base_iter <I, R, T>,
	private raw_tuple <I, I>
{
	using B = base_iter <I, R, T>;
	using B::ref;

	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using E = raw_tuple <I, I>;
	using iter = elem <0, I>;
	using end  = elem <1, I>;

	INLINE           l_ref <I> i()       { return iter::get(); }
	INLINE constexpr c_ref <I> i() const { return iter::get(); }

	INLINE           l_ref <I> e()       { return end::get(); }
	INLINE constexpr c_ref <I> e() const { return end::get(); }

public:
	using E::E;

	static constexpr bool finite = true;
	INLINE constexpr operator bool() const { return i() != e(); }

	INLINE constexpr R operator*()  const { return ref(*i()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return ++i(), *this; }
	INLINE traversor& operator--() { return --i(), *this; }

	INLINE traversor operator++(int) { return traversor(i()++, e); }
	INLINE traversor operator--(int) { return traversor(i()--, e); }

	INLINE constexpr R operator[](D n) const { return ref(i()[n]); }

	INLINE traversor& operator+=(D n) { return i() += n, *this; }
	INLINE traversor& operator-=(D n) { return i() -= n, *this; }

	INLINE traversor operator+(D n) { return traversor(i() + n, e); }
	INLINE traversor operator-(D n) { return traversor(i() - n, e); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ITER_HPP
