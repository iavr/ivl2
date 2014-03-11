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

#ifndef IVL_CORE_ARRAY_ITER_FUN_HPP
#define IVL_CORE_ARRAY_ITER_FUN_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename I>
INLINE constexpr I&& step_(_true, I&& i) { return fwd <I>(++i); }

template <typename I>
INLINE constexpr I&& step_(_false, I&& i) { return fwd <I>(--i); }

template <bool F, typename I>
INLINE constexpr I&& inc(I&& i) { return step_(expr <!F>(), i); }

template <bool F, typename I>
INLINE constexpr I&& dec(I&& i) { return step_(expr <F>(), i); }

//-----------------------------------------------------------------------------

template <bool F, typename I>
INLINE I&& ends_fix_(_true, I&& i) { return fwd <I>(i); }

template <bool F, typename I>
INLINE I&& ends_fix_(_false, I&& i) { return dec <F>(i); }

template <bool F, bool E, typename I>
INLINE I&& ends_fix(I&& i) { return ends_fix_<F>(expr <E>(), i); }

//-----------------------------------------------------------------------------

template <bool F, typename I>
INLINE I&& ends_tail(I&& i) { return inc <F>(i), i.sync(), fwd <I>(i); }

template <bool F, bool E, typename I>
INLINE I&& ends_flip(I&& i)
{
	return ends_fix <F, E>(i).swap(), i.remove_ref <I>::template flip <F, E>(),  // TODO extra stuff needed by GCC
	       ends_fix <F, E>(i).sync(), fwd <I>(i);
}

//-----------------------------------------------------------------------------

template <template <typename> class VT, typename Q>
class trav_ends
{
	using R = VT <Q>;
	using C = path_of <Q>;
	using G = expr <path_edge <Q>{}>;

//-----------------------------------------------------------------------------

	template <bool F, typename C, typename B, typename E>
	INLINE constexpr R
	flip(C, _false, B&& b, E&& e) const
		{ return trav <!F>(C(), dec <F>(e), dec <F>(b)); }

	template <bool F, typename C, typename B, typename E>
	INLINE constexpr R
	flip(C, _true, B&& b, E&& e) const
		{ return trav <!F>(C(), e, b); }

//-----------------------------------------------------------------------------

	template <bool F, typename B, typename E>
	INLINE constexpr R
	trav(tag::trav, B&& b, E&& e) const { return R(b, e); }

	template <bool F, typename C, typename B, typename E>
	INLINE constexpr R
	trav(tag::tail_<C>, B&& b, E&& e) const
		{ return trav <F>(C(), inc <F>(b), e); }

	template <bool F, typename C, typename B, typename E>
	INLINE constexpr R
	trav(tag::flip_<C>, B&& b, E&& e) const
		{ return flip <F>(C(), G(), b, e); }

	template <bool F, typename C, typename B, typename E>
	INLINE constexpr R
	trav(tag::edge_<C>, B&& b, E&& e) const
		{ return trav <F>(C(), b, dec <F>(e)); }

//-----------------------------------------------------------------------------

public:
	template <typename B, typename E>
	INLINE constexpr R
	operator()(B&& b, E&& e) const { return trav <false>(C(), b, e); }
};

//-----------------------------------------------------------------------------

template <template <typename> class VT, typename Q>
class join_ends
{
	using R = VT <Q>;
	using C = path_of <Q>;
	using G = expr <path_edge <Q>{}>;

//-----------------------------------------------------------------------------

	template <bool F, typename V>
	INLINE constexpr V&&
	trav(tag::trav, V&& v) const { return mv(v); }

	template <bool F, typename C, typename V>
	INLINE constexpr V&&
	trav(tag::tail_<C>, V&& v) const
		{ return trav <!F>(C(), ends_tail <F>(mv(v))); }

	template <bool F, typename C, typename V>
	INLINE constexpr V&&
	trav(tag::flip_<C>, V&& v) const
		{ return trav <F>(C(), ends_flip <F, G{}>(mv(v))); }

	template <bool F, typename C, typename V>
	INLINE constexpr V&&
	trav(tag::edge_<C>, V&& v) const { return trav <F>(C(), mv(v)); }

//-----------------------------------------------------------------------------

// 	template <typename F, typename L, typename... V, size_t N = sizeof...(V)>
// 	INLINE constexpr R
// 	trav(sizes <0, 0>, F&& f, L&& l, V&&... v) const { return R(f, N, v...); }
//
// 	template <typename F, typename L, typename... V>
// 	INLINE constexpr R
// 	trav(sizes <1, 0>, F&& f, L&& l, V&&... v) const { return R(l, -1, v...); }
//
// 	template <typename F, typename L, typename... V>
// 	INLINE constexpr R
// 	trav(sizes <0, 1>, F&& f, L&& l, V&&... v) const { return R(f, l, v...); }
//
// 	template <typename F, typename L, typename... V>
// 	INLINE constexpr R
// 	trav(sizes <1, 1>, F&& f, L&& l, V&&... v) const { return R(l, f, v...); }

//-----------------------------------------------------------------------------

public:
	template <typename B, typename E, typename... V>
	INLINE constexpr R
	operator()(B&& b, E&& e, V&&... v) const
		{ return trav <false>(C(), R(b, e, v...)); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_FUN_HPP
