#include "pch.h"

#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the Vector class using an integer vector, a pointer vector and
	//a vector of a custom class Foo.
	TEST_CLASS(VectorTest)
	{
	public:
		//This method sets up the initial memory state to check for memory leaks.
		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		//This test method checks the current memory state against the initial state to check for memory leaks.
		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(copyConstructorTest)
		{
			//Integer
			int32_t a = 10;
			Vector<int32_t> intVec1;

			Assert::IsTrue(intVec1.isEmpty());
			intVec1.pushBack(a);
			Assert::AreEqual(intVec1.front(), a);
			Vector<int32_t> intVec2 = intVec1;
			Assert::AreEqual(intVec2.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intVec2.front(), intVec1.front());

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec1;
			
			Assert::IsTrue(pointerVec1.isEmpty());
			pointerVec1.pushBack(test);
			Assert::AreEqual(pointerVec1.front(), test);
			Vector<int32_t*> pointerVec2 = pointerVec1;
			Assert::AreEqual(pointerVec2.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(pointerVec2.front(), pointerVec2.front());
			delete test;

			//Foo
			Vector<Foo> fooVec1;

			Assert::IsTrue(fooVec1.isEmpty());
			fooVec1.pushBack(Foo(a));
			Assert::AreEqual(fooVec1.front(), Foo(a));
			Vector<Foo> fooVec2 = fooVec1;
			Assert::AreEqual(fooVec2.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooVec2.front(), fooVec1.front());
		}

		TEST_METHOD(pushBackTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			int32_t c = 30;
			int32_t d = 40;
			int32_t e = 50;
			Vector<int32_t> intVec;

			Assert::AreEqual(intVec.size(), static_cast<uint32_t>(0));
			intVec.pushBack(a);
			Assert::AreEqual(intVec.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(intVec.front(), a);
			intVec.pushBack(b);
			intVec.pushBack(c);
			intVec.pushBack(d);
			intVec.pushBack(e);
			Assert::AreEqual(intVec.back(), e);
			Assert::AreEqual(intVec.capacity(), static_cast<uint32_t>(8));

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			
			Assert::AreEqual(pointerVec.size(), static_cast<uint32_t>(0));
			pointerVec.pushBack(test);
			Assert::AreEqual(pointerVec.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(pointerVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(pointerVec.front(), test);
			pointerVec.pushBack(test + a);
			pointerVec.pushBack(test + b);
			pointerVec.pushBack(test + c);
			pointerVec.pushBack(test + d);
			Assert::AreEqual(pointerVec.back(), test + d);
			Assert::AreEqual(pointerVec.capacity(), static_cast<uint32_t>(8));
			delete test;

			//Foo
			Vector<Foo> fooVec;

			Assert::AreEqual(fooVec.size(), static_cast<uint32_t>(0));
			fooVec.pushBack(Foo(a));
			Assert::AreEqual(fooVec.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(fooVec.front(), Foo(a));
			fooVec.pushBack(Foo(b));
			fooVec.pushBack(Foo(c));
			fooVec.pushBack(Foo(d));
			fooVec.pushBack(Foo(e));
			Assert::AreEqual(fooVec.back(), Foo(e));
			Assert::AreEqual(fooVec.capacity(), static_cast<uint32_t>(8));
		}

		TEST_METHOD(vectorBeginTest)
		{

		}

		TEST_METHOD(vectorEndTest)
		{

		}

		TEST_METHOD(assignmentOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			int32_t c = 30;
			int32_t d = 40;
			int32_t e = 50;

			Vector<int32_t> intVec1;
			intVec1.pushBack(a);
			Vector<int32_t> intVec2;
			Assert::AreEqual(intVec1.front(), a);
			intVec2 = intVec1;
			Assert::AreEqual(intVec2.front(), a);
			intVec1.pushBack(b);
			intVec1.pushBack(c);
			intVec1.pushBack(d);
			intVec1.pushBack(e);
			intVec2 = intVec1;
			Assert::AreEqual(intVec1.back(), intVec2.back());
			Assert::AreEqual(intVec2.back(), e);
			Assert::AreEqual(intVec2.size(), intVec1.size());
			Assert::AreEqual(intVec2.capacity(), intVec1.capacity());

			//Pointer
			int32_t* test = new int32_t;

			Vector<int32_t*> pointerVec1;
			pointerVec1.pushBack(test);
			Vector<int32_t*> pointerVec2;
			Assert::AreEqual(pointerVec1.front(), test);
			pointerVec2 = pointerVec1;
			Assert::AreEqual(pointerVec1.front(), test);
			pointerVec1.pushBack(test + b);
			pointerVec1.pushBack(test + c);
			pointerVec1.pushBack(test + d);
			pointerVec1.pushBack(test + e);
			pointerVec2 = pointerVec1;
			Assert::AreEqual(pointerVec1.back(), pointerVec2.back());
			Assert::AreEqual(pointerVec2.back(), test + e);
			Assert::AreEqual(pointerVec2.size(), pointerVec1.size());
			Assert::AreEqual(pointerVec2.capacity(), pointerVec1.capacity());
			delete test;

			//Foo
			Vector<Foo> fooVec1;
			fooVec1.pushBack(Foo(a));
			Vector<Foo> fooVec2;
			Assert::AreEqual(fooVec1.front(), Foo(a));
			fooVec2 = fooVec1;
			Assert::AreEqual(fooVec2.front(), Foo(a));
			fooVec1.pushBack(b);
			fooVec1.pushBack(c);
			fooVec1.pushBack(d);
			fooVec1.pushBack(e);
			fooVec2 = fooVec1;
			Assert::AreEqual(fooVec1.back(), fooVec2.back());
			Assert::AreEqual(fooVec2.back(), Foo(e));
			Assert::AreEqual(fooVec2.size(), fooVec1.size());
			Assert::AreEqual(fooVec2.capacity(), fooVec1.capacity());
		}

		TEST_METHOD(popBackTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			int32_t c = 30;
			int32_t d = 40;
			int32_t e = 50;
			Vector<int32_t> intVec;
			intVec.pushBack(a);
			intVec.pushBack(b);
			intVec.pushBack(c);
			Assert::AreEqual(intVec.size(), static_cast<uint32_t>(3));
			Assert::AreEqual(intVec.back(), c);
			Assert::AreEqual(intVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(intVec.popBack(), c);
			Assert::AreEqual(intVec.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(intVec.capacity(), static_cast<uint32_t>(4));
			intVec.pushBack(c);
			intVec.pushBack(d);
			intVec.pushBack(e);
			intVec.popBack();
			Assert::AreEqual(intVec.capacity(), static_cast<uint32_t>(8));

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			pointerVec.pushBack(test);
			pointerVec.pushBack(test + a);
			pointerVec.pushBack(test + b);
			Assert::AreEqual(pointerVec.size(), static_cast<uint32_t>(3));
			Assert::AreEqual(pointerVec.back(), test + b);
			Assert::AreEqual(pointerVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(pointerVec.popBack(), test + b);
			Assert::AreEqual(pointerVec.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(pointerVec.capacity(), static_cast<uint32_t>(4));
			pointerVec.pushBack(test + b);
			pointerVec.pushBack(test + c);
			pointerVec.pushBack(test + d);
			pointerVec.popBack();
			Assert::AreEqual(pointerVec.capacity(), static_cast<uint32_t>(8));
			delete test;

			//Foo
			Vector<Foo> fooVec;
			fooVec.pushBack(Foo(a));
			fooVec.pushBack(Foo(b));
			fooVec.pushBack(Foo(c));
			Assert::AreEqual(fooVec.size(), static_cast<uint32_t>(3));
			Assert::AreEqual(fooVec.back(), Foo(c));
			Assert::AreEqual(fooVec.capacity(), static_cast<uint32_t>(4));
			Assert::AreEqual(fooVec.popBack(), Foo(c));
			Assert::AreEqual(fooVec.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(fooVec.capacity(), static_cast<uint32_t>(4));
			fooVec.pushBack(Foo(c));
			fooVec.pushBack(Foo(d));
			fooVec.pushBack(Foo(e));
			fooVec.popBack();
			Assert::AreEqual(fooVec.capacity(), static_cast<uint32_t>(8));
		}

		TEST_METHOD(atOperatorTest)
		{
			int32_t a = 10;
			int32_t b = 20;
			int32_t c = 30;
			int32_t d = 40;
			int32_t e = 50;

		}

		TEST_METHOD(vectorFindTest)
		{

		}

		TEST_METHOD(vectorRemoveTest)
		{

		}

		TEST_METHOD(constFrontTest)
		{
			//Integer
			int32_t a = 10;
			Vector<int32_t> intVec;
			intVec.pushBack(a);

			const Vector<int32_t> constIntVec = intVec;
			Assert::AreEqual(constIntVec.front(), intVec.front());
			Assert::AreEqual(constIntVec.front(), a);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			pointerVec.pushBack(test);

			const Vector<int32_t*> constPointerVec = pointerVec;
			Assert::AreEqual(constPointerVec.front(), pointerVec.front());
			Assert::AreEqual(constPointerVec.front(), test);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			fooVec.pushBack(Foo(a));

			const Vector<Foo> constFooVec = fooVec;
			Assert::AreEqual(constFooVec.front(), fooVec.front());
			Assert::AreEqual(constFooVec.front(), Foo(a));
		}

		TEST_METHOD(constBackTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			Vector<int32_t> intVec;

			intVec.pushBack(a);
			const Vector<int32_t> constIntVec = intVec;
			Assert::AreEqual(constIntVec.back(), intVec.back());
			Assert::AreEqual(constIntVec.back(), a);

			intVec.pushBack(b);
			const Vector<int32_t> constIntVec1 = intVec;
			Assert::AreEqual(constIntVec1.back(), intVec.back());
			Assert::AreEqual(constIntVec1.back(), b);
			Assert::AreNotEqual(constIntVec1.back(), constIntVec1.front());

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;

			pointerVec.pushBack(test);
			const Vector<int32_t*> constPointerVec = pointerVec;
			Assert::AreEqual(constPointerVec.back(), pointerVec.back());
			Assert::AreEqual(constPointerVec.back(), test);

			pointerVec.pushBack(test + 1);
			const Vector<int32_t*> constPointerVec1 = pointerVec;
			Assert::AreEqual(constPointerVec1.back(), pointerVec.back());
			Assert::AreEqual(constPointerVec1.back(), test + 1);
			Assert::AreNotEqual(constPointerVec1.back(), constPointerVec1.front());
			delete test;

			//Foo
			Vector<Foo> fooVec;
			
			fooVec.pushBack(Foo(a));
			const Vector<Foo> constFooVec = fooVec;
			Assert::AreEqual(constFooVec.back(), fooVec.back());
			Assert::AreEqual(constFooVec.back(), Foo(a));

			fooVec.pushBack(Foo(b));
			const Vector<Foo> constFooVec1 = fooVec;
			Assert::AreEqual(constFooVec1.back(), fooVec.back());
			Assert::AreEqual(constFooVec1.back(), Foo(b));
			Assert::AreNotEqual(constFooVec1.back(), constFooVec1.front());
		}

		TEST_METHOD(isEmptyTest)
		{

		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}