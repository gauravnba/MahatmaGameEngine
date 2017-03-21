#include "pch.h"

#include "Datum.h"
#include "Scope.h"
#include "gtx/string_cast.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MahatmaGameEngine;

namespace UnitTestLibraryDesktop
{
	using namespace glm;
	using namespace std;
	//This Class tests all the methods in the Datum class
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

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum = scope;
			Datum tableDatum1 = tableDatum;
			Assert::IsTrue(tableDatum == tableDatum1);

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

			//RTTI
			RTTI* rtti = new Foo;
			Datum RTTIDatum1;
			RTTIDatum1.set(rtti);
			Datum RTTIDatum2 = RTTIDatum1;
			Assert::IsTrue(RTTIDatum2 == RTTIDatum1);
			delete rtti;
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

			//Table
			Datum tableDatum;
			tableDatum.setType(DatumType::TABLE);
			tableDatum.setSize(4);
			Assert::AreEqual(4U, tableDatum.size());
			Assert::AreEqual(4U, tableDatum.capacity());
			tableDatum.setSize(1);
			Assert::AreEqual(1U, tableDatum.size());
			Assert::AreEqual(4U, tableDatum.capacity());

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
			RTTI* rtti = new Foo;

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
			auto vecSetException = [&vecDatum, &mA] {vecDatum.set(mA, 0); };
			Assert::ExpectException<runtime_error>(vecSetException);

			//Matrix
			Datum matDatum;
			matDatum.set(mA, 0);
			matDatum.set(mB, 2);
			Assert::AreEqual(matDatum.size(), 3U);
			Assert::AreEqual(matDatum.get<mat4x4>(), mA);
			Assert::AreEqual(matDatum.get<mat4x4>(2), mB);
			auto matSetException = [&matDatum, &vA] {matDatum.set(vA, 0); };
			Assert::ExpectException<runtime_error>(matSetException);

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum.set(scope);
			Assert::AreEqual(tableDatum.size(), 1U);
			Assert::IsTrue(tableDatum.get<Scope*>() == &scope);
			auto tableSetException = [&tableDatum, &rtti] {tableDatum.set(rtti); };
			Assert::ExpectException<runtime_error>(tableSetException);

			//String
			Datum stringDatum;
			stringDatum.set(sA, 0);
			stringDatum.set(sB, 2);
			Assert::AreEqual(stringDatum.size(), 3U);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			Assert::AreEqual(stringDatum.get<string>(2), sB);
			auto stringSetException = [&intDatum, &sA] {intDatum.set(sA, 0); };
			Assert::ExpectException<runtime_error>(stringSetException);

			//RTTI
			Datum rttiDatum;
			rttiDatum.set(rtti);
			Assert::AreEqual(rttiDatum.size(), 1U);
			Assert::IsTrue(rttiDatum.get<RTTI*>() == rtti);
			auto rttiSetException = [&rttiDatum, &scope] {rttiDatum.set(scope); };
			Assert::ExpectException<runtime_error>(rttiSetException);
			delete rtti;
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
			auto intGetTypeException = [&intDatum] {intDatum.get<float>(); };
			Assert::ExpectException<exception>(intGetTypeException);

			//Float
			Datum floatDatum;
			floatDatum.set(fA, 0);
			floatDatum.set(fB, 2);
			Assert::AreEqual(floatDatum.size(), 3U);
			Assert::AreEqual(floatDatum.get<float>(), fA);
			Assert::AreEqual(floatDatum.get<float>(2U), fB);
			auto floatGetException = [&floatDatum] {floatDatum.get<float>(4); };
			Assert::ExpectException<exception>(floatGetException);
			auto floatGetTypeException = [&floatDatum] {floatDatum.get<vec4>(); };
			Assert::ExpectException<exception>(floatGetTypeException);

			//Vector
			Datum vecDatum;
			vecDatum.set(vA, 0);
			vecDatum.set(vB, 2);
			Assert::AreEqual(vecDatum.size(), 3U);
			Assert::AreEqual(vecDatum.get<vec4>(), vA);
			Assert::AreEqual(vecDatum.get<vec4>(2U), vB);
			auto vecGetException = [&vecDatum] {vecDatum.get<vec4>(4); };
			Assert::ExpectException<exception>(vecGetException);
			auto vecGetTypeException = [&vecDatum] {vecDatum.get<mat4x4>(); };
			Assert::ExpectException<exception>(vecGetTypeException);

