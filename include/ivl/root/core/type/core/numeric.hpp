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

#ifndef IVL_CORE_TYPE_CORE_NUMERIC_HPP
#define IVL_CORE_TYPE_CORE_NUMERIC_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace numeric {

//-----------------------------------------------------------------------------

template <typename T, T N> using integral = c_integral <T, N>;

template <typename T, T... N>
struct integrals : value <T>, type_seq <integrals <T, N...> > { };

//-----------------------------------------------------------------------------

template <int N = 0>    using number = integral <int, N>;
template <size_t N = 0> using size   = integral <size_t, N>;

template <int... N>    using numbers = integrals <int, N...>;
template <size_t... N> using sizes   = integrals <size_t, N...>;

//-----------------------------------------------------------------------------

template <typename T> struct int_type_t : id_t <T> { };
template <typename T> using  int_type   = type_of <int_type_t <T> >;

template <typename T, T N>
struct int_type_t <integral <T, N> > : id_t <T> { };

//-----------------------------------------------------------------------------

template <typename T, T N> using int_inc = integral <T, N + 1>;
template <typename T, T N> using int_dec = integral <T, N - 1>;

template <int N> using num_inc = int_inc <int, N>;
template <int N> using num_dec = int_dec <int, N>;

template <size_t N> using sz_inc = int_inc <size_t, N>;
template <size_t N> using sz_dec = int_dec <size_t, N>;

//-----------------------------------------------------------------------------

template <typename T, template <typename...> class F, typename P>
struct map_it;

template <
	typename T,
	template <typename...> class F,
	template <typename...> class C, typename... E
> struct map_it <T, F, C <E...> > : integrals <T, F <E>{}...> { };

template <typename T, template <typename...> class F, typename P>
using map_i = type_of <map_it <T, F, P> >;

template <template <typename...> class F, typename P>
using num_map = map_i <int, F, P>;

template <template <typename...> class F, typename P>
using sz_map = map_i <size_t, F, P>;

//-----------------------------------------------------------------------------

template <typename... I> struct join_it;
template <typename... I> using  join_i = type_of <join_it <I...> >;

template <typename T, T... L, T... R, typename... I>
struct join_it <integrals <T, L...>, integrals <T, R...>, I...> :
	join_it <integrals <T, L..., R...>, I...> { };

template <typename T, T... N>
struct join_it <integrals <T, N...> > : integrals <T, N...> { };

//-----------------------------------------------------------------------------

template <typename R, typename T, T B, typename S, S s>
struct linear;

template <typename U, U... N, typename T, T B, typename S, S s>
struct linear <integrals <U, N...>, T, B, S, s> :
	integrals <U, (B + s * N)...> { };

//-----------------------------------------------------------------------------

template <typename T, T B, T E, typename S = int, S s = 1>
struct range { };

template <int B, int E, int s = 1>
using num_range = range <int, B, E, int, s>;

template <size_t B, size_t E, int s = 1>
using sz_range  = range <size_t, B, E, int, s>;

//-----------------------------------------------------------------------------

template <typename T, typename S>
inline constexpr bool
rng_empty(T B, T E, S s) { return s > 0 ? B > E : B < E || !s; }

template <typename T, typename S>
inline constexpr size_t
rng_len(T B, T E, S s)
{
	return rng_empty(B, E, s) ? 0 :
		(s > 0 ? (E - B) / s : (B - E) / (-s)) + 1;
}

//-----------------------------------------------------------------------------

namespace details {

template <typename T, T B, T L, typename = integral <T, L> > struct rng_t_;
template <typename T, T B, T L> using  rng_ = type_of <rng_t_<T, B, L> >;

template <typename T, T B, T L, typename>
struct rng_t_: join_i <rng_<T, B, L/2>, rng_<T, B + L/2, (L+1)/2> > { };

template <typename T, T B, T L>
struct rng_t_<T, B, L, integral <T, 0> > : integrals <T> { };

template <typename T, T B, T L>
struct rng_t_<T, B, L, integral <T, 1> > : integrals <T, B> { };

template <typename T, T B, T E, typename S, S s, bool = (s > 0)>
struct rng_choose : linear <rng_<T, 0, (E - B + 1) / s>, T, B, S, s> { };

template <typename T, T B, T E, typename S, S s>
struct rng_choose <T, B, E, S, s, false> :
	linear <rng_<T, 0, (B - E + 1) / (-s)>, T, B, S, s> { };

}  // namespace details

template <typename T, T B, T E, typename S = int, S s = 1>
using rng_t = _if <rng_empty(B, E, s),
	integrals <T>, details::rng_choose <T, B, E, S, s>
>;

template <typename T, T B, T E, typename S = int, S s = 1>
using rng = type_of <rng_t <T, B, E, S, s> >;

//-----------------------------------------------------------------------------

template <int B, int E, int s = 1>
using num_rng_t = rng_t <int, B, E, int, s>;

template <size_t B, size_t E, int s = 1>
using sz_rng_t  = rng_t <size_t, B, E, int, s>;

template <int B, int E, int s = 1>
using num_rng = type_of <num_rng_t <B, E, s> >;

template <size_t B, size_t E, int s = 1>
using sz_rng  = type_of <sz_rng_t <B, E, s> >;

//-----------------------------------------------------------------------------

template <typename T, size_t L>
struct rng_of_it : rng_t <T, T{0}, T{L - 1}> { };

