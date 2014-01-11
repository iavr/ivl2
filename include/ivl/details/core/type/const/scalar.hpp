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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_SCALAR_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_SCALAR_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename T>
struct c_type : constant <T, c_type <T> >
{
	INLINE constexpr operator T() const { return T(); }
};

using c_null = c_type <nullptr_t>;

template <typename T, T V>
struct c_integral : constant <T, c_integral <T, V> >
{
	static constexpr T value = V;
	INLINE constexpr operator T() const { return value; }
};

template <typename T, T N> using c_enum = c_integral <T, N>;

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
struct c_scientific : floating <M, E>,
	constant <T, c_scientific <T, M, E> >
{
	INLINE constexpr operator T() const { return M() * std::pow(T(10), E()); }
};

template <int M = 0, char E = '\0'>
using c_float = c_scientific <float, c_int <M>, c_char <E> >;

template <long M = 0, short E = '\0'>
using c_double = c_scientific <double, c_long <M>, c_short <E> >;

template <long long M = 0, short E = '\0'>
using c_long_double =
	c_scientific <long double, c_long_long <M>, c_short <E> >;

//-----------------------------------------------------------------------------

template <typename T, typename M, typename E>
struct c_norm_scientific : floating <M, E>,
	constant <T, c_norm_scientific <T, M, E> >
{
	INLINE constexpr operator T() const
	{
		using namespace std;
		return c_scientific <T, M, E>() /
			(M() ? pow(T(10), floor(log10(abs(M())))) : T(1));
	}
};

template <int M = 0, char E = '\0'>
using c_norm_float = c_norm_scientific <float, c_int <M>, c_char <E> >;

template <long M = 0, short E = '\0'>
using c_norm_double = c_norm_scientific <double, c_long <M>, c_short <E> >;

template <long long M = 0, short E = '\0'>
using c_norm_long_double =
	c_norm_scientific <long double, c_long_long <M>, c_short <E> >;

//-----------------------------------------------------------------------------

template <typename T, T &R>
struct c_ref : constant <T&, c_ref <T, R> >
{
	INLINE constexpr operator T&() const { return R; }
};

template <typename T, T const &R>
struct c_cref : constant <T const&, c_cref <T, R> >
{
	INLINE constexpr operator T const&() const { return R; }
};

//-----------------------------------------------------------------------------

template <typename T, T *P>
struct c_ptr : constant <T*, c_ptr <T, P> >
{
	INLINE constexpr operator T*() const { return P; }
};

template <typename T, T const *P>
struct c_cptr : constant <T const*, c_cptr <T, P> >
{
	INLINE constexpr operator T const*() const { return P; }
};

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_SCALAR_HPP
