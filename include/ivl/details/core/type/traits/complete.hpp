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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_COMPLETE_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_COMPLETE_HPP

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

struct is_complete_test : public input <>
{
	template <typename T> static target <sizeof(T)> test(int);
};

//-----------------------------------------------------------------------------

template <typename... T> struct is_complete_;

template <typename H, typename T, typename... Tn>
struct is_complete_ <H, T, Tn...> :
	public is_complete_ <H>, public is_complete_ <T, Tn...> { };

template <>           struct is_complete_ <>     : public _true { };
template <>           struct is_complete_ <void> : public _true { };
template <typename H> struct is_complete_ <H, H> : public is_complete_ <H> { };

template <typename T> struct is_complete_ <T> :
	public sfinae <is_complete_test, remove_ref <T> > { };

template <typename R, typename... A>
struct is_complete_ <R (*)(A...)> : public is_complete_ <R> { };

template <typename R, typename... A>
struct is_complete_ <R (A...)> : public is_complete_ <R> { };

template <typename R, typename C>
struct is_complete_ <R C::*> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...)> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) volatile> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const volatile> :
	public is_complete_ <C> { };

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) &> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const&> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) volatile&> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const volatile&> :
	public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) &&> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const&&> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) volatile&&> : public is_complete_ <C> { };

template <typename R, typename C, typename... A>
struct is_complete_ <R (C::*)(A...) const volatile&&> :
	public is_complete_ <C> { };

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

}  // namespace details

template <typename T> using is_complete = details::is_complete_ <T>;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_COMPLETE_HPP
