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

#ifndef IVL_CORE_ATOM_TYPE_ATOM_HPP
#define IVL_CORE_ATOM_TYPE_ATOM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace atoms {
namespace details {

//-----------------------------------------------------------------------------

template <typename T, typename C, typename B>
struct atom_base;

template <typename T, typename B>
using tup_atom_base = atom_base <T, tag::tup, B>;

template <typename T, typename B>
using seq_atom_base = atom_base <T, tag::seq, B>;

//-----------------------------------------------------------------------------

template <typename T, typename C = tag::atom>
struct atom;

template <typename T> using raw_atom = atom <T, tag::raw>;
template <typename T> using tup_atom = atom <T, tag::tup>;
template <typename T> using seq_atom = atom <T, tag::seq>;
template <typename T> using ext_atom = atom <T, tag::ext>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::atom;
using details::raw_atom;
using details::tup_atom;
using details::seq_atom;
using details::ext_atom;

}  // namespace atoms

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ATOM_TYPE_ATOM_HPP
