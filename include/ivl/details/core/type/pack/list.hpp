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

template <typename E, typename T>
struct cons_t <E, _type <T> >;

template <typename P>             using car  = type_of <car_t <P> >;
template <typename P>             using cdr  = type_of <cdr_t <P> >;
template <typename E, typename P> using cons = type_of <cons_t <E, P> >;

//-----------------------------------------------------------------------------

template <typename P> struct cars_pt;
template <typename P> struct cdrs_pt;
template <typename A, typename P> struct conses_pt;

template <typename P>             using cars_p   = type_of <cars_pt <P> >;
template <typename P>             using cdrs_p   = type_of <cdrs_pt <P> >;
template <typename A, typename P> using conses_p = type_of <conses_pt <A, P> >;

template <typename P>
struct cars_pt { using type = cons <car <car <P> >, cars_p <cdr <P> > >; };

template <typename P>
struct cdrs_pt { using type = cons <cdr <car <P> >, cdrs_p <cdr <P> > >; };

template <typename A, typename P>
struct conses_pt
{
	using type = cons <cons <car <A>, car <P> >, conses_p <cdr <A>, cdr <P> > >;
};

template <template <typename...> class C>
struct cars_pt <C <> > { using type = C <>; };

template <template <typename...> class C>
struct cdrs_pt <C <> > { using type = C <>; };

template <typename A, template <typename...> class C>
struct conses_pt <A, C <> > { using type = C <>; };

//-----------------------------------------------------------------------------

template <typename... P> using cars_t = cars_pt <pack <P...> >;
template <typename... P> using cdrs_t = cdrs_pt <pack <P...> >;

template <typename A, typename... P>
using conses_t = conses_pt <A, pack <P...> >;

template <typename... P> using cars = type_of <cars_t <P...> >;
template <typename... P> using cdrs = type_of <cdrs_t <P...> >;

template <typename A, typename... P>
using conses = type_of <conses_t <A, P...> >;

//-----------------------------------------------------------------------------

}  // namespace packs

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_PACK_LIST_HPP
