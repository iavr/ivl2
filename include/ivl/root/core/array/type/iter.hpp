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

#ifndef IVL_CORE_ARRAY_TYPE_ITER_HPP
#define IVL_CORE_ARRAY_TYPE_ITER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename C, typename... A> class iterator;
template <typename C, typename... A> class traversor;

template <typename I, typename R = seq_ref <I>, typename T = seq_val <I> >
using iter_iter = iterator <data::iter <>, I, R, T>;

template <typename I, typename R = seq_ref <I>, typename T = seq_val <I> >
using iter_trav = traversor <data::iter <>, I, R, T>;

template <typename I, typename R, typename T = I>
using atom_iter = iterator <data::atom <>, I, R, T>;

template <typename I, typename R, typename T = I>
using atom_trav = traversor <data::atom <>, I, R, T>;

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename U>
using indirect_iter = iterator <data::indirect <>, I, R, T, U>;

template <typename V, typename R, typename T, typename U>
using indirect_trav = traversor <data::indirect <>, V, R, T, U>;

template <typename I, typename R, typename T, typename M, typename F>
using apply_iter = iterator <data::apply <>, I, R, T, M, F>;

template <typename V, typename R, typename T, typename M, typename F>
using apply_trav = traversor <data::apply <>, V, R, T, M, F>;

//-----------------------------------------------------------------------------

template <typename T> using ptr_iter = iter_iter <remove_ref <T>*>;

template <typename T, typename R = rref_opt <T> >
using raw_atom_trav = atom_trav <R, R>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::iterator;
using details::traversor;

using details::iter_iter;
using details::iter_trav;
using details::atom_iter;
using details::atom_trav;

using details::indirect_iter;
using details::indirect_trav;
using details::apply_iter;
using details::apply_trav;

using details::ptr_iter;
using details::raw_atom_trav;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_ITER_HPP
