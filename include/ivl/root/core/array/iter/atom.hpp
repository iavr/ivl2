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
   MERCHANTABILITY or FITNESS FOR A PArTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_ARRAY_ITER_ATOM_HPP
#define IVL_CORE_ARRAY_ITER_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename I, typename R, typename T,
	typename D = atom_iter <I, R, T>,
	typename TR = iter_traits <I, R, T, size_t>
>
class atom_iter_impl : public iter_base <D, TR, T>
{
	using B = iter_base <D, TR, T>;
	using d = seq_diff <B>;

	friend base_type_of <B>;

	using derived <D>::der_f;
	using derived <D>::der;

	using B::cast;

//-----------------------------------------------------------------------------

	INLINE void inc() { }
	INLINE void dec() { }

	INLINE void add(d n) { }
	INLINE void sub(d n) { }

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr R operator*()     const { return cast(B::val()); }
	INLINE constexpr R operator[](d n) const { return cast(B::val()); }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o) { return true; }
};

//-----------------------------------------------------------------------------

template <
	typename Q, typename I, typename R, typename T,
	typename D = atom_trav <Q, I, R, T>,
	typename TR = iter_traits <I, R, T, size_t>
>
class atom_trav_impl : public trav_base <D, TR, Q, T>
{
	using B = trav_base <D, TR, Q, T>;
	using d = seq_diff <B>;

	friend B;
	friend base_type_of <B>;

	using derived <D>::der_f;
	using derived <D>::der;

	using B::cast;

//-----------------------------------------------------------------------------

	INLINE void inc() { }
	INLINE void dec() { }

	INLINE void add(d n) { }
	INLINE void sub(d n) { }

//-----------------------------------------------------------------------------

public:
	using B::B;

	static constexpr bool finite = false;

	INLINE constexpr operator bool() const { return true; }

	INLINE constexpr R operator*()     const { return cast(B::val()); }
	INLINE constexpr R operator[](d n) const { return cast(B::val()); }

	INLINE bool operator+() const { return true; }
	INLINE bool operator-() const { return true; }

//-----------------------------------------------------------------------------

	// TODO
	INLINE bool operator!=(const D& o) { return true; }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
struct iterator <tag::atom, I, R, T> :
	atom_iter_impl <I, R, T>
{
	using atom_iter_impl <I, R, T>::atom_iter_impl;
};

//-----------------------------------------------------------------------------

template <typename Q, typename V, typename R, typename T>
struct traversor <tag::atom, Q, V, R, T> :
	atom_trav_impl <Q, V, R, T>
{
	using atom_trav_impl <Q, V, R, T>::atom_trav_impl;
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ATOM_HPP
