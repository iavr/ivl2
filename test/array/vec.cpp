#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "array min" << endl;
// 		array <int, 6> x{{14, 7, 3, -8, 9, 0}};

		constexpr size_t N = 11;
		array <int, N> x;
		for (size_t n = 0; n < N; n++)
			x[n] = 2 * n;

		cout << "x = " << x << endl;
		cout << "x = ", loop(op::left, cout, x), cout << endl;
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
