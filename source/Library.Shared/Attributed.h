#pragma once

#include "Scope.h"
#include "HashMap.h"
#include "Datum.h"
#include <string>
#include <cstdint>

namespace MahatmaGameEngine
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		typedef std::pair<uint64_t, Vector<std::string>> PrescribedAttributesPair;

		Attributed();

		~Attributed();

		Attributed(const Attributed& obj);

		Attributed(Attributed&& obj);

		Attributed& operator=(const Attributed& obj);

		Attributed& operator=(Attributed&& obj);

		bool isAttribute(const std::string& name);

		bool isPrescribedAttribute(const std::string& name);

		bool isAuxiliaryAttribute(const std::string& name);

		Datum& appendAuxiliaryAttribute(const std::string& name);

	protected:
		Datum& appendInternalAttribute(const std::string& name);

		template <typename T>
		Datum& appendExternalAttribute(const std::string& name, T* attribute, std::uint32_t numberOfElements = 1);

		static HashMap<std::uint64_t, Vector<std::string>> mPrescribedAttributes;
		uint32_t mAuxiliaryBegin;
	};
}

#include "Attributed.inl"