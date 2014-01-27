#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "minimum" << endl;
		cout << min(_(14, 7, 3, -8, 9, 0)) << endl;
		cout << max(_(14, 7, 3, -8, 9, 0)) << endl;
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