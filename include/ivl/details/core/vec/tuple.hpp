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

struct C;
namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// no alias: often used
struct tup_apply : rref_of <apply_tuple, any_tuple> { };
struct tup_loop_ : rref_of <loop_tuple,  any_tuple> { };

struct tup_loop
{
	template <typename... T>
	INLINE void operator()(T&&... t) const
		{ tup_loop_()(fwd <T>(t)...).loop(); }
};

template <typename F, typename... A>
using tup_auto_for = _if <vec_void <F(A...)>{}, tup_loop, tup_apply>;

using tup_auto = afun::choose_fun <tup_auto_for>;

//-----------------------------------------------------------------------------

template <typename S, typename D>
struct tup_sep_loop : derived <D, tup_sep_loop <S, D> >
{
	template <typename F, typename T, only_if <tup_empty <T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const { };

	template <typename F, typename T, only_if <tup_non_empty<T>{}> = 0>
	INLINE void operator()(F&& f, T&& t) const
	{
		fwd <F>(f)(tup_head()(fwd <T>(t)));
		S&& s = fwd <S>(this->der().sep());
		tup_loop()(pre_fun()(fwd <F>(f), fwd <S>(s)), tup_tail()(fwd <T>(t)));
	}
};

//-----------------------------------------------------------------------------

template <typename F, typename... B>
struct val_gen : B... { F val() const { return F(); } };

template <typename F> struct atom_gen : F { using F::F; };

//-----------------------------------------------------------------------------

template <typename R, typename T = op::call>
struct tup_vec_for
{
	template <typename... A>
	using map = _if <any_tuple <A...>{}, R, term_call <T> >;
};

template <typename F, typename R>
using tup_vec_f = vec_fun <
	val_gen <F>,
	tup_vec_for <R>::template map
>;

template <typename F> using tup_vec_apply = tup_vec_f <F, tup_apply>;
template <typename F> using tup_vec_loop  = tup_vec_f <F, tup_loop>;
template <typename F> using tup_vec_auto  = tup_vec_f <F, tup_auto>;

template <typename F, typename B = atom <F> >
using tup_vec = vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_auto>::template map
>;

template <typename F, size_t I = 0>
using tup_vec_mut = tup_vec_f <F, rec_call_mut <tup_loop, I> >;

template <typename F, size_t I = 0>
using tup_vec_copy = tup_vec_f <F, rec_call_copy <tup_apply, I> >;

//-----------------------------------------------------------------------------

template <typename F, typename T = op::bracket>
using tup_brak_vec_apply = brak_vec_fun <
	val_gen <F>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

template <typename F, typename B = atom <F>, typename T = op::bracket>
using tup_brak_vec = brak_vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_VEC_TUPLE_HPP
