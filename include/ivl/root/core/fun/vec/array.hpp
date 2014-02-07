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

#ifndef IVL_CORE_FUN_VEC_ARRAY_HPP
#define IVL_CORE_FUN_VEC_ARRAY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO
template <typename F, typename B = none>
struct seq_vec_apply : tup_vec_apply <F, B>
	{ using tup_vec_apply <F, B>::tup_vec_apply; };

template <typename F, typename B = none>
struct seq_vec_loop : tup_vec_loop <F, B>
	{ using tup_vec_loop <F, B>::tup_vec_loop; };

template <typename F, typename B = none>
struct seq_vec_auto : tup_vec_auto <F, B>
	{ using tup_vec_auto <F, B>::tup_vec_auto; };

template <typename F, typename B = atom <F> >
struct seq_vec : tup_vec <F, B>
	{ using tup_vec <F, B>::tup_vec; };

template <typename F, size_t I = 0>
struct seq_vec_mut : tup_vec_mut <F, I>
	{ using tup_vec_mut <F, I>::tup_vec_mut; };

template <typename F, size_t I = 0>
struct seq_vec_copy : tup_vec_copy <F, I>
	{ using tup_vec_copy <F, I>::tup_vec_copy; };

template <typename F, typename B = none>
struct seq_bra_vec_apply : tup_bra_vec_apply <F, B>
	{ using tup_bra_vec_apply <F, B>::tup_bra_vec_apply; };

template <typename F, typename B = atom <F> >
struct seq_bra_vec : tup_bra_vec <F, B>
	{ using tup_bra_vec <F, B>::tup_bra_vec; };

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_ARRAY_HPP
