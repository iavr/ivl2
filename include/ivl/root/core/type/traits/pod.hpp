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

#ifndef IVL_CORE_TYPE_TRAITS_POD_HPP
#define IVL_CORE_TYPE_TRAITS_POD_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_integral_ : _false { };

template <> struct is_integral_<bool>               : _true { };
template <> struct is_integral_<char>               : _true { };
template <> struct is_integral_<signed char>        : _true { };
template <> struct is_integral_<unsigned char>      : _true { };
template <> struct is_integral_<wchar_t>            : _true { };
template <> struct is_integral_<char16_t>           : _true { };
template <> struct is_integral_<char32_t>           : _true { };
template <> struct is_integral_<short>              : _true { };
template <> struct is_integral_<unsigned short>     : _true { };
template <> struct is_integral_<int>                : _true { };
template <> struct is_integral_<unsigned int>       : _true { };
template <> struct is_integral_<long>               : _true { };
template <> struct is_integral_<unsigned long>      : _true { };
template <> struct is_integral_<long long>          : _true { };
template <> struct is_integral_<unsigned long long> : _true { };

}  // namespace details

template <typename T>
using is_integral = details::is_integral_<remove_cv <T> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename T> struct is_floating_ : _false { };

template <> struct is_floating_<float>       : _true { };
template <> struct is_floating_<double>      : _true { };
template <> struct is_floating_<long double> : _true { };

}  // namespace details

template <typename T>
using is_floating = details::is_floating_<remove_cv <T> >;

//-----------------------------------------------------------------------------

template <typename T>
using is_arithmetic = expr <is_integral <T>() || is_floating <T>()>;

template <typename T>
using is_fundamental = expr <
	is_void <T>() || is_nullptr <T>() || is_arithmetic <T>()
>;

template <typename T>
using is_compound = expr <!is_fundamental <T>()>;

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool un, bool = is_arithmetic <T>()>
struct is_un_signed : expr <is_integral <T>() ? un ^ (T(-1) < T(0)) : !un> { };

template <typename T, bool un>
struct is_un_signed <T, un, false> : _false { };

}  // namespace details

template <typename T> using is_signed   = details::is_un_signed <T, false>;
template <typename T> using is_unsigned = details::is_un_signed <T, true>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_enum)

template <typename T> struct is_enum : expr <__is_enum(T)> { };

#else

template <typename T> using is_enum = expr <!(
	is_void <T>() || is_arithmetic <T>() ||
	is_ref <T>() || is_ptr <T>() || is_member_ptr <T>() ||
	is_arr <T>() || is_fun <T>() || is_union <T>() || is_class <T>()
)>;

#endif  // IVL_HAS_FEATURE(is_enum)

//-----------------------------------------------------------------------------

template <typename T> using is_scalar = expr <
	is_arithmetic <T>() || is_enum <T>() || is_ptr <T>() ||
	is_nullptr <T>() || is_member_ptr <T>()
>;

template <typename T> using is_object = expr <
	is_scalar <T>() || is_arr <T>() || is_union <T>() || is_class <T>()
>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_literal)

template <typename T> struct is_literal : expr <__is_literal(T)> { };

#else

namespace details {

template <typename T>
struct is_literal_ : expr <is_scalar <T>() || is_ref <T>() > { };

}  // namespace details

template <typename T>
using is_literal = details::is_literal_<remove_all_ext <T> >;

#endif  // IVL_HAS_FEATURE(is_literal)

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_std_layout)

template <typename T>
struct is_std_layout : expr <__is_std_layout(T)> { };

#else

template <typename T>
using is_std_layout = expr <is_scalar <remove_all_ext <T> >{}>;

#endif  // IVL_HAS_FEATURE(is_std_layout)

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(is_pod)

template <typename T> struct is_pod : expr <__is_pod(T)> { };

#else

template <typename T>
using is_pod = expr <is_trivial <T>() && is_std_layout <T>() >;

#endif  // IVL_HAS_FEATURE(is_pod)

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_TRAITS_POD_HPP
