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

#ifndef IVL_CORE_FUN_VEC_VEC_HPP
#define IVL_CORE_FUN_VEC_VEC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

using _auto = switch_fun_of <apply_sw <seq_auto, tup_auto> >;

//-----------------------------------------------------------------------------

template <typename R, typename C = op::call>
using vec_sw = map_if <any_group, R, atom_call <C> >;

template <typename F, typename R, typename B = none>
using vec_f = vec_fun_of <val_gen <F, B>, vec_sw <R> >;

// no alias: fwd-declared
template <typename F, typename B = none>
struct vec_apply : vec_f <F, apply, B> { };

template <typename F, typename B = none>
using vec_loop = vec_f <F, loop, B>;

template <typename F, typename B = none>
using vec_auto = vec_f <F, _auto, B>;

template <typename F, typename B = atom <F> >
using vec = vec_atom_of <atom_gen <B>, vec_sw <_auto> >;

//-----------------------------------------------------------------------------

// TODO
template <typename F, size_t I = 0> using vec_mut  = seq_vec_mut <F, I>;
template <typename F, size_t I = 0> using vec_copy = seq_vec_copy <F, I>;

//-----------------------------------------------------------------------------

template <typename F, typename B = none, typename C = op::bracket>
using bra_vec_apply =
	bra_vec_fun_of <val_gen <F, B>, vec_sw <vec_apply <C>, C> >;

template <typename F, typename B = atom <F>, typename C = op::bracket>
using bra_vec = bra_vec_atom_of <atom_gen <B>, vec_sw <vec_apply <C>, C> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::vec_apply;
using details::vec_loop;
using details::vec_auto;
using details::vec;
using details::vec_mut;
using details::vec_copy;
using details::bra_vec_apply;
using details::bra_vec;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_VEC_HPP
