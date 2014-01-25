#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;
using types::size;

//-----------------------------------------------------------------------------

template <char C>
struct rf
{
	char operator()(int x) { return x + C; }

	template <typename P>
	char _() const { return P()() + C; }
};

template <char C>
struct pf
{
	void operator()(int x) { cout << char(x + C) << " "; }

	template <typename P>
	void _() const { cout << char(P()() + C) << " "; }
};

template <char C> using vrf = afun::tvec_apply <rf <C> >;
template <char C> using vpf = afun::tvec_loop <pf <C> >;
template <char C> using arf = afun::tvec_auto <rf <C> >;
template <char C> using apf = afun::tvec_auto <pf <C> >;

//-----------------------------------------------------------------------------

template <template <char> class R, template <char> class V>
void temp()
{
	{
		cout << "custom _<>()" << endl;
		auto f = R <'A'>();
		auto F = _(R <'A'>(), R <'N'>());
		using p = size <5>;
		using P = pack <size <5>, pack <size <0>, size <2> > >;
		cout << f.template _<p>() << endl;
		cout << f.template _<P>() << endl;
		cout << F.template _<p>() << endl;
		cout << F.template _<P>() << endl;
		cout << _[F].template _<P>() << endl;
		cout << F.template _<_type <P> >() << endl;
		cout << endl;
	}

	{
		cout << "custom void _<>()" << endl;
		auto f = V <'A'>();
		auto F = _(V <'A'>(), V <'N'>());
		using p = size <5>;
		using P = pack <size <5>, pack <size <0>, size <2> > >;
		f.template _<p>(); cout << endl;
		f.template _<P>(); cout << endl;
		F.template _<p>(); cout << endl;
		F.template _<P>(); cout << endl;
		_[F].template _<P>(); cout << endl;
		F.template _<_type <P> >(); cout << endl;
		cout << endl;
	}
}

//-----------------------------------------------------------------------------

template <template <char> class R, template <char> class V>
void call()
{
	{
		cout << "custom op ()" << endl;
		auto f = R <'A'>();
		auto F = _(R <'A'>(), R <'N'>());
		auto p = 5;
		auto P = _(5, _(0, 2));
		cout << f(p) << endl;
		cout << f(P) << endl;
		cout << F(p) << endl;
		cout << F(P) << endl;
		cout << _[F](P) << endl;
		cout << F(_[P]) << endl;
		cout << endl;
	}

	{
		cout << "custom void op ()" << endl;
		auto f = V <'A'>();
		auto F = _(V <'A'>(), V <'N'>());
		auto p = 5;
		auto P = _(5, _(0, 2));
		f(p); cout << endl;
		f(P); cout << endl;
		F(p); cout << endl;
		F(P); cout << endl;
		_[F](P); cout << endl;
		F(_[P]); cout << endl;
		cout << endl;
	}
}

//-----------------------------------------------------------------------------

void run()
{

	{
		temp <vrf, vpf>();
		temp <arf, apf>();
		call <vrf, vpf>();
		call <arf, apf>();
	}

}

//-----------------------------------------------------------------------------

}  // namespace test

//-----------------------------------------------------------------------------

int main()
{
	test::run();
}
