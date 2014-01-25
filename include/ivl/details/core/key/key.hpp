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

#ifndef IVL_DETAILS_CORE_KEY_KEY_HPP
#define IVL_DETAILS_CORE_KEY_KEY_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K, typename V>
class key_val : private raw_tuple <V>
{
	template <typename T, typename R = raw_type <T> >
	using opt = base_opt <T, R, _if <eq <R, key_val>{}, V, R> >;

	template <typename T> using uopt = opt <add_uref <T> >;

	template <typename O, typename... A>
	using op = op_ref <opt <O>, uopt <A>...>;

public:
	using raw_tuple <V>::raw_tuple;
	using raw_tuple <V>::val;

	INLINE constexpr K key() const { return K(); }

	template <typename... A>
	INLINE op <key_val, A...>
	_(A&&... a) && { return op <key_val, A...>(mv(*this), fwd <A>(a)...); }

	template <typename... A>
	INLINE op <key_val&, A...>
	_(A&&... a) & { return op <key_val&, A...>(*this, fwd <A>(a)...); }

	template <typename... A>
	INLINE constexpr op <const key_val&, A...>
	_(A&&... a) const& { return op <const key_val&, A...>(*this, fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

template <typename K>
class key
{
	template <typename A>
	using kval = key_val <K, uref_opt <A> >;

	template <typename... A>
	using op = op_ref <K, uref_opt <A>...>;

public:
	template <typename A>
	INLINE constexpr kval <A>
	operator=(A&& a) const { return kval <A>(fwd <A>(a)); }

	template <typename... A>
	INLINE constexpr op <A...>
	_(A&&... a) const { return op <A...>(K(), fwd <A>(a)...); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::key_val;
using details::key;

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_KEY_KEY_HPP
