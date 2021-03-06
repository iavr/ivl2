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

#ifndef IVL_CORE_TUPLE_BASE_ACCESS_HPP
#define IVL_CORE_TUPLE_BASE_ACCESS_HPP

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

protected:
	INLINE           r_ref <E> val_f()      { return _at._<0>(der_f()); }

public:
	INLINE           r_ref <E> val() &&     { return _at._<0>(der_f()); }
	INLINE           l_ref <E> val() &      { return _at._<0>(der()); }
	INLINE constexpr c_ref <E> val() const& { return _at._<0>(der()); }
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

protected:
	INLINE           r_ref <E0> fst_f()      { return _at._<0>(der_f()); }
	INLINE           r_ref <E1> snd_f()      { return _at._<1>(der_f()); }

public:
	INLINE           r_ref <E0> fst() &&     { return _at._<0>(der_f()); }
	INLINE           l_ref <E0> fst() &      { return _at._<0>(der()); }
	INLINE constexpr c_ref <E0> fst() const& { return _at._<0>(der()); }

	INLINE           r_ref <E1> snd() &&     { return _at._<1>(der_f()); }
	INLINE           l_ref <E1> snd() &      { return _at._<1>(der()); }
	INLINE constexpr c_ref <E1> snd() const& { return _at._<1>(der()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::access;

//-----------------------------------------------------------------------------

}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_BASE_ACCESS_HPP
