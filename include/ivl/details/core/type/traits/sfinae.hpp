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

namespace tests {

//-----------------------------------------------------------------------------

template <size_t N> struct sz { char arr[N]; };

using pass = sz <1>;
using fail = sz <0>;

template <bool C> using pass_if = enable_if <C, pass>;
template <bool C> using fail_if = enable_if <C, fail>;

template <size_t> using target = pass;

//-----------------------------------------------------------------------------

template <typename C = number <0> >
struct input
{
	template <typename S, typename T, typename... Tn>
	static constexpr bool in() { return S::sz(C()()); }
};

template <template <typename...> class C>
struct input <temp <C> >
{
	template <typename S, typename T, typename... Tn>
	static constexpr bool in() { return S::sz(C <T>()); }
};

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename F>
struct fallback : public F
{
	using F::test;
	template <typename... T> static fail test(...);
};

template <typename F, typename... T>
struct size
{
	template <typename D>
	static constexpr bool sz(D&& d)
	{
		return sizeof(fallback <F>::template test <T...>(fwd <D>(d))) != 0;
	}
};

template <typename F, typename... T>
struct sfinae : public expr <F::template in <size <F, T...>, T...>()> { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::sfinae;

//-----------------------------------------------------------------------------

}  // namespace tests

namespace details { using namespace tests; }

using details::sfinae;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_SFINAE_HPP
