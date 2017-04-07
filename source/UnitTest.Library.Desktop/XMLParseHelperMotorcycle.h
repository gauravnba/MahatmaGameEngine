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

		virtual bool startElementHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& name, MahatmaGameEngine::HashMap<std::string, std::string>& attributesMap) override;

		virtual bool endElementHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& name) override;

		virtual void charDataHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& buffer) override;

		void addTagToHandle(const std::string& tag);

	private:
		MahatmaGameEngine::Vector<std::string> mListOfTags;
		std::string mCurrentElement;
	};
}