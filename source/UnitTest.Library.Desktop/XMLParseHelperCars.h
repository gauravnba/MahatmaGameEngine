#pragma once
#include "XMLParseHelper.h"
#include <string>
#include "Vector.h"
#include "Hashmap.h"

namespace UnitTestLibraryDesktop
{
	class XMLParseHelperCars : public MahatmaGameEngine::XMLParseHelper
	{
	public:
		XMLParseHelperCars() = default;

		XMLParseHelperCars(const XMLParseHelperCars& obj) = delete;

		XMLParseHelperCars(XMLParseHelperCars&& cars) = delete;

		virtual ~XMLParseHelperCars() = default;

		virtual void initialize() override;

		virtual XMLParseHelperCars* clone() override;

		virtual bool startElementHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& name, MahatmaGameEngine::HashMap<std::string, std::string>& attributesMap) override;

		virtual bool endElementHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& name) override;

		virtual void charDataHandler(MahatmaGameEngine::XMLParseMaster::SharedData* sharedData, const std::string& value) override;

	private:
		MahatmaGameEngine::Vector<std::string> mListOfTags;
		std::string mCurrentElement;
	};
}