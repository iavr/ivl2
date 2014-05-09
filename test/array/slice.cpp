#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;
using ivl::seq;
using ivl::range;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "bounded iota" << endl;
		cout << iota(6) << endl;
		cout << endl;

		cout << "unbounded iota" << endl;
		auto a = seq(2, 2, 2, 0, 2, 2);
		cout << a << endl;
		cout << a + iota() << endl;
		cout << endl;

		cout << "tiny iota" << endl;
		size <6> _6;
		cout << iota( 6) << endl;
		cout << iota(_6) << endl;
		cout << sizeof(iota( 6)) << endl;
		cout << sizeof(iota(_6)) << endl;
		cout << decltype(iota(_6))::order_type{} << endl;
		cout << endl;
	}

	{
		cout << "bounded slice" << endl;
		cout << slice(3,_,6) << endl;
		cout << slice(3,++_,6) << endl;
		cout << slice(3,--_,6) << endl;
		cout << endl;

		cout << "unbounded slice" << endl;
		auto a = seq(2, 2, 2, 0, 2, 2);
		cout << a << endl;
		cout << a + slice(3,_) << endl;
		cout << endl;

		cout << "vec-slice" << endl;
		auto e = seq(5, 6, 7);
		cout << slice(3,_,e) << endl;
		cout << _[a] + slice(_(3,5,7),_) << endl;
		cout << endl;

		cout << "range composites" << endl;
		auto r = slice(1,_,10);
		cout << r << endl;
		cout << flip(r) << endl;
		cout << join(r, tail(flip(r))) << endl;
		cout << endl;

		cout << "slice/range-indirect" << endl;
		auto x = seq(6, 1, -3, 8, -7, 9, 0, 1, 2, 6, 4, 3);
		auto y = cp(flip(x));
		cout << x << endl;
		cout << y << endl;
		cout << x[slice(3,_,6)] << endl;
		x[slice(3,_,6)] = y[3,_];
		cout << x << endl;
		x[3,_] = -y[slice(3,_,6)];
		cout << x << endl;
		cout << endl;

		using T = size_t;
		cout << "step-slice" << endl;
		cout << slice( 2,_+= 3,6) << endl;
		cout << slice( 2,_-=-3,6) << endl;
		cout << slice(19,_+=-3,6) << endl;
		cout << slice(19,_-= 3,6) << endl;
		cout << endl;

		cout << "tiny slice" << endl;
		size <2> _2;
		size <3> _3;
		size <6> _6;
		cout << slice( 2,_+= 3, 6) << endl;
		cout << slice(_2,_+=_3,_6) << endl;
		cout << sizeof(slice( 2,_+= 3)) << endl;
		cout << sizeof(slice(_2,_+=_3)) << endl;
		cout << sizeof(slice( 2,_+= 3, 6)) << endl;
		cout << sizeof(slice(_2,_+=_3,_6)) << endl;
		cout << decltype(slice(_2,_+=_3,_6))::order_type{} << endl;
		cout << endl;

		cout << "iterator slice" << endl;
		auto z = seq(6, 1, -3, 8, -7, 9, 0, 1, 2, 6, 4, 3);
		auto i = slice(z.begin(), _+=2, 6);
		cout << *i << endl;
		*i = 0;
		cout << z << endl;
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
