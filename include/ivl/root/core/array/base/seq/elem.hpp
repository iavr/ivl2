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

#ifndef IVL_CORE_ARRAY_BASE_ELEM_HPP
#define IVL_CORE_ARRAY_BASE_ELEM_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T>
class ref_elem;

template <typename T>
class ref_elem <T&>
{
	T& r;

public:
	ref_elem(T& r) : r(r) { }

	operator T&()       { return r; }
	operator T&() const { return r; }
};

//-----------------------------------------------------------------------------

template <typename T>
class ref_elem <T&&>
{
	T&& r;

public:
	ref_elem(T&& r) : r(mv(r)) { }

	operator T&&()       { return mv(r); }
	operator T&&() const { return mv(r); }

	operator T&()       { return r; }
	operator T&() const { return r; }
};

//-----------------------------------------------------------------------------

template <typename T>
using seq_elem = _if <is_ref <T>{}, ref_elem <T>, T>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_ARRAY_BASE_ELEM_HPP
