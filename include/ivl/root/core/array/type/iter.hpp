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

//-----------------------------------------------------------------------------

template <typename I, typename R = seq_iref <I>, typename T = seq_val <I> >
using iter_iter = iterator <tag::iter, I, R, T>;

template <
	typename Q, typename I, typename R = seq_iref <I>,
	typename T = seq_val <I>
>
using iter_trav = traversor <tag::iter, Q, I, R, T>;

template <
	typename Q, typename V, typename R = seq_iref <V>,
	typename T = seq_val <V>
>
using trav_trav = traversor <tag::trav, Q, V, R, T>;

//-----------------------------------------------------------------------------

template <typename I, typename R = rref_opt <I>, typename T = I>
using atom_iter = iterator <tag::atom, I, R, T>;

template <typename Q, typename I, typename R = rref_opt <I>, typename T = I>
using atom_trav = traversor <tag::atom, Q, I, R, T>;

template <typename I, typename R = rref_opt <I>, typename T = I>
using inf_trav = atom_trav <path, I, R, T>;

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename U>
using range_iter = iterator <tag::range, I, R, T, U>;

template <typename Q, typename I, typename R, typename T, typename U>
using range_trav = traversor <tag::range, Q, I, R, T, U>;

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T>
using flip_iter = iterator <tag::flip, I, R, T>;

template <typename Q, typename V, typename R, typename T>
using flip_trav = traversor <tag::flip, Q, V, R, T>;

template <typename I, typename R, typename T, typename U>
using indirect_iter = iterator <tag::indirect, I, R, T, U>;

template <typename Q, typename V, typename R, typename T, typename U>
using indirect_trav = traversor <tag::indirect, Q, V, R, T, U>;

//-----------------------------------------------------------------------------

template <typename I, typename R, typename T, typename G, typename F>
using apply_iter = iterator <tag::apply, I, R, T, G, F>;

template <
	typename Q, typename V, typename R, typename T,
	typename G, typename F
>
using apply_trav = traversor <tag::apply, Q, V, R, T, G, F>;

template <typename I, typename R, typename T, typename G>
using zip_iter = iterator <tag::zip, I, R, T, G>;

template <typename Q, typename V, typename R, typename T, typename G>
using zip_trav = traversor <tag::zip, Q, V, R, T, G>;

template <typename V, typename R, typename T>
using join_iter = iterator <tag::join, V, R, T>;

template <typename Q, typename V, typename R, typename T>
using join_trav = traversor <tag::join, Q, V, R, T>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::iterator;
using details::traversor;

using details::iter_iter;
using details::iter_trav;
using details::trav_trav;

using details::atom_iter;
using details::atom_trav;
using details::inf_trav;

using details::range_iter;
using details::range_trav;

using details::flip_iter;
using details::flip_trav;
using details::indirect_iter;
using details::indirect_trav;

using details::apply_iter;
using details::apply_trav;
using details::zip_iter;
using details::zip_trav;
using details::join_iter;
using details::join_trav;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_TYPE_ITER_HPP
