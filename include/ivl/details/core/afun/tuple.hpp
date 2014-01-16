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

#ifndef IVL_DETAILS_CORE_AFUN_TUPLE_HPP
#define IVL_DETAILS_CORE_AFUN_TUPLE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO: keys + operator[] ([val], [rref], [lref], [clref])
template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class... E
>
struct collect : collect <F, T, all_cond <E...>::template map> { };

template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class E
>
class collect <F, T, E>
{
	template <typename... A> using R = subs <T, F <A&&>...>;

public:
	template <typename... A, enable_if <E <A...>{}> = 0>
	INLINE constexpr R <A...>
	operator()(A&&... a) const { return R <A...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T = pre_tuple,
	template <typename...> class E = always
>
using val_of = collect <decay, T, E>;

template <
	template <typename...> class T = pre_tuple,
	template <typename...> class E = always
>
using rref_of = collect <base_opt, T, E>;

template <
	template <typename...> class T = pre_tuple,
	template <typename...> class E = always
>
using lref_of = collect <base_opt, T, E, all_lref>;

template <
	template <typename...> class T = pre_tuple,
	template <typename...> class E = always
>
using clref_of = collect <base_opt, T, E, all_clref>;

//-----------------------------------------------------------------------------

using tup_join = rref_of <join_tup, all_tuple>;
using tup      = rref_of <join_tuple>;

using tup_zip   = rref_of <zip_tup, all_tuple>;
using tup_inner = rref_of <zip_tuple, any_tuple>;

//-----------------------------------------------------------------------------

struct tup_head
{
	template <typename T, enable_if <as_tup_non_empty <T>{}> = 0>
	INLINE constexpr auto operator()(T&& t) const
	-> decltype(at()._<0>(fwd <T>(t)))
		{ return at()._<0>(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_tail
{
	template <typename T, enable_if <as_tup_non_empty <T>{}> = 0>
	INLINE constexpr tail_tup <base_opt <T&&> >
	operator()(T&& t) const { return tail_tup <base_opt <T&&> >(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_flip
{
	template <typename T, enable_if <tup_empty <T>{} || is_atom <T>{}> = 0>
	INLINE constexpr T&& operator()(T&& t) const { return fwd <T>(t); }

	template <typename T, enable_if <tup_non_empty <T>{}> = 0>
	INLINE constexpr auto operator()(T&& t) const
	-> decltype(at()._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)))
		{ return at()._<sz_range <tup_len <T>() - 1, 0, -1> >(fwd <T>(t)); }
};

//-----------------------------------------------------------------------------

struct tup_call
{
	template <typename F, typename T>
	INLINE constexpr auto operator()(F&& f, T&& t) const
	-> decltype(fwd <T>(t).call(fwd <F>(f)))
		{ return fwd <T>(t).call(fwd <F>(f)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::val_of;
using details::rref_of;
using details::lref_of;
using details::clref_of;

using val   = val_of <>;
using rref  = rref_of <>;
using lref  = lref_of <>;
using clref = clref_of <>;

using details::tup;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::val    val;
static __attribute__ ((unused)) afun::rref   rref;
static __attribute__ ((unused)) afun::lref   lref;
static __attribute__ ((unused)) afun::clref  clref;

static __attribute__ ((unused)) afun::tup    tup;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_AFUN_TUPLE_HPP
