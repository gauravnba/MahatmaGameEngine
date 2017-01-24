#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"
#include <cstdint>
#include <exception>

//Create ToString function for the Foo class.
namespace Microsoft 
{
	namespace VisualStudio 
	{
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

//Create ToString function for the integer Iterator class.
namespace Microsoft 
{
	namespace VisualStudio 
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<std::int32_t>::Iterator>(const MahatmaGameEngine::SList<std::int32_t>::Iterator& obj)
			{
				std::int32_t returnVal = *obj;
				return std::to_wstring(returnVal);
			}
		}
	}
}

//Created ToString function for the pointer Iterator class.
namespace Microsoft 
{
	namespace VisualStudio 
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<std::int32_t*>::Iterator>(const MahatmaGameEngine::SList<std::int32_t*>::Iterator& obj)
			{
				std::int32_t* returnVal = *obj;
				return std::to_wstring(*returnVal);
			}
		}
	}
}

//Created ToString function for the Foo Iterator class
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<Foo>::Iterator>(const MahatmaGameEngine::SList<Foo>::Iterator& obj)
			{
				Foo returnVal = *obj;
				return std::to_wstring(returnVal.getVar());
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
	TEST_CLASS(SListIteratorTest)
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

		TEST_METHOD(constructorTest)
		{
			//Integer. Wanted to name it the interator. YW.
			SList<int32_t>::Iterator intIt;
			auto nullIt = [&intIt] { ++intIt; };
			Assert::ExpectException<runtime_error>(nullIt);

			//Pointer. This one could have been the pointerator.
			SList<int32_t*>::Iterator pointerIt;
			auto nullPointer = [&pointerIt] { ++pointerIt; };
			Assert::ExpectException<runtime_error>(nullPointer);

			//Foo. And this one was going to be the Footerator. IKR
			SList<Foo>::Iterator fooIt;
			auto nullFoo = [&fooIt] { ++fooIt; };
			Assert::ExpectException<runtime_error>(nullFoo);
		}

		TEST_METHOD(copyConstructorTest)
		{
			//Integer
			int32_t a = 10;
			SList<int32_t> intList;
			intList.pushFront(a);
			
			SList<int32_t>::Iterator intIt = intList.begin();
			Assert::AreEqual(intList.begin(), intIt);

			//Pointer
			SList<int32_t*> pointerList;
			int32_t* test = new int32_t;
			pointerList.pushFront(test);

			SList<int32_t*>::Iterator pointerIt = pointerList.begin();
			Assert::AreEqual(pointerList.begin(), pointerIt);
			delete test;

			//Foo
			SList<Foo> fooList;
			fooList.pushFront(Foo(a));

			SList<Foo>::Iterator fooIt = fooList.begin();
			Assert::AreEqual(fooList.begin(), fooIt);
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt1 = intList.pushBack(a);
			SList<int32_t>::Iterator intIt2 = intList.pushBack(b);

			intIt1 = intIt2;
			Assert::AreEqual(intIt1, intIt2);

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt1 = pointerList.pushBack(test);
			SList<int32_t*>::Iterator pointerIt2 = pointerList.pushBack(test + 1);

			pointerIt1 = pointerIt2;
			Assert::AreEqual(pointerIt1, pointerIt2);
			delete test;

			//Foo
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt1 = fooList.pushBack(Foo(a));
			SList<Foo>::Iterator fooIt2 = fooList.pushBack(Foo(b));

			fooIt1 = fooIt2;
			Assert::AreEqual(fooIt1, fooIt2);
		}

		TEST_METHOD(separateListAssignmentOpTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList1;
			SList<int32_t> intList2;
			SList<int32_t>::Iterator intIt1 = intList1.pushBack(a);
			SList<int32_t>::Iterator intIt2 = intList2.pushBack(b);

			auto assignInt = [&intIt1, &intIt2] {intIt1 = intIt2; };
			Assert::ExpectException<runtime_error>(assignInt);

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList1;
			SList<int32_t*> pointerList2;
			SList<int32_t*>::Iterator pointerIt1 = pointerList1.pushBack(test);
			SList<int32_t*>::Iterator pointerIt2 = pointerList2.pushBack(test + 1);

			auto assignPointer = [&pointerIt1, &pointerIt2] {pointerIt1 = pointerIt2; };
			Assert::ExpectException<runtime_error>(assignPointer);
			delete test;

			//Foo
			SList<Foo> fooList1;
			SList<Foo> fooList2;
			SList<Foo>::Iterator fooIt1 = fooList1.pushBack(Foo(a));
			SList<Foo>::Iterator fooIt2 = fooList2.pushBack(Foo(b));

			auto assignFoo = [&fooIt1, &fooIt2] {fooIt1 = fooIt2; };
			Assert::ExpectException<runtime_error>(assignFoo);
		}

		TEST_METHOD(equalityOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;

			//Check for false.
			SList<int32_t>::Iterator intIt1 = intList.pushBack(a);
			SList<int32_t>::Iterator intIt2 = intList.pushBack(b);
			Assert::IsFalse(intIt1 == intIt2);

			//Use assignment operator to really make sure equality works.
			intIt1 = intIt2;
			Assert::IsTrue(intIt1 == intIt2);
			//End Integer Test

			//Pointer Test
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;

			//Check for false
			SList<int32_t*>::Iterator pointerIt1 = pointerList.pushBack(test);
			SList<int32_t*>::Iterator pointerIt2 = pointerList.pushBack(test + 1);
			Assert::IsFalse(pointerIt1 == pointerIt2);

			//Use assignment operator and then check for equality.
			pointerIt1 = pointerIt2;
			Assert::IsTrue(pointerIt1 == pointerIt2);
			delete test;
			//End Pointer Test

			//Foo test.
			SList<Foo> fooList;

			//Check false condition
			SList<Foo>::Iterator fooIt1 = fooList.pushBack(Foo(a));
			SList<Foo>::Iterator fooIt2 = fooList.pushBack(Foo(b));
			Assert::IsFalse(fooIt1 == fooIt2);

			//Check for true
			fooIt1 = fooIt2;
			Assert::IsTrue(fooIt1 == fooIt2);
			//End Foo test
		}

		TEST_METHOD(inequalityOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;

			//Check for false.
			SList<int32_t>::Iterator intIt1 = intList.pushBack(a);
			SList<int32_t>::Iterator intIt2 = intList.pushBack(b);
			Assert::IsTrue(intIt1 != intIt2);

			//Use assignment operator to really make sure equality works.
			intIt1 = intIt2;
			Assert::IsFalse(intIt1 != intIt2);
			//End Integer

			//Pointer Test
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;

			//Check for false
			SList<int32_t*>::Iterator pointerIt1 = pointerList.pushBack(test);
			SList<int32_t*>::Iterator pointerIt2 = pointerList.pushBack(test + 1);
			Assert::IsTrue(pointerIt1 != pointerIt2);

			//Use assignment operator and then check for equality.
			pointerIt1 = pointerIt2;
			Assert::IsFalse(pointerIt1 != pointerIt2);
			delete test;
			//End Pointer

			//Foo test.
			SList<Foo> fooList;

			//Check false condition
			SList<Foo>::Iterator fooIt1 = fooList.pushBack(Foo(a));
			SList<Foo>::Iterator fooIt2 = fooList.pushBack(Foo(b));
			Assert::IsTrue(fooIt1 != fooIt2);

			//Check for true
			fooIt1 = fooIt2;
			Assert::IsFalse(fooIt1 != fooIt2);
			//End Foo Test
		}

		TEST_METHOD(preIncrementOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt1;

			//Check for null increment exception
			auto intNullIncrement = [&intIt1] {++intIt1; };
			Assert::ExpectException<runtime_error>(intNullIncrement);

			//Check for iterator at end exception
			intIt1 = intList.pushFront(a);
			Assert::ExpectException<runtime_error>(intNullIncrement);

			//Check for functionality of pre-increment operator.
			intList.pushBack(b);
			SList<int32_t>::Iterator intIt2 = ++intIt1;
			Assert::AreEqual(intIt1, intIt2);
			Assert::AreNotEqual(intIt1, intList.begin());
			//End Integer test

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt1;

			//Check for null increment exception
			auto pointerNullIncrement = [&pointerIt1] {++pointerIt1; };
			Assert::ExpectException<runtime_error>(pointerNullIncrement);

			//Check for iterator at end exception
			pointerIt1 = pointerList.pushFront(test);
			Assert::ExpectException<runtime_error>(pointerNullIncrement);

			//Check for functionality of pre-increment operator.
			pointerList.pushBack(test + 1);
			SList<int32_t*>::Iterator pointerIt2 = ++pointerIt1;
			Assert::AreEqual(pointerIt1, pointerIt2);
			Assert::AreNotEqual(pointerIt1, pointerList.begin());
			delete test;
			//End Pointer test.

			//Foo test
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt1;

			//Check for null increment exception
			auto fooNullIncrement = [&fooIt1] {++fooIt1; };
			Assert::ExpectException<runtime_error>(fooNullIncrement);

			//Check for iterator at end exception
			fooIt1 = fooList.pushFront(Foo(a));
			Assert::ExpectException<runtime_error>(fooNullIncrement);

			//Check for functionality of pre-increment operator.
			fooList.pushBack(Foo(b));
			SList<Foo>::Iterator fooIt2 = ++fooIt1;
			Assert::AreEqual(fooIt1, fooIt2);
			Assert::AreNotEqual(fooIt1, fooList.begin());
			//End Foo test
		}

		TEST_METHOD(postIncrementOperatorTest)
		{
			//Integer
			int32_t a = 10;
			int32_t b = 20;
			SList<int32_t> intList;
			SList<int32_t>::Iterator intIt1;

			//Check for null increment exception
			auto intNullIncrement = [&intIt1] {intIt1++; };
			Assert::ExpectException<runtime_error>(intNullIncrement);

			//Check for iterator at end exception
			intIt1 = intList.pushFront(a);
			Assert::ExpectException<runtime_error>(intNullIncrement);

			//Check for functionality of post-increment operator.
			intList.pushBack(b);
			SList<int32_t>::Iterator intIt2 = intIt1++;
			Assert::AreNotEqual(intIt1, intIt2);
			Assert::AreNotEqual(intIt1, intList.begin());
			Assert::AreEqual(intIt2, intList.begin());
			//End Integer test

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*> pointerList;
			SList<int32_t*>::Iterator pointerIt1;

			//Check for null increment exception
			auto pointerNullIncrement = [&pointerIt1] {pointerIt1++; };
			Assert::ExpectException<runtime_error>(pointerNullIncrement);

			//Check for iterator at end exception
			pointerIt1 = pointerList.pushFront(test);
			Assert::ExpectException<runtime_error>(pointerNullIncrement);

			//Check for functionality of post-increment operator.
			pointerList.pushBack(test + 1);
			SList<int32_t*>::Iterator pointerIt2 = pointerIt1++;
			Assert::AreNotEqual(pointerIt1, pointerIt2);
			Assert::AreNotEqual(pointerIt1, pointerList.begin());
			Assert::AreEqual(pointerIt2, pointerList.begin());
			delete test;
			//End Pointer test.

			//Foo test
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIt1;

			//Check for null increment exception
			auto fooNullIncrement = [&fooIt1] {fooIt1++; };
			Assert::ExpectException<runtime_error>(fooNullIncrement);

			//Check for iterator at end exception
			fooIt1 = fooList.pushFront(Foo(a));
			Assert::ExpectException<runtime_error>(fooNullIncrement);

			//Check for functionality of pre-increment operator.
			fooList.pushBack(Foo(b));
			SList<Foo>::Iterator fooIt2 = fooIt1++;
			Assert::AreNotEqual(fooIt1, fooIt2);
			Assert::AreNotEqual(fooIt1, fooList.begin());
			Assert::AreEqual(fooIt2, fooList.begin());
			//End Foo test
		}

		TEST_METHOD(dereferenceOperatorTest)
		{
			//Integer
			int32_t a = 10;
			SList<int32_t>::Iterator intIt;

			//Test with uninitialized Iterator.
			auto intDereference = [&intIt] {*intIt; };
			Assert::ExpectException<runtime_error>(intDereference);

			//Test functionality of dereference operator.
			SList<int32_t> intList;
			intIt = intList.pushFront(a);
			Assert::AreEqual(*intIt, a);
			//End Integer Test

			//Pointer
			int32_t* test = new int32_t;
			SList<int32_t*>::Iterator pointerIt;

			//Test with uninitialized Iterator.
			auto pointerDereference = [&pointerIt] {*pointerIt; };
			Assert::ExpectException<runtime_error>(pointerDereference);

			//Test functionality of dereference operator.
			SList<int32_t*> pointerList;
			pointerIt = pointerList.pushFront(test);
			Assert::AreEqual(*pointerIt, test);
			delete test;
			//End Pointer test.

			//Foo Test
			SList<Foo>::Iterator fooIt;

			//Test with uninitialized Iterator.
			auto fooDereference = [&fooIt] {*fooIt; };
			Assert::ExpectException<runtime_error>(fooDereference);

			//Test functionality of dereference operator.
			SList<Foo> fooList;
			fooIt = fooList.pushFront(Foo(a));
			Assert::AreEqual(*fooIt, Foo(a));
			//End Foo test.
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListIteratorTest::sStartMemState;
}