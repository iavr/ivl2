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
	template <typename X, typename Y, typename Z>
	auto operator()(X&& x, Y&& y, Z&& z)
	-> decltype(_(fwd <Y>(y), fwd <Z>(z), fwd <X>(x)))
		{ return _(fwd <Y>(y), fwd <Z>(z), fwd <X>(x)); }
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
		auto t = _('a', 3.14, 2);
		cout << apply(inc, t) << endl;
		cout << endl;

		cout << "apply binary (zip)" << endl;
		cout << apply(add, t, _(1, 2, 3)) << endl;
		cout << endl;
	}

	{
		cout << "inner" << endl;
		auto t = _('a', 3.14, 2);
		cout << inner(t, 'X', _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "apply ternary (inner)" << endl;
		auto t = _('a', 3.14, 2);
		cout << apply(shift, t, 'X', _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "apply operator functor (inner)" << endl;
		auto t = _('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << apply(add, t, _(1, 2, 3, 4)) << endl;
		cout << apply(add, t, 2) << endl;
		cout << apply(add, 2, t) << endl;
		cout << apply(add, 2, _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "vec operator functor" << endl;
		auto t = _('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << Add(t, _(1, 2, 3, 4)) << endl;
		cout << Add(t, 2) << endl;
		cout << Add(2, t) << endl;
		cout << Add(2, _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto t = _('a', 3.14, 2, "hello");
		cout << t << endl;
		cout << t + _(1, 2, 3, 4) << endl;
		cout << t + 2 << endl;
		cout << 2 + t << endl;
		cout << 2 + _(1, 2, 3, 4) << endl;
		cout << endl;
	}

	{
		cout << "binary vec operator" << endl;
		auto t = _(5, 6, 7, 8);
		cout << 1 + 2 << endl;
		cout << t + 2 << endl;
		cout << 2 + t << endl;
		cout << t + _(1, 2, 3, 4) << endl;
		cout << t + _(1, 2, 3, 4, 5, 6) << endl;
		cout << t + _(1, 2, 3, _(4, 5, 6, _(7, 8))) << endl;
		cout << endl;
	}

	{
		cout << "void vec function" << endl;
		print(_(1, 2, 3, _(4, 5, 6, _(7, 8))));
		cout << endl;
		cout << endl;
	}

	{
		cout << "vec functor instance" << endl;
		auto t = _('a', 3.14, 2);
		cout << _[shift](t, 'X', _(1, 2, 3, 4)) << endl;
		cout << _[shift](_('a', 3.14, 2), 'X', _(1, 2, 3, 4)) << endl;
		cout << shift(_('a', 3.14, 2), 'X', _(1, 2, 3, 4)) << endl;
		cout << endl;
	}

	{
		cout << "vec function instance" << endl;
		cout << _[dist <double>](_(1, 2, 4, 8), 6, _(5, 6, 7, 8)) << endl;
		cout << _[([](int a, double x, double y) { return a * abs(x - y); })]
			(_(1, 2, 4, 8), 6, _(5, 6, 7, 8)) << endl;
		_[fprint](_(1, 2, 3, 4));
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
