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

struct subs_test : public subs_fun
{
	using subs_fun::_;
	template <typename... A> static nat _(...);
};

template <template <typename...> class F>
struct conv_test
{
	template <typename... A> static _false _(...);
	template <typename... A> static _true  _(subs <F, A...>);
};

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename... A>
using try_subs = apply_subs <subs_test, F, A...>;

template <template <typename...> class F, typename... A>
using sfinae = _not <is_nat <try_subs <F, A...> >{}>;

template <template <typename...> class F, typename... A>
using ret_sfinae = check_t <try_subs <F, A...> >;

template <typename S, template <typename...> class F, typename... A>
using conv_sfinae = decltype(conv_test <F>::template _<A...>(gen <S>()));

template <template <typename...> class F, typename A>
using null_sfinae = conv_sfinae <nullptr_t, F, A>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::sfinae;
using details::ret_sfinae;
using details::conv_sfinae;
using details::null_sfinae;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_SFINAE_HPP
