#include "RunOnUiThread.h"
#include "AutoCastTest.h"
#include "CallFunctionWithNParams.h"
#include "AutoSerialize.h"

void main()
{
	TestAutoSerialize();
	TestCallFunction();
	AutoCastTest();
	RunOnUiThreadTest();
}