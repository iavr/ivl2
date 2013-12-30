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

class M;
namespace ivl {

//-----------------------------------------------------------------------------

namespace afun_details {

//-----------------------------------------------------------------------------

struct member_call
{
	template <
		typename C, typename M, typename... A,
		enable_if <!is_key <M>()>
	= 0>
	INLINE constexpr auto operator()(C&& c, M&& m, A&&... a) const
	-> decltype(afun::op::ptr_call()(fwd <C>(c), fwd <M>(m), fwd <A>(a)...))
		{ return afun::op::ptr_call()(fwd <C>(c), fwd <M>(m), fwd <A>(a)...); }

	template <
		typename C, typename M, typename... A,
		enable_if <is_key <M>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, M m, A&&... a) const
	-> decltype(afun::key_call <M>()(fwd <C>(c), fwd <A>(a)...))
		{ return afun::key_call <M>()(fwd <C>(c), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename C, typename M>
class member_fun : private tuple <C, M>
{
	using B = tuple <C, M>;
	using B::fst_f;
	using B::fst;
	using B::snd_f;
	using B::snd;

	using MC = afun::vec <member_call>;  // can be void

public:
	using B::B;

	template <typename... A>
	INLINE auto operator()(A&&... a) &&
	-> decltype(MC()(fst_f(), snd_f(), fwd <A>(a)...))
		{ return MC()(fst_f(), snd_f(), fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr auto operator()(A&&... a) const&
	-> decltype(MC()(fst(), snd(), fwd <A>(a)...))
		{ return MC()(fst(), snd(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

class member
{
	template <typename B, typename E>
	using has_pow = can_call <afun::pow(B, E)>;

public:

	template <
		typename B, typename E,
		enable_if <!is_key <E>() && has_pow <B, E>()>
	= 0>
	INLINE constexpr auto operator()(B&& b, E&& e) const
	-> decltype(afun::pow()(fwd <B>(b), fwd <E>(e)))
		{ return afun::pow()(fwd <B>(b), fwd <E>(e)); }

	template <
		typename C, typename M,
		enable_if <!is_key <M>() && !has_pow <C, M>()>
	= 0>
	INLINE constexpr auto operator()(C&& c, M&& m) const
	-> decltype(afun::op::ptr_member()(fwd <C>(c), fwd <M>(m)))
		{ return afun::op::ptr_member()(fwd <C>(c), fwd <M>(m)); }

	template <
		typename C, typename M,
		enable_if <is_key <M>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, M m) const
	-> decltype(afun::key_member <M>()(fwd <C>(c)))
		{ return afun::key_member <M>()(fwd <C>(c)); }
};

//-----------------------------------------------------------------------------

class fun_member
{
	using VM = afun::vec_apply <member>;  // cannot be void (pow assumed so)

	template <typename... A>
	using MF = member_fun <base_opt <A&&>...>;

	template <typename C, typename M>
	using has_member = can_call <member(C, M)>;

public:

	template <
		typename C, typename M,
		enable_if <!vec_all <has_member, C, M>()>
	= 0>
	INLINE constexpr MF <C, M> operator()(C&& c, M&& m) const
		{ return MF <C, M>(fwd <C>(c), fwd <M>(m)); }

	template <
		typename C, typename M,
		enable_if <vec_all <has_member, C, M>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, M&& m) const
	-> decltype(VM()(fwd <C>(c), fwd <M>(m)))
		{ return VM()(fwd <C>(c), fwd <M>(m)); }
};

//-----------------------------------------------------------------------------

class op_member
{
	using MC = afun::vec <member_call>;  // can be void

public:

	template <
		typename C, typename M,
		enable_if <!is_op_ref <M>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, M&& m) const
	-> decltype(fun_member()(fwd <C>(c), fwd <M>(m)))
		{ return fun_member()(fwd <C>(c), fwd <M>(m)); }

	template <
		typename C, typename O,
		enable_if <is_op_ref <O>{}>
	= 0>
	INLINE constexpr auto operator()(C&& c, O&& o) const
	-> decltype(fwd <O>(o).ref().rcall(MC(), fwd <C>(c), fwd <O>(o).op()))
		{ return fwd <O>(o).ref().rcall(MC(), fwd <C>(c), fwd <O>(o).op()); }
};

//-----------------------------------------------------------------------------

}  // namespace afun_details

//-----------------------------------------------------------------------------

namespace afun { using member = afun_details::op_member; }

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_FUN_MEMBER_HPP
