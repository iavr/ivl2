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

#ifndef IVL_CORE_TYPE_CORE_TAG_HPP
#define IVL_CORE_TYPE_CORE_TAG_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tag {

//-----------------------------------------------------------------------------

template <typename... D> struct val_  { };
template <typename... D> struct rref_ { };
template <typename... D> struct lref_ { };
template <typename... D> struct cref_ { };
template <typename... D> struct ptr_  { };

template <typename... D> struct _int_   { };
template <typename... D> struct _float_ { };
template <typename... D> struct norm_   { };

template <typename... D> struct cons_  { };
template <typename... D> struct list_  { };
template <typename... D> struct array_ { };
template <typename... D> struct call_  { };

//-----------------------------------------------------------------------------

using val  = val_<>;
using rref = rref_<>;
using lref = lref_<>;
using cref = cref_<>;
using ptr  = ptr_<>;

using _int   = _int_<>;
using _float = _float_<>;
using norm   = norm_<>;

using cons  = cons_<>;
using list  = list_<>;
using array = array_<>;
using call  = call_<>;

using cons_list  = cons_<list>;
using int_array  = _int_<array>;
using array_list = array_<list>;

//-----------------------------------------------------------------------------

}  // namespace tag

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TYPE_CORE_TAG_HPP
