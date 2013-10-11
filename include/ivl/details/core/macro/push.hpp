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

#ifndef IVL_DETAILS_CORE_MACRO_PUSH_HPP
#define IVL_DETAILS_CORE_MACRO_PUSH_HPP

//-----------------------------------------------------------------------------

#ifndef IVL_MACROS_PUSHED

#pragma pack(push, _CRT_PACKING)

//-----------------------------------------------------------------------------

#ifdef _MSC_VER

#ifdef min
#pragma push_macro("min")
#undef min
#define IVL_POP_min
#endif

#ifdef max
#pragma push_macro("max")
#undef max
#define IVL_POP_max
#endif

#endif  // _MSC_VER

//-----------------------------------------------------------------------------

#ifdef CHECK
#pragma push_macro("CHECK")
#undef CHECK
#define IVL_POP_CHECK
#endif

#ifdef DEBUG
#pragma push_macro("DEBUG")
#undef DEBUG
#define IVL_POP_DEBUG
#endif

//-----------------------------------------------------------------------------

#define IVL_MACROS_PUSHED
#endif  // IVL_MACROS_PUSHED

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_MACRO_PUSH_HPP
