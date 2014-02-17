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

#ifndef IVL_CORE_ARRAY_BASE_SEQ_BASE_HPP
#define IVL_CORE_ARRAY_BASE_SEQ_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename TR, typename... E>
class seq_base : public derived <D>, public seq_store <TR, E...>
{
	using B = seq_store <TR, E...>;
	using T = seq_type <TR>;
	using S = seq_size <TR>;

	using RR = r_seq_ref <TR>;
	using RL = l_seq_ref <TR>;
	using RC = c_seq_ref <TR>;

	using IR = r_iter <TR>;
	using IL = l_iter <TR>;
	using IC = c_iter <TR>;

//-----------------------------------------------------------------------------

	INLINE           IR b_f()      { return der_f().begin(); }
	INLINE           IR b() &&     { return der_f().begin(); }
	INLINE           IL b() &      { return der().begin(); }
	INLINE constexpr IC b() const& { return der().begin(); }

	INLINE           IR e_f()      { return der_f().end(); }
	INLINE           IR e() &&     { return der_f().end(); }
	INLINE           IL e() &      { return der().end(); }
	INLINE constexpr IC e() const& { return der().end(); }

//-----------------------------------------------------------------------------

protected:
	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

public:
	using B::B;

	INLINE constexpr bool empty() const { return der().size() == 0; }

	INLINE           RR front() &&     { return *b_f(); }
	INLINE           RL front() &      { return *b(); }
	INLINE constexpr RC front() const& { return *b(); }

	INLINE           RR back() &&     { return e_f()[-1]; }
	INLINE           RL back() &      { return e()[-1]; }
	INLINE constexpr RC back() const& { return e()[-1]; }

//-----------------------------------------------------------------------------

	INLINE           RR operator[](S n) &&     { return b_f()[n]; }
	INLINE           RL operator[](S n) &      { return b()[n]; }
	INLINE constexpr RC operator[](S n) const& { return b()[n]; }

//-----------------------------------------------------------------------------

private:
	using data = seq_data_tuple <D, E...>;

	template <typename T, typename R = raw_type <T> >
	using opt = base_opt <T, R, _if <eq <R, D>{}, data, R> >;

	template <typename... A>
	using indir = subs <indirect_seq, opt <A>...>;

//-----------------------------------------------------------------------------

public:
	template <typename A, only_if <is_seq <A>{}> = 0>
	INLINE indir <A, D>
	operator[](A&& a) && { return make <indir>()(fwd <A>(a), der_f()); }

	template <typename A, only_if <is_seq <A>{}> = 0>
	INLINE indir <A, D&>
	operator[](A&& a) & { return make <indir>()(fwd <A>(a), der()); }

	template <typename A, only_if <is_seq <A>{}> = 0>
	INLINE constexpr indir <A, const D&>
	operator[](A&& a) const& { return make <indir>()(fwd <A>(a), der()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

using details::seq_traits;
using details::seq_base;

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_SEQ_BASE_HPP
