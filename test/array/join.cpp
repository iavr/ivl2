#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace types;
using ivl::flip;
using ivl::join;
using ivl::seq;

//-----------------------------------------------------------------------------

template <typename Z>
void traverse(Z&& z)
{
	arrays::join_path <> e;
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

//-----------------------------------------------------------------------------

void run()
{

	{
		cout << "join" << endl;
		auto E = seq();
		auto a = seq(0, 1, 2, 3);
		auto b = seq(-3.14, 12.71, -8e3);
		auto c = seq._<int>(-3.14, 12.71, -8e3);
		*join(a, c).begin() = 20;
		cout << a << endl;
		cout << join(a, b) << endl;
		auto j = join(E, a, b, E, seq(80, 1), E);
		auto jj = join(E, j, E, a, j, E);
		cout << j << endl;
		cout << flip(j) << endl;
		cout << jj << endl;
		cout << flip(jj) << endl;
		cout << endl;

		{
			cout << "join + flip/tail" << endl;
			auto a = jj;
			cout << "    " << a << endl;
			cout << "  F " << flip(a) << endl;
			cout << "  F " << flip(mv(a)) << endl;
			cout << " FF " << flip(flip(a)) << endl;
			cout << " TF " << tail(flip(a)) << endl;
			cout << " FT " << flip(tail(a)) << endl;
			cout << "TTF " << tail(tail(flip(a))) << endl;
			cout << "TFT " << tail(flip(tail(a))) << endl;
			cout << "FTT " << flip(tail(tail(a))) << endl;
			cout << endl;
		}

		cout << "join loop" << endl;
		traverse(jj);

		cout << "flip(join) loop" << endl;
		traverse(flip(jj));

	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
