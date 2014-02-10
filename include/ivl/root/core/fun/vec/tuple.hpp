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

#ifndef IVL_CORE_FUN_VEC_TUPLE_HPP
#define IVL_CORE_FUN_VEC_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F, typename... A>
using tup_auto_for = _if <vec_void <F(A...)>{}, tup_loop, tup_apply>;

using tup_auto = afun::choose_fun <tup_auto_for>;

//-----------------------------------------------------------------------------

template <typename F, typename B = none>
struct val_gen : B { F val() const { return F(); } };

template <typename F> struct atom_gen : F { using F::F; };

//-----------------------------------------------------------------------------

template <typename R, typename T = op::call>
struct tup_vec_for
{
	template <typename... A>
	using map = _if <any_tuple <A...>{}, R, atom_call <T> >;
};

template <typename F, typename R, typename B = none>
using tup_vec_f = vec_fun <
	val_gen <F, B>,
	tup_vec_for <R>::template map
>;

template <typename F, typename B = none>
using tup_vec_apply = tup_vec_f <F, tup_apply, B>;

template <typename F, typename B = none>
using tup_vec_loop = tup_vec_f <F, tup_loop, B>;

template <typename F, typename B = none>
using tup_vec_auto = tup_vec_f <F, tup_auto, B>;

template <typename F, typename B = atom <F> >
using tup_vec = vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_auto>::template map
>;

template <typename F, size_t I = 0>
using tup_vec_mut = tup_vec_f <F, mut_call <tup_loop, I> >;

template <typename F, size_t I = 0>
using tup_vec_copy = tup_vec_f <F, copy_call <tup_apply, I> >;

//-----------------------------------------------------------------------------

template <typename F, typename B = none, typename T = op::bracket>
using tup_bra_vec_apply = bra_vec_fun <
	val_gen <F, B>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

template <typename F, typename B = atom <F>, typename T = op::bracket>
using tup_bra_vec = bra_vec_atom <
	atom_gen <B>,
	tup_vec_for <tup_vec_apply <T>, T>::template map
>;

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct mut_fun
{
	template <
		typename... A,
		only_if <!is_const <remove_ref <pick <I, A...> > >()>
	= 0>
	INLINE constexpr ret <F(A...)>
	operator()(A&&... a) const { return F()(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_TUPLE_HPP