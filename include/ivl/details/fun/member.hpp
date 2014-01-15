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

class op_member
{
	using R = op::ref_member;
	using P = op::ptr_member;

	template <typename C, typename M>
	using F = _if <can_call <P(C, M)>{}, P, R>;

public:
	template <typename C, typename M>
	INLINE constexpr auto operator()(C&& c, M&& m) const
	-> decltype(F <C, M>()(fwd <C>(c), fwd <M>(m)))
		{ return F <C, M>()(fwd <C>(c), fwd <M>(m)); }
};

//-----------------------------------------------------------------------------

class op_call
{
	using R = op::ref_call;
	using P = op::ptr_call;

	template <typename C, typename M, typename... A>
	using F = _if <can_call <P(C, M, A...)>{}, P, R>;

public:
	template <typename C, typename M, typename... A>
	INLINE constexpr ret <F <C, M, A...>(C, M, A...)>
	operator()(C&& c, M&& m, A&&... a) const
		{ return F <C, M, A...>()(fwd <C>(c), fwd <M>(m), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

struct op_key_call
{
	template <
		typename C, typename M, typename... A,
		enable_if <!is_key <M>()>
	= 0>
	INLINE constexpr auto operator()(C&& c, M&& m, A&&... a) const
	-> decltype(op_call()(fwd <C>(c), fwd <M>(m), fwd <A>(a)...))
		{ return op_call()(fwd <C>(c), fwd <M>(m), fwd <A>(a)...); }

	template <
		typename C, typename M, typename... A,
		enable_if <is_key <M>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, M m, A&&... a) const
	-> decltype(key_call <M>()(fwd <C>(c), fwd <A>(a)...))
		{ return key_call <M>()(fwd <C>(c), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename C, typename M>
class member_fun : private raw_tuple <C, M>
{
	using B = raw_tuple <C, M>;
	using B::fst_f;
	using B::fst;
	using B::snd_f;
	using B::snd;

	using MC = vec_auto <op_key_call>;  // can be void

public:
	using B::B;

	template <typename... A>
	INLINE ret <MC(C, M, A...)>
	operator()(A&&... a) && { return MC()(fst_f(), snd_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr ret <MC(cltref <C>, cltref <M>, A...)>
	operator()(A&&... a) const& { return MC()(fst(), snd(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

class op_key_member
{
	template <typename C, typename M>
	using F = _if <can_call <pow(C, M)>{}, pow, op_member>;

public:
	template <typename C, typename M, enable_if <!is_key <M>()> = 0>
	INLINE constexpr auto operator()(C&& c, M&& m) const
	-> decltype(F <C, M>()(fwd <C>(c), fwd <M>(m)))
		{ return F <C, M>()(fwd <C>(c), fwd <M>(m)); }

	template <typename C, typename M, enable_if <is_key <M>{}> = 0>
	INLINE constexpr auto operator()(C&& c, M m) const
	-> decltype(key_member <M>()(fwd <C>(c)))
		{ return key_member <M>()(fwd <C>(c)); }
};

//-----------------------------------------------------------------------------

class fun_member
{
	using VM = vec_apply <op_key_member>;   // cannot be void (pow assumed so)
	using MF = rref_of <member_fun>;

	template <typename C, typename M>
	using has_member = can_call <op_key_member(C, M)>;

	template <typename C, typename M>
	using F = _if <vec_all <has_member, C, M>{}, VM, MF>;

public:
	template <typename C, typename M>
	INLINE constexpr ret <F <C, M>(C, M)>
	operator()(C&& c, M&& m) const
		{ return F <C, M>()(fwd <C>(c), fwd <M>(m)); }
};

//-----------------------------------------------------------------------------

class op_ref_member
{
	using MC = vec_auto <op_key_call>;  // can be void

public:
	template <typename C, typename M, enable_if <!is_op_ref <M>{}> = 0>
	INLINE constexpr ret <fun_member(C, M)>
	operator()(C&& c, M&& m) const
		{ return fun_member()(fwd <C>(c), fwd <M>(m)); }

	template <typename C, typename O, enable_if <is_op_ref <O>{}> = 0>
	INLINE constexpr auto operator()(C&& c, O&& o) const
	-> decltype(fwd <O>(o).ref().rcall(MC(), fwd <C>(c), fwd <O>(o).op()))
		{ return fwd <O>(o).ref().rcall(MC(), fwd <C>(c), fwd <O>(o).op()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using member = details::op_ref_member;

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_FUN_MEMBER_HPP
