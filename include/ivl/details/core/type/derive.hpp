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

#ifndef IVL_DETAILS_CORE_TYPE_DERIVE_HPP
#define IVL_DETAILS_CORE_TYPE_DERIVE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename... T> struct derive : public T... { };

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename A>
constexpr T&& rcast(A&& a) { return static_cast <T&&>(a); }

template <typename T, typename A>
constexpr T& lcast(A&& a) { return static_cast <T&>(a); }

template <typename T, typename A>
constexpr const T& clcast(A&& a) { return static_cast <const T&>(a); }

//-----------------------------------------------------------------------------

template <typename B, typename...>
struct based : public B
{
	using base_type = B;

protected:
	using B::B;

	INLINE           B&&       base_f()      { return rcast <B>(*this); }
	INLINE           B&&       base() &&     { return rcast <B>(*this); }
	INLINE           B&        base() &      { return lcast <B>(*this); }
	INLINE constexpr const B&  base() const& { return clcast <B>(*this); }
};

//-----------------------------------------------------------------------------

template <typename D, typename...>
struct derived
{
	using derived_type = D;

protected:
	INLINE           D&&       der_f()      { return rcast <D>(*this); }
	INLINE           D&&       der() &&     { return rcast <D>(*this); }
	INLINE           D&        der() &      { return lcast <D>(*this); }
	INLINE constexpr const D&  der() const& { return clcast <D>(*this); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::based;
using details::derived;

template <typename T> using base_type_of    = typename T::base_type;
template <typename T> using derived_type_of = typename T::derived_type;

//-----------------------------------------------------------------------------

template <typename... F> struct der_nfun;

template <typename F> struct der_nfun <F> : public F { };

template <typename F, typename... Fn>
class der_nfun <F, Fn...> : public F, public der_nfun <Fn...>
{
	using B = der_nfun <Fn...>;

public:
	using F::operator();
	using B::operator();
};

//-----------------------------------------------------------------------------

template <typename... F> struct der_tfun;

template <typename F> struct der_tfun <F> : public F { };

template <typename F, typename... Fn>
class der_tfun <F, Fn...> : public F, public der_tfun <Fn...>
{
	using B = der_tfun <Fn...>;

public:
	using F::_;
	using B::_;
};

//-----------------------------------------------------------------------------

template <typename... F> struct der_fun :
	public der_nfun <F...>, public der_tfun <F...> { };

//-----------------------------------------------------------------------------

}  // namespace types

using types::derived;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_DERIVE_HPP
