#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;

//-----------------------------------------------------------------------------

template <size_t N = 0> using A = array <int, N>;
template <size_t N = 0> using B = array <double, N>;

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "join" << endl;
		A <> E;
		A <4> a = {0, 1, 2, 3};
		B <3> b = {-3.14, 12.71, -8e3};
		A <3> c = {-3.14, 12.71, -8e3};
		*join(a, c).begin() = 20;
		cout << a << endl;
		cout << join(a, b) << endl;
		auto j = join(E, a, b, E, A <2>{0, 1}, E);
		auto jj = join(E, j, E, a, j, E);
		cout << j << endl;
		cout << flip(j) << endl;
		cout << jj << endl;
		cout << flip(jj) << endl;
		cout << endl;

		{
			cout << "join loop" << endl;
			arrays::edge_on <> e;
			auto z = j;
			for (auto v = z.trav(); v; ++v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(); v; v++)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(e)>>_; -v; --v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(e)>>_; -v; v--)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.begin(), e = z.end(); v != e; ++v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.begin(), e = z.end(); v != e; v++)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.end(), e = --z.begin(); --v != e;)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.end(), e = --z.begin(); v--, v != e;)
				cout << *v << " ";
			cout << endl;
			cout << endl;
		}

		{
			cout << "flip(join) loop" << endl;
			arrays::edge_on <> e;
			auto z = flip(j);
			for (auto v = z.trav(); v; ++v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(); v; v++)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(e)>>_; -v; --v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.trav(e)>>_; -v; v--)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.begin(), e = z.end(); v != e; ++v)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.begin(), e = z.end(); v != e; v++)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.end(), e = --z.begin(); --v != e;)
				cout << *v << " ";
			cout << endl;
			for (auto v = z.end(), e = --z.begin(); v--, v != e;)
				cout << *v << " ";
			cout << endl;
			cout << endl;
		}

	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
