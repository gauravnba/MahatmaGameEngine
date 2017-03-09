#pragma once

#include "Attributed.h"
#include "glm.hpp"
#include "Foo.h"
#include <cstdint>

namespace UnitTestLibraryDesktop
{
	class AttributedFoo : public MahatmaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)
	public:
		/**
		* Adds all the member variables as prescribed attributes to its Scope.
		*/
		AttributedFoo();

		AttributedFoo(const AttributedFoo& obj);

		AttributedFoo(AttributedFoo&& obj);

		AttributedFoo& operator=(const AttributedFoo& obj);

		AttributedFoo& operator=(AttributedFoo&& obj);

		/**
		* Destructor of this class
		*/
		virtual ~AttributedFoo();

		/**
		* Method created to expose Attributed::addNestedScope for testing
		*/
		MahatmaGameEngine::Datum& appendExistingScope(const std::string& name, MahatmaGameEngine::Scope& scope);

	private:
		void fixUpDatums();

		void initializeMembers();

		static const std::uint32_t numElements = 1;

		std::int32_t mIntAttribute[numElements];
		float mFloatAttribute[numElements];
		glm::vec4 mVectorAttribute[numElements];
		glm::mat4x4 mMatrixAttribute[numElements];
		std::string mStringAttribute[numElements];
		Scope* mScope;
		RTTI* mRTTIAttribute[numElements];
		Foo mFooExternal;

		std::int32_t mInternalInt;
		float mInternalFloat;
		glm::vec4 mInternalVector;
		glm::mat4x4 mInternalMatrix;
		std::string mInternalString;
		RTTI* mInternalRTTI;
		Foo mFooInternal;
	};
}