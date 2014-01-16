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

#ifndef IVL_DETAILS_CORE_TUPLE_BASE_ACCESS_HPP
#define IVL_DETAILS_CORE_TUPLE_BASE_ACCESS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tuples {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename... E>
struct access : elems <D>, derived <D> { using elems <D>::elems; };

//-----------------------------------------------------------------------------

template <typename D, typename E>
struct access <D, E> : elems <D>, derived <D>
{
protected:
	using derived <D>::der;
	using derived <D>::der_f;

public:
	using elems <D>::elems;

	INLINE           rtref <E>  val_f()      { return at._<0>(der_f()); }
	INLINE           rtref <E>  val() &&     { return at._<0>(der_f()); }
	INLINE           ltref <E>  val() &      { return at._<0>(der()); }
	INLINE constexpr cltref <E> val() const& { return at._<0>(der()); }
};

//-----------------------------------------------------------------------------

template <typename D, typename E0, typename E1>
struct access <D, E0, E1> : elems <D>, derived <D>
{
protected:
	using derived <D>::der;
	using derived <D>::der_f;

public:
	using elems <D>::elems;

	INLINE           rtref <E0>  fst_f()      { return at._<0>(der_f()); }
	INLINE           rtref <E0>  fst() &&     { return at._<0>(der_f()); }
	INLINE           ltref <E0>  fst() &      { return at._<0>(der()); }
	INLINE constexpr cltref <E0> fst() const& { return at._<0>(der()); }

	INLINE           rtref <E1>  snd_f()      { return at._<1>(der_f()); }
	INLINE           rtref <E1>  snd() &&     { return at._<1>(der_f()); }
	INLINE           ltref <E1>  snd() &      { return at._<1>(der()); }
	INLINE constexpr cltref <E1> snd() const& { return at._<1>(der()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TUPLE_BASE_ACCESS_HPP
