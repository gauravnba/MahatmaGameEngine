#pragma once

#include "Attributed.h"
#include "AttributedFoo.h"
#include "glm.hpp"
#include "Foo.h"
#include <cstdint>

namespace UnitTestLibraryDesktop
{
	class AttributedBar : public AttributedFoo
	{
		RTTI_DECLARATIONS(Attributed, AttributedFoo)
	public:
		/**
		* Adds all the member variables as prescribed attributes to its Scope.
		*/
		AttributedBar();

		AttributedBar(const AttributedBar& obj);

		AttributedBar(AttributedBar&& obj);

		AttributedBar& operator=(const AttributedBar& obj);

		AttributedBar& operator=(AttributedBar&& obj);

		virtual ~AttributedBar();

	private:
		void fixUpDatums();

		void initializeMembers();

		static const std::uint32_t numElements = 1;

		std::int32_t mDerivedExtInteger[numElements];
		glm::mat4x4 mDerivedExtMatrix[numElements];
		Scope* mDerivedScope;

		std::int32_t mDerivedIntInteger;
		glm::mat4x4 mDerivedIntMatrix;
	};
}