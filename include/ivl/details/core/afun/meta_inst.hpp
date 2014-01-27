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

#ifndef IVL_DETAILS_CORE_AFUN__META_INST__HPP
#define IVL_DETAILS_CORE_AFUN__META_INST__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F>
struct bind_of_
{
	template <typename... E>
	class map : public pre_tuple <E...>
	{
		using B = pre_tuple <E...>;
		using B::der_f;
		using B::call;

	public:
		using B::B;

		template <typename... A>
		INLINE ret <F(rtref <E>..., A...)>
		operator()(A&&... a) && { return der_f().call(F(), fwd <A>(a)...); }

		template <typename... A>
		INLINE ret <F(ltref <E>..., A...)>
		operator()(A&&... a) & { return call(F(), fwd <A>(a)...); }

		template <typename... A>
		INLINE constexpr ret <F(cltref <E>..., A...)>
		operator()(A&&... a) const& { return call(F(), fwd <A>(a)...); }
	};
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class bind_ : protected raw_tuple <F, E...>
{
	using B = raw_tuple <F, E...>;
	using H = tup_head;
	using T = tup_tail;
	using B::der_f;
	using B::der;

public:
	using B::B;

	template <typename... A>
	INLINE ret <rtref <F>(rtref <E>..., A...)>
	operator()(A&&... a) &&
		{ return T()(der_f()).call(H()(der_f()), fwd <A>(a)...); }

	template <typename... A>
	INLINE ret <ltref <F>(ltref <E>..., A...)>
	operator()(A&&... a) &
		{ return T()(der()).call(H()(der()), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <cltref <F>(cltref <E>..., A...)>
	operator()(A&&... a) const&
		{ return T()(der()).call(H()(der()), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
class pre_fun_ : protected raw_tuple <F, E...>
{
	using B = raw_tuple <F, E...>;
	using B::der;
	using B::der_f;
	using H = tup_head;
	using T = tup_tail;

public:
	using B::B;

	template <typename... A>
	INLINE ret <rtref <F>(A...)>
	operator()(A&&... a) &&
		{ return T()(der_f()).call(H()(der_f())), H()(der_f())(fwd <A>(a)...); }

	template <typename... A>
	INLINE ret <ltref <F>(A...)>
	operator()(A&&... a) &
		{ return T()(der()).call(H()(der())), H()(der())(fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <cltref <F>(A...)>
	operator()(A&&... a) const&
		{ return T()(der()).call(H()(der())), H()(der())(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F> using
bind_of = uref_of <bind_of_<F>::template map>;

using bind    = uref_of <bind_>;
using pre_fun = uref_of <pre_fun_>;

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

using details::bind_of;
using details::bind;
using details::pre_fun;
using details::tup_fun;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::bind     bind;
static __attribute__ ((unused)) afun::pre_fun  pre_fun;
static __attribute__ ((unused)) afun::tup_fun  tup_fun;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN__META_INST__HPP