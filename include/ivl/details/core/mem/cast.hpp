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

#ifndef IVL_DETAILS_CORE_MEM_CAST_HPP
#define IVL_DETAILS_CORE_MEM_CAST_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace mem {

//-----------------------------------------------------------------------------

template <typename T>
INLINE T* vary(const T* p) { return const_cast <T*>(p); }

template <typename T>
INLINE T& vary(const T& r) { return const_cast <T&>(r); }

//-----------------------------------------------------------------------------

template <typename T>
INLINE void* away(T& r) { return reinterpret_cast <void*> (r); }

template <typename T>
INLINE const void* away(const T& r)
	{ return reinterpret_cast <const void*>(r); }

//-----------------------------------------------------------------------------

template <typename T>
INLINE void* away(T* p) { return static_cast <void*> (p); }

template <typename T>
INLINE const void* away(const T* p) { return static_cast <const void*>(p); }

template <typename T>
INLINE void* ref (T& r) { return away(&r); }

template <typename T>
INLINE const void* ref (const T& r) { return away(&r); }

//-----------------------------------------------------------------------------

template <typename T>
INLINE T* back (void* p) { return static_cast <T*>(p); }

template <typename T>
INLINE const T* back (const void* p) { return static_cast <const T*>(p); }

template <typename T>
INLINE T& deref(void* p) { return *back <T>(p); }

template <typename T>
INLINE const T& deref(const void* p) { return *back <T>(p); }

//-----------------------------------------------------------------------------

INLINE void*       peek(void* p) { return deref <void*>(p); }
INLINE const void* peek(const void* p) { return deref <const void*>(p); }

//-----------------------------------------------------------------------------

}  // namespace mem

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_MEM_CAST_HPP
