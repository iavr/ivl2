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

#ifndef IVL_CORE_TUPLE_FUN_MAKE_HPP
#define IVL_CORE_TUPLE_FUN_MAKE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <template <typename...> class T>
struct make
{
	template <typename... A>
	INLINE constexpr subs <T, A...>
	operator()(A&&... a) const { return subs <T, A...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

// TODO: keys + operator[] ([val], [rref], [lref], [cref])
template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class... E
>
struct make_as : make_as <F, T, all_cond <E...>::template map> { };

template <
	template <typename...> class F,
	template <typename...> class T,
	template <typename...> class E
>
class make_as <F, T, E>
{
	template <typename... A> using R = subs <T, F <A>...>;

public:
	// TODO: {}() -> {} (needed by GCC)
	template <typename... A, only_if <E <A...>{}()> = 0>
	INLINE constexpr R <A...>
	operator()(A&&... a) const { return R <A...>(fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <
	template <typename...> class T,
	template <typename...> class... E
>
using copy_of = make_as <copy, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using uref_of = make_as <uref_opt, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using rref_of = make_as <rref_opt, T, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using lref_of = make_as <base_opt, T, all_lref, E...>;

template <
	template <typename...> class T,
	template <typename...> class... E
>
using cref_of = make_as <base_opt, T, all_cref, E...>;

//-----------------------------------------------------------------------------

template <typename T, template <typename...> class... E>
using copy_map = copy_of <T::template map, E...>;

template <typename T, template <typename...> class... E>
using uref_map = uref_of <T::template map, E...>;

template <typename T, template <typename...> class... E>
using rref_map = rref_of <T::template map, E...>;

template <typename T, template <typename...> class... E>
using lref_map = lref_of <T::template map, E...>;

template <typename T, template <typename...> class... E>
using cref_map = cref_of <T::template map, E...>;

using val   = copy_of <pre_tuple>;
using v_tup = copy_of <pre_tuple>;
using u_tup = uref_of <pre_tuple>;
using r_tup = rref_of <pre_tuple>;
using l_tup = lref_of <pre_tuple>;
using c_tup = cref_of <pre_tuple>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

using details::make;

using details::copy_of;
using details::uref_of;
using details::rref_of;
using details::lref_of;
using details::cref_of;

using details::val;
using details::v_tup;
using details::u_tup;
using details::r_tup;
using details::l_tup;
using details::c_tup;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::val    val;
static __attribute__ ((unused)) afun::v_tup  v_tup;
static __attribute__ ((unused)) afun::u_tup  u_tup;
static __attribute__ ((unused)) afun::r_tup  r_tup;
static __attribute__ ((unused)) afun::l_tup  l_tup;
static __attribute__ ((unused)) afun::c_tup  c_tup;

//-----------------------------------------------------------------------------

namespace tuples {
namespace details {

using afun::make;

}  // namespace details
}  // namespace tuples

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TUPLE_FUN_MAKE_HPP
