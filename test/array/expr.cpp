#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
using ivl::seq;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "expression" << endl;
		int i = -2, j = 9;
		double x = 0, y = -11;
		auto u = seq(_(x, j), _(y, i));
		auto a = seq(_(3.14, 1), _(7., 6));
		auto b = seq(_(2.18, 5), _(-2, 3));
		cout << a + 2 * b << endl;
		u = a + 2 * b;
		cout << u << endl;
		cout << endl;
	}

	{
		cout << "foo expression" << endl;
		foo i = -2, j = 9;
		foo x = 0, y = 2;
		auto u = seq(_(x, j), _(y, i));
		auto a = foo_seq(foo_seq(1, -1), foo_seq(7, 6));
		auto b = foo_seq(foo_seq(5, -2), foo_seq(-2, 3));
		cout << endl;
		cout << "begin" << endl;
		cout << (a + y * b)[1][0] << endl;
		cout << "end" << endl;
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
