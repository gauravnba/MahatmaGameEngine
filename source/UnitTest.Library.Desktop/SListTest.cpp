#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"

//Create ToString function for the Foo class.
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<Foo>(const Foo& obj)
			{
				std::uint32_t returnVal = obj.getVar();
				return std::to_wstring(returnVal);
			}
		}
	}
}

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

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}