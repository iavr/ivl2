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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_SFINAE_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_SFINAE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

// TODO: replace with always <> when made an alias (gcc issue; see types/logic)
template <typename...> using pass = _true;

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename P, size_t = length <P>{}>
struct map_test
{
	template <typename... T>             static _false              _(...);
	template <typename T, typename... A> static pass <F <T, A...> > _(int);
};

template <template <typename...> class F, typename P>
struct map_test <F, P, 1>
{
	template <typename... T> static _false        _(...);
	template <typename T>    static pass <F <T> > _(int);
};

template <template <typename...> class F, typename P>
struct map_test <F, P, 2>
{
	template <typename... T>          static _false           _(...);
	template <typename T, typename A> static pass <F <T, A> > _(int);
};

template <template <typename...> class F>
struct conv_test
{
	template <typename T> static _false _(...);
	template <typename T> static _true  _(F <T>);
};

template <template <typename...> class F>
struct ret_test
{
	template <typename... A> static nat      _(...);
	template <typename... A> static F <A...> _(_type <A>...);
};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename... A>
using sfinae_apply = decltype(T::template _<A...>(gen <S>()));

template <template <typename...> class F, typename... A>
using sfinae = sfinae_apply <int, map_test <F, pack <A...> >, A...>;

template <typename S, template <typename...> class F, typename A>
using conv_sfinae = sfinae_apply <S, conv_test <F>, A>;

template <template <typename...> class F, typename A>
using null_sfinae = conv_sfinae <nullptr_t, F, A>;

template <template <typename...> class F, typename... A>
using ret_sfinae = check_t <decltype(ret_test <F>::template _(_type <A>()...))>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::sfinae;
using details::conv_sfinae;
using details::null_sfinae;
using details::ret_sfinae;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_SFINAE_HPP
