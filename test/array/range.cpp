#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;
using ivl::seq;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "range" << endl;
		auto a = seq(2, 2, 2, 0, 2, 2);
		cout << a << endl;
		cout << a + (3,_) << endl;
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
