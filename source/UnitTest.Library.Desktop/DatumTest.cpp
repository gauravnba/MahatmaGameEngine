#include "pch.h"

#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace glm;
	using namespace std;
	//This Class tests all the methods in the Vector Iterator class using an integer vector, a pointer vector and
	//a vector of a custom class Foo.
	TEST_CLASS(DatumTest)
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
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			//Integer
			Datum intDatum;
			intDatum.set(iA);
			intDatum.set(iB, 1U);
			Datum intDatum1 = intDatum;
			Assert::IsTrue(intDatum == intDatum1);

			//Float
			Datum floatDatum;
			floatDatum.set(fA);
			floatDatum.set(fB, 1U);
			Datum floatDatum1 = floatDatum;
			Assert::IsTrue(floatDatum == floatDatum1);

			//Vector
			Datum vecDatum;
			vecDatum.set(vA);
			vecDatum.set(vB, 1U);
			Datum vecDatum1 = vecDatum;
			Assert::IsTrue(vecDatum == vecDatum1);

			//Matrix
			Datum matDatum;
			matDatum.set(mA);
			matDatum.set(mB, 1U);
			Datum matDatum1 = matDatum;
			Assert::IsTrue(matDatum == matDatum1);

			//String
			Datum stringDatum;
			stringDatum.set(sA);
			stringDatum.set(sB, 1U);
			Datum stringDatum1 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum1);
		}
		
		TEST_METHOD(setTypeTest)
		{
			Datum testDatum;
			testDatum.setType(DatumType::INTEGER);
			Assert::AreEqual(DatumType::INTEGER, testDatum.type());
			auto datumSetTypeException = [&testDatum] {testDatum.setType(DatumType::FLOAT); };
			Assert::ExpectException<runtime_error>(datumSetTypeException);
		}

		TEST_METHOD(setSizeTest)
		{
			//Integer
			Datum intDatum;
			auto setSizeException = [&intDatum] {intDatum.setSize(1); };
			Assert::ExpectException<runtime_error>(setSizeException);
			intDatum.setType(DatumType::INTEGER);
			intDatum.setSize(4);
			Assert::AreEqual(4U, intDatum.size());
			Assert::AreEqual(4U, intDatum.capacity());
			intDatum.setSize(2);
			Assert::AreEqual(2U, intDatum.size());
			Assert::AreEqual(4U, intDatum.capacity());

			//Floating type
			Datum floatDatum;
			floatDatum.setType(DatumType::FLOAT);
			floatDatum.setSize(4);
			Assert::AreEqual(4U, floatDatum.size());
			Assert::AreEqual(4U, floatDatum.capacity());
			floatDatum.setSize(2);
			Assert::AreEqual(2U, floatDatum.size());
			Assert::AreEqual(4U, floatDatum.capacity());

			//Vector type
			Datum vectorDatum;
			vectorDatum.setType(DatumType::VECTOR);
			vectorDatum.setSize(4);
			Assert::AreEqual(4U, vectorDatum.size());
			Assert::AreEqual(4U, vectorDatum.capacity());
			vectorDatum.setSize(2);
			Assert::AreEqual(2U, vectorDatum.size());
			Assert::AreEqual(4U, vectorDatum.capacity());

			//Matrix
			Datum matrixDatum;
			matrixDatum.setType(DatumType::MATRIX);
			matrixDatum.setSize(4);
			Assert::AreEqual(4U, matrixDatum.size());
			Assert::AreEqual(4U, matrixDatum.capacity());
			matrixDatum.setSize(2);
			Assert::AreEqual(2U, matrixDatum.size());
			Assert::AreEqual(4U, matrixDatum.capacity());

			//String
			Datum stringDatum;
			stringDatum.setType(DatumType::STRING);
			stringDatum.setSize(4);
			Assert::AreEqual(4U, stringDatum.size());
			Assert::AreEqual(4U, stringDatum.capacity());
			stringDatum.setSize(2);
			Assert::AreEqual(2U, stringDatum.size());
			Assert::AreEqual(4U, stringDatum.capacity());
		}

		TEST_METHOD(datumSetTest)
		{
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			//Integer
			Datum intDatum;
			intDatum.set(iA, 0);
			intDatum.set(iB, 2);
			Assert::AreEqual(intDatum.size(), 3U);
			Assert::AreEqual(intDatum.get<int32_t>(), iA);
			Assert::AreEqual(intDatum.get<int32_t>(2U), iB);
			auto floatSetException = [&intDatum, &fA] {intDatum.set(fA, 0); };
			Assert::ExpectException<runtime_error>(floatSetException);

			//Float
			Datum floatDatum;
			floatDatum.set(fA, 0);
			floatDatum.set(fB, 2);
			Assert::AreEqual(floatDatum.size(), 3U);
			Assert::AreEqual(floatDatum.get<float>(), fA);
			Assert::AreEqual(floatDatum.get<float>(2U), fB);
			auto intSetException = [&floatDatum, &iA] {floatDatum.set(iA, 0); };
			Assert::ExpectException<runtime_error>(intSetException);

			//Vector
			Datum vecDatum;
			vecDatum.set(vA, 0);
			vecDatum.set(vB, 2);
			Assert::AreEqual(vecDatum.size(), 3U);
			Assert::AreEqual(vecDatum.get<vec4>(), vA);
			Assert::AreEqual(vecDatum.get<vec4>(2U), vB);
			auto matSetException = [&vecDatum, &mA] {vecDatum.set(mA, 0); };
			Assert::ExpectException<runtime_error>(matSetException);

			//Matrix
			Datum matDatum;
			matDatum.set(mA, 0);
			matDatum.set(mB, 2);
			Assert::AreEqual(matDatum.size(), 3U);
			Assert::AreEqual(matDatum.get<mat4x4>(), mA);
			Assert::AreEqual(matDatum.get<mat4x4>(2), mB);
			auto vecSetException = [&matDatum, &vA] {matDatum.set(vA, 0); };
			Assert::ExpectException<runtime_error>(vecSetException);

			//String
			Datum stringDatum;
			stringDatum.set(sA, 0);
			stringDatum.set(sB, 2);
			Assert::AreEqual(stringDatum.size(), 3U);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			Assert::AreEqual(stringDatum.get<string>(2), sB);
			auto stringSetException = [&intDatum, &sA] {intDatum.set(sA, 0); };
			Assert::ExpectException<runtime_error>(stringSetException);
		}

		TEST_METHOD(datumGetTest)
		{
			//Integer
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			Datum intDatum;
			intDatum.set(iA, 0);
			intDatum.set(iB, 2);
			Assert::AreEqual(intDatum.size(), 3U);
			Assert::AreEqual(intDatum.get<int32_t>(), iA);
			Assert::AreEqual(intDatum.get<int32_t>(2U), iB);
			auto intGetException = [&intDatum] {intDatum.get<int32_t>(4); };
			Assert::ExpectException<exception>(intGetException);

			//Float
			Datum floatDatum;
			floatDatum.set(fA, 0);
			floatDatum.set(fB, 2);
			Assert::AreEqual(floatDatum.size(), 3U);
			Assert::AreEqual(floatDatum.get<float>(), fA);
			Assert::AreEqual(floatDatum.get<float>(2U), fB);
			auto floatGetException = [&floatDatum] {floatDatum.get<float>(4); };
			Assert::ExpectException<exception>(floatGetException);

			//Vector
			Datum vecDatum;
			vecDatum.set(vA, 0);
			vecDatum.set(vB, 2);
			Assert::AreEqual(vecDatum.size(), 3U);
			Assert::AreEqual(vecDatum.get<vec4>(), vA);
			Assert::AreEqual(vecDatum.get<vec4>(2U), vB);
			auto vecGetException = [&vecDatum] {vecDatum.get<vec4>(4); };
			Assert::ExpectException<exception>(vecGetException);

			//Matrix
			Datum matDatum;
			matDatum.set(mA, 0);
			matDatum.set(mB, 2);
			Assert::AreEqual(matDatum.size(), 3U);
			Assert::AreEqual(matDatum.get<mat4x4>(), mA);
			Assert::AreEqual(matDatum.get<mat4x4>(2), mB);
			auto matGetException = [&matDatum] {matDatum.get<mat4x4>(4); };
			Assert::ExpectException<exception>(matGetException);

			//String
			Datum stringDatum;
			stringDatum.set(sA, 0);
			stringDatum.set(sB, 2);
			Assert::AreEqual(stringDatum.size(), 3U);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			Assert::AreEqual(stringDatum.get<string>(2), sB);
			auto stringGetException = [&stringDatum] {stringDatum.get<string>(4); };
			Assert::ExpectException<exception>(stringGetException);
		}

		TEST_METHOD(assignmentOperatorTest)
		{
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			//Integer
			Datum intDatum;
			intDatum = iA;
			intDatum.set(iB, 1U);
			Datum intDatum1;
			intDatum1 = iB;
			intDatum1 = intDatum;
			Assert::IsTrue(intDatum == intDatum1);

			//Float
			Datum floatDatum;
			floatDatum = fA;
			floatDatum.set(fB, 1U);
			Datum floatDatum1;
			floatDatum1 = fB;
			floatDatum1 = floatDatum;
			Assert::IsTrue(floatDatum == floatDatum1);

			//Vector
			Datum vecDatum;
			vecDatum = vA;
			vecDatum.set(vB, 1U);
			Datum vecDatum1;
			vecDatum1 = vB;
			vecDatum1 = vecDatum;
			Assert::IsTrue(vecDatum == vecDatum1);

			//Matrix
			Datum matDatum;
			matDatum = mA;
			matDatum.set(mB, 1U);
			Datum matDatum1;
			matDatum1 = mB;
			matDatum1 = matDatum;
			Assert::IsTrue(matDatum == matDatum1);

			//String
			Datum stringDatum;
			stringDatum = sA;
			stringDatum.set(sB, 1U);
			Datum stringDatum1;
			stringDatum1 = sB;
			stringDatum1 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum1);
		}

		TEST_METHOD(setStorageTest)
		{

		}

		TEST_METHOD(equalityOperatorTest)
		{
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			//Integer
			Datum intDatum;
			intDatum = iA;
			intDatum.set(iB, 1U);
			Datum intDatum1;
			intDatum1 = iB;
			Assert::IsTrue(intDatum1 == iB);
			Assert::IsFalse(intDatum == intDatum1);
			intDatum1 = intDatum;
			Assert::IsTrue(intDatum == intDatum1);

			//Float
			Datum floatDatum;
			floatDatum = fA;
			floatDatum.set(fB, 1U);
			Datum floatDatum1;
			floatDatum1 = fB;
			Assert::IsTrue(floatDatum1 == fB);
			Assert::IsFalse(floatDatum == floatDatum1);
			floatDatum1 = floatDatum;
			Assert::IsTrue(floatDatum == floatDatum1);

			//Vector
			Datum vecDatum;
			vecDatum = vA;
			vecDatum.set(vB, 1U);
			Datum vecDatum1;
			vecDatum1 = vB;
			Assert::IsTrue(vecDatum1 == vB);
			Assert::IsFalse(vecDatum1 == vecDatum);
			vecDatum1 = vecDatum;
			Assert::IsTrue(vecDatum == vecDatum1);

			//Matrix
			Datum matDatum;
			matDatum = mA;
			matDatum.set(mB, 1U);
			Datum matDatum1;
			matDatum1 = mB;
			Assert::IsTrue(matDatum1 == mB);
			Assert::IsFalse(matDatum == matDatum1);
			matDatum1 = matDatum;
			Assert::IsTrue(matDatum == matDatum1);

			//String
			Datum stringDatum;
			stringDatum = sA;
			stringDatum.set(sB, 1U);
			Datum stringDatum1;
			stringDatum1 = sB;
			Assert::IsTrue(stringDatum1 == sB);
			Assert::IsFalse(stringDatum == stringDatum1);
			stringDatum1 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum1);
		}

		TEST_METHOD(inequalityOperatorTest)
		{
			int32_t iA = 10;
			int32_t iB = 20;
			float fA = 10.5f;
			float fB = 20.5f;
			float fC = 30.5f;
			float fD = 40.5f;
			vec4 vA = vec4(vec3(fA), fB);
			vec4 vB = vec4(vec3(fB), fA);
			vec4 vC = vec4(vec3(fC), fD);
			vec4 vD = vec4(vec3(fD), fC);
			mat4x4 mA = mat4x4(vA, vB, vC, vD);
			mat4x4 mB = mat4x4(vB, vC, vD, vA);
			mat4x4 mC = mat4x4(vC, vD, vA, vB);
			mat4x4 mD = mat4x4(vD, vA, vB, vC);
			string sA = "test";
			string sB = "anotherTest";

			//Integer
			Datum intDatum;
			intDatum = iA;
			intDatum.set(iB, 1U);
			Datum intDatum1;
			intDatum1 = iB;
			Assert::IsTrue(intDatum1 != iA);
			Assert::IsTrue(intDatum != intDatum1);
			intDatum1 = intDatum;
			Assert::IsFalse(intDatum != intDatum1);

			//Float
			Datum floatDatum;
			floatDatum = fA;
			floatDatum.set(fB, 1U);
			Datum floatDatum1;
			floatDatum1 = fB;
			Assert::IsTrue(floatDatum1 != fA);
			Assert::IsTrue(floatDatum != floatDatum1);
			floatDatum1 = floatDatum;
			Assert::IsFalse(floatDatum != floatDatum1);

			//Vector
			Datum vecDatum;
			vecDatum = vA;
			vecDatum.set(vB, 1U);
			Datum vecDatum1;
			vecDatum1 = vB;
			Assert::IsTrue(vecDatum1 != vA);
			Assert::IsTrue(vecDatum1 != vecDatum);
			vecDatum1 = vecDatum;
			Assert::IsFalse(vecDatum != vecDatum1);

			//Matrix
			Datum matDatum;
			matDatum = mA;
			matDatum.set(mB, 1U);
			Datum matDatum1;
			matDatum1 = mB;
			Assert::IsTrue(matDatum1 != mA);
			Assert::IsTrue(matDatum != matDatum1);
			matDatum1 = matDatum;
			Assert::IsFalse(matDatum != matDatum1);

			//String
			Datum stringDatum;
			stringDatum = sA;
			stringDatum.set(sB, 1U);
			Datum stringDatum1;
			stringDatum1 = sB;
			Assert::IsTrue(stringDatum1 != sA);
			Assert::IsTrue(stringDatum != stringDatum1);
			stringDatum1 = stringDatum;
			Assert::IsFalse(stringDatum != stringDatum1);
		}

		TEST_METHOD(setFromString)
		{

		}

		TEST_METHOD(toStringTest)
		{

		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}