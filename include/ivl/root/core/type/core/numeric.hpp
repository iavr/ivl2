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

template <typename T, typename S, S s, T E, T N, T... Nn>
struct rng_t_ : _if <(s > 0 ? N + s <= E : N + s >= E),
	rng_t_<T, S, s, E, N + s, Nn..., N>, integrals <T, Nn..., N>
> { };

}  // namespace details

template <typename T, T B, T E, typename S = int, S s = 1>  // B: begin; s: step; E: end
struct rng_t : _if <rng_empty(B, E, s),
	integrals <T>, details::rng_t_<T, S, s, E, B>
> { };

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
struct rng_of_it : rng_t <T, 0, L - 1> { };

template <typename T>
struct rng_of_it <T, 0> : integrals <T> { };

template <typename T, typename P>
using rng_of_pt = rng_of_it <T, length <P>{}>;

template <typename T, typename... E>
using rng_of_t = rng_of_pt <T, pack <E...> >;

template <typename T, size_t L>
using rng_of_i = type_of <rng_of_it <T, L> >;

template <typename T, typename P>
using rng_of_p = type_of <rng_of_pt <T, P> >;

template <typename T, typename... E>
using rng_of = type_of <rng_of_t <T, E...> >;

//-----------------------------------------------------------------------------

template <size_t L> using num_rng_of_it = rng_of_it <int, L>;
template <size_t L> using sz_rng_of_it  = rng_of_it <size_t, L>;

template <typename P> using num_rng_of_pt = rng_of_pt <int, P>;
template <typename P> using sz_rng_of_pt  = rng_of_pt <size_t, P>;

template <typename... E> using num_rng_of_t = rng_of_t <int, E...>;
template <typename... E> using sz_rng_of_t  = rng_of_t <size_t, E...>;

template <size_t L> using num_rng_of_i = type_of <num_rng_of_it <L> >;
template <size_t L> using sz_rng_of_i  = type_of <sz_rng_of_it <L> >;

template <typename P> using num_rng_of_p = type_of <num_rng_of_pt <P> >;
template <typename P> using sz_rng_of_p  = type_of <sz_rng_of_pt <P> >;

template <typename... E> using num_rng_of = type_of <num_rng_of_t <E...> >;
template <typename... E> using sz_rng_of  = type_of <sz_rng_of_t <E...> >;

//-----------------------------------------------------------------------------

template <size_t L, typename T, T N, T... Nn>
struct rep_it : _if <(L > 0),
	rep_it <L - 1, T, N, N, Nn...>, integrals <T, Nn...>
> { };

template <size_t L, typename T, T... N>
using rep_i = type_of <rep_it <L, T, N...> >;

template <size_t L, int... N>    using num_rep_t = rep_it <L, int, N...>;
template <size_t L, size_t... N> using sz_rep_t  = rep_it <L, size_t, N...>;

template <size_t L, int... N>    using num_rep = type_of <num_rep_t <L, N...> >;
template <size_t L, size_t... N> using sz_rep  = type_of <sz_rep_t <L, N...> >;

//-----------------------------------------------------------------------------

}  // namespace numeric

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
