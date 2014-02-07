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

#ifndef IVL_AFUN_LIMITS_HPP
#define IVL_AFUN_LIMITS_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace afun {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

namespace lim {

//-----------------------------------------------------------------------------

template <typename T>
using limits = std::numeric_limits <T>;

//-----------------------------------------------------------------------------

struct min
{
	template <typename T>
	INLINE T _() const { return limits <T>::min(); }
};

struct max
{
	template <typename T>
	INLINE T _() const { return limits <T>::max(); }
};

//-----------------------------------------------------------------------------

struct eps
{
	template <typename T = double>
	INLINE T _() const { return limits <T>::epsilon(); }
};

struct inf
{
	template <typename T = double>
	INLINE T _() const { return limits <T>::infinity(); }
};

struct nan
{
	template <typename T = double>
	INLINE T _() const { return limits <T>::quiet_NaN(); }
};

//-----------------------------------------------------------------------------

struct inf_min
{
	template <typename T>
	INLINE T _() const
	{
		return limits <T>::has_infinity ?
			-limits <T>::infinity() : limits <T>::min();
	}
};

struct inf_max
{
	template <typename T>
	INLINE T _() const
	{
		return limits <T>::has_infinity ?
			limits <T>::infinity() : limits <T>::max();
	}
};

//-----------------------------------------------------------------------------

}  // namespace lim

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

namespace lim {

using details::lim::min;
using details::lim::max;
using details::lim::eps;
using details::lim::inf;
using details::lim::nan;
using details::lim::inf_min;
using details::lim::inf_max;

}  // namespace lim

//-----------------------------------------------------------------------------

}  // namespace afun

//-----------------------------------------------------------------------------

namespace lim {

static __attribute__ ((unused)) afun::lim::min     min;
static __attribute__ ((unused)) afun::lim::max     max;
static __attribute__ ((unused)) afun::lim::eps     eps;
static __attribute__ ((unused)) afun::lim::inf     inf;
static __attribute__ ((unused)) afun::lim::nan     nan;
static __attribute__ ((unused)) afun::lim::inf_min inf_min;
static __attribute__ ((unused)) afun::lim::inf_max inf_max;

}  // namespace lim

//-----------------------------------------------------------------------------

using lim::eps;
using lim::inf;
using lim::nan;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_AFUN_LIMITS_HPP
