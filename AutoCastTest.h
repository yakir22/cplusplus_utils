#pragma once


struct IRD
{
	virtual ~IRD(){}
	int x;
};

struct TRD
{
	int t;
};

struct FRD
{
	int s;
};

struct LRD : IRD,TRD,FRD
{
	int l;
};


/*

struct C
{
	int y;
};

struct FinalWithB : A, B
{
	int z;
};

struct FinalWithC : A, C
{
	int z;
};
*/


void AutoCastTest()
{
/*
	auto l = new LRD;
	auto f = dynamic_cast<FRD*>(l);

	auto ol = offsetof(LRD, s);
	auto of = offsetof(FRD, s);

	auto of1 = offsetof(LRD, x);
	auto of2 = offsetof(IRD, x);

	decltype(LRD::x) a;
*/

	/*
	auto withB = new FinalWithB();
	auto withC = new FinalWithC();

	A* aWithB = dynamic_cast<A*>(withB);
	A* aWithC = dynamic_cast<A*>(withC);

	C* cFromB = dynamic_cast<C*>(aWithB);
	C* cFromC = dynamic_cast<C*>(aWithC);
*/
}







