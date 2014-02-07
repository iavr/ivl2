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

#ifndef IVL_CORE_FUN_VEC_TMP_HPP
#define IVL_CORE_FUN_VEC_TMP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename R, typename T = afun::pre_tmp_call>
struct tmp_vec_for
{
	template <typename P, typename... A>
	using map = _if <
		any_pack_p <P>() || any_tuple <A...>(),
		R, atom_call <T>
	>;
};

template <
	typename F, template <typename...> class V,
	typename B = none, typename T = afun::pre_tmp_call
>
using tmp_vec_f = tmp_vec_fun <
	val_gen <F, B>,
	tmp_vec_for <V <T>, T>::template map
>;

template <typename F, typename B = none>
using tmp_vec_apply = tmp_vec_f <F, vec_apply, B>;

template <typename F, typename B = none>
using tmp_vec_loop  = tmp_vec_f <F, vec_loop, B>;

template <typename F, typename B = none>
using tmp_vec_auto  = tmp_vec_f <F, vec_auto, B>;

template <typename F, typename B = atom <F>, typename T = afun::pre_tmp_call>
using tmp_vec = tmp_vec_atom <
	atom_gen <B>,
	tmp_vec_for <vec_auto <T>, T>::template map
>;

//-----------------------------------------------------------------------------

template <typename F, typename B = none>
using tvec_apply = vec_apply <F, tmp_vec_apply <F, B> >;

template <typename F, typename B = none>
using tvec_loop = vec_loop <F, tmp_vec_loop <F, B> >;

template <typename F, typename B = none>
using tvec_auto = vec_auto <F, tmp_vec_auto <F, B> >;

template <typename F, typename B = atom <F> >
using tvec = vec <F, tmp_vec <F, B> >;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tmp_vec_apply;
using details::tmp_vec_loop;
using details::tmp_vec_auto;
using details::tmp_vec;

using details::tvec_apply;
using details::tvec_loop;
using details::tvec_auto;
using details::tvec;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_VEC_TMP_HPP
