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

#ifndef IVL_ARRAY_HEAP_HPP
#define IVL_ARRAY_HEAP_HPP

#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace arrays {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename T>
class array <T, tag::heap>
{

//-----------------------------------------------------------------------------
// data

	T* ptr;
	size_t len;

//-----------------------------------------------------------------------------

	// actual length to be allocated (larger than needed to fit data)
	INLINE size_t capacity(size_t l) { return l ? math::next_pow2(l) : 0; }

	// allocate a given number of elements
	INLINE void allocate(size_t c) { ptr = new_<T>(c); }

	// deallocate (len != 0 iff allocated)
	INLINE void deallocate() { if (len) delete_(ptr); }

	// deallocate, then allocate
	INLINE void reallocate(size_t c) { deallocate(); allocate(c); }

//-----------------------------------------------------------------------------
// determine if size changes such that reallocation is needed...

	// ... given a new array length...
	INLINE bool changes(size_t l) { return cap_changes(capacity(l)); }

	// ... its capacity()...
	INLINE bool cap_changes(size_t c) { return c != capacity(len); }

	// ... or a new length for an inc/dec operation...
	INLINE bool step_changes(size_t l) { return math::is_pow_of2(l); }

//-----------------------------------------------------------------------------
// choose allocation mode: constructor or init

	template <bool N>
	INLINE void alloc() { N ? alloc_cons() : alloc_init(); }

	template <bool N, typename L>
	INLINE void alloc(L l) { N ? alloc_cons(l) : alloc_init(l); }

//-----------------------------------------------------------------------------
// constructor-allocate (no deallocating)

	INLINE void alloc_cons()         { ptr = 0; len = 0; }
	INLINE void alloc_cons(size_t l) { allocate(capacity(len = l)); }

//-----------------------------------------------------------------------------
// init-allocate (deallocate if needed)

	INLINE void alloc_init() { deallocate(); alloc_cons(); }

	INLINE void alloc_init(size_t l)
	{
		size_t c = capacity(l);
		if (cap_changes(c)) reallocate(c);
		len = l;
	}

//-----------------------------------------------------------------------------

	// reallocate, preserving data as long as they fit into new size
	// return true iff reallocation was actually made
	INLINE bool realloc(size_t l)
	{
		bool c = changes(l);
		if (c) copy(l);
		return len = l, c;
	}

	// copy data to new buffer of given length; discard old buffer
	INLINE void copy(size_t l) { swap(array(l, *this)); }

//-----------------------------------------------------------------------------
// expand: reallocate, then construct elements beyond old size

	template <typename L>
	INLINE void expand(L l) { size_t ol = len; realloc(l); cons_at(ol); }

	template <typename L, typename A>
	INLINE void expand(L l, A&& a)
	{
		size_t ol = len; realloc(l); cons_at(ol, fwd <A>(a));
	}

//-----------------------------------------------------------------------------
// contract: reallocate, or destruct elements not fitting new size

	template <typename L>
	INLINE void contract(L l) { if (!realloc(l)) destr_at(l); }

//-----------------------------------------------------------------------------
// resize to new length, preserving data as much as possible

	template <typename L>
	INLINE void grow(L l) { l > len ? expand(l) : contract(l); }

	template <typename L, typename A>
	INLINE void grow(L l, A&& a)
	{
		l > len ? expand(l, fwd <A>(a)) : contract(l);
	}

//-----------------------------------------------------------------------------
// increment / decrement length by one

	INLINE void inc() { if (step_changes(len + 1)) copy(len + 1); else ++len; }
	INLINE void dec() { if (step_changes(len))     copy(len - 1); else --len; }

//-----------------------------------------------------------------------------

	// iterate over all elements
	template <typename F>
	INLINE void it(F f) { loop(f, *this); }

	// iterate over elements starting at position p
	template <typename F>
	INLINE void it(F f, size_t p)
	{
		if (p < len)
			loop.iter(f, at(p), end());
	}

	// jointly iterate over all elements and another array
	template <typename F, typename T1, typename S1>
	INLINE void it(F f, const array <T1, S1>& a)
	{
		a.length() < len ?
			loop.iter(f, begin(), at(a.length()), a.begin()) :
			loop(f, *this, a);
	}

	// jointly iterate over elements starting at position p and another array
	template <typename F, typename T1, typename S1>
	INLINE void it(F f, size_t p, const array <T1, S1>& a)
	{
		if (p < len) p + a.length() < len ?
			loop.iter(f, at(p), at(p + a.length()), a.begin()) :
			loop.iter(f, at(p), end(),              a.begin());
	}

//-----------------------------------------------------------------------------
// construct / destruct all elements

	INLINE void destr_all()  { it(destruct); }

	INLINE void cons_all() { it(constructor()); }

	template <typename A>
	INLINE void cons_all(A&& a) { it(constructor(fwd <A>(a))); }

	// TODO: move
	template <typename T1, typename S1>
	INLINE void cons_all(array <T1, S1>&& a) { it(construct, a); }

	template <typename T1, typename S1>
	INLINE void cons_all(array <T1, S1>& a) { it(construct, a); }

	template <typename T1, typename S1>
	INLINE void cons_all(const array <T1, S1>& a) { it(construct, a); }

//-----------------------------------------------------------------------------
// construct / destruct elements starting at given position

