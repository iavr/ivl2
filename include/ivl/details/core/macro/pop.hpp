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

#ifndef IVL_DETAILS_CORE_MACRO_POP_HPP
#define IVL_DETAILS_CORE_MACRO_POP_HPP

//-----------------------------------------------------------------------------

#ifdef IVL_MACROS_PUSHED

//-----------------------------------------------------------------------------

#ifdef IVL_POP_INLINE
#pragma pop_macro("INLINE")
#undef IVL_POP_INLINE
#endif

#ifdef IVL_POP_CHECK
#pragma pop_macro("CHECK")
#undef IVL_POP_CHECK
#endif

#ifdef IVL_POP_DEBUG
#pragma pop_macro("DEBUG")
#undef IVL_POP_DEBUG
#endif

//-----------------------------------------------------------------------------

#ifdef _MSC_VER

#ifdef IVL_POP_max
#pragma pop_macro("max")
#undef IVL_POP_max
#endif

#ifdef IVL_POP_min
#pragma pop_macro("min")
#undef IVL_POP_min
#endif

#endif  // _MSC_VER

//-----------------------------------------------------------------------------

#pragma pack(pop)

#undef IVL_MACROS_PUSHED
#endif  // IVL_MACROS_PUSHED

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_MACRO_POP_HPP
