#include "pch.h"

#include "CppUnitTest.h"

#include "FooProduct.h"
#include "BarProduct.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace std;
	using namespace glm;
	//This Class tests all the methods in the Datum class
	TEST_CLASS(FactoryTests)
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

		TEST_METHOD(createTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			RTTI* fooProduct = fooFactory.create();
			Assert::IsTrue(fooProduct->is("FooProduct"));
			delete fooProduct;

			//Non-RTTI
			BarProductFactory barFactory;
			BarProduct* barProduct = static_cast<BarProduct*>(barFactory.create());
			barProduct->setProductValue(21);
			Assert::AreEqual(barProduct->getProductValue(), 21);
			delete barProduct;
		}

		TEST_METHOD(classNameTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			Assert::AreEqual(string("FooProduct"),fooFactory.className());

			//Non-RTTI
			BarProductFactory barFactory;
			Assert::AreEqual(string("BarProduct"), barFactory.className());
		}

		TEST_METHOD(factoryFindTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			Factory<RTTI>* fooFactoryFind = Factory<RTTI>::find("FooProduct");
			Assert::IsTrue(fooFactoryFind == &fooFactory);
			Factory<RTTI>* fooFactoryNotFound = Factory<RTTI>::find("NotFooProduct");
			Assert::IsNull(fooFactoryNotFound);

			//Non-RTTI
			BarProductFactory barFactory;
			Factory<BarProductAbstract>* barFactoryFind = Factory<BarProductAbstract>::find("BarProduct");
			Assert::IsTrue(barFactoryFind == &barFactory);
			Factory<BarProductAbstract>* barFactoryNotFound = Factory<BarProductAbstract>::find("NotBarProduct");
			Assert::IsNull(barFactoryNotFound);
		}

		TEST_METHOD(factoryStaticCreateTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			FooProduct* fooProduct = static_cast<FooProduct*>(Factory<RTTI>::create("FooProduct"));
			fooProduct->setProductValue(21);
			Assert::AreEqual(fooProduct->getProductValue(), 21);
			delete fooProduct;

			//Non-RTTI
			BarProductFactory barFactory;
			BarProduct* barProduct = static_cast<BarProduct*>(Factory<BarProductAbstract>::create("BarProduct"));
			barProduct->setProductValue(24);
			Assert::AreEqual(barProduct->getProductValue(), 24);
			delete barProduct;
		}

		TEST_METHOD(factoryBeginTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			FooProductFactory* fooFactoryBegin = static_cast<FooProductFactory*>((Factory<RTTI>::begin())->second);
			Assert::IsTrue(fooFactoryBegin == &fooFactory);

			//Non-RTTI
			BarProductFactory barFactory;
			BarProductFactory* barFactoryBegin = static_cast<BarProductFactory*>((Factory<BarProductAbstract>::begin())->second);
			Assert::IsTrue(barFactoryBegin == &barFactory);
		}

		TEST_METHOD(factoryEndTest)
		{
			//RTTI
			FooProductFactory fooFactory;
			HashMap<string, Factory<RTTI>*>::Iterator fooFactoryEnd = Factory<RTTI>::end();
			HashMap<string, Factory<RTTI>*>::Iterator fooFactoryBegin = Factory<RTTI>::begin();
			Assert::IsTrue((++fooFactoryBegin) == fooFactoryEnd);

			//Non-RTTI
			BarProductFactory barFactory;
			HashMap<string, Factory<BarProductAbstract>*>::Iterator barFactoryBegin = Factory<BarProductAbstract>::begin();
			HashMap<string, Factory<BarProductAbstract>*>::Iterator barFactoryEnd = Factory<BarProductAbstract>::end();
			Assert::IsTrue(++barFactoryBegin == barFactoryEnd);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FactoryTests::sStartMemState;
}