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

#ifndef IVL_CORE_TYPE_CONST_SCALAR_HPP
#define IVL_CORE_TYPE_CONST_SCALAR_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T, T V>
struct constant <tag::_int, non_type <T, V> > :
	details::const_base <T, c_integral <T, V> >
{
	static constexpr T value = V;
	INLINE constexpr operator T() const { return V; }
};

template <typename T, T N>  using c_enum = c_integral <T, N>;
template <typename T, T &R> using c_lref = c_integral <T&, R>;
template <typename T, T *P> using c_ptr  = c_integral <T*, P>;

//-----------------------------------------------------------------------------

template <bool B = true> using c_boolean = c_integral <bool, B>;

using c_true = c_boolean <true> ;
using c_false = c_boolean <false>;

template <char C = '\0'> using c_char = c_integral <char, C>;

template <signed char C = '\0'>
using c_signed_char = c_integral <signed char, C>;

template <unsigned char C = '\0'>
using c_unsigned_char = c_integral <unsigned char, C>;

template <wchar_t  C = L'\0'> using c_wchar_t  = c_integral <wchar_t, C>;
template <char16_t C = u'\0'> using c_char16_t = c_integral <char16_t, C>;
template <char32_t C = U'\0'> using c_char32_t = c_integral <char32_t, C>;

//-----------------------------------------------------------------------------

template <short N = 0>
using c_short = c_integral <short, N>;

template <unsigned short N = 0>
using c_unsigned_short = c_integral <unsigned short, N>;

template <int N = 0>
using c_int = c_integral <int, N>;

using c_zero = c_int <> ;
using c_one = c_int <1>;

template <unsigned N = 0>
using c_unsigned = c_integral <unsigned, N>;

template <unsigned int N = 0>
using c_unsigned_int = c_integral <unsigned int, N>;

template <long N = 0>
using c_long = c_integral <long, N>;

template <unsigned long N = 0>
using c_unsigned_long = c_integral <unsigned long, N>;

template <long long N = 0>
using c_long_long = c_integral <long long, N>;

template <unsigned long long N = 0>
using c_unsigned_long_long = c_integral <unsigned long long, N>;

//-----------------------------------------------------------------------------

template <size_t    N = 0> using c_size_t    = c_integral <size_t,    N>;
template <ptrdiff_t N = 0> using c_ptrdiff_t = c_integral <ptrdiff_t, N>;

//-----------------------------------------------------------------------------

template <typename M, typename E>
struct floating
{
	static constexpr value_type_of <M> mantissa = M::value;
	static constexpr value_type_of <E> exponent = E::value;
};

//-----------------------------------------------------------------------------

template <typename T, typename M, typename E>
struct constant <tag::_float, T, M, E> : floating <M, E>,
	details::const_base <T, c_floating <T, M, E> >
{
	INLINE constexpr operator T() const { return M() * std::pow(T(10), E()); }
};

template <int M = 0, char E = '\0'>
using c_float = c_floating <float, c_int <M>, c_char <E> >;

template <long M = 0, short E = '\0'>
using c_double = c_floating <double, c_long <M>, c_short <E> >;

template <long long M = 0, short E = '\0'>
using c_long_double =
	c_floating <long double, c_long_long <M>, c_short <E> >;

//-----------------------------------------------------------------------------

template <typename T, typename M, typename E>
struct constant <tag::norm, T, M, E> : floating <M, E>,
	details::const_base <T, c_norm <T, M, E> >
{
	INLINE constexpr operator T() const
	{
		using namespace std;
		return c_floating <T, M, E>() /
			(M() ? pow(T(10), floor(log10(abs(M())))) : T(1));
	}
};

template <int M = 0, char E = '\0'>
using c_norm_float = c_norm <float, c_int <M>, c_char <E> >;

template <long M = 0, short E = '\0'>
using c_norm_double = c_norm <double, c_long <M>, c_short <E> >;

template <long long M = 0, short E = '\0'>
using c_norm_long_double =
	c_norm <long double, c_long_long <M>, c_short <E> >;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CONST_SCALAR_HPP