			//Matrix
			Datum matDatum;
			matDatum.set(mA, 0);
			matDatum.set(mB, 2);
			Assert::AreEqual(matDatum.size(), 3U);
			Assert::AreEqual(matDatum.get<mat4x4>(), mA);
			Assert::AreEqual(matDatum.get<mat4x4>(2), mB);
			auto matGetException = [&matDatum] {matDatum.get<mat4x4>(4); };
			Assert::ExpectException<exception>(matGetException);
			auto matGetTypeException = [&matDatum] {matDatum.get<Scope*>(); };
			Assert::ExpectException<exception>(matGetTypeException);

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum = scope;
			Assert::IsTrue(tableDatum.get<Scope*>() == &scope);
			auto tableGetException = [&tableDatum] {tableDatum.get<Scope*>(1); };
			Assert::ExpectException<exception>(tableGetException);
			auto tableGetTypeException = [&tableDatum] {tableDatum.get<string>(); };
			Assert::ExpectException<exception>(tableGetTypeException);

			//String
			Datum stringDatum;
			stringDatum.set(sA, 0);
			stringDatum.set(sB, 2);
			Assert::AreEqual(stringDatum.size(), 3U);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			Assert::AreEqual(stringDatum.get<string>(2), sB);
			auto stringGetException = [&stringDatum] {stringDatum.get<string>(4); };
			Assert::ExpectException<exception>(stringGetException);
			auto stringGetTypeException = [&stringDatum] {stringDatum.get<RTTI*>(); };
			Assert::ExpectException<exception>(stringGetTypeException);

			//RTTI
			RTTI* rtti1 = new Foo;
			RTTI* rtti2 = new Foo;
			Datum rttiDatum;
			rttiDatum.set(rtti1);
			rttiDatum.set(rtti2, 1);
			Datum rttiDatum1 = rttiDatum;
			Assert::AreEqual(rttiDatum1.size(), 2U);
			Assert::IsTrue(rttiDatum.get<RTTI*>() == rtti1);
			Assert::IsTrue(rttiDatum1.get<RTTI*>(1) == rtti2);
			auto rttiGetException = [&rttiDatum1] {rttiDatum1.get<RTTI*>(4); };
			Assert::ExpectException<exception>(rttiGetException);
			auto rttiGetTypeException = [&rttiDatum1] {rttiDatum1.get<int32_t>(); };
			Assert::ExpectException<exception>(rttiGetTypeException);

