#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;

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
		cout << "array by element assignment" << endl;
		constexpr size_t N = 11;
		array <int, N> x;
		for (size_t n = 0; n < N; n++)
			x[n] = 2 * n;
		cout << "x = " << x << endl;
		cout << endl;
	}

	{
		cout << "array by element constructor" << endl;
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
		cout << "indirect-sequence" << endl;
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
		cout << "apply-sequence" << endl;
		array <int, 11> x{5, 9, 7, -2, 0, -8, 45, -1, 10, -3, 0};
		array <int, 11> y{7, -8, 0, 13, 128, 0, -2, 7, 6, 14, -9};
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "x + y = " << apply(afun::op::add(), x, y) << endl;
		cout << "x + 3 = " << apply(afun::op::add(), x, 3) << endl;
		cout << endl;
	}

	{
		cout << "array loop" << endl;
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
