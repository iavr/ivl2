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

#ifndef IVL_DETAILS_CORE_TYPE_CONST_SIG_HPP
#define IVL_DETAILS_CORE_TYPE_CONST_SIG_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace constants {

//-----------------------------------------------------------------------------

template <typename S> class c_sig { };

//-----------------------------------------------------------------------------

template <typename R, typename... A>
class c_sig <R (A...)>
{
	using RC = op::ref_call;
	using PC = op::ptr_call;

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A...)>
	struct function :
		public fun_constant <R (*)(A...), function <F> >
	{
		INLINE constexpr
		operator value_type_of <function>() const { return F; }
	};

//-----------------------------------------------------------------------------

	template <typename C, R (C::*M)(A...)>
	struct method :
		public fun_constant <R (C::*)(A...), method <C, M> >
	{
		INLINE constexpr
		operator value_type_of <method>() const { return M; }
	};

	template <typename C, R (C::*M)(A...) const>
	struct cmethod :
		public fun_constant <R (C::*)(A...) const, cmethod <C, M> >
	{
		INLINE constexpr
		operator value_type_of <cmethod>() const { return M; }
	};

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

	template <typename C, R (C::*M)(A...) &>
	struct lmethod :
		public fun_constant <R (C::*)(A...) &, lmethod <C, M> >
	{
		INLINE constexpr
		operator value_type_of <lmethod>() const { return M; }
	};

	template <typename C, R (C::*M)(A...) &&>
	struct rmethod :
		public fun_constant <R (C::*)(A...) &&, rmethod <C, M> >
	{
		INLINE constexpr
		operator value_type_of <rmethod>() const { return M; }
	};

	template <typename C, R (C::*M)(A...) const&>
	struct clmethod :
		public fun_constant <R (C::*)(A...) const&, clmethod <C, M> >
	{
		INLINE constexpr
		operator value_type_of <clmethod>() const { return M; }
	};

	template <typename C, R (C::*M)(A...) const&&>
	struct crmethod :
		public fun_constant <R (C::*)(A...) const&&, crmethod <C, M> >
	{
		INLINE constexpr
		operator value_type_of <crmethod>() const { return M; }
	};

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

//-----------------------------------------------------------------------------

	template <R (*F)(A...), typename... V>
	using call = c_call <function <F>(V...)>;

//-----------------------------------------------------------------------------

	template <typename C, R (C::*M)(A...), typename... V>
	using fun_call = c_op <RC (c_cons <C>, method <C, M>, V...)>;

	template <typename C, R (C::*M)(A...) const, typename... V>
	using cfun_call = c_op <RC (c_cons <C>, cmethod <C, M>, V...)>;

	template <typename C, C &O, R (C::*M)(A...), typename... V>
	using ref_call = c_op <RC (c_ref <C, O>, method <C, M>, V...)>;

	template <typename C, C const &O, R (C::*M)(A...) const, typename... V>
	using cref_call = c_op <RC (c_cref <C, O>, cmethod <C, M>, V...)>;

	template <typename C, C *O, R (C::*M)(A...), typename... V>
	using ptr_call = c_op <PC (c_ptr <C, O>, method <C, M>, V...)>;

	template <typename C, C const *O, R (C::*M)(A...) const, typename... V>
	using cptr_call = c_op <PC (c_cptr <C, O>, cmethod <C, M>, V...)>;

//-----------------------------------------------------------------------------

#if IVL_HAS_FEATURE(cxx_reference_qualified_functions)

	template <typename C, R (C::*M)(A...) &&, typename... V>
	using rfun_call = c_op <RC (c_cons <C>, rmethod <C, M>, V...)>;

	template <typename C, R (C::*M)(A...) const&&, typename... V>
	using crfun_call = c_op <RC (c_cons <C>, crmethod <C, M>, V...)>;

	template <typename C, C &O, R (C::*M)(A...) &, typename... V>
	using lref_call = c_op <RC (c_ref <C, O>, lmethod <C, M>, V...)>;

	template <typename C, C const &O, R (C::*M)(A...) const&, typename... V>
	using clref_call = c_op <RC (c_cref <C, O>, clmethod <C, M>, V...)>;

	template <typename C, C *O, R (C::*M)(A...) &, typename... V>
	using lptr_call = c_op <PC (c_ptr <C, O>, lmethod <C, M>, V...)>;

	template <typename C, C const *O, R (C::*M)(A...) const&, typename... V>
	using clptr_call = c_op <PC (c_cptr <C, O>, clmethod <C, M>, V...)>;

#endif  // IVL_HAS_FEATURE(cxx_reference_qualified_functions)

};

//-----------------------------------------------------------------------------

}  // namespace constants

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_TYPE_CONST_SIG_HPP
