#include "pch.h"

#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the SList class using an integer list, a pointer list and
	//a list of a custom class Foo.
	TEST_CLASS(SListTest)
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

		//The test checks if the constructor initializes the list the way it's supposed to.
		TEST_METHOD(constructorTest)
		{
			//Test constructor with integer (32 bits).
			SList<int32_t> intList;

			Assert::AreEqual(intList.size(), static_cast<uint32_t>(0));
			auto frontOfIntList = [&intList] {intList.front(); };
			Assert::ExpectException<runtime_error>(frontOfIntList);
			auto backOfIntList = [&intList] {intList.back(); };
			Assert::ExpectException<runtime_error>(backOfIntList);

			//Test constructor with pointer.
			SList<int32_t*> pointerList;

			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(0));
			auto frontOfPointerList = [&pointerList] {pointerList.front(); };
			Assert::ExpectException<runtime_error>(frontOfPointerList);
			auto backOfPointerList = [&pointerList] {pointerList.back(); };
			Assert::ExpectException<runtime_error>(backOfPointerList);

			//Test constructor with Foo
			SList<Foo> fooList;

			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));
			auto frontOfFooList = [&fooList] {fooList.front(); };
			Assert::ExpectException<runtime_error>(frontOfFooList);
			auto backOfFooList = [&fooList] {fooList.back(); };
			Assert::ExpectException<runtime_error>(backOfFooList);
		}

		//The test checks if the Copy Constructor copies a list to another list properly.
		TEST_METHOD(copyConstructorTest)
		{
			//Integer
			int32_t a = 10;
			SList<int32_t> intList1;
			intList1.pushFront(a);

			SList<int32_t> intList2 = intList1;

			Assert::AreEqual(intList1.size(), intList2.size());
			Assert::AreEqual(intList1.front(), intList2.front());

			//Pointer
			SList<int32_t*> pointerList1;

			int32_t* test = new int32_t;
			pointerList1.pushFront(test);

			SList<int32_t*> pointerList2 = pointerList1;

			Assert::AreEqual(pointerList1.size(), pointerList2.size());
			Assert::AreEqual(pointerList1.front(), pointerList2.front());
			
			delete test;

			//Class Foo
			SList<Foo> fooList1;
			fooList1.pushFront(Foo(a));

			SList<Foo> fooList2 = fooList1;

			Assert::AreEqual(fooList1.size(), fooList2.size());
			Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		//The test method tests the assignment operator by assigning a non-empty list to an empty one.
		TEST_METHOD(defaultAssignmentOperatorTest)
		{
			//Integer
			SList<int32_t> intList1;
			int32_t a = 10;
			intList1.pushFront(a);

			SList<int32_t> intList2;
			intList2 = intList1;

			Assert::AreEqual(intList1.size(), intList2.size());
			Assert::AreEqual(intList1.front(), intList2.front());

			//Pointer
			SList<int32_t*> pointerList1;

			int32_t* test = new int32_t;
			pointerList1.pushFront(test);

			SList<int32_t*> pointerList2;
			pointerList2 = pointerList1;

			Assert::AreEqual(pointerList1.size(), pointerList2.size());
			Assert::AreEqual(pointerList1.front(), pointerList2.front());

			delete test;

			//Class Foo
			SList<Foo> fooList1;
			fooList1.pushFront(Foo(a));

			SList<Foo> fooList2;
			fooList2 = fooList1;

			Assert::AreEqual(fooList1.size(), fooList2.size());
			Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		//Test assignment of a non-empty list to another non-empty list with different data in it.
		TEST_METHOD(nonEmptyListAssignmentOperatorTest)
		{
				//Integer
				SList<int32_t> intList1;
				int32_t a = 10;
				int32_t b = 10;

				intList1.pushFront(a);

				SList<int32_t> intList2;
				intList2.pushFront(b);

				intList2 = intList1;

				Assert::AreEqual(intList1.size(), intList2.size());
				Assert::AreEqual(intList1.front(), intList2.front());

				//Pointer
				SList<int32_t*> pointerList1;

				int32_t* test = new int32_t;
				pointerList1.pushFront(test);

				SList<int32_t*> pointerList2;
				pointerList2.pushFront(test + 1);

				pointerList2 = pointerList1;

				Assert::AreEqual(pointerList1.size(), pointerList2.size());
				Assert::AreEqual(pointerList1.front(), pointerList2.front());

				delete test;

				//Class Foo
				SList<Foo> fooList1;
				fooList1.pushFront(Foo(a));

				SList<Foo> fooList2;
				fooList2.pushFront(Foo(b));

				fooList2 = fooList1;

				Assert::AreEqual(fooList1.size(), fooList2.size());
				Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		//Test move semantics
		TEST_METHOD(moveSemeanticsTest)
		{
			//Integer
			SList<int32_t> intList1;
			int32_t a = 10;
			int32_t b = 10;

			intList1.pushFront(a);

			SList<int32_t> intList2 = move(intList1);
			Assert::AreEqual(intList1.size(), 0U);
			Assert::AreEqual(intList2.front(), a);
			Assert::AreEqual(intList2.size(), 1U);

			intList2.pushFront(b);

			intList1 = move(intList2);
			Assert::AreEqual(intList2.size(), 0U);
			Assert::AreEqual(intList1.front(), a);
			Assert::AreEqual(intList1.size(), 2U);


			//Pointer
			SList<int32_t*> pointerList1;

			int32_t* test = new int32_t;
			pointerList1.pushFront(test);

			SList<int32_t*> pointerList2 = move(pointerList1);
			Assert::AreEqual(pointerList1.size(), 0U);
			Assert::AreEqual(pointerList2.size(), 1U);
			Assert::AreEqual(pointerList2.front(), test);

			pointerList2.pushFront(test + 1);
			pointerList1 = move(pointerList2);

			Assert::AreNotEqual(pointerList1.size(), pointerList2.size());
			Assert::AreEqual(pointerList1.front(), test + 1);

			delete test;

			//Class Foo
			SList<Foo> fooList1;
			fooList1.pushFront(Foo(a));

			SList<Foo> fooList2 = move(fooList1);
			Assert::AreEqual(fooList1.size(), 0U);
			Assert::AreEqual(fooList2.size(), 1U);
			Assert::AreEqual(fooList2.front(), Foo(a));

			fooList2.pushFront(Foo(b));
			fooList1 = move(fooList2);

			Assert::AreNotEqual(fooList1.size(), fooList2.size());
			Assert::AreEqual(fooList1.front(), Foo(b));
		}

		//Test the push front method in the SList class.
		//Tests both pushFront on empty list and on a non-empty list.
		TEST_METHOD(pushFrontTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			intList.pushFront(a);
			Assert::AreEqual(intList.front(), a);

			intList.pushFront(b);
			Assert::AreEqual(intList.front(), b);

			//Pointer
			SList<int32_t*> pointerList;

			int32_t* test = new int32_t;
			pointerList.pushFront(test);

			Assert::AreEqual(pointerList.front(), test);

			pointerList.pushFront(test+1);
			Assert::AreEqual(pointerList.front(), (test+1));

			delete test;

			//Class Foo
			SList<Foo> fooList;

			fooList.pushFront(Foo(a));
			Assert::AreEqual(fooList.front(), Foo(a));

			fooList.pushFront(Foo(b));
			Assert::AreEqual(fooList.front(), Foo(b));
		}

		//Tests the popFront method on lists that are empty and then on non-empty lists.
		TEST_METHOD(popFrontTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			
			auto popNullFromInt = [&intList] {intList.popFront(); };
			Assert::ExpectException<runtime_error>(popNullFromInt);

			intList.pushFront(a);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intList.popFront(), a);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(0));

			intList.pushFront(a);
			intList.pushFront(b);

			Assert::AreEqual(intList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(intList.popFront(), b);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(1));

			//Pointer
			SList<int32_t*> pointerList;

			auto popNullFromPointer = [&pointerList] {pointerList.popFront(); };
			Assert::ExpectException<runtime_error>(popNullFromPointer);

			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(pointerList.popFront(), test);
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(0));

			pointerList.pushFront(test);
			pointerList.pushFront(test + 1);

			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(pointerList.popFront(), (test + 1));
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(1));

			delete test;

			//Class Foo
			SList<Foo> fooList;

			auto popNullFromFoo = [&fooList] {fooList.popFront(); };
			Assert::ExpectException<runtime_error>(popNullFromFoo);

			fooList.pushFront(Foo(a));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooList.popFront(), Foo(a));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));

			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));

			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(fooList.popFront(), Foo(b));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
		}

		//Tests pushBack on an empty and then a non-empty list.
		TEST_METHOD(pushBackTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;

			SList<int32_t> intList;
			intList.pushBack(a);
			Assert::AreEqual(intList.back(), a);

			intList.pushBack(b);
			Assert::AreEqual(intList.back(), b);

			//Pointer
			SList<int32_t*> pointerList;

			int32_t* test = new int32_t;
			pointerList.pushBack(test);
			Assert::AreEqual(pointerList.back(), test);

			pointerList.pushBack(test + 1);
			Assert::AreEqual(pointerList.back(), (test + 1));

			delete test;

			//Class Foo
			SList<Foo> fooList;

			fooList.pushBack(Foo(a));
			Assert::AreEqual(fooList.back(), Foo(a));

			fooList.pushBack(Foo(b));
			Assert::AreEqual(fooList.back(), Foo(b));
		}

		//Tests the clear method on a list with size 2.
		TEST_METHOD(clearListTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;

			intList.pushFront(a);
			intList.pushFront(b);

			Assert::AreEqual(intList.size(), static_cast<uint32_t>(2));
			intList.clear();
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(0));

			//Pointer
			SList<int32_t*> pointerList;

			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			pointerList.pushFront(test);

			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(2));
			pointerList.clear();
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(0));
			delete test;

			//Class Foo
			SList<Foo> fooList;
			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));

			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(2));
			fooList.clear();
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));
		}

		//Tests both cases of the boolean method isEmpty.
		TEST_METHOD(isEmptyTest)
		{
			//Integer
			int32_t a = 10;

			SList<int32_t> intList;
			Assert::IsTrue(intList.isEmpty());
			intList.pushFront(a);
			Assert::IsFalse(intList.isEmpty());

			//Pointer
			SList<int32_t*> pointerList;
			Assert::IsTrue(pointerList.isEmpty());

			int32_t* test = new int32_t;
			pointerList.pushFront(test);

			Assert::IsFalse(pointerList.isEmpty());
			delete test;

			//Class Foo
			SList<Foo> fooList;
			Assert::IsTrue(fooList.isEmpty());

			fooList.pushFront(Foo(a));
			Assert::IsFalse(fooList.isEmpty());
		}

		//Tests the front method on an empty list and then a non-empty list.
		TEST_METHOD(frontTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;

			SList<int32_t> intList;
			auto frontOfInt = [&intList] {intList.front(); };
			Assert::ExpectException<runtime_error>(frontOfInt);

			intList.pushFront(a);
			intList.pushFront(b);
			Assert::AreEqual(intList.front(), b);

			//Pointer
			SList<int32_t*> pointerList;
			auto frontOfPointer = [&pointerList] {pointerList.front(); };
			Assert::ExpectException<runtime_error>(frontOfPointer);

			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			pointerList.pushFront(test + 1);
			Assert::AreEqual(pointerList.front(), (test+1));
			
			delete test;

			//Class Foo
			SList<Foo> fooList;
			
			auto frontOfFoo = [&fooList] {fooList.front(); };
			Assert::ExpectException<runtime_error>(frontOfFoo);

			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));
			Assert::AreEqual(fooList.front(), Foo(b));
		}

		//Tests the back method on an empty and a non-empty list.
		TEST_METHOD(backTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;

			SList<int32_t> intList;
			auto backOfInt = [&intList] {intList.back(); };
			Assert::ExpectException<runtime_error>(backOfInt);

			intList.pushFront(a);
			intList.pushFront(b);
			Assert::AreEqual(intList.back(), a);

			//Pointer
			SList<int32_t*> pointerList;
			auto backOfPointer = [&pointerList] {pointerList.back(); };
			Assert::ExpectException<runtime_error>(backOfPointer);

			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			pointerList.pushFront(test + 1);
			Assert::AreEqual(pointerList.back(), (test));

			delete test;

			//Class Foo
			SList<Foo> fooList;

			auto backOfFoo = [&fooList] {fooList.back(); };
			Assert::ExpectException<runtime_error>(backOfFoo);

			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));
			Assert::AreEqual(fooList.back(), Foo(a));
		}

		//Similar to the frontTest, but here, we check the const version of the method on const lists.
		TEST_METHOD(constFrontTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			const SList<int32_t> emptyIntList;
			auto frontOfInt = [&emptyIntList] {emptyIntList.front(); };
			Assert::ExpectException<runtime_error>(frontOfInt);

			SList<int32_t> intList;
			intList.pushFront(a);
			intList.pushFront(b);

			const SList<int32_t> constIntList = intList;
			Assert::AreEqual(constIntList.front(), b);

			//Pointer
			const SList<int32_t*> emptyPointerList;
			auto frontOfPointer = [&emptyPointerList] {emptyPointerList.front(); };
			Assert::ExpectException<runtime_error>(frontOfPointer);

			SList<int32_t*> pointerList;
			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			pointerList.pushFront(test + 1);

			const SList<int32_t*> constPointerList = pointerList;
			Assert::AreEqual(constPointerList.front(), (test + 1));

			delete test;

			//Class Foo
			const SList<Foo> emptyFooList;
			auto frontOfFoo = [&emptyFooList] {emptyFooList.front(); };
			Assert::ExpectException<runtime_error>(frontOfFoo);

			SList<Foo> fooList;
			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));

			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(constFooList.front(), Foo(b));
		}

		//Const lists used to test the const version of back.
		TEST_METHOD(constBackTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			const SList<int32_t> emptyIntList;
			auto backOfInt = [&emptyIntList] {emptyIntList.back(); };
			Assert::ExpectException<runtime_error>(backOfInt);

			SList<int32_t> intList;
			intList.pushFront(a);
			intList.pushFront(b);

			const SList<int32_t> constIntList = intList;
			Assert::AreEqual(constIntList.back(), a);

			//Pointer
			const SList<int32_t*> emptyPointerList;
			auto backOfPointer = [&emptyPointerList] {emptyPointerList.back(); };
			Assert::ExpectException<runtime_error>(backOfPointer);

			SList<int32_t*> pointerList;
			int32_t* test = new int32_t;
			pointerList.pushFront(test);
			pointerList.pushFront(test + 1);

			const SList<int32_t*> constPointerList = pointerList;
			Assert::AreEqual(constPointerList.back(), test);

			delete test;

			//Class Foo
			const SList<Foo> emptyFooList;
			auto backOfFoo = [&emptyFooList] {emptyFooList.back(); };
			Assert::ExpectException<runtime_error>(backOfFoo);

			SList<Foo> fooList;
			fooList.pushFront(Foo(a));
			fooList.pushFront(Foo(b));

			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(constFooList.back(), Foo(a));
		}

		TEST_METHOD(sListBeginTest)
		{
			//Integer
			int32_t a = 0;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt1 = intList.pushFront(a);
			Assert::AreEqual(intIt1, intList.begin());
			SList<int32_t>::Iterator intIt2;
			Assert::AreNotEqual(intIt2, intList.begin());

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt1 = pointerList.pushFront(test);
			Assert::AreEqual(pointerIt1, pointerList.begin());
			SList<int32_t*>::Iterator pointerIt2;
			Assert::AreNotEqual(pointerIt2, pointerList.begin());
			delete test;

			//Foo
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt1 = fooList.pushFront(Foo(a));
			Assert::AreEqual(fooIt1, fooList.begin());
			SList<Foo>::Iterator fooIt2;
			Assert::AreNotEqual(fooIt2, fooList.begin());
		}

		TEST_METHOD(sListEndTest)
		{
			//Integer
			int32_t a = 0;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt1 = intList.pushFront(a);
			Assert::AreNotEqual(intIt1, intList.end());

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt1 = pointerList.pushFront(test);
			Assert::AreNotEqual(pointerIt1, pointerList.end());
			delete test;

			//Foo
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt1 = fooList.pushFront(Foo(a));
			Assert::AreNotEqual(fooIt1, fooList.end());
		}

		TEST_METHOD(insertAfterTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			int32_t c = 30;
			SList<int32_t> intList1;
			SList<int32_t>::Iterator intIt1 = intList1.begin();

			//insertAfter in empty list.
			intIt1 = intList1.insertAfter(intIt1, a);
			Assert::AreEqual(intList1.front(), a);

			//insertAfter in list with one item.
			intList1.insertAfter(intIt1, b);
			Assert::AreEqual(intList1.back(), b);

			//insertAfter with iterator belonging to another list.
			SList<int32_t> intList2;
			SList<int32_t>::Iterator intIt2 = intList2.begin();
			auto intInsertException = [&intList1, &intIt2, &c] {intList1.insertAfter(intIt2, c); };
			Assert::ExpectException<runtime_error>(intInsertException);
			//End Integer

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList1;
			SList<int32_t*>::Iterator pointerIt1 = pointerList1.begin();

			//insertAfter in empty list.
			pointerIt1 = pointerList1.insertAfter(pointerIt1, test);
			Assert::AreEqual(pointerList1.front(), test);

			//insertAfter in list with one item.
			pointerList1.insertAfter(pointerIt1, (test + 1));
			Assert::AreEqual(pointerList1.back(), (test + 1));

			//insertAfter with iterator belonging to another list.
			SList<int32_t*> pointerList2;
			SList<int32_t*>::Iterator pointerIt2 = pointerList2.begin();
			auto pointerInsertException = [&pointerList1, &pointerIt2, &test] {pointerList1.insertAfter(pointerIt2, (test + 2)); };
			Assert::ExpectException<runtime_error>(pointerInsertException);
			delete test;
			//End Pointer test

			//Foo
			SList<Foo> fooList1;
			SList<Foo>::Iterator fooIt1 = fooList1.begin();

			//insertAfter in empty list.
			fooIt1 = fooList1.insertAfter(fooIt1, Foo(a));
			Assert::AreEqual(fooList1.front(), Foo(a));

			//insertAfter in list with one item.
			fooList1.insertAfter(fooIt1, Foo(b));
			Assert::AreEqual(fooList1.back(), Foo(b));

			//insertAfter with iterator belonging to another list.
			SList<Foo> fooList2;
			SList<Foo>::Iterator fooIt2 = fooList2.begin();
			auto fooInsertException = [&fooList1, &fooIt2, &c] {fooList1.insertAfter(fooIt2, Foo(c)); };
			Assert::ExpectException<runtime_error>(fooInsertException);
			//End Foo
		}

		TEST_METHOD(sListRemoveTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt = intList.begin();
			//Test for an empty list.
			intList.remove(a);

			//Test for a list with a single item.
			intIt = intList.insertAfter(intIt, a);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intList.find(a), intIt);
			intList.remove(a);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(0));
			Assert::AreEqual(intList.find(a), intList.begin());

			//Test for a populated list.
			intIt = intList.insertAfter(intList.begin(), a);
			intIt = intList.insertAfter(intIt, b);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(intList.find(b), intIt);
			intList.remove(b);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intList.find(b), intList.end());
			//End Integer

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt = pointerList.begin();
			//Test for an empty list.
			pointerList.remove(test);

			//Test for a list with a single item.
			pointerIt = pointerList.insertAfter(pointerIt, test);
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(pointerList.find(test), pointerIt);
			pointerList.remove(test);
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(0));
			Assert::AreEqual(pointerList.find(test), pointerList.begin());

			//Test for a populated list.
			pointerIt = pointerList.insertAfter(pointerList.begin(), test);
			pointerIt = pointerList.insertAfter(pointerIt, (test + 1));
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(pointerList.find(test + 1), pointerIt);
			pointerList.remove(test + 1);
			Assert::AreEqual(pointerList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(pointerList.find(test + 1), pointerList.end());
			delete test;
			//End Pointer

			//Foo Test
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt = fooList.begin();
			//Test for an empty list.
			fooList.remove(Foo(a));

			//Test for a list with a single item.
			fooIt = fooList.insertAfter(fooIt, a);
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooList.find(Foo(a)), fooIt);
			fooList.remove(Foo(a));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));
			Assert::AreEqual(fooList.find(Foo(a)), fooList.begin());

			//Test for a populated list.
			fooIt = fooList.insertAfter(fooList.begin(), Foo(a));
			fooIt = fooList.insertAfter(fooIt, Foo(b));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(fooList.find(Foo(b)), fooIt);
			fooList.remove(Foo(b));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooList.find(Foo(b)), fooList.end());
			//End Foo test
		}

		TEST_METHOD(sListFindTest)
		{
			//Integer test
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt = intList.begin();
			//Test with empty list.
			Assert::AreEqual(intList.find(a), intList.end());
			//Test with populated list.
			intIt = intList.insertAfter(intIt, a);
			intIt = intList.insertAfter(intIt, b);
			Assert::AreEqual(intList.find(b), intIt);
			//End Integer test

			//Pointer test
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt = pointerList.begin();
			//Test with empty list.
			Assert::AreEqual(pointerList.find(test), pointerList.end());
			//Test with populated list.
			pointerIt = pointerList.insertAfter(pointerIt, test);
			pointerIt = pointerList.insertAfter(pointerIt, test + 1);
			Assert::AreEqual(pointerList.find(test + 1), pointerIt);
			delete test;
			//End Pointer test

			//Foo Test
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt = fooList.begin();
			//Test with empty list.
			Assert::AreEqual(fooList.find(Foo(a)), fooList.end());
			//Test with populated list.
			fooIt = fooList.insertAfter(fooIt, Foo(a));
			fooIt = fooList.insertAfter(fooIt, Foo(b));
			Assert::AreEqual(fooList.find(Foo(b)), fooIt);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}