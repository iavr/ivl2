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

template <typename T, typename VT>
struct tmp_vec_for
{
	template <typename P, typename... A>
	using map = _if <
		any_pack_p <P>() || any_tuple <A...>(),
		rec_call <VT>, term_call <T>
	>;
};

template <typename T, template <typename...> class V, typename F>
using tmp_vec_vt = tmp_vec_fun <
	gen_val <F, V <F> >,
	tmp_vec_for <T, V <T> >::template map
>;

template <template <typename...> class V, typename F>
using tmp_vec_v = tmp_vec_vt <afun::pre_tmp_call, V, F>;

//-----------------------------------------------------------------------------

template <typename F> using tmp_vec_apply = tmp_vec_v <vec_apply, F>;
template <typename F> using tmp_vec_loop  = tmp_vec_v <vec_loop, F>;
template <typename F> using tmp_vec_auto  = tmp_vec_v <vec_auto, F>;

//-----------------------------------------------------------------------------

// publicly derived from vec, then atom: used as base of fun_atom
template <typename T, typename F>
using tmp_vec_t = tmp_vec_atom <
	gen_atom <vec <F> >,
	tmp_vec_for <T, vec_auto <T> >::template map
>;

template <typename F>
using tmp_vec = tmp_vec_t <afun::pre_tmp_call, F>;

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
