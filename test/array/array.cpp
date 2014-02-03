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

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
