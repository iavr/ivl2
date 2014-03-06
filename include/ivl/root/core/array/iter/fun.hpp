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

template <template <typename> class VT, typename Q>
class ends
{
	using R = VT <Q>;
	using C = sizes <path_flip <Q>{}, path_edge <Q>{}>;

	template <typename B, typename E>
	INLINE constexpr R
	trav(sizes <0, 0>, B&& b, E&& e) const { return R(b, e); }

	template <typename B, typename E>
	INLINE constexpr R
	trav(sizes <1, 0>, B&& b, E&& e) const { return R(--e, --b); }

	template <typename B, typename E>
	INLINE constexpr R
	trav(sizes <0, 1>, B&& b, E&& e) const { return R(b, --e); }

	template <typename B, typename E>
	INLINE constexpr R
	trav(sizes <1, 1>, B&& b, E&& e) const { return R(--e, b); }

public:
	template <typename B, typename E>
	INLINE constexpr R
	operator()(B&& b, E&& e) const { return trav(C(), b, e); }
};

//-----------------------------------------------------------------------------

template <template <typename> class VT, typename Q>
class join_ends
{
	using R = VT <Q>;
	using C = sizes <path_flip <Q>{}, path_edge <Q>{}>;

	template <typename F, typename L, typename... V, size_t N = sizeof...(V)>
	INLINE constexpr R
	trav(sizes <0, 0>, F&& f, L&& l, V&&... v) const { return R(f, N, v...); }

	template <typename F, typename L, typename... V>
	INLINE constexpr R
	trav(sizes <1, 0>, F&& f, L&& l, V&&... v) const { return R(l, -1, v...); }

	template <typename F, typename L, typename... V>
	INLINE constexpr R
	trav(sizes <0, 1>, F&& f, L&& l, V&&... v) const { return R(f, l, v...); }

	template <typename F, typename L, typename... V>
	INLINE constexpr R
	trav(sizes <1, 1>, F&& f, L&& l, V&&... v) const { return R(l, f, v...); }

public:
	template <typename F, typename L, typename... V>
	INLINE constexpr R
	operator()(F&& f, L&& l, V&&... v) const { return trav(C(), f, l, v...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_FUN_HPP
