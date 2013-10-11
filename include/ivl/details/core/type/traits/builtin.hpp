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

#ifndef IVL_DETAILS_CORE_TYPE_TRAITS_BUILTIN_HPP
#define IVL_DETAILS_CORE_TYPE_TRAITS_BUILTIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

#if defined(__clang__)

	#define IVL_HAS_FEATURE(x) __has_feature(x)

#else  // defined(__clang__)

	#define IVL_GCC_NO_is_convertible_to
	#define IVL_GCC_NO_is_literal
	#define IVL_GCC_NO_is_std_layout
	#define IVL_GCC_NO_cxx_reference_qualified_functions
	#define IVL_HAS_FEATURE(x) !defined(IVL_GCC_NO_##x)

#endif  // defined(__clang__)

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

template <typename T> using is_union     = expr <__is_union(T)>;
template <typename T> using is_trivial   = expr <__is_trivial(T)>;
template <typename T> using is_final     = expr <__is_final(T)>;
template <typename T> using alignment_of = size <__alignof__(T)>;

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_TRAITS_BUILTIN_HPP
