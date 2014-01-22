#include <ivl/ivl>

//-----------------------------------------------------------------------------

namespace test {

using namespace ivl;
using namespace ivl::types;
namespace op = ivl::op;
using types::size;

//-----------------------------------------------------------------------------

struct A { int x; };
struct B : A { };
struct C : A { };

template <typename S>
S& operator<<(S& s, A) { return s << "A"; }

template <typename S>
S& operator<<(S& s, B) { return s << "B"; }

template <typename S>
S& operator<<(S& s, C) { return s << "C"; }

//-----------------------------------------------------------------------------

struct convert
{
	template <typename P, typename T>
	P _(T&& x) const { return (P) fwd <T>(x); }
};

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

template <char C> using vrf = afun::tmp_vec_apply <rf <C> >;
template <char C> using vpf = afun::tmp_vec_loop <pf <C> >;
template <char C> using arf = afun::tmp_vec_auto <rf <C> >;
template <char C> using apf = afun::tmp_vec_auto <pf <C> >;

//-----------------------------------------------------------------------------

template <template <char> class R, template <char> class V>
void temp()
{
	{
		cout << "custom template _" << endl;
		auto f = R <'A'>();
		auto F = val(R <'A'>(), R <'N'>());
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
		cout << "custom void template _" << endl;
		auto f = V <'A'>();
		auto F = val(V <'A'>(), V <'N'>());
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
		cout << "custom operator()" << endl;
		auto f = R <'A'>();
		auto F = val(R <'A'>(), R <'N'>());
		auto p = 5;
		auto P = val(5, val(0, 2));
		cout << f(p) << endl;
		cout << f(P) << endl;
		cout << F(p) << endl;
		cout << F(P) << endl;
		cout << _[F](P) << endl;
		cout << F(_[P]) << endl;
		cout << endl;
	}

	{
		cout << "custom void operator()" << endl;
		auto f = V <'A'>();
		auto F = val(V <'A'>(), V <'N'>());
		auto p = 5;
		auto P = val(5, val(0, 2));
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
		cout << "sizeof, alignof, C-style conversion" << endl;
		using S = pack <char, int, double>;
		using T = pack <char, int, double, array <double> >;
		cout << _sizeof(_('a', 5, 3.14, array <double>())) << endl;
		cout << _sizeof._<T>() << endl;
		cout << _alignof._<T>() << endl;
		float x = '0' + 3.14;
		cout << op::conv._<S>(x) << endl;
		cout << endl;
	}

	{
		cout << "static_cast" << endl;
		B b;
		C c;
		A &lb = b, &lc = c;
		A &&rb = B(), &&rc = C();
		cout << _static_cast._<A>(_(c, b)) << endl;
		cout << _static_cast._<pack <C&, B&> >(_(lc, lb)) << endl;  // only if B, C are non-empty
		cout << _static_cast._<pack <C&&, B&&> >(_(rc, rb)) << endl;
		cout << endl;
	}

	{
		cout << "custom template _" << endl;
		using C = afun::tmp_vec_apply <convert>;
		using S = pack <char, int, double>;
		float f = '0' + 3.14;
		double d = '0' + 6.18;
		size_t s = 1234567890;
		auto x = _(f, d, s);
		cout << C()._<S>(x) << endl;
		cout << C()._<S>(_[x]) << endl;
		cout << endl;
	}

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
