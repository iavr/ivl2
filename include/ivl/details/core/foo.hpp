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

#ifndef IVL_DETAILS_CORE_FOO_HPP
#define IVL_DETAILS_CORE_FOO_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

template <typename T = int>
class foo_
{
	using F = foo_;
	using R = types::raw_type <T>;
	R val;

public:
	foo_() : val() { cout << "foo()" << endl; }

	foo_(R&& v) : val(mv(v)) { cout << "foo(&&" << val << ")" << endl; }

	foo_(const R& v) : val(v) { cout << "foo(&" << val << ")" << endl; }

	foo_(F&& f) : val(mv(f.val))
		{ cout << "&&foo(" << val << ")" << endl; }

	foo_(const F& f) : val(f.val)
		{ cout << "&foo(" << val << ")" << endl; }

	~foo_() { cout << "~foo(" << val << ")" << endl; }

	F& operator=(F&& f)
	{
		cout << "=&&foo(" << f.val << ")" << endl;
		return val = mv(f.val), *this;
	}

	F& operator=(const F& f)
	{
		cout << "=&foo(" << f.val << ")" << endl;
		return val = f.val, *this;
	}

//-----------------------------------------------------------------------------

	friend std::ostream& operator<<(std::ostream& os, const F& f)
	{
		return os << "<<foo(" << f.val << ")";
	}

//-----------------------------------------------------------------------------

	F operator+(const F& f) const
	{
		cout << "+foo(" << val << "+" << f.val <<
			"=" << val + f.val << ")" << endl;
		return val + f.val;
	}

	F operator*(const F& f) const
	{
		cout << "*foo(" << val << "*" << f.val << "="
			<< val * f.val << ")" << endl;
		return val * f.val;
	}

	bool operator<(const F& f) const
	{
		cout << "<foo(" << val << "<" << f.val << "="
			<< (val < f.val) << ")" << endl;
		return val < f.val;
	}
};

using foo = foo_<>;

//-----------------------------------------------------------------------------

namespace types {
namespace traits {

namespace details {

template <typename T, bool = is_tuple <T>()>
struct foo_of_ : id_t <foo_<T> > { };

template <typename T>
struct foo_of_<T, true> : id_t <T> { };

}  // namespace details

template <typename T> using foo_of_t = details::foo_of_<T>;
template <typename T> using foo_of = type_of <foo_of_t <T> >;

}  // namespace traits
}  // namespace types

//-----------------------------------------------------------------------------

namespace tuples {

template <typename... A>
using foo_tuple = pre_tuple <types::foo_of <A>...>;

}  // namespace tuples

//-----------------------------------------------------------------------------

namespace afun {

using foos = afun::val_of <tuples::foo_tuple>;

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::foos foos;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DETAILS_CORE_FOO_HPP
