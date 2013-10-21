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

namespace afun_details {

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class bind_ : private tuple <F, tuple <E...> >
{
	using T = tuple <E...>;
	using B = tuple <F, T>;
	using TF = under_elem <0, B>;
	using TE = under_elem <1, B>;

public:
	template <typename G, typename... A>
	INLINE constexpr
	bind_(G&& g, A&&... a) : B(fwd <G>(g), T(fwd <A>(a)...)) { }

	template <typename... A>
	INLINE ret <F(E..., A...)>
	operator()(A&&... a) &&
		{ return TE::fwd().call(TF::fwd(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <const F&(const E&..., A...)>
	operator()(A&&... a) const&
		{ return TE::get().call(TF::get(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre_fun_ : private tuple <F, tuple <E...> >
{
	using T = tuple <E...>;
	using B = tuple <F, T>;
	using TF = under_elem <0, B>;
	using TE = under_elem <1, B>;

public:
	template <typename G, typename... A>
	INLINE constexpr
	pre_fun_(G&& g, A&&... a) : B(fwd <G>(g), T(fwd <A>(a)...)) { }

	template <typename... A>
	INLINE ret <F(A...)>
	operator()(A&&... a) &&
		{ return TE::fwd().call(TF::fwd()), TF::fwd()(fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <const F&(A...)>
	operator()(A&&... a) const&
		{ return TE::get().call(TF::get()), TF::get()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

// TODO: gcc ICE: template <typename F, typename... E>
template <typename... T> using bind    = afun_details::bind_<T...>;
template <typename... T> using pre_fun = afun_details::pre_fun_<T...>;

}  // namespace afun

static __attribute__ ((unused)) afun::rref_of <afun::bind>    bind;
static __attribute__ ((unused)) afun::rref_of <afun::pre_fun> pre_fun;

namespace afun_details { using ivl::bind; }  // not types::bind

//-----------------------------------------------------------------------------

namespace afun_details {

struct tup_fun_
{
	template <typename F>
	INLINE constexpr auto operator()(F&& f) const
		-> decltype(bind(_call, fwd <F>(f)))
		{ return bind(_call, fwd <F>(f)); }
};

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

using tup_fun = afun_details::tup_fun_;

}  // namespace afun

static __attribute__ ((unused)) afun::tup_fun tup_fun;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_META_HPP
