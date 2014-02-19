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

#ifndef IVL_CORE_FUN_FOLD_FOLD_HPP
#define IVL_CORE_FUN_FOLD_FOLD_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F> using accum     = seq_accum <F>;
template <typename F> using accum_off = seq_accum_off <F>;

template <
	typename F, typename I = F, typename E = get <0>,
	template <typename> class R = common_of,
	typename XI = id_fun, typename XE = id_fun, typename U = accum <F>
>
using fold = seq_fold <F, I, E, R, XI, XE, U>;

template <
	typename F, typename I = F, typename E = get <0>,
	template <typename> class R = common_of
>
using fold_off = seq_fold_off <F, I, E, R>;

template <typename F, typename I = F, typename E = get <0> >
using collect = fold <F, I, E, copy>;

template <typename F, typename I = F, typename E = get <0> >
using collect_off = fold_off <F, I, E, copy>;

//-----------------------------------------------------------------------------

template <typename F>
struct vec_fold : F, vec_apply <arg_fun_of <F> >
{
	using vec_apply <arg_fun_of <F> >::operator();

	template <typename T, only_if <is_tuple <T>{}> = 0>
	INLINE constexpr ret <F(T)>
	operator()(T&& t) const { return F::operator()(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::accum;
using details::accum_off;
using details::fold;
using details::fold_off;
using details::collect;
using details::collect_off;

using details::vec_fold;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_FUN_FOLD_FOLD_HPP
