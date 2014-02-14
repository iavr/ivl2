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

#ifndef IVL_CORE_FUN_FOLD_TUPLE_HPP
#define IVL_CORE_FUN_FOLD_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename L = tup_loop>
class tup_accum
{
	template <typename T> using acc = bind_args <mut_fun <F>, T>;

public:
	template <
		typename I, typename... A, typename T = copy <I>,
		only_if <any_tuple <A...>{}>
	= 0>
	INLINE constexpr T
	operator()(I&& i, A&&... a) const
		{ return L()(acc <T>(fwd <I>(i)), fwd <A>(a)...).val(); }
};

template <typename F>
using tup_accum_off = tup_accum <F, tup_scan>;

//-----------------------------------------------------------------------------

template <
	typename F, typename I = F, typename E = get <0>,
	template <typename> class R = common_of,
	typename XI = id_fun, typename XE = id_fun, typename U = tup_accum <F>
>
class tup_fold
{
	template <typename T, typename... A>
	INLINE constexpr copy <ret <XI(T)> >
	op(_true, A&&... a) const { return XI()(I().template _<T>()); }

	template <typename T, typename... A>
	INLINE constexpr copy <ret <XI(T)> >
	op(_false, A&&... a) const
	{
		return U()(XE()(E()(static_cast <R <A> >(tup_head()(fwd <A>(a)))...)),
			tup_tail_of <rref_opt>()(fwd <A>(a))...);
	}

public:
	template <
		typename... A, typename T = copy <ret <E(R <A>...)> >,
		only_if <any_tuple <A...>{}>
	= 0>
	INLINE constexpr copy <ret <XI(T)> >
	operator()(A&&... a) const
		{ return op <T>(types::_or <fix_empty <A>...>{}, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <size_t O>
struct add_offset
{
	template <typename A>
	INLINE constexpr pre_tuple <rref_opt <A>, size_t>
	operator()(A&& a) const
		{ return pre_tuple <rref_opt <A>, size_t>(fwd <A>(a), O); }
};

template <
	typename F, typename I = F, typename E = get <0>,
	template <typename> class R = common_of
>
using tup_fold_off = tup_fold <
	F, I, E, R, add_offset <size_t(-1)>, add_offset <0>,
	tup_accum <F, tup_tail_scan>
>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_FOLD_TUPLE_HPP
