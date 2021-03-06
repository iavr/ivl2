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

#ifndef IVL_CORE_TYPE_TRAITS_TRAITS_HPP
#define IVL_CORE_TYPE_TRAITS_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

template <typename T> struct is_const           : _false { };
template <typename T> struct is_const <T const> : _true  { };

template <typename T> struct is_vol              : _false { };
template <typename T> struct is_vol <T volatile> : _true  { };

template <typename T> struct is_rref       : _false { };
template <typename T> struct is_rref <T&&> : _true  { };

template <typename T> struct is_lref       : _false { };
template <typename T> struct is_lref <T&>  : _true  { };

template <typename T> struct is_ref       : _false { };
template <typename T> struct is_ref <T&>  : _true  { };
template <typename T> struct is_ref <T&&> : _true  { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_ptr_     : _false { };
template <typename T> struct is_ptr_<T*> : _true  { };

template <typename T> struct is_nullptr_            : _false { };
template <>           struct is_nullptr_<nullptr_t> : _true  { };

template <typename T> struct is_void_       : _false { };
template <>           struct is_void_<void> : _true  { };

}  // namespace details

template <typename T> using is_ptr     = details::is_ptr_    <remove_cv <T> >;
template <typename T> using is_nullptr = details::is_nullptr_<remove_cv <T> >;
template <typename T> using is_void    = details::is_void_   <remove_cv <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_TRAITS_HPP
