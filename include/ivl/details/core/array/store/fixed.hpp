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

#ifndef IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP
#define IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T, size_t N>
struct fixed_store
{
	T a[N];

	INLINE T*       data()       { return a; }
	INLINE const T* data() const { return a; }
};

template <typename T>
struct fixed_store <T, 0>
{
	INLINE T*       data()       { return nullptr; }
	INLINE const T* data() const { return nullptr; }
};

//-----------------------------------------------------------------------------

template <typename T, size_t N>
class sequence <data::fixed <>, T, sizes <N> > :
	public base_seq <sequence <data::fixed <>, T, sizes <N> >, seq_types <T> >,
	fixed_store <T, N>
{
	friend base_seq <sequence, seq_types <T> >;

	using F  = fixed_store <T, N>;
	using ST = seq_types <T>;

	using I  = seq_iter <ST>;
	using IF = seq_fwd_iter <ST>;
	using IC = seq_const_iter <ST>;
	using V  = seq_trav <ST>;
	using VF = seq_fwd_trav <ST>;
	using VC = seq_const_trav <ST>;

//-----------------------------------------------------------------------------

	INLINE T*       b()       { return F::data(); }
	INLINE const T* b() const { return F::data(); }
	INLINE T*       e()       { return F::data() + N; }
	INLINE const T* e() const { return F::data() + N; }

//-----------------------------------------------------------------------------

public:

	INLINE constexpr size_t max_size() const { return N; }
	INLINE constexpr size_t size()     const { return N; }

	INLINE           IF begin() &&     { return IF(b()); }
	INLINE           I  begin() &      { return I(b()); }
	INLINE constexpr IC begin() const& { return IC(b()); }

	INLINE           IF end() &&     { return IF(e()); }
	INLINE           I  end() &      { return I(e()); }
	INLINE constexpr IC end() const& { return IC(e()); }

	INLINE           VF trav() &&     { return VF(b(), e()); }
	INLINE           V  trav() &      { return V (b(), e()); }
	INLINE constexpr VC trav() const& { return VC(b(), e()); }

	INLINE           IF data() &&     { return IF(b()); }
	INLINE           I  data() &      { return I(b()); }
	INLINE constexpr IC data() const& { return IC(b()); }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_ARRAY_STORE_FIXED_HPP
