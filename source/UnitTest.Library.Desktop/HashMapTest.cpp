#include "pch.h"

#include "FooDefaultHash.h"
#include "DefaultHash.h"
#include "HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	//This Class tests all the methods in the Vector Iterator class using an integer vector, a pointer vector and
	//a vector of a custom class Foo.
	TEST_CLASS(HashMapTest)
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

		TEST_METHOD(hashFunctorTest)
		{
			//HashFunctor for Integer
			int32_t a = 10;
			int32_t b = 10;
			int32_t c = 20;
			DefaultHash<int32_t> intHashFunctor;
			std::uint32_t intHash1 = intHashFunctor(a);
			std::uint32_t intHash2 = intHashFunctor(b);
			std::uint32_t intHash3 = intHashFunctor(c);
			Assert::AreEqual(intHash1, intHash2);
			Assert::AreNotEqual(intHash1, intHash3);

			//HashFunctor for integer pointer.
			int32_t* pA = &a;
			int32_t* pB = &a;
			int32_t* pC = &b;
			DefaultHash<int32_t*> pointerHashFunctor;
			std::uint32_t pointerHash1 = pointerHashFunctor(pA);
			std::uint32_t pointerHash2 = pointerHashFunctor(pB);
			std::uint32_t pointerHash3 = pointerHashFunctor(pC);
			Assert::AreEqual(pointerHash1, pointerHash2);
			Assert::AreNotEqual(pointerHash1, pointerHash3);

			//HashFunctor for char*
			char* cString1 = "test";
			char* cString2 = "test";
			char* cString3 = "test1";
			DefaultHash<char*> pCharHashFunctor;
			std::uint32_t pCharHash1 = pCharHashFunctor(cString1);
			std::uint32_t pCharHash2 = pCharHashFunctor(cString2);
			std::uint32_t pCharHash3 = pCharHashFunctor(cString3);
			Assert::AreEqual(pCharHash1, pCharHash2);
			Assert::AreNotEqual(pCharHash1, pCharHash3);

			//HashFunctor for std::string
			std::string string1 = "stringTest";
			std::string string2 = "stringTest";
			std::string string3 = "stringTest1";
			DefaultHash<std::string> stringHashFunctor;
			std::uint32_t stringHash1 = stringHashFunctor(string1);
			std::uint32_t stringHash2 = stringHashFunctor(string2);
			std::uint32_t stringHash3 = stringHashFunctor(string3);
			Assert::AreEqual(stringHash1, stringHash2);
			Assert::AreNotEqual(stringHash1, stringHash3);

			//Foo
			Foo foo1 = Foo(10);
			Foo foo2 = Foo(10);
			Foo foo3 = Foo(20);
			DefaultHash<Foo> fooHashFunctor;
			std::uint32_t fooHash1 = fooHashFunctor(foo1);
			std::uint32_t fooHash2 = fooHashFunctor(foo2);
			std::uint32_t fooHash3 = fooHashFunctor(foo3);
			Assert::AreEqual(fooHash1, fooHash2);
			Assert::AreNotEqual(fooHash1, fooHash3);
		}

		TEST_METHOD(copyConstructorTest)
		{
			//Integer
			int32_t intKey1 = 10;
			int32_t intKey2 = 20;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey2, 200));

			HashMap<int32_t, int32_t> intMap1 = intMap;
			Assert::AreEqual(intMap[intKey1], intMap1[intKey1]);

			//Char*
			char* charKey1 = "test";
			char* charKey2 = "test1";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey2, 200));

			HashMap<char*, int32_t> charMap1 = charMap;
			Assert::AreEqual(charMap[charKey2], charMap1[charKey2]);

			//String type
			string stringKey1 = string("testString");
			string stringKey2 = string("testString1");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey2, 200));

			HashMap<std::string, int32_t> stringMap1 = stringMap;
			Assert::AreEqual(stringMap[stringKey1], stringMap1[stringKey1]);

			//Foo
			Foo fooKey1 = Foo(10);
			Foo fooKey2 = Foo(20);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey2, 200));

			HashMap<Foo, int32_t> fooMap1 = fooMap;
			Assert::AreEqual(fooMap[fooKey1], fooMap1[fooKey1]);
		}

		TEST_METHOD(hashmapInsertTest)
		{
			//Integer
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			Assert::AreEqual(intMap.find(intKey1), intMap.begin());
			Assert::AreEqual(intMap[intKey1], 100);

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			Assert::AreEqual(charMap.find(charKey1), charMap.begin());
			Assert::AreEqual(charMap[charKey1], 100);

			//String type
			string stringKey1 = string("testString");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			Assert::AreEqual(stringMap.find(stringKey1), stringMap.begin());
			Assert::AreEqual(stringMap[stringKey1], 100);

			//Foo
			Foo fooKey1 = Foo(10);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			Assert::AreEqual(fooMap.find(fooKey1), fooMap.begin());
			Assert::AreEqual(fooMap[fooKey1], 100);
		}

		TEST_METHOD(hashmapSizeTest)
		{
			//Integer
			int32_t intKey1 = 10;
			int32_t intKey2 = 20;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.size(), 0U);

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey2, 200));
			Assert::AreEqual(intMap.size(), 2U);

			//Char*
			char* charKey1 = "test";
			char* charKey2 = "test1";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.size(), 0U);

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey2, 100));

			const HashMap<char*, int32_t> charMap1 = charMap;
			Assert::AreEqual(charMap.size(), 2U);

			//String type
			string stringKey1 = string("testString");
			string stringKey2 = string("testString1");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.size(), 0U);

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey2, 200));

			Assert::AreEqual(stringMap.size(), 2U);

			//Foo
			Foo fooKey1 = Foo(10);
			Foo fooKey2 = Foo(20);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.size(), 0U);

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey2, 200));

			Assert::AreEqual(fooMap.size(), 2U);
		}

		TEST_METHOD(containsKeyTest)
		{
			//Integer
			int32_t intKey1 = 10;
			int32_t intKey2 = 20;
			HashMap<int32_t, int32_t> intMap;

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			Assert::IsTrue(intMap.containsKey(intKey1));
			Assert::IsFalse(intMap.containsKey(intKey2));

			//Char*
			char* charKey1 = "test";
			char* charKey2 = "test1";
			HashMap<char*, int32_t> charMap;

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			Assert::IsTrue(charMap.containsKey(charKey1));
			Assert::IsFalse(charMap.containsKey(charKey2));

			//String type
			string stringKey1 = string("testString");
			string stringKey2 = string("testString1");
			HashMap<string, int32_t> stringMap;

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			Assert::IsTrue(stringMap.containsKey(stringKey1));
			Assert::IsFalse(stringMap.containsKey(stringKey2));

			//Foo
			Foo fooKey1 = Foo(10);
			Foo fooKey2 = Foo(20);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			Assert::IsTrue(fooMap.containsKey(fooKey1));
			Assert::IsFalse(fooMap.containsKey(fooKey2));
		}

		TEST_METHOD(hashmapFindTest)
		{
			//Integer
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			const HashMap<int32_t, int32_t> intMap1 = intMap;
			Assert::AreEqual(intMap1.begin(), intMap1.find(intKey1));

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			const HashMap<char*, int32_t> charMap1 = charMap;
			Assert::AreEqual(charMap1.begin(), charMap1.find(charKey1));

			//String type
			string stringKey1 = string("testString");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			const HashMap<std::string, int32_t> stringMap1 = stringMap;
			Assert::AreEqual(stringMap1.begin(), stringMap1.find(stringKey1));

			//Foo
			Foo fooKey1 = Foo(10);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			const HashMap<Foo, int32_t> fooMap1 = fooMap;
			Assert::AreEqual(fooMap1.begin(), fooMap1.find(fooKey1));
		}

		TEST_METHOD(indexOperatorTest)
		{
			//Integer
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			const HashMap<int32_t, int32_t> intMap1 = intMap;
			Assert::AreEqual(intMap1[intKey1], 100);

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			const HashMap<char*, int32_t> charMap1 = charMap;
			Assert::AreEqual(charMap1[charKey1], 100);

			//String type
			string stringKey1 = string("testString");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			const HashMap<std::string, int32_t> stringMap1 = stringMap;
			Assert::AreEqual(stringMap1[stringKey1], 100);

			//Foo
			Foo fooKey1 = Foo(10);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			const HashMap<Foo, int32_t> fooMap1 = fooMap;
			Assert::AreEqual(fooMap1[fooKey1], 100);
		}

		TEST_METHOD(hashmapRemoveTest)
		{
			//Integer
			int32_t intKey1 = 10;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));

			Assert::AreNotEqual(intMap.begin(), intMap.end());

			intMap.remove(intKey1);
			Assert::AreEqual(intMap.begin(), intMap.end());

			//Char*
			char* charKey1 = "test";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));

			Assert::AreNotEqual(charMap.begin(), charMap.end());

			charMap.remove(charKey1);
			Assert::AreEqual(charMap.begin(), charMap.end());

			//String type
			string stringKey1 = string("testString");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));

			Assert::AreNotEqual(stringMap.begin(), stringMap.end());

			stringMap.remove(stringKey1);
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			//Foo
			Foo fooKey1 = Foo(10);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));

			Assert::AreNotEqual(fooMap.begin(), fooMap.end());

			fooMap.remove(fooKey1);
			Assert::AreEqual(fooMap.begin(), fooMap.end());
		}

		TEST_METHOD(hashmapClearTest)
		{
			//Integer
			int32_t intKey1 = 10;
			int32_t intKey2 = 20;
			HashMap<int32_t, int32_t> intMap;
			Assert::AreEqual(intMap.begin(), intMap.end());

			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey1, 100));
			intMap.insert(HashMap<int32_t, int32_t>::PairType(intKey2, 100));
			Assert::AreNotEqual(intMap.begin(), intMap.end());

			intMap.clear();
			Assert::AreEqual(intMap.begin(), intMap.end());

			//Char*
			char* charKey1 = "test";
			char* charKey2 = "test1";
			HashMap<char*, int32_t> charMap;
			Assert::AreEqual(charMap.begin(), charMap.end());

			charMap.insert(HashMap<char*, int32_t>::PairType(charKey1, 100));
			charMap.insert(HashMap<char*, int32_t>::PairType(charKey2, 100));

			Assert::AreNotEqual(charMap.begin(), charMap.end());

			charMap.clear();
			Assert::AreEqual(charMap.begin(), charMap.end());

			//String type
			string stringKey1 = string("testString");
			string stringKey2 = string("testString1");
			HashMap<string, int32_t> stringMap;
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey1, 100));
			stringMap.insert(HashMap<string, int32_t>::PairType(stringKey2, 100));

			Assert::AreNotEqual(stringMap.begin(), stringMap.end());

			stringMap.clear();
			Assert::AreEqual(stringMap.begin(), stringMap.end());

			//Foo
			Foo fooKey1 = Foo(10);
			Foo fooKey2 = Foo(10);
			HashMap<Foo, int32_t> fooMap;
			Assert::AreEqual(fooMap.begin(), fooMap.end());

			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey1, 100));
			fooMap.insert(HashMap<Foo, int32_t>::PairType(fooKey2, 100));

			Assert::AreNotEqual(fooMap.begin(), fooMap.end());

			fooMap.clear();
			Assert::AreEqual(fooMap.begin(), fooMap.end());
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}