#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace tuple_test {

using namespace ivl;
using namespace ivl::types;
using ivl::flip;
using ivl::join;
using ivl::apply;
using ivl::bind;
using ivl::call;

//-----------------------------------------------------------------------------

struct A { };

struct B
{
	char c;
	operator char() const { return c; }
	B& operator++() { ++++c; return *this; }
};

void swap(B& a, B& b) { std::swap(++a, ++b); }

template <typename E1, typename E2>
tuple <E1, E2>
mk_tup(E1&& e1, E2&& e2)
{
	return _(e1, e2);
}

tuple <int, string>
gen_tup()
{
	return _(5, "hello");
}

struct
{
	template <typename X>
	X operator()(const X& x) { return x + 1; }
}
inc;

struct int_ref
{
	int& i;
	int_ref(int& i) : i(i) { }
};

//-----------------------------------------------------------------------------

void run()
{
	{
		cout << "streaming:" << endl;
// 		array <int> a(2);  // TODO: ARRAY
// 		const array <double> b(4, -8);  // TODO: ARRAY
		int l[] = { 1, 2, 3 };
		int* p = 0;

// 		cout << _(7, "hello", 56.3, a, 'c', b, p) << endl;
// 		cout << _(7, "hello", 56.3, a, 'c', _(3.14, "world!"), b, p) << endl;
		cout << _(7, "hello", 56.3, 'c', p) << endl;
		cout << _(7, "hello", 56.3, 'c', _(3.14, "world!"), p) << endl;
		cout << endl;
	}

	{
		cout << "random access:" << endl;
		int i = 4;
		double x = 3.14;
		tuple <double&, int> t = _(x, i);
		t.at <0>() = 0.2;
		t.at <1>() = 8;
		cout << x << " " << i << endl;
		cout << endl;
	}

	{
		cout << "tuple return:" << endl;
		int i = 4;
		double x = 3.14;
		tuple <double&, int> u = mk_tup(x, i);
		cout << u.at <0>() << " " << u.at <1>() << endl;
		cout << gen_tup() << endl;
		cout << endl;
	}

	{
		cout << "empty tuple:" << endl;
		tuple <> e;
		const tuple <> ec;
		tuple <> e2 = e;
		tuple <> e3 = ec;
		tuple <> e4 = _();
		cout << endl;
	}

	{
		cout << "const tuple to non-const ref:" << endl;
		int i = 4;
		double x = 3.14;
		tuple <double&, int> t = _(x, i);
		const tuple <double&, int>& u = t;
		(tuple <double&, int>(_(x, i))).at <0>() = 2.18;
		cout << x << endl;
		t.at <0>() = 1.18;
		cout << x << endl;
		u.at <0>() = 0.18;
		cout << x << endl;
		cout << endl;
	}

	{
		cout << "auto tuple type:" << endl;
		double a = 2;
// 		array <int> a(2);  // TODO: ARRAY
// // 		const array <double> b(4, -8);
		int l[] = {1, 2, 3};
		int* p = 0;
		int x = 0;

// TODO: array bug
// // 		auto t = _(7, "hello", 56.3, a, 'c', l, b, p);
// 		auto t = _(7, "hello", 56.3, a, 'c', l, p);  // TODO: ARRAY
		auto t = _(7, "hello", 56.3, a, 'c', l, p);
		cout << t.at <1>() << endl;
		cout << endl;

		auto w = _(_(x));
		w.val() = _(8);
		cout << x << endl;
		w.val().val() = 3;
		cout << x << endl;
		cout << endl;
	}

	{
		cout << "assignment:" << endl;
		int i = 4;
		double x = 3.14;
		_(x, i) = _(-2.27, 8);
		cout << x << " " << i << endl;
		_(x, i) = 4;
		cout << _(x, i) << endl;
		cout << endl;
	}

	{
		cout << "tuple swap:" << endl;
		int i = 4, j = 8;
		double x = 3.14, y = 2.17;
		B c{'c'}, d{'d'};
		cout << _(i, _(x, c)) << " " << _(j, _(y, d)) << endl;
		swap(_(i, _(x, c)), _(j, _(y, d)));
		cout << _(i, _(x, c)) << " " << _(j, _(y, d)) << endl;
		cout << endl;
	}

	{
		cout << "tuple element of empty type:" << endl;
		int i;
		A a, b;
		tuple <A, int> t = _(a, 4);
		const tuple <A, int> u = _(a, 8);
		_(b, i) = t;
		cout << i << endl;
		_(b, i) = u;
		cout << i << endl;
		cout << endl;
	}

	{
		cout << "flip" << endl;
		tuple <int, double> x = flip(_(3.14, 5));
		cout << x << endl;
		cout << _(5, -9, "hello", 'c', 19) << endl;
		cout << flip(_(5, -9, "hello", 'c', 19)) << endl;
		cout << endl;
	}

	{
		cout << "indirect tuple:" << endl;
		double a = 2;
// 		array <int> a(2);  // TODO: ARRAY
// // 		const array <double> b(4, -8);
		int l[] = { 1, 2, 3 };
		int* p = 0;

// TODO: array bug
// // 		auto t = _(7, "hello", 56.3, a, 'c', l, b, p);
// 		auto t = _(7, "hello", 56.3, a, 'c', p);  // TODO: ARRAY
		auto t = _(7, "hello", 56.3, a, 'c', p);
		cout << t << endl;
		cout << t.at <sizes <0, 3, 3, 2, 0, 4, 0, 5> >() << endl;
		cout << t.at <0, 3, 3, 2, 0, 4, 0, 5>() << endl;
		t.at <sz_range <0, 4, 2> >() = _(-7, 3.14, 'd');
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "zip" << endl;
		auto n = _('a', 'b', 'c', 'd');
		auto v = _(3.14, 2.71, -3e19, 0);
		cout << zip(n, v) << endl;
		int i, j;
		double f, g;
		zip(_(i, f), _(j, g)) = _(_(3, 4), _(2.71, 3.14));
		cout << _(i, j) << " " << _(f, g) << endl;
		cout << endl;
	}

	{
		cout << "join" << endl;
		auto a = _('a', 'b', 'c', 'd');
		auto b = _(3.14, 2.71, -3e19, 0);
		cout << join(a, b, _(), _(0, 1)) << endl;
		cout << endl;
	}

	{
		cout << "atom" << endl;
		cout << _[3].val() << endl;
		cout << _[3] << endl;
		cout << tup_len <decltype(_[3])>() << endl;
		cout << endl;
	}

	{
		cout << "tup" << endl;
		auto a = _('a', 'b', 'c', 'd');
		auto b = _(3.14, 2.71, -3e19, 0);
		cout << tup("hello", "world", -19) << endl;
		cout << tup(a, b, _(), _(0, 1)) << endl;
		cout << tup(a, "hello", b, "world", _(), -19, _(0, 1)) << endl;
		cout << tup(a, "hello", _[b], "world", _(), -19, _[_(0, 1)]) << endl;
		cout << _(a, "hello", b, "world", _(), -19, _(0, 1)) << endl;
		cout << _(a, "hello", _[b], "world", _(), -19, _[_(0, 1)]) << endl;
		cout << endl;
	}
}
//-----------------------------------------------------------------------------

}  // namespace tuple_test

//-----------------------------------------------------------------------------

int main()
{
	tuple_test::run();
}
