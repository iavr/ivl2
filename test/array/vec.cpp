#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
using ivl::apply;

//-----------------------------------------------------------------------------

struct
{
	template <typename X>
	X operator()(const X& x) { return x + 1; }
}
inc;

struct
{
	template <
		typename X, typename Y, typename Z,
		typename A = array <common <X, Y, Z>, 3>
	>
	A operator()(X&& x, Y&& y, Z&& z)
		{ return A(fwd <Y>(y), fwd <Z>(z), fwd <X>(x)); }
}
shift;

afun::op::add add;

afun::vec <afun::op::add> Add;

struct P
{
	template <typename T>
	void operator()(const T& x) { cout << x << " "; }
};

afun::vec <P> print;

template <typename T>
T dist(int a, const T& x, const T& y) { return a * abs(x - y); }

void fprint(int x) { cout << x << " "; }

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "apply unary" << endl;
		using A = array <int, 3>;
		A a = {-1, 3.14, 2};
		cout << apply(inc, a) << endl;
		cout << endl;

		cout << "apply binary (zip)" << endl;
		cout << apply(add, a, A{1, 2, 3}) << endl;
		cout << endl;
	}

// 	{
// 		cout << "inner" << endl;
// 		auto t = _('a', 3.14, 2);
// 		cout << inner(t, 'X', _(1, 2, 3, 4)) << endl;
// 		cout << endl;
// 	}

	{
		cout << "apply ternary (inner)" << endl;
		using A = array <int, 3>;
		A a = {-1, 3.14, 2};
		cout << apply(shift, a, 18, A{1, 2, 3}) << endl;
		cout << endl;
	}

	{
		cout << "apply operator functor (inner)" << endl;
		using A = array <int, 4>;
		A a = {-1, 3.14, 2, 12};
		cout << a << endl;
		cout << apply(add, a, A{1, 2, 3, 4}) << endl;
		cout << apply(add, a, 2) << endl;
		cout << apply(add, 2, a) << endl;
		cout << apply(add, 2, A{1, 2, 3, 4}) << endl;
		cout << endl;
	}

	{
		cout << "vec operator functor" << endl;
		using A = array <int, 4>;
		A a = {-1, 3.14, 2, 12};
		cout << a << endl;
		cout << Add(a, A{1, 2, 3, 4}) << endl;
		cout << Add(a, 2) << endl;
		cout << Add(2, a) << endl;
		cout << Add(2, A{1, 2, 3, 4}) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		using A = array <int, 4>;
		A a = {-1, 3.14, 2, 12};
		cout << a << endl;
		cout << a + A{1, 2, 3, 4} << endl;
		cout << a + 2 << endl;
		cout << 2 + a << endl;
		cout << 2 + A{1, 2, 3, 4} << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		using A = array <int, 4>;
		using B = array <int, 6>;
		using C = array <A, 2>;
		A a = A{5, 6, 7, 8};
		cout << 1 + 2 << endl;
		cout << a + 2 << endl;
		cout << 2 + a << endl;
		cout << a + A{1, 2, 3, 4} << endl;
		cout << a + B{1, 2, 3, 4, 5, 6} << endl;
		cout << 2 + C{A{1, 2, 3, 4}, A{5, 6, 7, 8}} << endl;
		cout << endl;
	}

	{
		cout << "void vec function" << endl;
		using A = array <int, 4>;
		using B = array <int, 8>;
		using C = array <A, 2>;
		print(C{A{1, 2, 3, 4}, A{5, 6, 7, 8}});
		cout << endl;
		print(B{1, 2, 3, 4, 5, 6, 7, 8});
		cout << endl;
	}

// 	{
// 		cout << "vec functor instance" << endl;
// 		auto t = _('a', 3.14, 2);
// 		cout << _[shift](t, 'X', _(1, 2, 3, 4)) << endl;
// 		cout << _[shift](_('a', 3.14, 2), 'X', _(1, 2, 3, 4)) << endl;
// 		cout << shift(_('a', 3.14, 2), 'X', _(1, 2, 3, 4)) << endl;
// 		cout << endl;
// 	}
//
// 	{
// 		cout << "vec function instance" << endl;
// 		cout << _[dist <double>](_(1, 2, 4, 8), 6, _(5, 6, 7, 8)) << endl;
// 		cout << _[([](int a, double x, double y) { return a * abs(x - y); })]
// 			(_(1, 2, 4, 8), 6, _(5, 6, 7, 8)) << endl;
// 		_[fprint](_(1, 2, 3, 4));
// 		cout << endl;
// 		cout << endl;
// 	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
