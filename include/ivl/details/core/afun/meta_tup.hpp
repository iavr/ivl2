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

#ifndef IVL_CORE_AFUN__META_TUP__HPP
#define IVL_CORE_AFUN__META_TUP__HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename F, typename... E>
class binder : public pre_tuple <E...>
{
	using B = pre_tuple <E...>;
	using B::der_f;
	using B::der;

public:
	using B::B;

	template <typename... A>
	INLINE ret <C(F, B&&, A...)>
	operator()(A&&... a) && { return C()(F(), der_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE ret <C(F, B&, A...)>
	operator()(A&&... a) & { return C()(F(), der(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr res <C(F, const B&, A...)>
	operator()(A&&... a) const& { return C()(F(), der(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, typename... E>
using bind_tup = binder <op::call, F, E...>;

template <typename F, typename... E>
using bind_args = binder <tup_call, F, E...>;

template <typename F, typename... E>
using bind_ = bind_args <op::call, F, E...>;

template <typename F, typename... E>
using pre_fun_ = bind_tup <head_fun_of <pre_call>, F, E...>;

//-----------------------------------------------------------------------------

template <typename F>
using bind_of = uref_of <types::bind <bind_args, F>::template map>;

using bind    = uref_of <bind_>;
using pre_fun = uref_of <pre_fun_>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::bind_of;
using details::bind;
using details::pre_fun;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::bind     bind;
static __attribute__ ((unused)) afun::pre_fun  pre_fun;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_AFUN__META_TUP__HPP
