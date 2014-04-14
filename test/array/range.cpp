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
		cout << "bounded range" << endl;
		cout << (3,_,8) << endl;
		cout << (8,_,3) << endl;
		cout << (3,--_,8) << endl;
		cout << (8,--_,3) << endl;
		cout << endl;

		cout << "unbounded range" << endl;
		auto a = seq(2, 2, 2, 0, 2, 2);
		cout << a << endl;
		cout << a + (3,_) << endl;
		cout << endl;

		cout << "vec-range" << endl;
		auto e = seq(7, 8, 9);
		cout << range(3,_,e) << endl;
		cout << _[a] + range(_(3,5,7),_) << endl;
		cout << endl;

		cout << "range composites" << endl;
		auto r = (1,_,10);
		cout << r << endl;
		cout << flip(r) << endl;
		cout << join(r, tail(flip(r))) << endl;
		cout << endl;

		cout << "range-indirect" << endl;
		auto x = seq(6, 1, -3, 8, -7, 9, 0, 1, 2, 6, 4, 3);
		auto y = cp(flip(x));
		cout << x << endl;
		cout << y << endl;
		cout << x[3,_,8] << endl;
		x[3,_,8] = y[3,_];
		cout << x << endl;
		x[3,_] = -y[3,_,8];
		cout << x << endl;
		cout << endl;

		using T = size_t;
		cout << "step-range" << endl;
		cout << (2,_+=3,19) << endl;
		cout << (19,_+=3,2) << endl;
		cout << (2,_-=3,19) << endl;
		cout << (19,_-=3,2) << endl;
		auto l = (T(2),_,T(14));
		cout << zip(l, range(T(4),_+=3,l)) << endl;
		cout << zip(l, range(T(4),_-=-3,l)) << endl;
		cout << zip(l, range(T(12),_+=-3,l)) << endl;
		cout << zip(l, range(T(12),_-=3,l)) << endl;
		cout << endl;

		cout << "tiny range" << endl;
		size <2> _2;
		size <3> _3;
		cout << (_2,_+=_3,19) << endl;
		cout << ( 2,_+= 3,19) << endl;
		cout << sizeof(_2,_+=_3) << endl;
		cout << sizeof( 2,_+= 3) << endl;
		cout << sizeof(_2,_+=_3,19) << endl;
		cout << sizeof( 2,_+= 3,19) << endl;
		cout << endl;

		cout << "iterator range" << endl;
		auto z = seq(6, 1, -3, 8, -7, 9, 0, 1, 2, 6, 4, 3);
		auto i = (z.begin(), _+=2, z.end()-1);
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
