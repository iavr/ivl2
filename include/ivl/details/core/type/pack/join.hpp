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

#ifndef IVL_DETAILS_CORE_TYPE_PACK_JOIN_HPP
#define IVL_DETAILS_CORE_TYPE_PACK_JOIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

template <template <typename...> class C, template <typename...> class D>
struct fuse { template <typename... E> using map = C <E...>; };

template <template <typename...> class D>
struct fuse <_type, D> { template <typename... E> using map = D <E...>; };

template <>
struct fuse <_type, _type>
{ template <typename... E> using map = pack <E...>; };

//-----------------------------------------------------------------------------

template <typename... P> struct join_t;
template <typename... P> using  join = type_of <join_t <P...> >;

template <
	template <typename...> class E, template <typename...> class F,
	typename... L, typename... R, typename... P
>
struct join_t <E <L...>, F <R...>, P...> :
	public join_t <typename fuse <E, F>::template map <L..., R...>, P...> { };

template <template <typename...> class E, typename... T>
struct join_t <E <T...> > { using type = E <T...>; };

//-----------------------------------------------------------------------------

template <typename... I> struct join_it;
template <typename... I> using  join_i = type_of <join_it <I...> >;

template <typename T, T... L, T... R, typename... I>
struct join_it <integrals <T, L...>, integrals <T, R...>, I...> :
	public join_it <integrals <T, L..., R...>, I...> { };

template <typename T, T... N>
struct join_it <integrals <T, N...> > : public integrals <T, N...> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename I, typename... E> struct major_t_;

template <size_t... I, typename... E>
struct major_t_<sizes <I...>, E...> :
	public join_it <sz_rep <length <E>{}, I>...> { };

}  // namespace details

template <typename... E>
using major_t = details::major_t_<sz_rng_of <E...>, E...>;

template <typename... E>
using minor_t = join_it <sz_rng_of_p <E>...> ;

template <typename... E> using major = type_of <major_t <E...> >;
template <typename... E> using minor = type_of <minor_t <E...> >;

//-----------------------------------------------------------------------------

template <typename P> struct flip_pt;
template <typename P> using flip_p = type_of <flip_pt <P> >;

template <template <typename...> class C, typename E, typename... En>
struct flip_pt <C <E, En...> > :
	public join_t <flip_p <C <En...> >, C <E> > { };

template <template <typename...> class C>
struct flip_pt <C <> > { using type = C <>; };

template <typename... E> using flip_t = flip_pt <pack <E...> >;
template <typename... E> using flip   = type_of <flip_t <E...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_JOIN_HPP