			delete rtti1;
			delete rtti2;
		}

		TEST_METHOD(datumConstGetTest)
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

			//Integer
			Datum intDatum;
			intDatum.set(iA, 0);
			intDatum.set(iB, 2);
			const Datum intDatum1 = intDatum;
			Assert::AreEqual(intDatum1.size(), 3U);
			Assert::AreEqual(intDatum1.get<int32_t>(), iA);
			Assert::AreEqual(intDatum1.get<int32_t>(2U), iB);
			auto intGetException = [&intDatum1] {intDatum1.get<int32_t>(4); };
			Assert::ExpectException<exception>(intGetException);
			auto intGetTypeException = [&intDatum1] {intDatum1.get<float>(); };
			Assert::ExpectException<exception>(intGetTypeException);

			//Float
			Datum floatDatum;
			floatDatum.set(fA, 0);
			floatDatum.set(fB, 2);
			const Datum floatDatum1 = floatDatum;
			Assert::AreEqual(floatDatum1.size(), 3U);
			Assert::AreEqual(floatDatum1.get<float>(), fA);
			Assert::AreEqual(floatDatum1.get<float>(2U), fB);
			auto floatGetException = [&floatDatum1] {floatDatum1.get<float>(4); };
			Assert::ExpectException<exception>(floatGetException);
			auto floatGetTypeException = [&floatDatum1] {floatDatum1.get<vec4>(); };
			Assert::ExpectException<exception>(floatGetTypeException);

			//Vector
			Datum vecDatum;
			vecDatum.set(vA, 0);
			vecDatum.set(vB, 2);
			const Datum vecDatum1 = vecDatum;
			Assert::AreEqual(vecDatum1.size(), 3U);
			Assert::AreEqual(vecDatum1.get<vec4>(), vA);
			Assert::AreEqual(vecDatum1.get<vec4>(2U), vB);
			auto vecGetException = [&vecDatum1] {vecDatum1.get<vec4>(4); };
			Assert::ExpectException<exception>(vecGetException);
			auto vecGetTypeException = [&vecDatum1] {vecDatum1.get<mat4x4>(); };
			Assert::ExpectException<exception>(vecGetTypeException);

			//Matrix
			Datum matDatum;
			matDatum.set(mA, 0);
			matDatum.set(mB, 2);
			const Datum matDatum1 = matDatum;
			Assert::AreEqual(matDatum1.size(), 3U);
			Assert::AreEqual(matDatum1.get<mat4x4>(), mA);
			Assert::AreEqual(matDatum1.get<mat4x4>(2), mB);
			auto matGetException = [&matDatum1] {matDatum1.get<mat4x4>(4); };
			Assert::ExpectException<exception>(matGetException);
			auto matGetTypeException = [&matDatum1] {matDatum1.get<Scope*>(); };
			Assert::ExpectException<exception>(matGetTypeException);

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum = scope;
			const Datum tableDatum1 = tableDatum;
			Assert::IsTrue(tableDatum1.get<Scope*>() == &scope);
			auto tableGetException = [&tableDatum1] {tableDatum1.get<Scope*>(1); };
			Assert::ExpectException<exception>(tableGetException);
			auto tableGetTypeException = [&tableDatum1] {tableDatum1.get<string>(); };
			Assert::ExpectException<exception>(tableGetTypeException);

			//String
			Datum stringDatum;
			stringDatum.set(sA, 0);
			stringDatum.set(sB, 2);
			const Datum stringDatum1 = stringDatum;
			Assert::AreEqual(stringDatum1.size(), 3U);
			Assert::AreEqual(stringDatum1.get<string>(), sA);
			Assert::AreEqual(stringDatum1.get<string>(2), sB);
			auto stringGetException = [&stringDatum1] {stringDatum1.get<string>(4); };
			Assert::ExpectException<exception>(stringGetException);
			auto stringGetTypeException = [&stringDatum1] {stringDatum1.get<RTTI*>(); };
			Assert::ExpectException<exception>(stringGetTypeException);

			//RTTI
			RTTI* rtti1 = new Foo;
			RTTI* rtti2 = new Foo;
			Datum rttiDatum;
			rttiDatum.set(rtti1);
			rttiDatum.set(rtti2, 1);
			const Datum rttiDatum1 = rttiDatum;
			Assert::AreEqual(rttiDatum1.size(), 2U);
			Assert::IsTrue(rttiDatum.get<RTTI*>() == rtti1); 
			Assert::IsTrue(rttiDatum1.get<RTTI*>(1) == rtti2);
			auto rttiGetException = [&rttiDatum1] {rttiDatum1.get<RTTI*>(4); };
			Assert::ExpectException<exception>(rttiGetException);
			auto rttiGetTypeException = [&rttiDatum1] {rttiDatum1.get<int32_t>(); };
			Assert::ExpectException<exception>(rttiGetTypeException);

			delete rtti1;
			delete rtti2;
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

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum = scope;
			Datum tableDatum1;
			tableDatum1 = tableDatum;
			Assert::IsTrue(tableDatum1 == tableDatum);

			//String
			Datum stringDatum;
			stringDatum = sA;
			stringDatum.set(sB, 1U);
			Datum stringDatum1;
			stringDatum1 = sB;
			stringDatum1 = stringDatum;
			Assert::IsTrue(stringDatum == stringDatum1);

			//RTTI
			RTTI* rtti1 = new Foo;
			RTTI* rtti2 = new Foo;
			Datum rttiDatum;
			rttiDatum = rtti1;
			rttiDatum.set(rtti2, 1);
			Datum rttiDatum1;
			rttiDatum1 = rtti2;
			rttiDatum1 = rttiDatum;
			Assert::IsTrue(rttiDatum1 == rttiDatum);

			delete rtti1;
			delete rtti2;
		}

		TEST_METHOD(moveSemanticsTest)
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
			Datum intDatum1 = move(intDatum);
			Assert::AreEqual(intDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(intDatum.size(), 0U);
			Assert::AreEqual(intDatum1.size(), 2U);
			Assert::AreEqual(intDatum1.get<int32_t>(1U), iB);
			auto datumMoveException = [&intDatum] {intDatum.get<int32_t>(); };
			Assert::ExpectException<exception>(datumMoveException);

			intDatum1.set(iA, 2U);
			intDatum = move(intDatum1);
			Assert::AreEqual(intDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(intDatum1.size(), 0U);
			Assert::AreEqual(intDatum.size(), 3U);
			Assert::AreEqual(intDatum.get<int32_t>(2U), iA);

			//Float
			Datum floatDatum;
			floatDatum = fA;
			floatDatum.set(fB, 1U);
			Datum floatDatum1 = move(floatDatum);
			Assert::AreEqual(floatDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(floatDatum.size(), 0U);
			Assert::AreEqual(floatDatum1.size(), 2U);
			Assert::AreEqual(floatDatum1.get<float>(1U), fB);

			floatDatum1.set(fA, 2U);
			floatDatum = move(floatDatum1);
			Assert::AreEqual(floatDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(floatDatum1.size(), 0U);
			Assert::AreEqual(floatDatum.size(), 3U);
			Assert::AreEqual(floatDatum.get<float>(2U), fA);

			//Vector
			Datum vecDatum;
			vecDatum = vA;
			vecDatum.set(vB, 1U);
			Datum vecDatum1 = move(vecDatum);
			Assert::AreEqual(vecDatum.size(), 0U);
			Assert::AreEqual(vecDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(vecDatum1.size(), 2U);
			Assert::AreEqual(vecDatum1.get<vec4>(1U), vB);

			vecDatum1.set(vA, 2U);
			vecDatum = move(vecDatum1);
			Assert::AreEqual(vecDatum1.size(), 0U);
			Assert::AreEqual(vecDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(vecDatum.size(), 3U);
			Assert::AreEqual(vecDatum.get<vec4>(2U), vA);

			//Matrix
			Datum matDatum;
			matDatum = mA;
			matDatum.set(mB, 1U);
			Datum matDatum1 = move(matDatum);
			Assert::AreEqual(matDatum.size(), 0U);
			Assert::AreEqual(matDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(matDatum1.size(), 2U);
			Assert::AreEqual(matDatum1.get<mat4x4>(1U), mB);

			matDatum1.set(mC, 2U);
			matDatum = move(matDatum1);
			Assert::AreEqual(matDatum1.size(), 0U);
			Assert::AreEqual(matDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(matDatum.size(), 3U);
			Assert::AreEqual(matDatum.get<mat4x4>(2U), mC);

			//Table
			Datum tableDatum;
			Scope scope;
			scope.append(string("test"));
			tableDatum = scope;
			Datum tableDatum1 = move(tableDatum);
			Assert::AreEqual(tableDatum.size(), 0U);
			Assert::AreEqual(tableDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(tableDatum1.size(), 1U);
			Assert::IsTrue(tableDatum1.get<Scope*>() == &scope);

			tableDatum = move(tableDatum1);
			Assert::AreEqual(tableDatum1.size(), 0U);
			Assert::AreEqual(tableDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(tableDatum.size(), 1U);
			Assert::IsTrue(tableDatum.get<Scope*>() == &scope);

			//String
			Datum stringDatum;
			stringDatum = sA;
			stringDatum.set(sB, 1U);
			Datum stringDatum1 = move(stringDatum);
			Assert::AreEqual(stringDatum.size(), 0U);
			Assert::AreEqual(stringDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(stringDatum1.size(), 2U);
			Assert::AreEqual(stringDatum1.get<string>(1U), sB);

			stringDatum1.set(sA, 2U);
			stringDatum = move(stringDatum1);
			Assert::AreEqual(stringDatum1.size(), 0U);
			Assert::AreEqual(stringDatum1.type(), DatumType::UNKNOWN);
			Assert::AreEqual(stringDatum.size(), 3U);
			Assert::AreEqual(stringDatum.get<string>(2U), sA);

			//RTTI
			RTTI* rtti1 = new Foo;
			RTTI* rtti2 = new Foo;

			Datum rttiDatum;
			rttiDatum = rtti1;
			rttiDatum.set(rtti2, 1);
			Datum rttiDatum1 = move(rttiDatum);
			Assert::AreEqual(rttiDatum.size(), 0U);
			Assert::AreEqual(rttiDatum.type(), DatumType::UNKNOWN);
			Assert::AreEqual(rttiDatum1.size(), 2U);
			Assert::IsTrue(rttiDatum1.get<RTTI*>(1U) == rtti2);

			rttiDatum1.set(rtti1, 2U);
			rttiDatum = move(rttiDatum1);
			rttiDatum1.~Datum();
			Assert::AreEqual(rttiDatum.size(), 3U);
			Assert::IsTrue(rttiDatum.get<RTTI*>(2U) == rtti1);

			delete rtti1;
			delete rtti2;
		}

		TEST_METHOD(setStorageTest)
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
			uint32_t numElements = 2;
			int32_t* intArray = static_cast<int32_t*>(malloc(numElements * sizeof(int32_t)));
			intArray[0] = iA;
			intArray[1] = iB;
			Datum intDatum;
			intDatum.setStorage(intArray, numElements);
			Assert::AreEqual(intDatum.type(), DatumType::INTEGER);
			auto externalIntSetRangeException = [&intDatum, &iA] {intDatum.set(iA, 4); };
			Assert::ExpectException<out_of_range>(externalIntSetRangeException);
			Assert::AreEqual(intDatum.get<int32_t>(), iA);
			Assert::AreEqual(intDatum.get<int32_t>(1), iB);
			free(intArray);

			//Float
			float* floatArray = static_cast<float*>(malloc(numElements * sizeof(float)));
			floatArray[0] = fA;
			floatArray[1] = fB;
			Datum floatDatum;
			floatDatum.setStorage(floatArray, numElements);
			Assert::AreEqual(floatDatum.type(), DatumType::FLOAT);
			auto externalFloatSetRangeException = [&floatDatum, &fA] {floatDatum.set(fA, 4); };
			Assert::ExpectException<out_of_range>(externalFloatSetRangeException);
			Assert::AreEqual(floatDatum.get<float>(), fA);
			Assert::AreEqual(floatDatum.get<float>(1), fB);
			free(floatArray);

			//Vector
			vec4* vecArray = static_cast<vec4*>(malloc(numElements * sizeof(vec4)));
			vecArray[0] = vA;
			vecArray[1] = vB;
			Datum vecDatum;
			vecDatum.setStorage(vecArray, numElements);
			Assert::AreEqual(vecDatum.type(), DatumType::VECTOR);
			auto externalVectorSetRangeException = [&vecDatum, &vA] {vecDatum.set(vA, 4); };
			Assert::ExpectException<out_of_range>(externalVectorSetRangeException);
			Assert::AreEqual(vecDatum.get<vec4>(), vA);
			Assert::AreEqual(vecDatum.get<vec4>(1), vB);
			free(vecArray);

			//Matrix
			mat4x4* matrixArray = static_cast<mat4x4*>(malloc(numElements * sizeof(mat4x4)));
			matrixArray[0] = mA;
			matrixArray[1] = mB;
			Datum matrixDatum;
			matrixDatum.setStorage(matrixArray, numElements);
			Assert::AreEqual(matrixDatum.type(), DatumType::MATRIX);
			auto externalMatrixSetRangeException = [&matrixDatum, &mA] {matrixDatum.set(mA, 4); };
			Assert::ExpectException<out_of_range>(externalMatrixSetRangeException);
			Assert::AreEqual(matrixDatum.get<mat4x4>(), mA);
			Assert::AreEqual(matrixDatum.get<mat4x4>(1), mB);
			free(matrixArray);

			//String
			string* stringArray = static_cast<string*>(malloc(numElements * sizeof(string)));
			new(&stringArray[0]) string(sA);
			new(&stringArray[1]) string(sB);
			Datum stringDatum;
			stringDatum.setStorage(stringArray, numElements);
			Assert::AreEqual(stringDatum.type(), DatumType::STRING);
			auto externalStringSetRangeException = [&stringDatum, &sA] {stringDatum.set(sA, 4); };
			Assert::ExpectException<out_of_range>(externalStringSetRangeException);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			Assert::AreEqual(stringDatum.get<string>(1), sB);
			stringArray[0].~string();
			stringArray[1].~string();
			free(stringArray);

			//RTTI
			RTTI* rttiArray[2];
			rttiArray[0] = new Foo;
			rttiArray[1] = new Foo;

			Datum rttiDatum;
			rttiDatum.setStorage(rttiArray, numElements);
			Assert::AreEqual(rttiDatum.type(), DatumType::RTTI_POINTER);
			auto externalRTTISetRangeException = [&rttiDatum, &rttiArray] {rttiDatum.set(rttiArray[0], 4); };
			Assert::ExpectException<out_of_range>(externalRTTISetRangeException);
			Assert::IsTrue(rttiDatum.get<RTTI*>() == rttiArray[0]);
			Assert::IsTrue(rttiDatum.get<RTTI*>(1) == rttiArray[1]);

			delete rttiArray[1];
			delete rttiArray[0];
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

			//Table
			Datum tableDatum;
			Scope scope;
			tableDatum = scope;
			Datum tableDatum1 = tableDatum;
			Assert::IsFalse(tableDatum != tableDatum1);

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

			//RTTI
			RTTI* rtti1 = new Foo;
			RTTI* rtti2 = new Foo;

			Datum rttiDatum;
			rttiDatum = rtti1;
			rttiDatum.set(rtti2, 1U);
			Datum rttiDatum1;
			rttiDatum1 = rtti2;
			Assert::IsTrue(rttiDatum1 != rtti1);
			Assert::IsTrue(rttiDatum != rttiDatum1);
			rttiDatum1 = rttiDatum;
			Assert::IsFalse(rttiDatum != rttiDatum1);

			delete rtti1;
			delete rtti2;
		}

		TEST_METHOD(setFromStringTest)
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
			auto intTypeMissingException = [&intDatum, &iA] {intDatum.setFromString(to_string(iA)); };
			Assert::ExpectException<runtime_error>(intTypeMissingException);
			intDatum.setType(DatumType::INTEGER);
			intDatum.setFromString(to_string(iA));
			Assert::AreEqual(intDatum.get<int32_t>(), iA);
			intDatum.setFromString(to_string(iB), 1);
			Assert::AreEqual(intDatum.get<int32_t>(1), iB);

			//Float
			Datum floatDatum;
			floatDatum.setType(DatumType::FLOAT);
			floatDatum.setFromString(to_string(fA));
			Assert::AreEqual(floatDatum.get<float>(), fA);
			floatDatum.setFromString(to_string(fB), 1);
			Assert::AreEqual(floatDatum.get<float>(1), fB);

			//Vector
			Datum vectorDatum;
			vectorDatum.setType(DatumType::VECTOR);
			vectorDatum.setFromString(to_string(vA));
			Assert::AreEqual(vectorDatum.get<vec4>(), vA);
			vectorDatum.setFromString(to_string(vB), 1);
			Assert::AreEqual(vectorDatum.get<vec4>(1), vB);

			//Matrix
			Datum matrixDatum;
			matrixDatum.setType(DatumType::MATRIX);
			matrixDatum.setFromString(to_string(mA));
			Assert::AreEqual(matrixDatum.get<mat4x4>(), mA);
			matrixDatum.setFromString(to_string(mB), 1);
			Assert::AreEqual(matrixDatum.get<mat4x4>(1), mB);

			//String
			Datum stringDatum;
			stringDatum.setType(DatumType::STRING);
			stringDatum.setFromString(sA);
			Assert::AreEqual(stringDatum.get<string>(), sA);
			stringDatum.setFromString(sB, 1);
			Assert::AreEqual(stringDatum.get<string>(1), sB);
		}

		TEST_METHOD(toStringTest)
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
			auto intDataTypeException = [&intDatum] {intDatum.toString(); };
			Assert::ExpectException<runtime_error>(intDataTypeException);
			intDatum.set(iA);
			intDatum.set(iB, 1);
			Assert::AreEqual(intDatum.toString(), to_string(iA));
			Assert::AreEqual(intDatum.toString(1), to_string(iB));

			//Float
			Datum floatDatum;
			auto floatDataTypeException = [&floatDatum] {floatDatum.toString(); };
			Assert::ExpectException<runtime_error>(floatDataTypeException);
			floatDatum.set(fA);
			floatDatum.set(fB, 1);
			Assert::AreEqual(floatDatum.toString(), to_string(fA));
			Assert::AreEqual(floatDatum.toString(1), to_string(fB));

			//Vector
			Datum vectorDatum;
			auto vecDataTypeException = [&vectorDatum] {vectorDatum.toString(); };
			Assert::ExpectException<runtime_error>(vecDataTypeException);
			vectorDatum.set(vA);
			vectorDatum.set(vB, 1);
			Assert::AreEqual(vectorDatum.toString(), to_string(vA));
			Assert::AreEqual(vectorDatum.toString(1), to_string(vB));

			//Matrix
			Datum matrixDatum;
			auto matrixDataTypeException = [&matrixDatum] {matrixDatum.toString(); };
			Assert::ExpectException<runtime_error>(matrixDataTypeException);
			matrixDatum.set(mA);
			matrixDatum.set(mB, 1);
			Assert::AreEqual(matrixDatum.toString(), to_string(mA));
			Assert::AreEqual(matrixDatum.toString(1), to_string(mB));

			//Table
			Datum scopeDatum;
			Scope scope;
			scopeDatum.set(scope);
			Assert::AreEqual(scopeDatum.toString(), string("Scope"));

			//String
			Datum stringDatum;
			auto stringDataTypeException = [&stringDatum] {stringDatum.toString(); };
			Assert::ExpectException<runtime_error>(stringDataTypeException);
			stringDatum.set(sA);
			stringDatum.set(sB, 1);
			Assert::AreEqual(stringDatum.toString(), sA);
			Assert::AreEqual(stringDatum.toString(1), sB);

			//RTTI
			RTTI* rtti = new Foo;
			Datum rttiDatum;
			rttiDatum = rtti;
			Assert::AreEqual(rttiDatum.toString(), string("RTTI"));
			delete rtti;
		}

		TEST_METHOD(datumRemoveTest)
		{
			Datum tableDatum;
			Scope scope1;
			Scope scope2;
			Scope scope3;
			tableDatum.set(scope1);
			tableDatum.set(scope2, 1);
			tableDatum.set(scope3, 2);
			Assert::IsTrue(tableDatum.removeTable(&scope1));
			Assert::AreEqual(tableDatum.size(), 2U);
			Assert::IsTrue(*(tableDatum.get<Scope*>()) == scope2);
			auto scopeRemoved = [&tableDatum]{ tableDatum.get<Scope*>(2); };
			Assert::ExpectException<exception>(scopeRemoved);
		}

		TEST_METHOD(tableEqualityTest)
		{
			SCOPE_TEST_DATA_DECLARATION

			//POPULATE_TEST_SCOPE

			//UNREFERENCED_PARAMETER(childTable);

			Scope testScope;													
			Datum* integer = &(testScope.append(intType));					
			integer->set(iA);												
			Datum* floatingPoint = &(testScope.append(floatType));			
			floatingPoint->set(fA);											
			floatingPoint->set(fB);											
			Datum* vector4 = &(testScope.append(vecType));					
			vector4->set(vA);												
			vector4->set(vB);												
			Datum* matrix4x4 = &(testScope.append(matrixType));				
			matrix4x4->set(mA);												
			matrix4x4->set(mB);												
			Datum* stringDatum = &(testScope.append(stringType));			
			stringDatum->set(sA);											
			stringDatum->set(sB);											
			Scope* childTable = &(testScope.appendScope(tableType));

			Scope newScope = testScope;
			Datum newScopeDatum;
			newScopeDatum.set(newScope);
			Datum testScopeDatum = newScopeDatum;

			Assert::IsTrue(newScopeDatum == newScope);
			Assert::IsFalse(newScopeDatum != newScope);
			Assert::IsFalse(newScopeDatum == childTable);
			Assert::IsTrue(newScopeDatum != childTable);
			Assert::IsTrue(newScopeDatum == testScopeDatum);

			Datum scope1;
			scope1.set(newScope);

			Scope inequalScope;
			inequalScope.append(intType);
			inequalScope.append(floatType);
			inequalScope.append(vecType);
			inequalScope.append(matrixType);
			inequalScope.append(stringType);
			inequalScope.appendScope(tableType);
			Datum inequalScopeDatum;
			inequalScopeDatum.set(inequalScope);

			Assert::IsFalse(inequalScopeDatum == testScopeDatum);
		}

		TEST_METHOD(removeTableTest)
		{
			Scope scope;
			Scope& scopeChild1 = scope.appendScope("Child");
			Scope& scopeChild2 = scope.appendScope("Child");
			Scope randomScope;
			Assert::IsFalse(&scopeChild2 == &scopeChild1);
			Assert::IsTrue(scope["Child"].removeTable(&scopeChild2));
			Assert::IsTrue(scope["Child"].get<Scope*>() == &scopeChild1);
			Assert::IsFalse(scope["Child"].removeTable(&randomScope));
			delete &scopeChild2;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DatumTest::sStartMemState;
}