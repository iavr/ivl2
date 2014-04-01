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
		auto t = seq(_(x, j), _(y, i));
		auto a = seq(_(3.14, 1), _(7., 6));
		auto b = seq(_(2.18, 5), _(-2, 3));
		cout << a + 2 * b << endl;
		t = a + 2 * b;
		cout << t << endl;
		cout << endl;
	}

// 	{
// 		cout << "foo expression" << endl;
// 		foo x = 0, i = -2, j = 9, z = 2;
// 		auto t = _(x, _(i, j));
// 		auto a = foos(1, foos(7, 6));
// 		auto b = foos(5, foos(-2, 3));
// 		cout << endl;
// 		cout << "begin" << endl;
// 		cout << at._<0>(at._<1>((a + z * b))) << endl;
// 		cout << "end" << endl;
// 		cout << endl;
// 	}

}
//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
