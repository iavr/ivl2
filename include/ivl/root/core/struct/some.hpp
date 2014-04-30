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

#ifndef IVL_CORE_STRUCT_SOME_HPP
#define IVL_CORE_STRUCT_SOME_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace structs {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

INLINE constexpr size_t
stack_size() { return 2 * sizeof(void*); }

//-----------------------------------------------------------------------------

template <size_t N = stack_size()>
class some_store
{
	char space[N];

	template <typename T>
	static constexpr bool fits() { return sizeof(raw_type <T>) <= N; }

public:
	template <typename D, typename V>
	D* copy(V&& v)
	{
		return fits <D>() ? new(space) D{fwd <V>(v)} :
		                    new        D{fwd <V>(v)};
	}

	template <typename D, typename V, typename B>
	B* move(V&& v, B*& p)
	{
		B* q = fits <D>() ? copy<D>(fwd <V>(v)) : p;
		p = nullptr;
		return q;
	}

	template <typename D>
	void free(D* p) { fits <D>() ? p->~D() : delete p; }
};

//-----------------------------------------------------------------------------

template <typename A = some_store<> >
class some_base : A
{
	struct base
	{
		virtual ~base() { }
		virtual bool is(type_id_t) const = 0;
		virtual base *copy(A&) const = 0;
		virtual base *move(A&, base*&) = 0;
		virtual void free(A&) = 0;
	} *p = nullptr;

//-----------------------------------------------------------------------------

	template <typename T>
	struct data : base, private raw_tuple <T>
	{
		using raw_tuple <T>::raw_tuple;
		using raw_tuple <T>::val;

		bool is(type_id_t id) const override { return id == type_id <T>(); }

		base* copy(A& a) const override
		{
			return a.template copy <data>(val());
		}

		base* move(A& a, base*& p) override
		{
			return a.template move<data>(mv(val()), p);
		}

		void free(A& a) override { a.free(this); }
	};

//-----------------------------------------------------------------------------

	template<typename T, typename V>
	V&& check(V&& v) const
	{
		if (!is <T>()) throw std::bad_cast();
		return fwd <V>(v);
	}

	template<typename T>
	T& stat() { return static_cast <data <T>&>(*p).val(); }

	template<typename T>
	const T& stat() const { return static_cast <const data <T>&>(*p).val(); }

	template<typename T> T&       dyn()       { return check <T>(stat <T>()); }
	template<typename T> const T& dyn() const { return check <T>(stat <T>()); }

//-----------------------------------------------------------------------------

	template<typename T>
	using none = _not <eq <some_base, decay <T> >{}>;

//-----------------------------------------------------------------------------

	base* move(some_base& s)       { return s.p->move(*this, s.p); }
	base* copy(const some_base& s) { return s.p->copy(*this); }

	base* read(some_base&& s)      { return s.p ? move(s) : s.p; }
	base* read(const some_base& s) { return s.p ? copy(s) : s.p; }

	template <typename V, typename U = decay <V>, only_if <none <V>{}> = 0>
	base* read(V&& v) { return A::template copy <data <U> >(fwd <V>(v)); }

//-----------------------------------------------------------------------------

	template<typename X>
	some_base& assign(X&& x)
	{
		if (!p) p = read(fwd <X>(x));
		else
		{
			some_base t{mv(*this)};
			try        { p = read(fwd <X>(x)); }
			catch(...) { p = move(t); throw; }
		}
		return *this;
	}

	void swap(some_base& s)
	{
		     if   (!p)   p = read(mv(s));
		else if (!s.p) s.p = move(*this);
		else
		{
			some_base t{mv(*this)};
			try        { p = move(s); }
			catch(...) { p = move(t); throw; }
			s.p = move(t);
		}
	}

//-----------------------------------------------------------------------------

public:
	 some_base() { }
	~some_base() { if (p) p->free(*this); }

	some_base(some_base&& s)      : p{read(mv(s))} { }
	some_base(const some_base& s) : p{read(s)} { }

	template<typename V, only_if <none <V>{}> = 0>
	some_base(V&& v) : p{read(fwd <V>(v))} { }

	some_base& operator=(some_base&& s)      { return assign(mv(s)); }
	some_base& operator=(const some_base& s) { return assign(s); }

	template<typename V, only_if <none <V>{}> = 0>
	some_base& operator=(V&& v) { return assign(fwd <V>(v)); }

	friend void swap(some_base& s, some_base& r) { s.swap(r); }

	void clear() { if(p) { p->free(*this); p = nullptr; } }

	bool empty() const { return p; }

	template<typename T>
	bool is() const { return p ? p->is(type_id <T>()) : false; }

	template<typename T> T&&      _() &&     { return mv(stat<T>()); }
	template<typename T> T&       _() &      { return stat<T>(); }
	template<typename T> const T& _() const& { return stat<T>(); }

	template<typename T> T&&      to() &&     { return mv(dyn<T>()); }
	template<typename T> T&       to() &      { return dyn<T>(); }
	template<typename T> const T& to() const& { return dyn<T>(); }
};

//-----------------------------------------------------------------------------

template <size_t N = stack_size()>
using some_ = some_base <some_store <N> >;

using some = some_<>;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace structs

//-----------------------------------------------------------------------------

using structs::details::some_;
using structs::details::some;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_STRUCT_SOME_HPP
