#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
using ivl::apply;
using ivl::seq;

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
		auto a = seq._<int>(-1, 3.14, 2);
		cout << apply(inc, a) << endl;
		cout << endl;

		cout << "apply binary (zip)" << endl;
		cout << apply(add, a, seq(1, 2, 3)) << endl;
		cout << endl;
	}

	{
		cout << "inner" << endl;
		auto a = seq._<int>(-1, 3.14, 2, 12);
		cout << inner(a, -18, seq(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "apply ternary (inner)" << endl;
		auto a = seq._<int>(-1, 3.14, 2);
		cout << apply(shift, a, 18, seq(1, 2, 3)) << endl;
		cout << endl;
	}

	{
		cout << "apply operator functor (inner)" << endl;
		auto a = seq._<int>(-1, 3.14, 2, 12);
		cout << a << endl;
		cout << apply(add, a, seq(1, 2, 3, 4)) << endl;
		cout << apply(add, a, 2) << endl;
		cout << apply(add, 2, a) << endl;
		cout << apply(add, 2, seq(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "vec operator functor" << endl;
		auto a = seq._<int>(-1, 3.14, 2, 12);
		cout << a << endl;
		cout << Add(a, seq(1, 2, 3, 4)) << endl;
		cout << Add(a, 2) << endl;
		cout << Add(2, a) << endl;
		cout << Add(2, seq(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto a = seq._<int>(-1, 3.14, 2, 12);
		cout << a << endl;
		cout << a + seq(1, 2, 3, 4) << endl;
		cout << a + 2 << endl;
		cout << 2 + a << endl;
		cout << 2 + seq(1, 2, 3, 4) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto a = seq(5, 6, 7, 8);
		cout << 1 + 2 << endl;
		cout << a + 2 << endl;
		cout << 2 + a << endl;
		cout << a + seq(1, 2, 3, 4) << endl;
		cout << a + seq(1, 2, 3, 4, 5, 6) << endl;
		cout << 2 + seq(seq(1, 2, 3, 4), seq(5, 6, 7, 8)) << endl;
		cout << endl;
	}

	{
		cout << "void vec function" << endl;
		print(seq(seq(1, 2, 3, 4), seq(5, 6, 7, 8)));
		cout << endl;
		print(seq(1, 2, 3, 4, 5, 6, 7, 8));
		cout << endl;
		cout << endl;
	}

	{
		cout << "vec functor instance" << endl;
		auto a = seq._<int>(-1, 3.14, 2);
		cout << _[shift](a, 18, seq(1, 2, 3)) << endl;
		cout << _[shift](seq._<int>(-1, 3.14, 2), 18, seq(1, 2, 3)) << endl;
		cout << endl;
	}

	{
		cout << "vec function instance" << endl;
		auto v = seq._<double>(5, 6, 7, 8);
		cout << _[dist <double>](seq(1, 2, 4, 8), 6, v) << endl;
		cout << _[([](int a, double x, double y) { return a * abs(x - y); })]
			(seq(1, 2, 4, 8), 6, v) << endl;
		_[fprint](seq(1, 2, 3, 4));
		cout << endl;
		cout << endl;
	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
