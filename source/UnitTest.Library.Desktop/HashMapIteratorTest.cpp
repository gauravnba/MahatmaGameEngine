#include "pch.h"

#include "HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the Vector Iterator class using an integer vector, a pointer vector and
	//a vector of a custom class Foo.
	TEST_CLASS(HashMapIteratorTest)
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
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			HashMap<int32_t, int32_t>::Iterator intMapIt = intMap.begin();
			Assert::AreEqual(intMapIt, intMap.begin());

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			HashMap<char*, int32_t>::Iterator charMapIt = charMap.begin();
			Assert::AreEqual(charMapIt, charMap.begin());

			//String
			string stringKey1 = "testString";
			HashMap<string, int32_t> stringMap;
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			HashMap<string, int32_t>::Iterator stringMapIt = stringMap.begin();
			Assert::AreEqual(stringMapIt, stringMap.begin());

			//Foo
			Foo fooKey1 = Foo(intKey1);
			HashMap<Foo, int32_t> fooMap;
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			HashMap<Foo, int32_t>::Iterator fooMapIt = fooMap.begin();
			Assert::AreEqual(fooMapIt, fooMap.begin());
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			//Integer
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			HashMap<int32_t, int32_t>::Iterator intMapIt;
			intMapIt = intMap.begin();
			Assert::AreEqual(intMapIt, intMap.begin());

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			HashMap<char*, int32_t>::Iterator charMapIt;
			charMapIt = charMap.begin();
			Assert::AreEqual(charMapIt, charMap.begin());

			//String
			string stringKey1 = "testString";
			HashMap<string, int32_t> stringMap;
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			HashMap<string, int32_t>::Iterator stringMapIt;
			stringMapIt = stringMap.begin();
			Assert::AreEqual(stringMapIt, stringMap.begin());

			//Foo
			Foo fooKey1 = Foo(intKey1);
			HashMap<Foo, int32_t> fooMap;
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			HashMap<Foo, int32_t>::Iterator fooMapIt;
			fooMapIt = fooMap.begin();
			Assert::AreEqual(fooMapIt, fooMap.begin());
		}

		TEST_METHOD(incrementOperatorTest)
		{
			//Integer
			int32_t intKey1 = 10;
			int32_t intKey2 = 20;
			HashMap<int32_t, int32_t>::Iterator intMapIt;
			auto intMapIncrement = [&intMapIt] {intMapIt++; };
			Assert::ExpectException<std::exception>(intMapIncrement);
			HashMap<int32_t, int32_t> intMap;

			intMapIt = intMap.begin();
			Assert::ExpectException<std::exception>(intMapIncrement);

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey2, 200));
			intMapIt = intMap.begin();
			HashMap<int32_t, int32_t>::Iterator intMapIt2 = intMapIt++;
			Assert::AreNotEqual(intMapIt, intMapIt2);
			Assert::AreEqual(intMapIt2, intMap.begin());

			//Char*
			char* charKey1 = "test";
			char* charKey2 = "test1";
			char* charKey3 = "testThree";
			HashMap<char*, int32_t>::Iterator charMapIt;
			auto charMapIncrement = [&charMapIt] {charMapIt++; };
			Assert::ExpectException<std::exception>(charMapIncrement);

			HashMap<char*, int32_t> charMap;
			charMapIt = charMap.begin();
			Assert::ExpectException<std::exception>(charMapIncrement);
			
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey2, 200));
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey3, 300));
			charMapIt = charMap.begin();
			HashMap<char*, int32_t>::Iterator charMapIt2 = charMapIt++;
			HashMap<char*, int32_t>::Iterator charMapIt3 = charMapIt++;
			Assert::AreNotEqual(charMapIt3, charMapIt);
			Assert::AreNotEqual(charMapIt, charMapIt2);
			Assert::AreEqual(charMapIt2, charMap.begin());

			//String
			string stringKey1 = "testString";
			string stringKey2 = "testString1";
			HashMap<string, int32_t>::Iterator stringMapIt;
			auto stringMapIncrement = [&stringMapIt] {stringMapIt++; };
			Assert::ExpectException<std::exception>(stringMapIncrement);

			HashMap<string, int32_t> stringMap;
			stringMapIt = stringMap.begin();
			Assert::ExpectException<std::exception>(stringMapIncrement);

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey2, 200));
			stringMapIt = stringMap.begin();
			HashMap<string, int32_t>::Iterator stringMapIt1 = stringMapIt++;
			Assert::AreNotEqual(stringMapIt1, stringMapIt);
			Assert::AreEqual(stringMapIt1, stringMap.begin());

			//Foo
			Foo fooKey1 = Foo(intKey1);
			Foo fooKey2 = Foo(intKey2);
			HashMap<Foo, int32_t>::Iterator fooMapIt;
			auto fooMapIncrement = [&fooMapIt] {fooMapIt++; };
			Assert::ExpectException<std::exception>(fooMapIncrement);

			HashMap<Foo, int32_t> fooMap;
			fooMapIt = fooMap.begin();
			Assert::ExpectException<std::exception>(fooMapIncrement);

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey2, 200));
			fooMapIt = fooMap.begin();
			HashMap<Foo, int32_t>::Iterator fooMapIt1 = fooMapIt++;
			Assert::AreNotEqual(fooMapIt, fooMapIt1);
			Assert::AreEqual(fooMapIt1, fooMap.begin());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapIteratorTest::sStartMemState;
}