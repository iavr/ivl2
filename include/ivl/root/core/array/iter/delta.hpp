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

#ifndef IVL_CORE_ARRAY_ITER_DELTA_HPP
#define IVL_CORE_ARRAY_ITER_DELTA_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D>
struct delta_base : derived <D>
{
private:
	using derived <D>::der;

protected:
	template <typename F, typename I, typename O>
	INLINE constexpr ret <F(I, O)>
	inv(bool c, F f, I&& i, O&& o) const { return c ? f(i, o) : f(o, i); }

public:
	template <typename I> INLINE I next(I i) const { der().inc(i); return i; }
	template <typename I> INLINE I prev(I i) const { der().dec(i); return i; }

	template <typename I, typename d>
	INLINE I rel(I i, d n) const { der().add(i, n); return i; }

	template <typename d, typename B, typename E>
	INLINE void
	trunc(B&& b, E&& e) const
	{
		d s = der().template diff <d>((der().inc(e), fwd <E>(e)), b);
		e = s <= 0 ? b : rel <copy <E> >(b, s);
	}
};

//-----------------------------------------------------------------------------

template <>
struct delta <afun::op::inc_> : delta_base <inc_delta>
{
	template <typename I> INLINE void inc(I&& i) const { ++i; }
	template <typename I> INLINE void dec(I&& i) const { --i; }

	template <typename I, typename d>
	INLINE void add(I&& i, d n) const { i += n; }

	template <typename I, typename d>
	INLINE void sub(I&& i, d n) const { i -= n; }

	template <typename F, typename I, typename O>
	INLINE constexpr bool
	comp(F f, I&& i, O&& o) const { return f(i, o); }

	template <typename d, typename I, typename O>
	INLINE constexpr d
	diff(I&& i, O&& o) const { return static_cast <d>(i - o); }

	template <typename d, typename B, typename E>
	INLINE void
	trunc(B&& b, E&& e) const { if (++e < b) e = b; }
};

//-----------------------------------------------------------------------------

template <>
struct delta <afun::op::dec_> : delta_base <dec_delta>
{
	template <typename I> INLINE void inc(I&& i) const { --i; }
	template <typename I> INLINE void dec(I&& i) const { ++i; }

	template <typename I, typename d>
	INLINE void add(I&& i, d n) const { i -= n; }

	template <typename I, typename d>
	INLINE void sub(I&& i, d n) const { i += n; }

	template <typename F, typename I, typename O>
	INLINE constexpr bool
	comp(F f, I&& i, O&& o) const { return f(o, i); }

	template <typename d, typename I, typename O>
	INLINE constexpr d
	diff(I&& i, O&& o) const { return static_cast <d>(o - i); }

	template <typename d, typename B, typename E>
	INLINE void
	trunc(B&& b, E&& e) const { if (--e > b) e = b; }
};

//-----------------------------------------------------------------------------

template <typename U>
class delta <afun::op::add, U> :
	public delta_base <add_delta <U> >,
	public raw_tuple <U>
{
	using S = delta_base <add_delta <U> >;
	using B = raw_tuple <U>;
	using B::val;
	using S::inv;

public:
	using B::B;
	using S::rel;

	template <typename I> INLINE void inc(I&& i) const { i += val(); }
	template <typename I> INLINE void dec(I&& i) const { i -= val(); }

	template <typename I, typename d>
	INLINE void add(I&& i, d n) const { i += n * val(); }

	template <typename I, typename d>
	INLINE void sub(I&& i, d n) const { i -= n * val(); }

	template <typename F, typename I, typename O>
	INLINE constexpr bool
	comp(F f, I&& i, O&& o) const { return inv(val() > 0, f, i, o); }

	template <typename d, typename I, typename O>
	INLINE constexpr d
	diff(I&& i, O&& o) const { return static_cast <d>(i - o) / val(); }
};

//-----------------------------------------------------------------------------

template <typename U>
class delta <afun::op::sub, U> :
	public delta_base <sub_delta <U> >,
	public raw_tuple <U>
{
	using S = delta_base <sub_delta <U> >;
	using B = raw_tuple <U>;
	using B::val;
	using S::inv;

public:
	using B::B;
	using S::rel;

	template <typename I> INLINE void inc(I&& i) const { i -= val(); }
	template <typename I> INLINE void dec(I&& i) const { i += val(); }

	template <typename I, typename d>
	INLINE void add(I&& i, d n) const { i -= n * val(); }

	template <typename I, typename d>
	INLINE void sub(I&& i, d n) const { i += n * val(); }

	template <typename F, typename I, typename O>
	INLINE constexpr bool
	comp(F f, I&& i, O&& o) const { return inv(val() > 0, f, o, i); }

	template <typename d, typename I, typename O>
	INLINE constexpr d
	diff(I&& i, O&& o) const { return static_cast <d>(o - i) / val(); }
};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_ITER_DELTA_HPP
