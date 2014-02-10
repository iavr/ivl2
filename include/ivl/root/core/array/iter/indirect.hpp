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

#ifndef IVL_CORE_ARRAY_ITER_INDIRECT_HPP
#define IVL_CORE_ARRAY_ITER_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename U>
class iterator <data::indirect <>, I, R, T, U> :
	public base_iter <I, R, T>,
	private raw_tuple <I, rref_opt <U> >
{
	using B = base_iter <I, R, T>;
	using B::ref;

	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using RU = rref_opt <U>;
	using E  = raw_tuple <I, RU>;
	using iter  = elem <0, I>;
	using under = elem <1, RU>;

	INLINE           l_ref <I>  i()       { return iter::get(); }
	INLINE constexpr cl_ref <I> i() const { return iter::get(); }

	INLINE constexpr RU u() const { return static_cast <RU>(under::get()); }

//-----------------------------------------------------------------------------

public:
	using E::E;

	INLINE constexpr R operator*()  const { return ref(u()[*i()]); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return ++i(), *this; }
	INLINE iterator& operator--() { return --i(), *this; }

	INLINE iterator operator++(int) { return iterator(i()++, u()); }
	INLINE iterator operator--(int) { return iterator(i()--, u()); }

	INLINE constexpr R operator[](D n) const { return ref(u()[i()[n]]); }

	INLINE iterator& operator+=(D n) { return i() += n, *this; }
	INLINE iterator& operator-=(D n) { return i() -= n, *this; }

	INLINE iterator operator+(D n) { return iterator(i() + n, u()); }
	INLINE iterator operator-(D n) { return iterator(i() - n, u()); }
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename T, typename U>
class traversor <data::indirect <>, V, R, T, U> :
	public base_trav <true, V, R, T>,
	private raw_tuple <V, rref_opt <U> >
{
	using B = base_trav <true, V, R, T>;
	using B::ref;

	using D = seq_diff <B>;
	using P = seq_ptr <B>;

	using RU = rref_opt <U>;
	using E  = raw_tuple <V, RU>;
	using trav  = elem <0, V>;
	using under = elem <1, RU>;

	INLINE           l_ref <V>  v()       { return trav::get(); }
	INLINE constexpr cl_ref <V> v() const { return trav::get(); }

	INLINE constexpr RU u() const { return static_cast <RU>(under::get()); }

public:
	using E::E;

	INLINE constexpr operator bool() const { return v(); }

	INLINE constexpr R operator*()  const { return ref(u()[*v()]); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return ++v(), *this; }
	INLINE traversor& operator--() { return --v(), *this; }

	INLINE traversor operator++(int) { return traversor(v()++, u()); }
	INLINE traversor operator--(int) { return traversor(v()--, u()); }

	INLINE constexpr R operator[](D n) const { return ref(u()[v()[n]]); }

	INLINE traversor& operator+=(D n) { return v() += n, *this; }
	INLINE traversor& operator-=(D n) { return v() -= n, *this; }

	INLINE traversor operator+(D n) { return traversor(v() + n, u()); }
	INLINE traversor operator-(D n) { return traversor(v() - n, u()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_INDIRECT_HPP
