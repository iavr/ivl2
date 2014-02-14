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

template <typename I, typename R, typename T>
class iterator <data::atom <>, I, R, T> :
	public iter_base <atom_iter <I, R, T>, iter_traits <I, R, T, size_t> >,
	private raw_tuple <T>
{
	using TR = iter_traits <I, R, T, size_t>;
	using B = iter_base <atom_iter <I, R, T>, TR>;
	using B::ref;

	using D = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using E = raw_tuple <T>;

public:
	using E::E;

	INLINE constexpr R operator*()  const { return ref(E::val()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE iterator& operator++() { return *this; }
	INLINE iterator& operator--() { return *this; }

	INLINE iterator& operator++(int) { return *this; }
	INLINE iterator& operator--(int) { return *this; }

	INLINE constexpr R operator[](D n) const { return ref(E::val()); }

	INLINE iterator& operator+=(D n) { return *this; }
	INLINE iterator& operator-=(D n) { return *this; }

	INLINE iterator& operator+(D n) { return *this; }
	INLINE iterator& operator-(D n) { return *this; }
};

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
class traversor <data::atom <>, I, R, T> :
	public iter_base <atom_trav <I, R, T>, iter_traits <I, R, T, size_t> >,
	private raw_tuple <T>
{
	using TR = iter_traits <I, R, T, size_t>;
	using B = iter_base <atom_trav <I, R, T>, TR>;
	using B::ref;

	using D = seq_diff <TR>;
	using P = seq_ptr <TR>;

	using E = raw_tuple <T>;

public:
	using E::E;

	static constexpr bool finite = false;
	INLINE constexpr operator bool() const { return true; }

	INLINE constexpr R operator*()  const { return ref(E::val()); }
	INLINE           P operator->() const { return &(operator*()); }

	INLINE traversor& operator++() { return *this; }
	INLINE traversor& operator--() { return *this; }

	INLINE traversor& operator++(int) { return *this; }
	INLINE traversor& operator--(int) { return *this; }

	INLINE constexpr R operator[](D n) const { return ref(E::val()); }

	INLINE traversor& operator+=(D n) { return *this; }
	INLINE traversor& operator-=(D n) { return *this; }

	INLINE traversor& operator+(D n) { return *this; }
	INLINE traversor& operator-(D n) { return *this; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_ATOM_HPP
