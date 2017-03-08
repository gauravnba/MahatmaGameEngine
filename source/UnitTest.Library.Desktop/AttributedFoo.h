#pragma once

#include "Attributed.h"
#include "glm.hpp"
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

		void fixUpDatums();

		void initializeMembers();

		template <typename T>
		void appendAnInternalAttribute(const std::string& name, const T& value, std::uint32_t numElements = 1)
		{
			appendInternalAttribute(name, value, numElements);
		};

		/**
		* Destructor of this class
		*/
		virtual ~AttributedFoo();

	private:
		static const std::uint32_t numElements = 1;

		std::int32_t mIntAttribute[numElements];
		float mFloatAttribute[numElements];
		glm::vec4 mVectorAttribute[numElements];
		glm::mat4x4 mMatrixAttribute[numElements];
		std::string mStringAttribute[numElements];
		Scope mScope;
	};
}