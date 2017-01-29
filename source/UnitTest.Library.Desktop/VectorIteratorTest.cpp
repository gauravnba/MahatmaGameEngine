#include "pch.h"

#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the Vector Iterator class using an integer vector, a pointer vector and
	//a vector of a custom class Foo.
	TEST_CLASS(VectorIteratorTest)
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
			Vector<int32_t> intVec;
			intVec.pushBack(a);
			Vector<int32_t>::Iterator interator1 = intVec.begin();
			Vector<int32_t>::Iterator interator2 = interator1;
			Assert::AreEqual(*interator1, a);
			Assert::AreEqual(interator1, interator2);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			pointerVec.pushBack(test);
			Vector<int32_t*>::Iterator pointerator1 = pointerVec.begin();
			Vector<int32_t*>::Iterator pointerator2 = pointerator1;
			Assert::AreEqual(*pointerator1, test);
			Assert::AreEqual(pointerator2, pointerator1);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			fooVec.pushBack(Foo(a));
			Vector<Foo>::Iterator footerator1 = fooVec.begin();
			Vector<Foo>::Iterator footerator2 = footerator1;
			Assert::AreEqual(*footerator1, Foo(a));
			Assert::AreEqual(footerator1, footerator2);
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			//Integer
			int32_t a = 0;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator1 = intVec.pushBack(a);
			Vector<int32_t>::Iterator interator2;
			Assert::AreNotEqual(interator2, interator1);
			interator2 = interator1;
			Assert::AreEqual(interator2, interator1);
			Assert::AreEqual(*interator2, a);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator1 = pointerVec.pushBack(test);
			Vector<int32_t*>::Iterator pointerator2;
			Assert::AreNotEqual(pointerator2, pointerator1);
			pointerator2 = pointerator1;
			Assert::AreEqual(pointerator2, pointerator1);
			Assert::AreEqual(*pointerator2, test);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator1 = fooVec.pushBack(Foo(a));
			Vector<Foo>::Iterator footerator2;
			Assert::AreNotEqual(footerator2, footerator1);
			footerator2 = footerator1;
			Assert::AreEqual(footerator2, footerator1);
			Assert::AreEqual(*footerator2, Foo(a));
		}

		TEST_METHOD(equalityOperatorTest)
		{
			//Integer
			int32_t a = 0;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator1 = intVec.pushBack(a);
			Vector<int32_t>::Iterator interator2;
			Assert::IsFalse(interator2 == interator1);
			interator2 = interator1;
			Assert::IsTrue(interator2 == interator1);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator1 = pointerVec.pushBack(test);
			Vector<int32_t*>::Iterator pointerator2;
			Assert::IsFalse(pointerator1 == pointerator2);
			pointerator2 = pointerator1;
			Assert::IsTrue(pointerator2 == pointerator1);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator1 = fooVec.pushBack(Foo(a));
			Vector<Foo>::Iterator footerator2;
			Assert::IsFalse(footerator2 == footerator1);
			footerator2 = footerator1;
			Assert::IsTrue(footerator2 == footerator1);
		}

		TEST_METHOD(inequalityOperatorTest)
		{
			//Integer
			int32_t a = 0;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator1 = intVec.pushBack(a);
			Vector<int32_t>::Iterator interator2;
			Assert::IsTrue(interator2 != interator1);
			interator2 = interator1;
			Assert::IsFalse(interator2 != interator1);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator1 = pointerVec.pushBack(test);
			Vector<int32_t*>::Iterator pointerator2;
			Assert::IsTrue(pointerator1 != pointerator2);
			pointerator2 = pointerator1;
			Assert::IsFalse(pointerator2 != pointerator1);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator1 = fooVec.pushBack(Foo(a));
			Vector<Foo>::Iterator footerator2;
			Assert::IsTrue(footerator2 != footerator1);
			footerator2 = footerator1;
			Assert::IsFalse(footerator2 != footerator1);
		}

		TEST_METHOD(preIncrementOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 11;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator;
			auto intIncrement = [&interator] {++interator; };
			Assert::ExpectException<runtime_error>(intIncrement);
			interator = intVec.pushBack(a);
			intVec.pushBack(b);
			Assert::AreEqual(interator, intVec.begin());
			++interator;
			Assert::AreEqual(interator, ++(intVec.begin()));
			++interator;
			Assert::ExpectException<runtime_error>(intIncrement);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator;
			auto pointerIncrement = [&pointerator] {++pointerator; };
			Assert::ExpectException<runtime_error>(pointerIncrement);
			pointerator = pointerVec.pushBack(test);
			pointerVec.pushBack(test + 1);
			Assert::AreEqual(pointerator, pointerVec.begin());
			++pointerator;
			Assert::AreEqual(pointerator, ++(pointerVec.begin()));
			++pointerator;
			Assert::ExpectException<runtime_error>(pointerIncrement);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator;
			auto fooIncrement = [&footerator] {++footerator; };
			Assert::ExpectException<runtime_error>(fooIncrement);
			footerator = fooVec.pushBack(Foo(a));
			fooVec.pushBack(Foo(b));
			Assert::AreEqual(footerator, fooVec.begin());
			++footerator;
			Assert::AreEqual(footerator, ++fooVec.begin());
			++footerator;
			Assert::ExpectException<runtime_error>(fooIncrement);
		}

		TEST_METHOD(postIncrementOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 11;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator1;
			Vector<int32_t>::Iterator interator2;
			auto intIncrement = [&interator1] {interator1++; };
			Assert::ExpectException<runtime_error>(intIncrement);
			interator1 = intVec.pushBack(a);
			intVec.pushBack(b);
			Assert::AreEqual(interator1, intVec.begin());
			interator2 = interator1++;
			Assert::AreEqual(interator2, intVec.begin());
			Assert::AreEqual(interator1, ++(intVec.begin()));
			Assert::ExpectException<runtime_error>(intIncrement);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator1;
			Vector<int32_t*>::Iterator pointerator2;
			auto pointerIncrement = [&pointerator1] {pointerator1++; };
			Assert::ExpectException<runtime_error>(pointerIncrement);
			pointerator1 = pointerVec.pushBack(test);
			pointerVec.pushBack(test + 1);
			Assert::AreEqual(pointerator1, pointerVec.begin());
			pointerator2 = pointerator1++;
			Assert::AreEqual(pointerator2, pointerVec.begin());
			Assert::AreEqual(pointerator1, ++(pointerVec.begin()));
			Assert::ExpectException<runtime_error>(pointerIncrement);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator1;
			auto fooIncrement = [&footerator1] {footerator1++; };
			Assert::ExpectException<runtime_error>(fooIncrement);
			footerator1 = fooVec.pushBack(Foo(a));
			fooVec.pushBack(Foo(b));
			Assert::AreEqual(footerator1, fooVec.begin());
			Vector<Foo>::Iterator footerator2 = footerator1++;
			Assert::AreEqual(footerator2, fooVec.begin());
			Assert::AreEqual(footerator1, ++(fooVec.begin()));
			Assert::ExpectException<runtime_error>(fooIncrement);
		}

		TEST_METHOD(dereferenceOperatorTest)
		{
			//Integer
			int32_t a = 10;
			Vector<int32_t> intVec;
			Vector<int32_t>::Iterator interator;
			auto intDereference = [&interator] {*interator; };
			Assert::ExpectException<runtime_error>(intDereference);
			interator = intVec.pushBack(a);
			Assert::AreEqual(*interator, a);

			//Pointer
			int32_t* test = new int32_t;
			Vector<int32_t*> pointerVec;
			Vector<int32_t*>::Iterator pointerator;
			auto pointerDereference = [&pointerator] {*pointerator; };
			Assert::ExpectException<runtime_error>(pointerDereference);
			pointerator = pointerVec.pushBack(test);
			Assert::AreEqual(*pointerator, test);
			delete test;

			//Foo
			Vector<Foo> fooVec;
			Vector<Foo>::Iterator footerator;
			auto fooDereference = [&footerator] {*footerator; };
			Assert::ExpectException<runtime_error>(fooDereference);
			footerator = fooVec.pushBack(Foo(a));
			Assert::AreEqual(*footerator, Foo(a));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorIteratorTest::sStartMemState;
}