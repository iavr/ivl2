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

#ifndef IVL_DETAILS_CORE_VEC_FUN_HPP
#define IVL_DETAILS_CORE_VEC_FUN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C>
struct atom_call
{
	template <typename F, typename... A>
	INLINE constexpr auto
	operator()(F&& f, A&&... a) const
	-> decltype(C()(fwd <F>(f).val(), fwd <A>(a)...))
		{ return C()(fwd <F>(f).val(), fwd <A>(a)...); }
};

template <typename C, size_t I = 0>
struct mut_call
{
	template <typename F, typename... A>
	INLINE constexpr pick <I, A...>&&
	operator()(F&& f, A&&... a) const
		{ return C()(fwd <F>(f), fwd <A>(a)...), get <I>(fwd <A>(a)...); }
};

template <typename C, size_t I = 0>
struct copy_call
{
	template <typename F, typename... A>
	INLINE constexpr copy <pick <I, A...> >
	operator()(F&& f, A&&... a) const
		{ return copy <pick <I, A...> >(C()(fwd <F>(f), fwd <A>(a)...)); }
};

//-----------------------------------------------------------------------------

template <typename F, template <typename...> class M>
struct bra_vec_fun
{
	template <typename A>
	INLINE constexpr auto operator[](A&& a) const
	-> decltype(subs <M, A>()(F(), fwd <A>(a)))
		{ return subs <M, A>()(F(), fwd <A>(a)); }
};

template <typename F, template <typename...> class M>
struct vec_fun : F
{
	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const
	-> decltype(subs <M, A...>()(*this, fwd <A>(a)...))
		{ return subs <M, A...>()(*this, fwd <A>(a)...); }
};

template <typename F, template <typename...> class M>
struct tmp_vec_fun : F
{
	template <typename... P, typename... A, typename T = tup_tmp <P...> >
	INLINE constexpr auto _(A&&... a) const
	-> decltype(subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...))
		{ return subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, template <typename...> class M>
struct bra_vec_atom : F
{
	using F::F;

	template <typename A>
	INLINE auto operator[](A&& a) &&
	-> decltype(subs <M, A>()(mv(*this), fwd <A>(a)))
		{ return subs <M, A>()(mv(*this), fwd <A>(a)); }

	template <typename A>
	INLINE auto operator[](A&& a) &
	-> decltype(subs <M, A>()(*this, fwd <A>(a)))
		{ return subs <M, A>()(*this, fwd <A>(a)); }

	template <typename A>
	INLINE constexpr auto operator[](A&& a) const&
	-> decltype(subs <M, A>()(*this, fwd <A>(a)))
		{ return subs <M, A>()(*this, fwd <A>(a)); }
};

//-----------------------------------------------------------------------------

template <typename F, template <typename...> class M>
struct vec_atom : F
{
	using F::F;

	template <typename... A>
	INLINE auto operator()(A&&... a) &&
	-> decltype(subs <M, A...>()(mv(*this), fwd <A>(a)...))
		{ return subs <M, A...>()(mv(*this), fwd <A>(a)...); }

	template <typename... A>
	INLINE auto operator()(A&&... a) &
	-> decltype(subs <M, A...>()(*this, fwd <A>(a)...))
		{ return subs <M, A...>()(*this, fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const&
	-> decltype(subs <M, A...>()(*this, fwd <A>(a)...))
		{ return subs <M, A...>()(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F, template <typename...> class M>
struct tmp_vec_atom : F
{
	using F::F;

	template <typename... P, typename... A, typename T = tup_tmp <P...> >
	INLINE auto _(A&&... a) &&
	-> decltype(subs <M, pack <P...>, A...>()(mv(*this), T(), fwd <A>(a)...))
		{ return subs <M, pack <P...>, A...>()(mv(*this), T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tup_tmp <P...> >
	INLINE auto _(A&&... a) &
	-> decltype(subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...))
		{ return subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...); }

	template <typename... P, typename... A, typename T = tup_tmp <P...> >
	INLINE constexpr auto _(A&&... a) const&
	-> decltype(subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...))
		{ return subs <M, pack <P...>, A...>()(*this, T(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_FUN_HPP
