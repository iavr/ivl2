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

#ifndef IVL_CORE_TOOLS_FOO_HPP
#define IVL_CORE_TOOLS_FOO_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace tools {

//-----------------------------------------------------------------------------

template <typename T = int>
class foo_
{
	using F = foo_;
	using R = types::raw_type <T>;
	R val;

	template <typename U>
	friend class foo_;

public:
	foo_() : val{} { cout << "foo()" << endl; }

	foo_(R&& v) : val{mv(v)} { cout << "foo(&&" << val << ")" << endl; }

	foo_(const R& v) : val{v} { cout << "foo(&" << val << ")" << endl; }

	foo_(F&& f) : val{mv(f).val}
		{ cout << "&&foo(" << val << ")" << endl; }

	foo_(const F& f) : val{f.val}
		{ cout << "&foo(" << val << ")" << endl; }

	template <typename U>
	explicit foo_(foo_<U>&& f) : val(mv(f).val)
		{ cout << "&&foo<>(" << val << ")" << endl; }

	template <typename U>
	explicit foo_(const foo_<U>& f) : val(f.val)
		{ cout << "&foo<>(" << val << ")" << endl; }

//-----------------------------------------------------------------------------

	~foo_() { cout << "~foo(" << val << ")" << endl; }

//-----------------------------------------------------------------------------

	F& operator=(F&& f)
	{
		cout << "=&&foo(" << f.val << ")" << endl;
		val = mv(f.val);
		return *this;
	}

	F& operator=(const F& f)
	{
		cout << "=&foo(" << f.val << ")" << endl;
		val = f.val;
		return *this;
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

//-----------------------------------------------------------------------------

	template <typename S, only_if <types::is_stream <S>{}> = 0>
	friend S& operator<<(S& s, const F& f)
	{
		return s << "<<foo(" << f.val << ")";
	}

};

using foo = foo_<>;

//-----------------------------------------------------------------------------

}  // namespace tools

using tools::foo_;
using tools::foo;

//-----------------------------------------------------------------------------

namespace types {
namespace traits {

//-----------------------------------------------------------------------------

namespace details {

// extending definition @type/traits/relation
template <typename A, typename B>
struct common_rec <tools::foo_<A>, tools::foo_<B> > :
	id_t <tools::foo_<common2 <A, B> > > { };

}  // namespace details

//-----------------------------------------------------------------------------

namespace details {

template <typename T, bool = is_tuple <T>() || is_seq <T>()>
struct foo_of_ : id_t <T> { };

template <typename T>
struct foo_of_<T, false> : id_t <tools::foo_<T> > { };

}  // namespace details

template <typename T> using foo_of_t = details::foo_of_<T>;
template <typename T> using foo_of = type_of <foo_of_t <T> >;

//-----------------------------------------------------------------------------

}  // namespace traits
}  // namespace types

//-----------------------------------------------------------------------------

namespace tuples {

template <typename... A>
using foo_tuple = pre_tuple <types::foo_of <A>...>;

}  // namespace tuples

//-----------------------------------------------------------------------------

namespace arrays {

template <typename... A>
using foo_seq = types::make_seq <types::foo_of <A>...>;

}  // namespace arrays

//-----------------------------------------------------------------------------

namespace afun {

using foos = afun::copy_of <tuples::foo_tuple>;
using foo_seq = afun::copy_of <arrays::foo_seq>;

}  // namespace afun

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) afun::foos    foos;
static __attribute__ ((unused)) afun::foo_seq foo_seq;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_TOOLS_FOO_HPP
