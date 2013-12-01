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

#ifndef IVL_DETAILS_CORE_TYPE_META_HPP
#define IVL_DETAILS_CORE_TYPE_META_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace meta {

//-----------------------------------------------------------------------------

template <template <typename...> class F, typename... V>
struct bind
{
	template <typename... A>
	using map = subs <F, V..., A...>;
};

//-----------------------------------------------------------------------------

template <typename T> using eq_to = bind <eq, T>;

//-----------------------------------------------------------------------------

template <template <typename...> class F, template <typename...> class G>
struct compose
{
	template <typename... A>
	using map = F <subs <G, A...> >;
};

//-----------------------------------------------------------------------------

template <template <typename...> class F> using hold = compose <id_t, F>;

//-----------------------------------------------------------------------------

template <template <typename...> class F>
struct neg
{
	template <typename... A>
	using map = expr <!subs <F, A...>()>;
};

//-----------------------------------------------------------------------------

}  // namespace meta

using namespace meta;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_META_HPP
