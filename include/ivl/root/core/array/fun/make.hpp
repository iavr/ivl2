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

#ifndef IVL_CORE_ARRAY_FUN_MAKE_HPP
#define IVL_CORE_ARRAY_FUN_MAKE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class... E
>
struct tmp_make_as : tmp_make_as <F, T, all_cond <E...>::template map> { };

template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class E
>
class tmp_make_as <F, T, E>
{
	template <typename... A> using R = subs <T, F <A>...>;

public:
	// TODO: {}() -> {} (needed by GCC)
	template <typename... U, typename... A, only_if <E <A...>{}()> = 0>
	INLINE constexpr R <U..., A...>
	_(A&&... a) const { return R <U..., A...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T,
	template <typename...> class... E
>
using tmp_copy_of = tmp_make_as <copy, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using tmp_uref_of = tmp_make_as <uref_opt, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using tmp_rref_of = tmp_make_as <rref_opt, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using tmp_lref_of = tmp_make_as <base_opt, T, all_lref, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using tmp_cref_of = tmp_make_as <base_opt, T, all_cref, E...>;

//-----------------------------------------------------------------------------

template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
struct t_make_as : make_as <F, T, E...>, tmp_make_as <F, S, E...> { };

//-----------------------------------------------------------------------------

template <
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
using t_copy_of = t_make_as <copy, T, S, E...>;

template <
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
using t_uref_of = t_make_as <uref_opt, T, S, E...>;

template <
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
using t_rref_of = t_make_as <rref_opt, T, S, E...>;

template <
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
using t_lref_of = t_make_as <base_opt, T, S, all_lref, E...>;

template <
	template <typename...> class T,
	template <typename...> class S,
	template <typename...> class... E
>
using t_cref_of = t_make_as <base_opt, T, S, all_cref, E...>;

//-----------------------------------------------------------------------------

template <typename U, typename... A>
using new_seq_of = fixed_array <U, sizeof...(A)>;

template <typename... A>
using new_seq = new_seq_of <common_or <int, A...>, A...>;

using v_seq = t_copy_of <new_seq, new_seq_of>;
using   seq = t_uref_of <new_seq, new_seq_of>;
using u_seq = t_uref_of <new_seq, new_seq_of>;
using r_seq = t_rref_of <new_seq, new_seq_of>;
using l_seq = t_lref_of <new_seq, new_seq_of>;
using c_seq = t_cref_of <new_seq, new_seq_of>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::tmp_copy_of;
using details::tmp_uref_of;
using details::tmp_rref_of;
using details::tmp_lref_of;
using details::tmp_cref_of;

using details::t_copy_of;
using details::t_uref_of;
using details::t_rref_of;
using details::t_lref_of;
using details::t_cref_of;

using details::v_seq;
using details::  seq;
using details::u_seq;
using details::r_seq;
using details::l_seq;
using details::c_seq;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::v_seq  v_seq;
static __attribute__ ((unused)) afun::  seq    seq;
static __attribute__ ((unused)) afun::u_seq  u_seq;
static __attribute__ ((unused)) afun::r_seq  r_seq;
static __attribute__ ((unused)) afun::l_seq  l_seq;
static __attribute__ ((unused)) afun::c_seq  c_seq;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_FUN_MAKE_HPP