	template <typename P>
	INLINE void destr_at(P p)  { it(destruct, p); }

	template <typename P>
	INLINE void cons_at(P p) { it(constructor(), p); }

	template <typename P, typename A>
	INLINE void cons_at(P p, A&& a) { it(constructor(fwd <A>(a)), p); }

	// TODO: move or copy?
	template <typename P, typename T1, typename S1>
	INLINE void cons_at(P p, array <T1, S1>&& a) { it(construct, a, p); }

	template <typename P, typename T1, typename S1>
	INLINE void cons_at(P p, array <T1, S1>& a) { it(construct, a, p); }

	template <typename P, typename T1, typename S1>
	INLINE void cons_at(P p, const array <T1, S1>& a) { it(construct, a, p); }

//-----------------------------------------------------------------------------

	template <bool N>
	INLINE void cons() { if (!N) destr_all(); alloc <N>(); }

	template <bool N, typename L>
	INLINE void cons(L l) { if (!N) destr_all(); alloc <N>(l); cons_all(); }

	template <bool N, typename L, typename A>
	INLINE void cons(L l, A&& a)
	{
		if (!N) destr_all(); alloc <N>(l); cons_all(fwd <A>(a));
	}

	// TODO: move
	template <bool N, typename T1, typename S1>
	INLINE void cons(array <T1, S1>&& a) { cons <N>(a.length(), a); }

	template <bool N, typename T1, typename S1>
	INLINE void cons(array <T1, S1>& a) { cons <N>(a.length(), a); }

	template <bool N, typename T1, typename S1>
	INLINE void cons(const array <T1, S1>& a) { cons <N>(a.length(), a); }

//-----------------------------------------------------------------------------

	INLINE void bound(size_t k) { CHECK(k < len, e_bound); }

	INLINE void non_empty() { CHECK(len, e_access); }

public:

//-----------------------------------------------------------------------------

	using iterator = T*;
	using const_iterator = const T*;

//-----------------------------------------------------------------------------

	INLINE ~array() { destr_all(); deallocate(); }

//-----------------------------------------------------------------------------
// constructors

	INLINE array() { cons <true>(); }

	template <typename L, only_if <!is_seq <L>()> = 0>
	INLINE explicit array(L l) { cons <true>(fwd <L>(l)); }

	template <typename A, only_if <(is_seq <A>())> = 0>
	INLINE array(A&& a) { cons <true>(fwd <A>(a)); }

	template <typename L, typename A>
	INLINE array(L l, A&& a) { cons <true>(l, fwd <A>(a)); }

//-----------------------------------------------------------------------------
// initializers, following exactly the signatures of all constructors
// except for the explicit separation of overloads (2,3) which are treated
// uniformly here

	INLINE void init() { cons <false>(); }

	template <typename A>
	INLINE void init(A&& a) { cons <false>(fwd <A>(a)); }

	template <typename L, typename A>
	INLINE void init(L l, A&& a) { cons <false>(l, fwd <A>(a)); }

//-----------------------------------------------------------------------------
// assignment

	template <typename T1, typename S1>
	INLINE array& operator=(const array <T1, S1>& a) { init(a); return *this; }

//-----------------------------------------------------------------------------
// resize to new length, preserving data as much as possible

	template <typename L>
	INLINE void resize(L l) { grow(l); }

	template <typename L, typename A>
	INLINE void resize(L l, A&& a) { grow(l, fwd <A>(a)); }

//-----------------------------------------------------------------------------
// push / pop one element at end position, incrementing / decrementing
// length by one

	// TODO: construct(back(), _);
	INLINE T& push_back() { return inc(), constructor()(back()), back(); }

	template <typename A>
	INLINE T& push_back(A&& a)
	{
		return inc(), construct(back(), fwd <A>(a)), back();
	}

	INLINE void pop_back() { destruct(back()), dec(); }

//-----------------------------------------------------------------------------

	// swap all members with another array
	template <typename A>
	INLINE void swap(A&& a)
	{
		std::swap(ptr, a.ptr);
		std::swap(len, a.len);
	}

//-----------------------------------------------------------------------------

	INLINE bool   empty()    const { return !len; }
	INLINE size_t size()     const { return len; }
	INLINE size_t length()   const { return len; }
	INLINE size_t capacity() const { return capacity(len); }
	INLINE T*     data()     const { return ptr; }

//-----------------------------------------------------------------------------

	INLINE T&       operator[](size_t k)       { return *at(k); }
	INLINE const T& operator[](size_t k) const { return *at(k); }

	INLINE iterator       at(size_t k)       { return bound(k), ptr + k; }
	INLINE const_iterator at(size_t k) const { return bound(k), ptr + k; }

//-----------------------------------------------------------------------------

	INLINE T&       front()       { return non_empty(), *begin(); }
	INLINE const T& front() const { return non_empty(), *begin(); }

	INLINE T&       back()       { return non_empty(), *(end() - 1); }
	INLINE const T& back() const { return non_empty(), *(end() - 1); }

//-----------------------------------------------------------------------------

	INLINE iterator       begin()       { return ptr; }
	INLINE const_iterator begin() const { return ptr; }

	INLINE iterator       end()       { return ptr + len; }
	INLINE const_iterator end() const { return ptr + len; }

};

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace arrays

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_ARRAY_HEAP_HPP
