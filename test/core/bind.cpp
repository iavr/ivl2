#include <ivl/ivl>

using namespace ivl;

struct
{
	template <typename A, typename B, typename C>
	void operator()(A&& a, B&& b, C&& c) const
	{
		cout << a << " " << b << " " << c << endl;
	}
}
f;

// TODO: bind[val]
afun::val_of <afun::details::bind_> vbind;

auto b()
-> decltype(bind(f, 4, 'A'))
	{ return bind(f, 4, 'A'); }

auto vb()
-> decltype(vbind(f, 4, 'A'))
	{ return vbind(f, 4, 'A'); }

int main ()
{
	{
		b()("hello");
		auto g = bind(f, 4, 'A');
		g("hello");
		bind(f, 4, 'A')("hello");
		cout << endl;
	}

	{
		vb()("hello");
		auto g = vbind(f, 4, 'A');
		g("hello");
		vbind(f, 4, 'A')("hello");
		cout << endl;
	}
}
