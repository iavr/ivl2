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

#ifndef IVL_DETAILS_CORE_FUN_MEMBER_HPP
#define IVL_DETAILS_CORE_FUN_MEMBER_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct key_member_call
{
	template <typename C, typename M>
	INLINE constexpr auto operator()(C&& c, M m) const
	-> decltype(key_member <M>()(fwd <C>(c)))
		{ return key_member <M>()(fwd <C>(c)); }
};

struct key_call_call
{
	template <typename C, typename M, typename... A>
	INLINE constexpr auto operator()(C&& c, M m, A&&... a) const
	-> decltype(key_call <M>()(fwd <C>(c), fwd <A>(a)...))
		{ return key_call <M>()(fwd <C>(c), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename F>
struct op_ref_call
{
	template <typename C, typename O>
	INLINE constexpr auto operator()(C&& c, O&& o) const
	-> decltype(fwd <O>(o).ref().rcall(F(), fwd <C>(c), fwd <O>(o).op()))
		{ return fwd <O>(o).ref().rcall(F(), fwd <C>(c), fwd <O>(o).op()); }
};

//-----------------------------------------------------------------------------

// c .* &C::m VS p ->* &C::m
using op_member = try_fun <op::ref_member, op::ptr_member>;

// c .* &C::m(a...) VS p ->* &C::m(a...)
using op_call   = try_fun <op::ref_call,   op::ptr_call>;

// c ->* k VS c ->* &C::m OR pow(b, e)
template <typename C, typename M, bool = is_key <M>()>
struct op_key_member_for_t : call_first_t <pack <pow, op_member>(C, M)> { };

template <typename C, typename M>
struct op_key_member_for_t <C, M, true> : id_t <key_member_call> { };

template <typename C, typename M>
using op_key_member_for = type_of <op_key_member_for_t <C, M> >;

// c ->* k._(a...) OR (c ->* k)(a...) VS c ->* _[&C::m]._(a...) OR (c ->* &C::m)(a...)
template <typename C, typename M, typename... A>
using op_key_call_for = _if <is_key <M>{}, key_call_call, op_call>;

using op_key_member = choose_fun <op_key_member_for>;
using op_key_call   = choose_fun <op_key_call_for>;

using vec_op_key_member = vec_apply <op_key_member>;  // cannot be void (pow assumed so)
using vec_op_key_call   = vec_auto  <op_key_call>;    // can be void

// c ->* m._(a...) VS c ->* m OR (c ->* m)(a...)
template <typename C, typename M>
using op_ref_member_for = _if <
	is_op_ref <M>{},
	op_ref_call <vec_op_key_call>,
	try_fun <vec_op_key_member, binder <vec_op_key_call> >
>;

using op_ref_member = choose_fun <op_ref_member_for>;

// _[b] ->* e VS c ->* m
template <typename A, typename B>
using member_for = _if <
	is_atom <A>() && !is_class <raw_type <B> >(),
	atom_call <op_ref_member>,
	op_ref_member
>;

using member = choose_fun <member_for>;

//-----------------------------------------------------------------------------

}  // namespace details

using details::op_member;
using details::op_call;
using details::op_key_member;
using details::op_key_call;
using details::op_ref_member;
using details::member;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

namespace fun {

using op_key_member = afun::details::vec_op_key_member;
using op_key_call   = afun::details::vec_op_key_call;

}  // namespace fun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_FUN_MEMBER_HPP