template <typename T>
struct rng_of_it <T, 0> : integrals <T> { };

template <typename T, size_t L>
using rng_of_i = type_of <rng_of_it <T, L> >;

//-----------------------------------------------------------------------------

template <typename T, typename P>
using rng_of_pt = rng_of_it <T, length <P>{}>;

template <typename T, typename... E>
using rng_of_t = rng_of_pt <T, pack <E...> >;

template <typename T, typename P>
using rng_of_p = type_of <rng_of_pt <T, P> >;

template <typename T, typename... E>
using rng_of = type_of <rng_of_t <T, E...> >;

//-----------------------------------------------------------------------------

template <size_t L> using num_rng_of_it = rng_of_it <int, L>;
template <size_t L> using sz_rng_of_it  = rng_of_it <size_t, L>;

template <size_t L> using num_rng_of_i = type_of <num_rng_of_it <L> >;
template <size_t L> using sz_rng_of_i  = type_of <sz_rng_of_it <L> >;

//-----------------------------------------------------------------------------

template <typename P> using num_rng_of_pt = rng_of_pt <int, P>;
template <typename P> using sz_rng_of_pt  = rng_of_pt <size_t, P>;

template <typename... E> using num_rng_of_t = rng_of_t <int, E...>;
template <typename... E> using sz_rng_of_t  = rng_of_t <size_t, E...>;

template <typename P> using num_rng_of_p = type_of <num_rng_of_pt <P> >;
template <typename P> using sz_rng_of_p  = type_of <sz_rng_of_pt <P> >;

template <typename... E> using num_rng_of = type_of <num_rng_of_t <E...> >;
template <typename... E> using sz_rng_of  = type_of <sz_rng_of_t <E...> >;

//-----------------------------------------------------------------------------

template <size_t L, typename T, T N> struct rep_it;
template <size_t L, typename T, T N> using rep_i = type_of <rep_it <L, T, N> >;

template <size_t L, typename T, T N>
struct rep_it : join_it <rep_i <L/2, T, N>, rep_i <(L+1)/2, T, N> > { };

template <typename T, T N> struct rep_it <0, T, N> : integrals <T> { };
template <typename T, T N> struct rep_it <1, T, N> : integrals <T, N> { };

template <size_t L, int... N>    using num_rep_t = rep_it <L, int, N...>;
template <size_t L, size_t... N> using sz_rep_t  = rep_it <L, size_t, N...>;

template <size_t L, int... N>    using num_rep = type_of <num_rep_t <L, N...> >;
template <size_t L, size_t... N> using sz_rep  = type_of <sz_rep_t <L, N...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename A>
INLINE constexpr A min_(A a, A b) { return a < b ? a : b; }

template <typename A>
INLINE constexpr A max_(A a, A b) { return a > b ? a : b; }

}  // namespace details

template <typename I> struct int_min;
template <typename I> struct int_max;
template <typename I> struct int_sum;
template <typename I> struct int_prod;

template <typename T, T N, T... R>
struct int_min <integrals <T, N, R...> > :
	integral <T, details::min_(N, int_min <integrals <T, R...> >{}())> {};

template <typename T, T N, T... R>
struct int_max <integrals <T, N, R...> > :
	integral <T, details::max_(N, int_max <integrals <T, R...> >{}())> {};

template <typename T, T N, T... R>
struct int_sum <integrals <T, N, R...> > :
	integral <T, N + int_sum <integrals <T, R...> >{}> {};

template <typename T, T N, T... R>
struct int_prod <integrals <T, N, R...> > :
	integral <T, N * int_prod <integrals <T, R...> >{}> {};

template <typename T>
struct int_min <integrals <T> > :
	integral <T, std::numeric_limits <T>::max()> {};

template <typename T>
struct int_max <integrals <T> > :
	integral <T, std::numeric_limits <T>::min()> {};

template <typename T>
struct int_sum <integrals <T> > : integral <T, 0> {};

template <typename T>
struct int_prod <integrals <T> > : integral <T, 1> {};

//-----------------------------------------------------------------------------

template <int... N> using num_min  = int_min  <integrals <int, N...> >;
template <int... N> using num_max  = int_max  <integrals <int, N...> >;
template <int... N> using num_sum  = int_sum  <integrals <int, N...> >;
template <int... N> using num_prod = int_prod <integrals <int, N...> >;

template <size_t... N> using sz_min  = int_min  <integrals <size_t, N...> >;
template <size_t... N> using sz_max  = int_max  <integrals <size_t, N...> >;
template <size_t... N> using sz_sum  = int_sum  <integrals <size_t, N...> >;
template <size_t... N> using sz_prod = int_prod <integrals <size_t, N...> >;

//-----------------------------------------------------------------------------

}  // namespace numeric

//-----------------------------------------------------------------------------

using namespace numeric;

//-----------------------------------------------------------------------------

template <typename P> using length_of = size <P::length>;

template <template <typename...> class C, typename... E>
struct length_t <C <E...> > : size <sizeof...(E)> { };

template <size_t L, typename T>
struct length_t <repeat <L, T> > : size <L> { };

template <typename T, T... N>
struct length_t <integrals <T, N...> > : size <sizeof...(N)> { };

template <typename T, T B, T E, typename S, S s>
struct length_t <range <T, B, E, S, s> > : size <rng_len(B, E, s)> { };

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_NUMERIC_HPP
