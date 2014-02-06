#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "aggr array" << endl;
		aggr_array <int, 0> x{{}};
		aggr_array <int, 5> y{{5, 9, 7, -2, 0}};
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
		cout << "array by initializer list" << endl;
		foo f4(4), f5(5), f6(6);
		cout << endl << "begin" << endl;
		array <foo, 3> x{f4, f5, f6};
		cout << "end" << endl << endl;
		cout << "x = " << x << endl;
		cout << endl;
	}

	{
		cout << "indirect array" << endl;
		constexpr size_t N = 11;
		array <int, N> x;
		for (size_t n = 0; n < N; n++)
			x[n] = 2 * n;
		array <int, 4> i;
		i[0] = 5; i[1] = 8; i[2] = 0; i[3] = 8;
		cout << "x = " << x << endl;
		cout << "x[i] = " << x[i] << endl;

// 		array <array <int, 4>, 2> j;
// 		j[0] = i; j[1] = i;
// 		cout << "x[j] = " << x[j] << endl;

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
