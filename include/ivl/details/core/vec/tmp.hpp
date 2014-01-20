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

#ifndef IVL_DETAILS_CORE_VEC_TMP_HPP
#define IVL_DETAILS_CORE_VEC_TMP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <template <typename...> class V, typename F>
class pre_tmp_vec_f
{
	using VT = V <afun::pre_tmp_call>;

public:
	template <
		typename... P, typename... A,
		enable_if <!any_pack <P...>() && !any_tuple <A...>()> = 0
	>
	INLINE constexpr auto _(A&&... a) const
	-> decltype(F().template _<P...>(fwd <A>(a)...))
		{ return F().template _<P...>(fwd <A>(a)...); }

	template <
		typename... P, typename... A,
		enable_if <any_pack <P...>() || any_tuple <A...>()> = 0
	>
	INLINE constexpr auto _(A&&... a) const
	-> decltype(VT()(*this, tup_tmp <P...>(), fwd <A>(a)...))
		{ return VT()(*this, tup_tmp <P...>(), fwd <A>(a)...); }
};

template <template <typename...> class V, typename F>
struct tmp_vec_f : pre_tmp_vec_f <V, F>, V <F> { };

//-----------------------------------------------------------------------------

template <typename F> using tmp_vec_apply = tmp_vec_f <vec_apply, F>;
template <typename F> using tmp_vec_loop  = tmp_vec_f <vec_loop, F>;
template <typename F> using tmp_vec_auto  = tmp_vec_f <vec_auto, F>;

//-----------------------------------------------------------------------------

template <typename F>
class tmp_vec : public vec <F>
{
	using T  = afun::pre_tmp_call;
	using VT = vec_auto <T>;
	using B = vec <F>;

public:
	using B::B;
	using B::val_f;
	using B::val;

//-----------------------------------------------------------------------------

	// TODO: decltype for clang + GCC
	template <
		typename... P, typename... A,
		enable_if <!any_pack <P...>() && !any_tuple <A...>()> = 0
	>
	INLINE auto _(A&&... a) &&
	-> decltype(T()(gen <F&&>(), tmp <P...>(), fwd <A>(a)...))
		{ return T()(val_f(), tmp <P...>(), fwd <A>(a)...); }

	template <
		typename... P, typename... A,
		enable_if <!any_pack <P...>() && !any_tuple <A...>()> = 0
	>
	INLINE auto _(A&&... a) &
	-> decltype(T()(gen <F&>(), tmp <P...>(), fwd <A>(a)...))
		{ return T()(val(), tmp <P...>(), fwd <A>(a)...); }

	template <
		typename... P, typename... A,
		enable_if <!any_pack <P...>() && !any_tuple <A...>()> = 0
	>
	INLINE constexpr auto _(A&&... a) const&
	-> decltype(T()(gen <const F&>(), tmp <P...>(), fwd <A>(a)...))
		{ return T()(val(), tmp <P...>(), fwd <A>(a)...); }

//-----------------------------------------------------------------------------

	template <
		typename... P, typename... A,
		enable_if <any_pack <P...>() || any_tuple <A...>()> = 0
	>
	INLINE auto _(A&&... a) &&
	-> decltype(VT()(mv(*this), tup_tmp <P...>(), fwd <A>(a)...))
		{ return VT()(mv(*this), tup_tmp <P...>(), fwd <A>(a)...); }

	template <
		typename... P, typename... A,
		enable_if <any_pack <P...>() || any_tuple <A...>()> = 0
	>
	INLINE auto _(A&&... a) &
	-> decltype(VT()(*this, tup_tmp <P...>(), fwd <A>(a)...))
		{ return VT()(*this, tup_tmp <P...>(), fwd <A>(a)...); }

	template <
		typename... P, typename... A,
		enable_if <any_pack <P...>() || any_tuple <A...>()> = 0
	>
	INLINE constexpr auto _(A&&... a) const&
	-> decltype(VT()(*this, tup_tmp <P...>(), fwd <A>(a)...))
		{ return VT()(*this, tup_tmp <P...>(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tmp_vec_apply;
using details::tmp_vec_loop;
using details::tmp_vec_auto;
using details::tmp_vec;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TMP_HPP
