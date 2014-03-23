#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;
using ivl::seq;

//-----------------------------------------------------------------------------

template <size_t N = 0> using A = array <int, N>;
template <size_t N = 0> using B = array <double, N>;

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

// 	{
// 		cout << "array by seq" << endl;
// 		int k = 8;
// 		const int n = 14;
// 		double x = 4.5;
// 		const double y = 3.14;
// 		auto i = seq(5, 9, 7, -2, 0);
// 		auto d = seq(5.28, 8.79, -0.84, -4.18);
// 		auto a = seq(k, n, x, y, 5, 0);
// 		cout << "i = " << i << endl;
// 		cout << "d = " << d << endl;
// 		cout << "a = " << a << endl;
// 		cout << endl;
// 	}

	{
		cout << "head/tail" << endl;
		using A = array <int, 11>;
		A a{5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0};
		cout << a << endl;
		cout << head(a) << endl;
		cout << tail(a) << endl;
		cout << tail(tail(a)) << endl;
		cout << endl;
	}

	{
		cout << "flip" << endl;
		using A = array <int, 11>;
		A a{5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0};
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
		array <int, 11> x{5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0};
		array <int, 4>  i{5, 8, 0, 8};
		cout << "x = " << x << endl;
		cout << "i = " << i << endl;
		cout << "x[i] = " << x[i] << endl;

		using A = array <int, 4>;
		array <A, 2> j(i, A{7, 2, 10., 5});
		cout << "j = " << j << endl;
		cout << "x[j] = " << x[j] << endl;

		cout << endl;
	}

	{
		cout << "zip/inner" << endl;
		array <char, 4> c = {'a', 'b', 'c', 'd'};
		array <int, 4>  i = {3, 2, -4, 0};
		cout << zip(c, i) << endl;
		zip(c, i)[1] = _('e', 18);
		cout << c << endl << i << endl;
		cout << inner(c, -24) << endl;
		cout << endl;
	}

	{
		cout << "join" << endl;
		A <> E;
		A <4> a = {0, 1, 2, 3};
		B <3> b = {-3.14, 12.71, -8e3};
		A <3> c = {-3.14, 12.71, -8e3};
		cout << join(a, b, E, A <2>{0, 1}) << endl;
		cout << join(E, a, b, E, A <2>{0, 1}, E) << endl;
		cout << join(a, b) << endl;
		*join(a, c).begin() = 20;
		cout << a << endl;
		cout << flip(join(a, c, E, A <2>{0, 1})) << endl;
		cout << endl;
	}

// 	{
// 		cout << "arr" << endl;
// 		A <> E;
// 		A <4> a = {0, 1, 2, 3};
// 		B <3> b = {-3.14, 12.71, -8e3};
// 		cout << arr(5, a, 14, 0, 0, b, E, A <2>{0, 1}) << endl;
// 		auto j = arr(5, a, 14, 0, 0, b, E, A <2>{0, 1});
// 		cout << j << endl;
// 		cout << endl;
// 	}

	{
		cout << "apply" << endl;
		using A = array <int, 11>;
		A x{5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0};
		A y{7, -8, 0, 13, 128, 0, -2, 7, 6, 14, -9};
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "x + y = " << apply(op::add, x, y) << endl;
		cout << "x + 3 = " << apply(op::add, x, 3) << endl;
		cout << endl;
	}

	{
		cout << "loop" << endl;
		array <int, 6> x{14, 7, 3, -8, 9, 0};

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
