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

#ifndef IVL_CORE_TYPE_CORE_DERIVE_HPP
#define IVL_CORE_TYPE_CORE_DERIVE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename A>
constexpr T&& r_cast(A&& a) { return static_cast <T&&>(a); }

template <typename T, typename A>
constexpr T& l_cast(A&& a) { return static_cast <T&>(a); }

template <typename T, typename A>
constexpr const T& c_cast(A&& a) { return static_cast <const T&>(a); }

//-----------------------------------------------------------------------------

template <typename B, typename...>
struct based : B
{
protected:
	using base_type = B;
	using B::B;

	INLINE           B&&       base_f()      { return r_cast <B>(*this); }
	INLINE           B&&       base() &&     { return r_cast <B>(*this); }
	INLINE           B&        base() &      { return l_cast <B>(*this); }
	INLINE constexpr const B&  base() const& { return c_cast <B>(*this); }
};

//-----------------------------------------------------------------------------

template <typename D, typename...>
struct derived
{
protected:
	using derived_type = D;

	INLINE           D&&       der_f()      { return r_cast <D>(*this); }
	INLINE           D&&       der() &&     { return r_cast <D>(*this); }
	INLINE           D&        der() &      { return l_cast <D>(*this); }
	INLINE constexpr const D&  der() const& { return c_cast <D>(*this); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::based;
using details::derived;

template <typename T> using base_type_of    = typename T::base_type;
template <typename T> using derived_type_of = typename T::derived_type;

//-----------------------------------------------------------------------------

template <typename... B> struct der_cons;

template <typename B, typename... Bn>
struct der_cons <B, Bn...> : B, der_cons <Bn...>
{
	using B::B;
	using der_cons <Bn...>::der_cons;
};

template <>
struct der_cons <> { };

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

using types::derived;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_DERIVE_HPP
