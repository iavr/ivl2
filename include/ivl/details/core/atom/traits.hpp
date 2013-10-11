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

#ifndef IVL_DETAILS_CORE_ATOM_TRAITS_HPP
#define IVL_DETAILS_CORE_ATOM_TRAITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace traits {

using atom_details::atom;

//-----------------------------------------------------------------------------

namespace details {

template <typename T>
struct is_atom_ : public _false { };

template <typename T>
struct is_atom_<atom <T> > : public _true { };

}  // namespace details

template <typename T> using is_atom = details::is_atom_<raw_type <T> >;

template <typename T>
struct as_tuple : public expr <is_tuple <T>{} || is_atom <T>{}> { };

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = as_tuple <T>{}>
struct wrap_t_ : public id_t <T> { };

template <typename T>
struct wrap_t_<T, false> { using type = atom <T>; };

}  // namespace details

template <typename T> using wrap_t = details::wrap_t_<T>;
template <typename T> using wrap   = type_of <wrap_t <T> >;

// //-----------------------------------------------------------------------------
//
// template <typename T> using tup_len = length_of <raw_type <T> >;
//
//-----------------------------------------------------------------------------

template <typename A>
struct tup_types_t <_type <A> > { using type = _type <A>; };

// //-----------------------------------------------------------------------------
//
// template <size_t I, typename T>
// using tup_elem_t = tup_tx_t <T, pick_p <I, raw_types <T> > >;
//
// template <size_t I, typename T>
// using tup_elem = type_of <tup_elem_t <I, T> >;
//
//-----------------------------------------------------------------------------

template <typename A>
struct rtref_t <_type <A> > { using type = atom <rtref <A> >; };

template <typename A>
struct ltref_t <_type <A> > { using type = atom <ltref <A> >; };

template <typename A>
struct cltref_t <_type <A> > { using type = atom <cltref <A> >; };

// //-----------------------------------------------------------------------------
//
// template <typename T>
// using tuple_of_t = _if <is_tuple <T>{}, raw_type_t <T>, id_t <tuple <T> > >;
//
// template <typename T> using tuple_of = type_of <tuple_of_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ATOM_TRAITS_HPP
