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

#ifndef IVL_CORE_ARRAY_BEGIN_HPP
#define IVL_CORE_ARRAY_BEGIN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace traits {

template <typename I> struct seq_iref_t;
template <typename I> struct seq_val_t;

template <typename I> using seq_iref = type_of <seq_iref_t <I> >;
template <typename I> using seq_val  = type_of <seq_val_t <I> >;

}  // namespace traits
}  // namespace types

//-----------------------------------------------------------------------------

namespace arrays {
namespace details {

using namespace types;
using namespace tuples;
using afun::make;
using types::bind;

}  // namespace details
}  // namespace arrays

//-----------------------------------------------------------------------------

namespace afun {
namespace details {

using namespace arrays;

}  // namespace details
}  // namespace afun

//-----------------------------------------------------------------------------

namespace types {
namespace traits {

template <typename T> struct as_seq;
template <typename T> struct seq_atom_of_t;
template <typename T> using  seq_atom_of = type_of <seq_atom_of_t <T> >;

namespace details {

using namespace arrays;

}  // namespace details
}  // namespace traits
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BEGIN_HPP
