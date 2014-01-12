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

#ifndef IVL_DETAILS_CORE_VEC_TUPLE_HPP
#define IVL_DETAILS_CORE_VEC_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using tup_apply = rref_of <apply_tuple, any_tuple>;
using tup_loop_ = rref_of <loop_tuple,  any_tuple>;

struct tup_loop
{
	template <typename... T>
	INLINE void operator()(T&&... t) const
		{ tup_loop_()(fwd <T>(t)...).loop(); }
};

//-----------------------------------------------------------------------------

template <typename S, typename D>
struct tup_sep_loop : derived <D, tup_sep_loop <S, D> >
{
	template <typename F, typename T, enable_if <tup_empty <T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const { };

	template <typename F, typename T, enable_if <tup_non_empty<T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const
	{
		fwd <F>(f)(tup_head()(fwd <T>(t)));
		S&& s = fwd <S>(this->der().sep());
		tup_loop()(pre_fun()(fwd <F>(f), fwd <S>(s)), tup_tail()(fwd <T>(t)));
	}
};

//-----------------------------------------------------------------------------

template <typename F>
struct tup_vec_apply
{
	template <typename... A, enable_if <!any_tuple <A...>()> = 0>
	INLINE constexpr ret <F(A...)> operator()(A&&... a) const
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(tup_apply()(*this, fwd <A>(a)...))
		{ return tup_apply()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
struct tup_vec_loop
{
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	INLINE void operator()(A&&... a) const { F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	INLINE void operator()(A&&... a) const { tup_loop()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
struct tup_vec_auto
{
	template <typename... A, enable_if <!any_tuple <A...>()> = 0>
	INLINE constexpr ret <F(A...)> operator()(A&&... a) const
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <vec_non_void <F(A...)>{}> = 0>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(tup_apply()(*this, fwd <A>(a)...))
		{ return tup_apply()(*this, fwd <A>(a)...); }

	template <typename... A, enable_if <vec_void <F(A...)>{}> = 0>
	INLINE void operator()(A&&... a) const { tup_loop()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
class tup_vec : public atom <F>  // not private, not tuple: used as base of fun_atom
{
	using B = atom <F>;

public:
	using B::B;
	using B::val_f;
	using B::val;

	template <typename... A, enable_if <!any_tuple <A...>()> = 0>
	INLINE ret <F(A...)> operator()(A&&... a) &&
		{ return val_f()(fwd <A>(a)...); }

	template <typename... A, enable_if <!any_tuple <A...>()> = 0>
	INLINE constexpr ret <F(A...)> operator()(A&&... a) const&
		{ return val()(fwd <A>(a)...); }

	template <typename... A, enable_if <vec_non_void <F(A...)>{}> = 0>
	INLINE auto operator()(A&&... a) &&
	-> decltype(tup_apply()(mv(*this), fwd <A>(a)...))
		{ return tup_apply()(mv(*this), fwd <A>(a)...); }

	template <typename... A, enable_if <vec_non_void <F(A...)>{}> = 0>
	INLINE constexpr auto operator()(A&&... a) const&
	-> decltype(tup_apply()(*this, fwd <A>(a)...))
		{ return tup_apply()(*this, fwd <A>(a)...); }

	template <typename... A, enable_if <vec_void <F(A...)>{}> = 0>
	INLINE void operator()(A&&... a) && { tup_loop()(mv(*this), fwd <A>(a)...); }

	template <typename... A, enable_if <vec_void <F(A...)>{}> = 0>
	INLINE void operator()(A&&... a) const& { tup_loop()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct tup_vec_mut
{
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	INLINE ret <F(A...)> operator()(A&&... a) const
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	INLINE pick <I, A...>&& operator()(A&&... a) const
		{ return tup_loop()(*this, fwd <A>(a)...), get <I>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct tup_vec_copy
{
	template <typename... A, enable_if <!any_tuple <A...>{}> = 0>
	INLINE ret <F(A...)> operator()(A&&... a) const
		{ return F()(fwd <A>(a)...); }

	template <typename... A, enable_if <any_tuple <A...>{}> = 0>
	INLINE create <pick <I, A...> > operator()(A&&... a) const
	{
		create <pick <I, A...> > b = get <I>(fwd <A>(a)...);
		return tup_loop()(*this, fwd <A>(a)...), b;
	}
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TUPLE_HPP
