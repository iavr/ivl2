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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_MEMBER_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename R, typename C, R C::*M>
struct c_member : public constant <R C::*, c_member <R, C, M> >
{
	INLINE constexpr operator R C::*() const { return M; }
};

template <typename R, typename C, R const C::*M>
struct c_cmember : public constant <R const C::*, c_cmember <R, C, M> >
{
	INLINE constexpr operator R const C::*() const { return M; }
};

//-----------------------------------------------------------------------------

template <typename R, typename C, C &O, R C::*M>
using c_ref_member =
	c_op <op::ptr_member (c_ref <C, O>, c_member <R, C, M>)>;

template <typename R, typename C, C const &O, R const C::*M>
using c_cref_member =
	c_op <op::ptr_member (c_cref <C, O>, c_cmember <R, C, M>)>;

//-----------------------------------------------------------------------------

template <typename R, typename C, C *O, R C::*M>
using c_ptr_member =
	c_op <op::ptr_member (c_ptr <C, O>, c_member <R, C, M>)>;

template <typename R, typename C, C const *O, R const C::*M>
using c_cptr_member =
	c_op <op::ptr_member (c_cptr <C, O>, c_cmember <R, C, M>)>;

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_MEMBER_HPP
