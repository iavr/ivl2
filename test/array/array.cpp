#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;
using ivl::seq;

//-----------------------------------------------------------------------------

struct B
{
	char c;
	operator char() const { return c; }
	B& operator++() { return ++++c, *this; }
};

void swap(B& a, B& b) { std::swap(++a, ++b); }

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "aggr array" << endl;
		aggr_array <int, 0> x = {};
		aggr_array <int, 5> y = {5, 9, 7, -2, 0};
		cout << "x = " << aggr_array <int, 5>{{5, 9, 7, -2, 0}} << endl;
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << endl;
	}

	{
		cout << "element assignment" << endl;
		constexpr size_t N = 11;
		array <int, N> x;
		for (size_t n = 0; n < N; n++)
			x[n] = 2 * n;
		cout << "x = " << x << endl;
		cout << endl;
	}

	{
		cout << "element construction" << endl;
		foo f4(4), f5(5), f6(6);
		cout << endl << "begin" << endl;
		array <foo, 3> x = {f4, f5, f6};
		cout << "end" << endl << endl;
		cout << "x = " << x << endl;
		cout << endl;
	}

	cout << endl;

	{
		cout << "array by other array" << endl;
		array <double, 4>  d = {5.28, 8.79, -0.84, -4.18};
		array <int, 4> i = d;
		cout << "d = " << d << endl;
		cout << "i = " << i << endl;
		cout << endl;
	}

	{
		cout << "array by seq" << endl;
		int k = 8;
		const int n = 14;
		double x = 4.5;
		const double y = 3.14;
		cout << seq(5, 9, 7, -2, 0) << endl;
		cout << seq(5.28, 8.79, -0.84, -4.18) << endl;
		cout << seq(k, n, x, y, 5, 0) << endl;
		cout << endl;
	}

	{
		cout << "empty array:" << endl;
		using E = array <int, 0>;
		E e;
		const E ec;
		E e2 = e;
		E e3 = ec;
		E e4 = seq();
		cout << endl;
	}

	{
		cout << "array of ref/tuple" << endl;
		int j = 8, k = 0;
		double x = 4.5, z = 0;
		auto a = seq(j, k);
		cout << ++a;
		cout << ": (j, k) = " << _(j, k) << endl;
		auto b = seq(_(k, x), _(j, z));
		b[0] = _(5, -2.3);
		cout << b << ": (k, x) = " << _(k, x) << endl;
		cout << endl;
	}

	{
		cout << "assignment" << endl;
		auto a = seq(5, 9, 7, -2, 0);
		auto b = seq(3.14, 3, -2, 4., 8);
		cout << a << endl << b << endl;
		a = 2 * flip(b);
		cout << a << endl;
		cout << (a = 2) << endl;
		cout << endl;
	}

	{
		cout << "array swap:" << endl;
		double x = 3.14, y = 2.17;
		B c{'c'}, d{'d'};
		cout << seq(_(x, c)) << " " << seq(_(y, d)) << endl;
		swap(seq(_(x, c)), seq(_(y, d)));
		cout << seq(_(x, c)) << " " << seq(_(y, d)) << endl;
		cout << endl;
	}

	{
		cout << "head/tail" << endl;
		auto a = seq(5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0);
		cout << a << endl;
		cout << head(a) << endl;
		cout << tail(a) << endl;
		cout << tail(tail(a)) << endl;
		cout << endl;
	}

	{
		cout << "flip" << endl;
		auto a = seq(5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0);
		cout << "    " << a << endl;
		cout << "  F " << flip(a) << endl;
		cout << "  F " << flip(mv(a)) << endl;
		cout << " FF " << flip(flip(a)) << endl;
		cout << " TF " << tail(flip(a)) << endl;
		cout << " FT " << flip(tail(a)) << endl;
		cout << "TTF " << tail(tail(flip(a))) << endl;
		cout << "TFT " << tail(flip(tail(a))) << endl;
		cout << "FTT " << flip(tail(tail(a))) << endl;
		cout << endl;
	}

	{
		cout << "indirect" << endl;
		auto x = seq(5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0);
		auto i = seq(5, 8, 0, 8);
		cout << "x = " << x << endl;
		cout << "i = " << i << endl;
		cout << "x[i] = " << x[i] << endl;
		auto j = seq(i, seq._<int>(7, 2, 10., 5));
		cout << "j = " << j << endl;
		cout << "x[j] = " << x[j] << endl;
		cout << endl;
	}

	{
		cout << "zip/inner" << endl;
		auto c = seq('a', 'b', 'c', 'd');
		auto i = seq(3, 2, -4, 0);
		cout << zip(c, i) << endl;
		zip(c, i)[1] = _('e', 18);
		cout << c << endl << i << endl;
		cout << inner(c, -24) << endl;
		cout << endl;
	}

	{
		cout << "join" << endl;
		auto E = seq();
		auto a = seq(0, 1, 2, 3);
		auto b = seq(-3.14, 12.71, -8e3);
		auto c = seq._<int>(-3.14, 12.71, -8e3);
		cout << join(a, b, E, seq(0, 1)) << endl;
		cout << join(E, a, b, E, seq(0, 1), E) << endl;
		cout << join(a, b) << endl;
		*join(a, c).begin() = 20;
		cout << a << endl;
		cout << flip(join(a, c, E, seq(0, 1))) << endl;
		cout << endl;
	}

	{
		cout << "arr" << endl;
		auto E = seq();
		auto a = seq(0, 1, 2, 3);
		auto b = seq(-3.14, 12.71, -8e3);
		cout << arr(5, a, 14, 0, 0, b, E, seq(0, 1)) << endl;
		auto j = arr(5, a, 14, 0, 0, b, E, seq(0, 1));
		cout << j << endl;
		cout << endl;
	}

	{
		cout << "apply" << endl;
		auto x = seq(5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0);
		auto y = seq(7, -8, 0, 13, 128, 0, -2, 7, 6, 14, -9);
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "x + y = " << apply(op::add, x, y) << endl;
		cout << "x + 3 = " << apply(op::add, x, 3) << endl;
		cout << endl;
	}

	{
		cout << "loop" << endl;
		auto x = seq(14, 7, 3, -8, 9, 0);
		cout << "x = " << x << endl;
		cout << "x = ", loop(op::left, cout, mv(x)), cout << endl;
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
