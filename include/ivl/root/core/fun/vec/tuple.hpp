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

template <typename F, typename B = none>
struct val_gen : B { INLINE constexpr F val() const { return F(); } };

template <typename F> struct atom_gen : F { using F::F; };

//-----------------------------------------------------------------------------

template <typename F, typename... A>
using tup_auto_sw = _if <tup_vec_void <F(A...)>{}, tup_loop, tup_apply>;

struct tup_auto : switch_fun <tup_auto_sw> { };

//-----------------------------------------------------------------------------

template <typename R, typename C = op::call>
using tup_vec_sw = map_if <any_tuple, R, atom_call <C> >;

template <typename F, typename R, typename B = none>
using tup_vec_f = vec_fun_of <val_gen <F, B>, tup_vec_sw <R> >;

template <typename F, typename B = none>
struct tup_vec_apply : tup_vec_f <F, tup_apply, B> { };

template <typename F, typename B = none>
struct tup_vec_loop : tup_vec_f <F, tup_loop, B> { };

template <typename F, typename B = none>
struct tup_vec_auto : tup_vec_f <F, tup_auto, B> { };

template <typename F, typename B = atom <F> >
using tup_vec = vec_atom_of <atom_gen <B>, tup_vec_sw <tup_auto> >;

//-----------------------------------------------------------------------------

template <typename F, size_t I = 0>
struct tup_vec_mut : tup_vec_f <F, mut_call <tup_loop, I> > { };

template <typename F, size_t I = 0>
struct tup_vec_copy : tup_vec_f <F, copy_call <tup_apply, I> > { };

//-----------------------------------------------------------------------------

template <typename F, typename B = none, typename C = op::bracket>
using tup_bra_vec_apply =
	bra_vec_fun_of <val_gen <F, B>, tup_vec_sw <tup_vec_apply <C>, C> >;

template <typename F, typename B = atom <F>, typename C = op::bracket>
using tup_bra_vec =
	bra_vec_atom_of <atom_gen <B>, tup_vec_sw <tup_vec_apply <C>, C> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_TUPLE_HPP
