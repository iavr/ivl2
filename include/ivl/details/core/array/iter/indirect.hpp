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

#ifndef IVL_DETAILS_CORE_ARRAY_ITER_INDIRECT_HPP
#define IVL_DETAILS_CORE_ARRAY_ITER_INDIRECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename I, typename R, typename U>
class iterator <data::indirect <>, I, R, U> :
	public base_iter <I, R>,
	private raw_tuple <rref_opt <U> >
{
	using D = seq_diff <I>;
	using P = seq_ptr <I>;

	using B = base_iter <I, R>;
	using B::ref;

	using RU = rref_opt <U>;
	using E  = raw_tuple <RU>;
	using under = elem <0, RU>;

	I i;

	INLINE constexpr RU u() const { return static_cast <RU>(under::get()); }

//-----------------------------------------------------------------------------

public:
	template <typename _I, typename _U>
	INLINE constexpr explicit iterator(_I&& i, _U&& u) :
		i(fwd <_I>(i)), E(fwd <_U>(u)) { }

	INLINE constexpr R operator*()  const { return ref(u()[*i]); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return ++i, *this; }
	INLINE iterator& operator--() { return --i, *this; }

	INLINE iterator operator++(int) { return iterator(i++, u()); }
	INLINE iterator operator--(int) { return iterator(i--, u()); }

	INLINE constexpr R operator[](D n) const { return ref(u()[i[n]]); }

	INLINE iterator& operator+=(D n) { return i += n, *this; }
	INLINE iterator& operator-=(D n) { return i -= n, *this; }

	INLINE iterator operator+(D n) { return iterator(i + n, u()); }
	INLINE iterator operator-(D n) { return iterator(i - n, u()); }
};

//-----------------------------------------------------------------------------

template <typename V, typename R, typename U>
class traversor <data::indirect <>, V, R, U> :
	public base_trav <true, V, R, U>,
	private raw_tuple <rref_opt <U> >
{
	using D = seq_diff <V>;
	using P = seq_ptr <V>;

	using B = base_trav <true, V, R, U>;
	using B::ref;

	using RU = rref_opt <U>;
	using E  = raw_tuple <RU>;
	using under = elem <0, RU>;

	V v;

	INLINE constexpr RU u() const { return static_cast <RU>(under::get()); }

public:
	template <typename _V, typename _U>
	INLINE constexpr explicit traversor(_V&& v, _U&& u) :
		v(fwd <_V>(v)), E(fwd <_U>(u)) { }

	INLINE constexpr operator bool() const { return v; }

	INLINE constexpr R operator*()  const { return ref(u()[*v]); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return ++v, *this; }
	INLINE traversor& operator--() { return --v, *this; }

	INLINE traversor operator++(int) { return traversor(v++, u()); }
	INLINE traversor operator--(int) { return traversor(v--, u()); }

	INLINE constexpr R operator[](D n) const { return ref(u()[v[n]]); }

	INLINE traversor& operator+=(D n) { return v += n, *this; }
	INLINE traversor& operator-=(D n) { return v -= n, *this; }

	INLINE traversor operator+(D n) { return traversor(v + n, u()); }
	INLINE traversor operator-(D n) { return traversor(v - n, u()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_ITER_INDIRECT_HPP
