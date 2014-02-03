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

#ifndef IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP
#define IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename T, template <typename...> class I = ptr_iter,
	template <typename...> class V = ptr_trav,
	typename S = size_t, typename D = ptrdiff_t
>
struct seq_types
{
	using value_type = T;
	using size_type = S;
	using difference_type = D;

	using iterator = I <T, ltref <T> >;
	using fwd_iterator = I <T, rtref <T> >;
	using const_iterator = I <const T, cltref <T> >;

	using traversor = V <T, ltref <T> >;
	using fwd_traversor = V <T, rtref <T> >;
	using const_traversor = V <const T, cltref <T> >;
};

//-----------------------------------------------------------------------------

template <typename D, typename ST>
class base_seq : public derived <D>, public ST
{
	using T  = seq_val <ST>;
	using S  = seq_size <ST>;
	using R  = ltref <T>;
	using RF = rtref <T>;
	using RC = cltref <T>;
	using I  = seq_iter <ST>;
	using IF = seq_fwd_iter <ST>;
	using IC = seq_const_iter <ST>;

//-----------------------------------------------------------------------------

	INLINE           IF b_f()      { return der_f().begin(); }
	INLINE           IF b() &&     { return der_f().begin(); }
	INLINE           I  b() &      { return der().begin(); }
	INLINE constexpr IC b() const& { return der().begin(); }

	INLINE           IF e_f()      { return der_f().end(); }
	INLINE           IF e() &&     { return der_f().end(); }
	INLINE           I  e() &      { return der().end(); }
	INLINE constexpr IC e() const& { return der().end(); }

//-----------------------------------------------------------------------------

protected:
	using derived <D>::der_f;
	using derived <D>::der;

//-----------------------------------------------------------------------------

public:
	INLINE constexpr bool empty() const { return der().size() == 0; }

	INLINE           RF front() &&     { return *b_f(); }
	INLINE           R  front() &      { return *b(); }
	INLINE constexpr RC front() const& { return *b(); }

	INLINE           RF back() &&     { return e_f()[-1]; }
	INLINE           R  back() &      { return e()[-1]; }
	INLINE constexpr RC back() const& { return e()[-1]; }

//-----------------------------------------------------------------------------

	INLINE           RF operator[](S n) &&     { return b_f()[n]; }
	INLINE           R  operator[](S n) &      { return b()[n]; }
	INLINE constexpr RC operator[](S n) const& { return b()[n]; }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_BASE_BASE_HPP
