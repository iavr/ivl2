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

#ifndef IVL_DETAILS_CORE_TYPE_PACK_SELECT_HPP
#define IVL_DETAILS_CORE_TYPE_PACK_SELECT_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

namespace details {

template <bool B, typename C, typename D>
using if_cons = _if <B, cons_t <C, type_of <D> >, D>;

template <template <typename...> class F, typename C, typename D>
using if_fun_cons = if_cons <F <C>{}, C, D>;

template <template <typename...> class F, typename P, bool = is_null <P>{}>
struct select_ : public if_fun_cons <F, car <P>, select_<F, cdr <P> > > { };

template <template <typename...> class F, typename P>
struct select_<F, P, true> { using type = P; };

}  // namespace details

template <template <typename...> class F, typename P>
struct select_pt : public details::select_<F, P> { };

template <template <typename...> class F, typename T>
struct select_pt <F, _type <T> > : public details::select_<F, pack <T> > { };

template <template <typename...> class F, typename P>
using select_p = type_of <select_pt <F, P> >;

template <template <typename...> class F, typename... E>
using select_t = select_pt <F, pack <E...> >;

template <template <typename...> class F, typename... E>
using select = type_of <select_t <F, E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <size_t I, typename P>
struct pick_pt_ : public pick_pt_<I - 1, cdr <P> > { };

template <typename P>
struct pick_pt_<0, P> { using type = car <P>; };

}  // namespace details

template <size_t I, typename T>
struct pick_pt : public details::pick_pt_<I, T> { };

template <size_t I, typename T>
struct pick_pt <I, _type <T> > { using type = T; };

template <size_t I, size_t L, typename T>
struct pick_pt <I, repeat <L, T> > : public _if_t <(I < L), T, nat> { };

template <size_t I, typename P> using pick_p = type_of <pick_pt <I, P> >;

template <size_t I, typename... E> using pick_t = pick_pt <I, pack <E...> >;
template <size_t I, typename... E> using pick   = type_of <pick_t <I, E...> >;

//-----------------------------------------------------------------------------

template <size_t I, typename P> struct pick_it;
template <size_t I, typename P> using  pick_i = type_of <pick_it <I, P> >;

template <size_t I, typename T, T... N>
struct pick_it <I, integrals <T, N...> > :
	public pick_t <I, integral <T, N>...> { };

template <size_t I, typename T, T B, T E, typename S, S s>
struct pick_it <I, range <T, B, E, S, s> > :
	public integral <T, B + s * I> { };

//-----------------------------------------------------------------------------

template <typename P> using fst_p = pick_p <0, P>;
template <typename P> using snd_p = pick_p <1, P>;

template <typename P> using fst_i = pick_i <0, P>;
template <typename P> using snd_i = pick_i <1, P>;

template <typename... E> using fst = pick <0, E...>;
template <typename... E> using snd = pick <1, E...>;

//-----------------------------------------------------------------------------

template <size_t N, typename T> struct rep_t;
template <size_t N, typename T> using rep = type_of <rep_t <N, T> >;

template <size_t N, typename T>
struct rep_t : public cons_t <T, rep <N-1, T> > { };

template <typename T>
struct rep_t <0, T> { using type = pack <>; };

//-----------------------------------------------------------------------------

namespace details {

inline constexpr bool  // assumes s > 0
in_rng(size_t B, size_t E, int s, size_t I)
	{ return B <= I && I <= E && (I - B) % s == 0; }

template <
	size_t B, size_t E, int s, typename P,
	size_t I = 0, bool = is_null <P>{}
>
struct choose_rng_r : public if_cons <
	in_rng(B, E, s, I), car <P>, choose_rng_r <B, E, s, cdr <P>, I + 1>
> { };

template <size_t B, size_t E, int s, typename P, size_t I>
struct choose_rng_r <B, E, s, P, I, true> { using type = P; };

template <size_t B, size_t E, int s, typename P, bool = (s > 0)>
struct choose_rng_d : public choose_rng_r <B, E, s, P> { };

template <size_t B, size_t E, int s, typename P>
struct choose_rng_d <B, E, s, P, false> :
	public flip_pt <type_of <choose_rng_r <E, B, -s, P> > > { };

template <size_t B, size_t E, int s, typename P>
struct choose_rng : public choose_rng_d <B, E, s, P> { };

template <size_t B, size_t E, int s, typename T>
struct choose_rng <B, E, s, _type <T> > :
	public rep_t <rng_len(B, E, s), T> { };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename F, typename P> struct choose_pt;
template <typename F, typename P> using choose_p = type_of <choose_pt <F, P> >;

template <size_t I, size_t... In, typename P>
struct choose_pt <sizes <I, In...>, P> :
	public cons_t <pick_p <I, P>, choose_p <sizes <In...>, P> > { };

template <typename P>
struct choose_pt <sizes <>, P> { using type = null_of <P>; };

template <size_t B, size_t E, int s, typename P>
struct choose_pt <sz_range <B, E, s>, P> :
	public details::choose_rng <B, E, s, P> { };

template <typename I, typename... E>
using choose_t = choose_pt <I, pack <E...> >;

template <typename I, typename... E>
using choose = type_of <choose_t <I, E...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_SELECT_HPP
