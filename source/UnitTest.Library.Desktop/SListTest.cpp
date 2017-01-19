#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"
#include <cstdint>
#include <exception>

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
			SList<int32_t> intList1;
			intList1.pushFront(10);

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
			fooList1.pushFront(Foo(10));

			SList<Foo> fooList2 = fooList1;

			Assert::AreEqual(fooList1.size(), fooList2.size());
			Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		TEST_METHOD(defaultAssignmentOperatorTest)
		{
			//Integer
			SList<int32_t> intList1;

			intList1.pushFront(10);

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
			fooList1.pushFront(Foo(10));

			SList<Foo> fooList2;
			fooList2 = fooList1;

			Assert::AreEqual(fooList1.size(), fooList2.size());
			Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		TEST_METHOD(nonEmptyListAssignmentOperatorTest)
		{
				//Integer
				SList<int32_t> intList1;

				intList1.pushFront(10);

				SList<int32_t> intList2;
				intList2.pushFront(20);

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
				fooList1.pushFront(Foo(10));

				SList<Foo> fooList2;
				fooList2.pushFront(Foo(20));

				fooList2 = fooList1;

				Assert::AreEqual(fooList1.size(), fooList2.size());
				Assert::AreEqual(fooList1.front(), fooList2.front());
		}

		TEST_METHOD(pushFrontTest)
		{
			//Integer
			SList<int32_t> intList;
			intList.pushFront(10);
			Assert::AreEqual(intList.front(), static_cast<int32_t>(10));

			intList.pushFront(20);
			Assert::AreEqual(intList.front(), static_cast<int32_t>(20));

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

			fooList.pushFront(Foo(10));
			Assert::AreEqual(fooList.front(), Foo(10));

			fooList.pushFront(Foo(20));
			Assert::AreEqual(fooList.front(), Foo(20));
		}

		TEST_METHOD(popFrontTest)
		{
			//Integer
			SList<int32_t> intList;
			
			auto popNullFromInt = [&intList] {intList.popFront(); };
			Assert::ExpectException<runtime_error>(popNullFromInt);

			intList.pushFront(10);
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(intList.popFront(), static_cast<int32_t>(10));
			Assert::AreEqual(intList.size(), static_cast<uint32_t>(0));

			intList.pushFront(10);
			intList.pushFront(20);

			Assert::AreEqual(intList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(intList.popFront(), static_cast<int32_t>(20));
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

			fooList.pushFront(Foo(10));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
			Assert::AreEqual(fooList.popFront(), Foo(10));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));

			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));

			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(2));
			Assert::AreEqual(fooList.popFront(), Foo(20));
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(1));
		}

		TEST_METHOD(pushBackTest)
		{
			//Integer
			SList<int32_t> intList;
			intList.pushBack(10);
			Assert::AreEqual(intList.back(), static_cast<int32_t>(10));

			intList.pushBack(20);
			Assert::AreEqual(intList.back(), static_cast<int32_t>(20));

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

			fooList.pushBack(Foo(10));
			Assert::AreEqual(fooList.back(), Foo(10));

			fooList.pushBack(Foo(20));
			Assert::AreEqual(fooList.back(), Foo(20));
		}

		TEST_METHOD(clearListTest)
		{
			//Integer
			SList<int32_t> intList;

			intList.pushFront(10);
			intList.pushFront(20);

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
			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));

			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(2));
			fooList.clear();
			Assert::AreEqual(fooList.size(), static_cast<uint32_t>(0));
		}

		TEST_METHOD(isEmptyTest)
		{
			//Integer
			SList<int32_t> intList;
			Assert::IsTrue(intList.isEmpty());
			intList.pushFront(10);
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

			fooList.pushFront(Foo(10));
			Assert::IsFalse(fooList.isEmpty());
		}

		TEST_METHOD(frontTest)
		{
			//Integer
			SList<int32_t> intList;
			auto frontOfInt = [&intList] {intList.front(); };
			Assert::ExpectException<runtime_error>(frontOfInt);

			intList.pushFront(10);
			intList.pushFront(20);
			Assert::AreEqual(intList.front(), static_cast<int32_t>(20));

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

			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));
			Assert::AreEqual(fooList.front(), Foo(20));
		}

		TEST_METHOD(backTest)
		{
			//Integer
			SList<int32_t> intList;
			auto backOfInt = [&intList] {intList.back(); };
			Assert::ExpectException<runtime_error>(backOfInt);

			intList.pushFront(10);
			intList.pushFront(20);
			Assert::AreEqual(intList.back(), static_cast<int32_t>(10));

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

			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));
			Assert::AreEqual(fooList.back(), Foo(10));
		}

		//TODO--Complete const tests.
		TEST_METHOD(constFrontTest)
		{
			//Integer
			const SList<int32_t> emptyIntList;
			auto frontOfInt = [&emptyIntList] {emptyIntList.front(); };
			Assert::ExpectException<runtime_error>(frontOfInt);

			SList<int32_t> intList;
			intList.pushFront(10);
			intList.pushFront(20);

			const SList<int32_t> constIntList = intList;
			Assert::AreEqual(constIntList.front(), static_cast<int32_t>(20));

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
			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));

			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(constFooList.front(), Foo(20));
		}

		TEST_METHOD(constBackTest)
		{
			//Integer
			const SList<int32_t> emptyIntList;
			auto backOfInt = [&emptyIntList] {emptyIntList.back(); };
			Assert::ExpectException<runtime_error>(backOfInt);

			SList<int32_t> intList;
			intList.pushFront(10);
			intList.pushFront(20);

			const SList<int32_t> constIntList = intList;
			Assert::AreEqual(constIntList.back(), static_cast<int32_t>(10));

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
			fooList.pushFront(Foo(10));
			fooList.pushFront(Foo(20));

			const SList<Foo> constFooList = fooList;
			Assert::AreEqual(constFooList.back(), Foo(10));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}