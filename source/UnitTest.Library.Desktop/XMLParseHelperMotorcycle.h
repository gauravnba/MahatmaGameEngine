#pragma once
#include "XMLParseHelper.h"
#include <string>
#include "Vector.h"
#include "Hashmap.h"

namespace UnitTestLibraryDesktop
{
	class XMLParseHelperMotorcycle : public MahatmaGameEngine::XMLParseHelper
	{
	public:
		XMLParseHelperMotorcycle() = default;

		XMLParseHelperMotorcycle(const XMLParseHelperMotorcycle& obj) = delete;

		XMLParseHelperMotorcycle(XMLParseHelperMotorcycle&& cars) = delete;

		virtual ~XMLParseHelperMotorcycle() = default;

		virtual void initialize() override;

		virtual XMLParseHelperMotorcycle* clone() override;

		virtual bool startElementHandler(const std::string& name, MahatmaGameEngine::HashMap<std::string, std::string>& attributesMap) override;

		virtual bool endElementHandler(const std::string& name) override;

		virtual void charDataHandler(const char* buffer, std::uint32_t length) override;

		void addTagToHandle(const std::string& tag);

	private:
		MahatmaGameEngine::HashMap<std::string, std::string> mFoundAttributes;
		MahatmaGameEngine::Vector<std::string> mListOfTags;
		std::string mCurrentElement;
	};
}