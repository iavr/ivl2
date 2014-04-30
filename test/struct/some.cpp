#include <ivl/ivl>
#include <algorithm>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;

//-----------------------------------------------------------------------------

void run()
{
	using A = array <int, 7>;

	some a0 = true;
	some a1 = 'A';
	some a2 = 6;
	some a3 = 3.14;
	some a4 = "hello,";
	some a5 = A{6, 5, 4, 3, 2, 1, 0};
	some a6 = 2.71;
	some a7 = string("world!");

	cout << "* some{T}; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()        << endl;
	cout << "[1] char        : " << a1._<char>()        << endl;
	cout << "[2] int         : " << a2._<int>()         << endl;
	cout << "[3] double      : " << a3._<double>()      << endl;
	cout << "[4] const char* : " << a4._<const char*>() << endl;
	cout << "[5] array<int>  : " << a5._<A>()           << endl;
	cout << "[6] double      : " << a6._<double>()      << endl;
	cout << "[7] string      : " << a7._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	some c0 = a0;
	some c1 = a1;
	some c2 = a2;
	some c3 = a3;
	some c4{a4};
	some c5{a5};
	some c6{a6};
	some c7{a7};

	a0.clear();
	a1.clear();
	a2.clear();
	a3.clear();
	a4.clear();
	a5.clear();
	a6.clear();
	a7.clear();

	cout << "* some{some&}; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << c0._<bool>()        << endl;
	cout << "[1] char        : " << c1._<char>()        << endl;
	cout << "[2] int         : " << c2._<int>()         << endl;
	cout << "[3] double      : " << c3._<double>()      << endl;
	cout << "[4] const char* : " << c4._<const char*>() << endl;
	cout << "[5] array<int>  : " << c5._<A>()           << endl;
	cout << "[6] double      : " << c6._<double>()      << endl;
	cout << "[7] string      : " << c7._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	some m0 = mv(c0);
	some m1 = mv(c1);
	some m2 = mv(c2);
	some m3 = mv(c3);
	some m4{mv(c4)};
	some m5{mv(c5)};
	some m6{mv(c6)};
	some m7{mv(c7)};

	cout << "* some{some&&}; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << m0._<bool>()        << endl;
	cout << "[1] char        : " << m1._<char>()        << endl;
	cout << "[2] int         : " << m2._<int>()         << endl;
	cout << "[3] double      : " << m3._<double>()      << endl;
	cout << "[4] const char* : " << m4._<const char*>() << endl;
	cout << "[5] array<int>  : " << m5._<A>()  << endl;
	cout << "[6] double      : " << m6._<double>()      << endl;
	cout << "[7] string      : " << m7._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	array<some, 8> a;
	a[0] = true;
	a[1] = 'A';
	a[2] = 6;
	a[3] = 3.14;
	a[4] = "hello,";
	a[5] = A{6, 5, 4, 3, 2, 1, 0};
	a[6] = 2.71;
	a[7] = string("world!");

	cout << "* some <- T; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()        << endl;
	cout << "[1] char        : " << a[1]._<char>()        << endl;
	cout << "[2] int         : " << a[2]._<int>()         << endl;
	cout << "[3] double      : " << a[3]._<double>()      << endl;
	cout << "[4] const char* : " << a[4]._<const char*>() << endl;
	cout << "[5] array<int>  : " << a[5]._<A>()           << endl;
	cout << "[6] double      : " << a[6]._<double>()      << endl;
	cout << "[7] string      : " << a[7]._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a[0] = m0;
	a[1] = m1;
	a[2] = m2;
	a[3] = m3;
	a[4] = m4;
	a[5] = m5;
	a[6] = m6;
	a[7] = m7;

	cout << "* some <- some&; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()        << endl;
	cout << "[1] char        : " << a[1]._<char>()        << endl;
	cout << "[2] int         : " << a[2]._<int>()         << endl;
	cout << "[3] double      : " << a[3]._<double>()      << endl;
	cout << "[4] const char* : " << a[4]._<const char*>() << endl;
	cout << "[5] array<int>  : " << a[5]._<A>()           << endl;
	cout << "[6] double      : " << a[6]._<double>()      << endl;
	cout << "[7] string      : " << a[7]._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a[0] = mv(m0);
	a[1] = mv(m1);
	a[2] = mv(m2);
	a[3] = mv(m3);
	a[4] = mv(m4);
	a[5] = mv(m5);
	a[6] = mv(m6);
	a[7] = mv(m7);

	cout << "* some <- some&&; some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a[0]._<bool>()        << endl;
	cout << "[1] char        : " << a[1]._<char>()        << endl;
	cout << "[2] int         : " << a[2]._<int>()         << endl;
	cout << "[3] double      : " << a[3]._<double>()      << endl;
	cout << "[4] const char* : " << a[4]._<const char*>() << endl;
	cout << "[5] array<int>  : " << a[5]._<A>()           << endl;
	cout << "[6] double      : " << a[6]._<double>()      << endl;
	cout << "[7] string      : " << a[7]._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	auto is_double = [](const some& s) { return s.is<double>(); };
	cout << "there are "
		<< std::count_if(a.begin(), a.end(), is_double)  // TODO: replace
		<< " elements of type 'double' in vector a" << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	a0 = a[0];
	a1 = a[1];
	a2 = a[2];
	a3 = a[3];
	a4 = a[4];
	a5 = a[5];
	a6 = a[6];
	a7 = a[7];

	cout << "* type check :" << endl << endl;
	cout << "[0] is long / bool        : " << a0.is<long>() << " / " << a0.is<bool>()        << endl;
	cout << "[1] is long / char        : " << a1.is<long>() << " / " << a1.is<char>()        << endl;
	cout << "[2] is long / int         : " << a2.is<long>() << " / " << a2.is<int>()         << endl;
	cout << "[3] is long / double      : " << a3.is<long>() << " / " << a3.is<double>()      << endl;
	cout << "[4] is long / const char* : " << a4.is<long>() << " / " << a4.is<const char*>() << endl;
	cout << "[5] is long / array<int>  : " << a5.is<long>() << " / " << a5.is<A>()           << endl;
	cout << "[6] is long / double      : " << a6.is<long>() << " / " << a6.is<double>()      << endl;
	cout << "[7] is long / string      : " << a7.is<long>() << " / " << a7.is<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	cout << "* swap:" << endl << endl;

	cout << "[5] array<int>  : " << a5._<A>()      << endl;
	cout << "[7] string      : " << a7._<string>() << endl;

	swap(a5, a7);

	cout << "[5] string      : " << a5._<string>() << endl;
	cout << "[7] array<int>  : " << a7._<A>()      << endl;

	swap(a5, a7);
	cout << endl;

//-----------------------------------------------------------------------------

	auto& l0 = a0._<bool>();         l0 = false;
	auto& l1 = a1._<char>();         l1 = 'B';
	auto& l2 = a2._<int>();          l2 = 8;
	auto& l3 = a3._<double>();       l3 = -3.14;
	auto& l4 = a4._<const char*>();  l4 = "Hello,";
	auto& l5 = a5._<A>();            l5[2] = -2;
	auto& l6 = a6._<double>();       l6 = -2.71;
	auto& l7 = a7._<string>();       l7 += " ...";

	a5._<A>()[4] = -2;
	a7._<string>()[0] = 'W';

	cout << "* T&(some&); some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()        << endl;
	cout << "[1] char        : " << a1._<char>()        << endl;
	cout << "[2] int         : " << a2._<int>()         << endl;
	cout << "[3] double      : " << a3._<double>()      << endl;
	cout << "[4] const char* : " << a4._<const char*>() << endl;
	cout << "[5] array<int>  : " << a5._<A>()           << endl;
	cout << "[6] double      : " << a6._<double>()      << endl;
	cout << "[7] string      : " << a7._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	auto&& r0 = mv(a0)._<bool>();         r0 = true;
	auto&& r1 = mv(a1)._<char>();         r1 = 'C';
	auto&& r2 = mv(a2)._<int>();          r2 = 12;
	auto&& r3 = mv(a3)._<double>();       r3 = 3.14159;
	auto&& r4 = mv(a4)._<const char*>();  r4 = "HEllo,";
	auto&& r5 = mv(a5)._<A>();            r5[3] = -4;
	auto&& r6 = mv(a6)._<double>();       r6 = 2.71828;
	auto&& r7 = mv(a7)._<string>();       r7 += " !!!";

	a5._<A>()[5] = -4;            // no move; mv(a5)._<A>()[5] is int&& (not assignable)
	mv(a7)._<string>()[1] = 'O';  // ok: mv(a7)._<string>()[1] is char&, not char&&

	cout << "* T&&(some&&); some._<T>() :" << endl << endl;
	cout << "[0] bool        : " << a0._<bool>()        << endl;
	cout << "[1] char        : " << a1._<char>()        << endl;
	cout << "[2] int         : " << a2._<int>()         << endl;
	cout << "[3] double      : " << a3._<double>()      << endl;
	cout << "[4] const char* : " << a4._<const char*>() << endl;
	cout << "[5] array<int>  : " << a5._<A>()           << endl;
	cout << "[6] double      : " << a6._<double>()      << endl;
	cout << "[7] string      : " << a7._<string>()      << endl;
	cout << endl;

//-----------------------------------------------------------------------------

	struct E
	{
		int i;  // non-empty, otherwise move optimized
		E() { }
		E(E&&) { throw E(); }
		E(const E&) { }
		E& operator=(E&&) = delete;
		E& operator=(E const&) = delete;
	};

//-----------------------------------------------------------------------------

	cout << "* assign exceptions:" << endl << endl;

	some z = 4;
	cout << "init:  z = " << z._<int>() << endl;
	try { z = E{}; }
	catch(...) {
		cout << "catch: z = " << z._<int>() << endl;
	}
	cout << endl;

	z = A{6, 5, 4, 3, 2, 1, 0};
	cout << "init:  z = " << z._<A>() << endl;
	try { z = E{}; }
	catch(...) {
		cout << "catch: z = " << z._<A>() << endl;
	}
	cout << endl;

//-----------------------------------------------------------------------------

	cout << "* swap exceptions:" << endl << endl;

	some e = static_cast<const E&>(E{});

	z = 4;
	cout << "init:  z = " << z._<int>() << endl;
	try { swap(z, e); }
	catch(...) {
		cout << "catch: z = " << z._<int>() << endl;
	}
	try { swap(e, z); }
	catch(...) {
		cout << "catch: z = " << z._<int>() << endl;
	}
	cout << endl;

	z = A{6, 5, 4, 3, 2, 1, 0};
	cout << "init:  z = " << z._<A>() << endl;
	try { swap(z, e); }
	catch(...) {
		cout << "catch: z = " << z._<A>() << endl;
	}
	try { swap(e, z); }
	catch(...) {
		cout << "catch: z = " << z._<A/**/>() << endl;
	}
	cout << endl;

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
