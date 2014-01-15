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

#ifndef IVL_DETAILS_CORE_AFUN_META_HPP
#define IVL_DETAILS_CORE_AFUN_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class bind_ : private raw_tuple <F, E...>
{
	using B = raw_tuple <F, E...>;
	using B::der;
	using B::der_f;

public:
	using B::B;

	template <typename... A>
	INLINE ret <F(E..., A...)>
	operator()(A&&... a) &&
		{ return tup_tail()(der_f()).call(tup_head()(der_f()), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <F(E..., A...)>
	operator()(A&&... a) const&
		{ return tup_tail()(der()).call(tup_head()(der()), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre_fun_ : private raw_tuple <F, E...>
{
	using B = raw_tuple <F, E...>;
	using B::der;
	using B::der_f;

public:
	using B::B;

	template <typename... A>
	INLINE ret <F(A...)>
	operator()(A&&... a) &&
	{
		return tup_tail()(der_f()).call(tup_head()(der_f())),
		       tup_head()(der_f())(fwd <A>(a)...);
	}

	template <typename... A>
	INLINE constexpr ret <F(A...)>
	operator()(A&&... a) const&
	{
		return tup_tail()(der()).call(tup_head()(der())),
		       tup_head()(der())(fwd <A>(a)...);
	}
};

//-----------------------------------------------------------------------------

using bind    = rref_of <bind_>;
using pre_fun = rref_of <pre_fun_>;

//-----------------------------------------------------------------------------

struct tup_fun
{
	template <typename F>
	INLINE constexpr auto operator()(F&& f) const
	-> decltype(bind()(tup_call(), fwd <F>(f)))
		{ return bind()(tup_call(), fwd <F>(f)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::bind;
using details::pre_fun;
using details::tup_fun;

//-----------------------------------------------------------------------------

}  // namespace fun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::bind     bind;
static __attribute__ ((unused)) afun::pre_fun  pre_fun;
static __attribute__ ((unused)) afun::tup_fun  tup_fun;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_META_HPP
