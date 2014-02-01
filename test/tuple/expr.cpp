#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "expression" << endl;
		int x = 0, i = -2, j = 9;
		auto t = _(x, _(i, j));
		auto a = _(1, _(7, 6));
		auto b = _(5, _(-2, 3));
		cout << a + 2 * b << endl;
		t = a + 2 * b;
		cout << t << endl;
		cout << endl;
	}

	{
		cout << "foo expression" << endl;
		foo x = 0, i = -2, j = 9, z = 2;
		auto t = _(x, _(i, j));
		auto a = foos(1, foos(7, 6));
		auto b = foos(5, foos(-2, 3));
		cout << endl;
		cout << "begin" << endl;
		cout << at._<0>(at._<1>((a + z * b))) << endl;
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
