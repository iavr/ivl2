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

#ifndef IVL_DETAILS_CORE_PLATFORM_MSC_HPP
#define IVL_DETAILS_CORE_PLATFORM_MSC_HPP

//-----------------------------------------------------------------------------

#ifdef _MSC_VER

//-----------------------------------------------------------------------------

#define __attribute__(X)

//-----------------------------------------------------------------------------

#pragma warning(disable: 4099)
#pragma warning(disable: 4221)
#pragma warning(disable: 4006)
#pragma warning(disable: 4288)
#pragma warning(disable: 4522)

// for specific exceptions, if they are to be used on function declarations
#pragma warning(disable : 4290)

// conversion ptrdiff_t -> int
#pragma warning(disable: 4244)

// conversion size_t -> unsigned int
#pragma warning(disable: 4267)

// decorated name length exceeded; name truncated
#pragma warning(disable: 4503)

//-----------------------------------------------------------------------------

#endif  // _MSC_VER

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_PLATFORM_MSC_HPP
