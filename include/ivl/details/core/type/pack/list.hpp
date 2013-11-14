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

#ifndef IVL_DETAILS_CORE_TYPE_PACK_LIST_HPP
#define IVL_DETAILS_CORE_TYPE_PACK_LIST_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace packs {

//-----------------------------------------------------------------------------

template <typename P> struct car_t;
template <typename P> struct cdr_t;
template <typename E, typename P> struct cons_t;

template <template <typename...> class C, typename E, typename... En>
struct car_t <C <E, En...> > { using type = E; };

template <template <typename...> class C, typename E, typename... En>
struct cdr_t <C <E, En...> > { using type = C <En...>; };

template <typename E, template <typename...> class C, typename... En>
struct cons_t <E, C <En...> > { using type = C <E, En...>; };

template <typename T> struct car_t <_type <T> > : public id_t <T> { };
template <typename T> struct cdr_t <_type <T> > : public _type <T> { };

template <typename T> struct car_t <repeat <0, T> >;
template <typename T> struct cdr_t <repeat <0, T> >;

template <size_t L, typename T>
struct car_t <repeat <L, T> > : public id_t <T> { };

template <size_t L, typename T>
struct cdr_t <repeat <L, T> > : public repeat <L - 1, T> { };

template <typename E, typename T>           struct cons_t <E, _type <T> >;
template <typename E, size_t L, typename T> struct cons_t <E, repeat <L, T> >;

template <typename P>             using car  = type_of <car_t <P> >;
template <typename P>             using cdr  = type_of <cdr_t <P> >;
template <typename E, typename P> using cons = type_of <cons_t <E, P> >;

//-----------------------------------------------------------------------------

template <typename E, typename... En>
struct car_lt { using type = E; };

template <typename E, typename... En>
struct cdr_lt { using type = pack <En...>; };

template <typename... E> using car_l = type_of <car_lt <E...> >;
template <typename... E> using cdr_l = type_of <cdr_lt <E...> >;

//-----------------------------------------------------------------------------

namespace details {

template <typename P,             bool = is_null <P>{}> struct cars_pt_;
template <typename P,             bool = is_null <P>{}> struct cdrs_pt_;
template <typename E, typename P, bool = is_null <P>{}> struct conses_pt_;

template <typename P>             using cars_p_   = type_of <cars_pt_<P> >;
template <typename P>             using cdrs_p_   = type_of <cdrs_pt_<P> >;
template <typename E, typename P> using conses_p_ = type_of <conses_pt_<E, P> >;

template <typename P, bool>
struct cars_pt_ : public cons_t <car <car <P> >, cars_p_<cdr <P> > > { };

template <typename P, bool>
struct cdrs_pt_ : public cons_t <cdr <car <P> >, cdrs_p_<cdr <P> > > { };

template <typename E, typename P, bool>
struct conses_pt_ :
	public cons_t <cons <car <E>, car <P> >, conses_p_<cdr <E>, cdr <P> > > { };

template <typename P> struct cars_pt_<P, true> { using type = P; };
template <typename P> struct cdrs_pt_<P, true> { using type = P; };

template <typename E, typename P>
struct conses_pt_<E, P, true> { using type = P; };

}  // namespace details

//-----------------------------------------------------------------------------

template <typename P> using cars_pt = details::cars_pt_<P>;
template <typename P> using cdrs_pt = details::cdrs_pt_<P>;
template <typename E, typename P> using conses_pt = details::conses_pt_<E, P>;

template <typename P>             using cars_p   = type_of <cars_pt <P> >;
template <typename P>             using cdrs_p   = type_of <cdrs_pt <P> >;
template <typename E, typename P> using conses_p = type_of <conses_pt <E, P> >;

template <typename... P> using cars_t = cars_pt <pack <P...> >;
template <typename... P> using cdrs_t = cdrs_pt <pack <P...> >;

template <typename E, typename... P>
using conses_t = conses_pt <E, pack <P...> >;

template <typename... P> using cars = type_of <cars_t <P...> >;
template <typename... P> using cdrs = type_of <cdrs_t <P...> >;

template <typename E, typename... P>
using conses = type_of <conses_t <E, P...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_LIST_HPP
