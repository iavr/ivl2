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

#ifndef IVL_DETAILS_CORE_DEBUG_CHECK_HPP
#define IVL_DETAILS_CORE_DEBUG_CHECK_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

#include <cassert>
#include <exception>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

#if defined IVL_ASSERT

#define CHECK(cond, except) \
	assert(cond && IVL_##except##_MSG);

#elif defined IVL_THROW  // IVL_ASSERT

#define CHECK(cond, except) \
	if(!cond) \
		throw(except());

#else  // IVL_THROW

#define CHECK(cond, except) ;

#endif  // IVL_ASSERT

//-----------------------------------------------------------------------------

#if defined IVL_SYS_ASSERT

#define SYS_CHECK(cond, except) \
	assert(cond && IVL_##except##_MSG);

#elif defined IVL_SYS_THROW  // IVL_SYS_ASSERT

#define SYS_CHECK(cond, except) \
	if(!cond) \
		throw(except());

#else  // IVL_SYS_THROW

#define SYS_CHECK(cond, except) ;

#endif  // IVL_ASSERT

//-----------------------------------------------------------------------------

struct exception : std::exception { };

//-----------------------------------------------------------------------------

#define IVL_e_range_MSG    "value out of range"
#define IVL_e_domain_MSG   "value out of domain"
#define IVL_e_comp_MSG     "illegal computation"

#define IVL_e_bound_MSG    "index out of bounds"
#define IVL_e_size_MSG     "size incompatible with operation"
#define IVL_e_dim_MSG      "number of dimensions incompatible with operation"

#define IVL_e_access_MSG   "invalid memory access"
#define IVL_e_alloc_MSG    "memory allocation failure"
#define IVL_e_io_MSG       "i/o error"
#define IVL_e_system_MSG   "system error"

//-----------------------------------------------------------------------------

// value out of representation range
struct e_range : exception
{
	virtual const char* what() const throw() { return IVL_e_range_MSG; }
};

// value out of domain of function
struct e_domain : exception
{
	virtual const char* what() const throw() { return IVL_e_domain_MSG; }
};

// any other error in evaluating an expression
struct e_comp : exception
{
	virtual const char* what() const throw() { return IVL_e_comp_MSG; }
};

//-----------------------------------------------------------------------------

// array index out of bounds
struct e_bound : exception
{
	virtual const char* what() const throw() { return IVL_e_bound_MSG; }
};

// invalid array size or incompatible array sizes
struct e_size : exception
{
	virtual const char* what() const throw() { return IVL_e_size_MSG; }
};

// invalid array no. of dimensions or incompatible array no. of dimensions
struct e_dim : exception
{
	virtual const char* what() const throw() { return IVL_e_dim_MSG; }
};

//-----------------------------------------------------------------------------

// invalid memory access, e.g. to NULL
struct e_access : exception
{
	virtual const char* what() const throw() { return IVL_e_access_MSG; }
};

// memory allocation failure
struct e_alloc : exception
{
	virtual const char* what() const throw() { return IVL_e_alloc_MSG; }
};

// i/o error, e.g. file or network
struct e_io : exception
{
	virtual const char* what() const throw() { return IVL_e_io_MSG; }
};

// any other system call error that does not depend on the CPU
struct e_system : exception
{
	virtual const char* what() const throw() { return IVL_e_system_MSG; }
};

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_DEBUG_CHECK_HPP
