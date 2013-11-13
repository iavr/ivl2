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
class bind_ : private tuple <F, E...>
{
	using B = tuple <F, E...>;
	using B::der;
	using B::der_f;

public:
	using B::B;

	template <typename... A>
	INLINE ret <F(E..., A...)>
	operator()(A&&... a) &&
		{ return _tail(der_f()).call(_head(der_f()), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <F(E..., A...)>
	operator()(A&&... a) const&
		{ return _tail(der()).call(_head(der()), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre_fun_ : private tuple <F, E...>
{
	using B = tuple <F, E...>;
	using B::der;
	using B::der_f;

public:
	using B::B;

	template <typename... A>
	INLINE ret <F(A...)>
	operator()(A&&... a) &&
	{
		return _tail(der_f()).call(_head(der_f())),
		       _head(der_f())(fwd <A>(a)...);
	}

	template <typename... A>
	INLINE constexpr ret <F(A...)>
	operator()(A&&... a) const&
	{
		return _tail(der()).call(_head(der())),
		       _head(der())(fwd <A>(a)...);
	}
};

//-----------------------------------------------------------------------------

template <typename F>
class unvoid_ : private tuple <F>
{
	using B = tuple <F>;
	using U = under_elem <0, B>;

public:
	using B::B;

	template <typename... A>
	INLINE int
	operator()(A&&... a) && { return U::fwd()(fwd <A>(a)...), 0; }

	template <typename... A>
	INLINE constexpr int
	operator()(A&&... a) const& { return U::get()(fwd <A>(a)...), 0; }
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun {

// TODO: gcc ICE: template <typename F, typename... E>
template <typename... T> using bind    = afun_details::bind_<T...>;
template <typename... T> using pre_fun = afun_details::pre_fun_<T...>;
// unvoid <> defined @afun/begin

}  // namespace afun

static __attribute__ ((unused)) afun::rref_of <afun::bind>    bind;
static __attribute__ ((unused)) afun::rref_of <afun::pre_fun> pre_fun;
static __attribute__ ((unused)) afun::rref_of <afun::unvoid>  unvoid;

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
